#pragma once
#include "datalayer.h"
#include "metadata_helper.h"

namespace comm {
namespace datalayer {

class Method : public IProviderNode
{
public:
  enum class EMethodType
  {
    READ,
    WRITE,
  };

  Method(IProvider* provider, const std::string& address, EMethodType type, const std::string& inType, const std::string outType)
    : m_provider(provider)
    , m_address(address)
    , m_type(type)
    , m_inType(inType)
    , m_outType(outType)
  {
    m_provider->registerNode(m_address, this);
  };

  virtual ~Method()
  {
    m_provider->unregisterNode(m_address);
  };

  virtual void onMethod(const std::string& address, const comm::datalayer::Variant* data, const ResponseCallback& callback) = 0;

  void onCreate(const std::string& , const comm::datalayer::Variant* , const comm::datalayer::IProviderNode::ResponseCallback& callback) override
  {
    callback(DlResult::DL_UNSUPPORTED, nullptr);
  }

  void onRemove(const std::string& , const ResponseCallback& callback) override
  {
    callback(DlResult::DL_UNSUPPORTED, nullptr);
  }

  void onBrowse(const std::string& , const ResponseCallback& callback) override
  {
    callback(DlResult::DL_UNSUPPORTED, nullptr);
  }

  void onRead(const std::string& address, const comm::datalayer::Variant* data, const ResponseCallback& callback) override
  {
    if (m_type != EMethodType::READ)
    {
      callback(DlResult::DL_UNSUPPORTED, nullptr);
      return;
    }
    onMethod(address, data, callback);
  }

  void onWrite(const std::string& address, const Variant* data, const ResponseCallback& callback) override
  {
    if (m_type != EMethodType::WRITE)
    {
      callback(DlResult::DL_UNSUPPORTED, nullptr);
      return;
    }
    onMethod(address, data, callback);
  }

  void onMetadata(const std::string& , const ResponseCallback& callback) override
  {
    Variant metadata;
    std::vector<std::pair<std::string, std::string>> references;
    if (m_inType == m_outType)
    {
      if(m_inType.size())
      {
        references.push_back({((m_type == EMethodType::READ) ? std::string("read") : std::string("write")) + "Type", m_inType});
      }
    }
    else
    {
      if (m_inType.size())
      {
        references.push_back({((m_type == EMethodType::READ) ? std::string("read") : std::string("write")) + "InType", m_inType});
      }
      if (m_outType.size())
      {
        references.push_back({((m_type == EMethodType::READ) ? std::string("read") : std::string("write")) + "OutType", m_outType});
      }
    }

    MetadataHelper::createMetadata(
      metadata, NodeClass_Method,
      m_type == EMethodType::READ, m_type == EMethodType::WRITE, false, false, false,
      references);
    callback(DlResult::DL_OK, &metadata);
  }

protected:
private:
  IProvider* m_provider;
  std::string m_address;
  EMethodType m_type;
  std::string m_inType;
  std::string m_outType;
};

}
}
