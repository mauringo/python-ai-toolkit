#pragma once
#include "datalayer.h"
#include "metadata_generated.h"
#include "metadata_helper.h"
#include "comm/datalayer/program_task_generated.h"
#include "comm/datalayer/program_task_all_generated.h"
#include "comm/datalayer/address.h"
#include "comm/datalayer/inherit_recursive_mutex.h"
#include <random>
#include <map>

namespace comm {
namespace datalayer {

class Task
{
public:
  Task(const std::string& id, const Variant* parameters)
    : m_id(id)
    , m_parameters(*parameters)
    , m_taskState(ProgramTaskState_pending)
  {
    setState(ProgramTaskState_pending, 0);
  }

  virtual ~Task() = default;

  void setState(comm::datalayer::ProgramTaskState state, uint32_t progress, const std::string& progressInfo = "")
  {
    flatbuffers::FlatBufferBuilder builder;
    auto id = builder.CreateString(m_id);
    auto info = builder.CreateString(progressInfo);
    builder.Finish(comm::datalayer::CreateProgramTask(builder, id, state, progress, 0, info));
    m_state.copyFlatbuffers(builder);
    m_taskState = state;
  }

  void setError(uint32_t mainDiagnosisCode, uint32_t detailedDiagnosisCode, const std::string& dynamicDescription = "")
  {
    m_taskState = ProgramTaskState_failed;
    auto task = UnPackProgramTask(m_state.getData());
    flatbuffers::FlatBufferBuilder builder;
    auto diagnosis = CreateDiagnosisDirect(builder, mainDiagnosisCode, detailedDiagnosisCode, dynamicDescription.c_str(), "datalayer");
    builder.Finish(CreateProgramTaskDirect(builder, task->id.c_str(), m_taskState, 100, diagnosis, nullptr));
    m_state.copyFlatbuffers(builder);

  }

  virtual Variant getState() final
  {
    return m_state;
  };

  virtual ProgramTaskState getTaskState() final
  {
    return m_taskState;
  }

  virtual Variant getParameters() final
  {
    return m_parameters;
  }

protected:
  const std::string m_id;
  Variant m_parameters;
  
private:
  ProgramTaskState m_taskState;
  Variant m_state;
};

class Program : IProviderNode
{
public:
  Program(IProvider* provider, const std::string& baseAddress, const std::string& pathParameterType = "")
    : m_provider(provider)
    , m_pathParameterType(pathParameterType)
    , m_pathType(pathParameterType)
    , m_baseAddress(baseAddress)
  {
    m_provider->registerNode(m_baseAddress, this);
    m_provider->registerNode(m_baseAddress + "/*", this);
    m_provider->registerNode(m_baseAddress + "/*/parameters", this);
    if(m_pathParameterType.rfind(".bfbs") != std::string::npos)
    {
      m_pathType = "types/program/" + m_baseAddress;
      m_provider->registerType("types/program/" + m_baseAddress, pathParameterType);
    }
  };

  virtual ~Program()
  {
    garbageCollection();
    m_provider->unregisterNode(m_baseAddress);
    m_provider->unregisterNode(m_baseAddress + "/*");
    m_provider->unregisterNode(m_baseAddress + "/*/parameters");
    if (m_pathParameterType.rfind(".bfbs") != std::string::npos)
    {
      m_provider->unregisterType("types/program/" + m_baseAddress);
    }
  };

  void setBaseAddressDescription(const std::string& desciprion)
  {
    m_descriptionBaseAddress = desciprion;
  }

  /************************************************************************/
  /* methods to override                                                  */
  /************************************************************************/
  virtual DlResult onCreate(const std::string& id, const Variant* parameters, Task** task) = 0;

  virtual DlResult onRemove(const std::string&)
  {
    return DlResult::DL_OK;
  }

  // Is called before execution of onBrowse(), can e.g. be used for the garbage collection, so that the sub nodes are up-to-date when browsing
  virtual DlResult preOnBrowse()
  {
    return DlResult::DL_OK;
  }

  virtual DlResult garbageCollection()
  {
    std::lock_guard<InheritRecursiveMutex> guard(m_mapMtx);
    for (auto task = m_mapTasks.begin(); task != m_mapTasks.end();)
    {
      auto state = task->second->getTaskState();
      if ((state == ProgramTaskState_done) ||
          (state == ProgramTaskState_failed))
      {
        delete task->second;
        task = m_mapTasks.erase(task);
      }
      else
      {
        task++;
      }
    }
    return DlResult::DL_OK;
  }

  /************************************************************************/
  /* IProviderNode interface                                              */
  /************************************************************************/
  void onCreate(const std::string& address, const comm::datalayer::Variant* parameters, const comm::datalayer::IProviderNode::ResponseCallback& callback) override
  {
    std::lock_guard<InheritRecursiveMutex> guard(m_mapMtx);
    if (address != m_baseAddress)
    {
      callback(DlResult::DL_UNSUPPORTED, nullptr);
      return;
    }
    if (!m_pathType.empty() && (parameters == nullptr))
    {
      callback(DlResult::DL_TYPE_MISMATCH, nullptr);
      return;
    }
    std::string myID;
    for (;;)
    {
      myID = getUuid();
      if (m_mapTasks.find(myID) == m_mapTasks.end())
      {
        break;
      }
    }

    Task* task;
    DlResult result;
    if (nullptr == parameters)
    {
      comm::datalayer::Variant emptyData;
      emptyData.setValue("");
      result = onCreate(myID, &emptyData, &task);
    }
    else
    {
      result = onCreate(myID, parameters, &task);
    }
    
    if (STATUS_FAILED(result))
    {
      callback(result, parameters);
      return;
    }
    
    m_mapTasks[myID] = task;
    Variant createdResource;
    createdResource.setValue(m_baseAddress + "/" + myID);
    callback(DlResult::DL_OK_NO_CONTENT, &createdResource);
  };

  void onRemove(const std::string& address, const ResponseCallback& callback) override
  {
    std::string part = address.substr(m_baseAddress.size());
    if (part.length())
    {
      Address addr(part);
      auto parts = addr.parse();
      if (parts.size() == 1)
      {
        std::lock_guard<InheritRecursiveMutex> guard(m_mapMtx);

        auto myID = address.substr(m_baseAddress.size() + 1);
        auto task = m_mapTasks.find(myID);
        if (task == m_mapTasks.end())
        {
          callback(DlResult::DL_INVALID_ADDRESS, nullptr);
          return;
        }
        auto state = task->second->getTaskState();
        if ((state != ProgramTaskState_done) &&
            (state != ProgramTaskState_failed))
        {
          callback(DlResult::DL_INVALID_OPERATION_MODE, nullptr);
          return;
        }

        auto result = onRemove(myID);

        delete task->second;
        m_mapTasks.erase(task);
        callback(result, nullptr);
      }
    }

    callback(DlResult::DL_UNSUPPORTED, nullptr);
    return;
  };

  void onBrowse(const std::string& address, const ResponseCallback& callback) override
  {
    DlResult dlResult = preOnBrowse();

    std::lock_guard<InheritRecursiveMutex> guard(m_mapMtx);
    if (address == m_baseAddress)
    {
      std::vector<std::string> result;
      result.reserve(m_mapTasks.size());
      for (auto item : m_mapTasks)
      {
        result.push_back(item.first);
      }
      Variant returnValue;
      returnValue.setValue(result);
      callback(dlResult, &returnValue);
      return;
    }
    callback(DlResult::DL_UNSUPPORTED, nullptr);
  };

  void onRead(const std::string& address, const comm::datalayer::Variant* , const ResponseCallback& callback) override
  {
    std::lock_guard<InheritRecursiveMutex> guard(m_mapMtx);
    std::string part = address.substr(m_baseAddress.size());
    if (part.length())
    {
      Address addr(part);
      auto parts = addr.parse();
      // return state of one task
      auto task = m_mapTasks.find(parts[0]);
      if (task == m_mapTasks.end())
      {
        callback(DlResult::DL_INVALID_ADDRESS, nullptr);
        return;
      }
      if (parts.size() == 1)
      {
        auto state = task->second->getState();
        callback(DlResult::DL_OK, &state);
        return;
      }
      if (parts.size() == 2)
      {
        if (parts[1] == "parameters")
        {
          auto parameters = task->second->getParameters();
          callback(DlResult::DL_OK, &parameters);
          return;
        }
      }
      callback(DlResult::DL_INVALID_ADDRESS, nullptr);
    }
    else
    {
      flatbuffers::FlatBufferBuilder builder;
      std::vector<flatbuffers::Offset<ProgramTask>> tasks;
      // return state of all tasks
      for (auto& task : m_mapTasks)
      {
        auto state = task.second->getState();
        auto progTask = UnPackProgramTask(state.getData());
        tasks.push_back(CreateProgramTask(builder, progTask.get()));
      }
      builder.Finish(CreateProgramTaskAllDirect(builder, &tasks));
      Variant states;
      states.copyFlatbuffers(builder);
      callback(DlResult::DL_OK, &states);
    }
  };

  void onWrite(const std::string& , const Variant* , const ResponseCallback& callback) override
  {
    callback(DlResult::DL_UNSUPPORTED, nullptr);
  };

  void onMetadata(const std::string& address, const ResponseCallback& callback) override
  {
    Variant metadata;
    std::string part = address.substr(m_baseAddress.size());
    if (part.length())
    {
      Address addr(part);
      auto parts = addr.parse();
      if (parts.size() == 1)
      { // metadata of task
        MetadataHelper::createMetadata(metadata, NodeClass_Resource, true, false, false, true, true, {{"readType", "types/datalayer/program-task"}}, "Information about task properties (node name, task state, task progress).");
        callback(DlResult::DL_OK, &metadata);
        return;
      }
      if (parts.size() == 2)
      { // subnode of task
        if (parts[1] == "parameters")
        {
          if (m_pathType.empty())
          {
            MetadataHelper::createMetadata(metadata, NodeClass_Variable, true, false, false, false, false, {}, "Properties of the task (empty).");
          }
          else
          {
            MetadataHelper::createMetadata(metadata, NodeClass_Variable, true, false, false, false, false, {{"readType", m_pathType}}, "Properties of the task.");
          }
          
          callback(DlResult::DL_OK, &metadata);
          return;
        }
      }
    }
    else
    {
      if (m_pathType.empty())
      {
        MetadataHelper::createMetadata(metadata, NodeClass_Program, true, false, true, false, true, {{"readType", "types/datalayer/program-task-all"}}, m_descriptionBaseAddress);
      }
      else
      {
        MetadataHelper::createMetadata(metadata, NodeClass_Program, true, false, true, false, true, {
          {"readType", "types/datalayer/program-task-all"},
          {"createType", m_pathType}},
          m_descriptionBaseAddress);
      }

      callback(DlResult::DL_OK, &metadata);
      return;
    }

    callback(DlResult::DL_INVALID_ADDRESS, nullptr);
  };

private:

  std::string getUuid()
  {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    const char* v = "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<int> dist(0, static_cast<int>(strlen(v)-1));

    std::string res;
    for (int i = 0; i < 8; i++)
    {
      res += v[dist(rng)];
    }
    return res;
  }

  std::string m_descriptionBaseAddress = "";

protected:
  InheritRecursiveMutex m_mapMtx;
  std::map<std::string,Task*> m_mapTasks;
  IProvider* m_provider;
  std::string m_pathParameterType;
  std::string m_pathType;
  std::string m_baseAddress;
};

}
}

