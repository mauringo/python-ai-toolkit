#pragma once
#include "datalayer.h"
#include "flatbuffers_celix.h"
#include "flatbuffer_json.h"
#include "persistence_helper.h"
#include "compliance_checker.h"

namespace common {
namespace log {
namespace trace {
  class IRegistration;
}}}

//! Namespace for datalayer
namespace comm {
namespace datalayer {

enum class BindNode { FRONTEND_TCP, BACKEND_TCP, FRONTEND_IPC, BACKEND_IPC, FRONTEND_INPROC, BACKEND_INPROC, IPC_PATH, NO_SAVE };
class Factory;
class Broker;
class RealtimeBroker;
class FlatbufferJson;
class PersistenceHelper;
class ComplianceChecker;
class RTDebug;
class LoadSaveProvider;
class WatchlistProvider;
class ServerSettingsProvider;
namespace remote{
  class C2CMain;
}

//! DatalayerSystem which includes a broker
class DatalayerSystem
{
public:
  DatalayerSystem(std::string ipcPath = "");
  ~DatalayerSystem();

  //! Returns the factory to create clients and provider for the datalayer
  //! @return Factory
  IDataLayerFactory3* factory();

  //! Returns converter between JSON and Variant
  //! @return Converter between JSON and Variant
  IFlatbufferJson* jsonConverter();

  //! Returns persistence helper
  //! @return persistence helper
  PersistenceHelper* persistenceHelper();

  //! Returns compliance checker
  //! @return compliance checker
  ComplianceChecker* complianceChecker();

  //! Returns datalayer c interface
  //! @return datalayer c interface
  DatalayerCItf* datalayerCInterface();

  //! Returns flatbuffers c interface
  //! @return flatbuffers c interface
  FlatbuffersCItf* flatbuffersCInterface();

  //! Start the datalayer (broker)
  void start(bool boStartBroker = true);

  //! Stop the datalayer (broker)
  //! returns false if there is a client or provider active
  bool stop(bool boForceProviderStop = false);

  std::string getBrokerBindNode(BindNode type);

  void setRTParallelClientAsDefault(bool value);

  void setBfbsPath(std::string path);;

  std::string getServerPublicKey();

  //! By default key is requested using HTTPS from remote control.
  //! This function sets the public key of the remote control.
  //! @param[in] key     Remote TCP server public key
  //! @return none
  DlResult setRemotePublicKey(const std::string& key);

  //! By default token is fetched from deviceadmin using HTTPS from remote control.
  //! This function sets the token of the remote control.
  //! @param[in] key     Remote TCP server public key
  //! @return none
  DlResult setRemoteToken(const std::string& token);

  DlResult setDebugAddress(const std::string& address);

  DlResult persistNvram();

  DlResult enableTrace(bool boEnable, ::common::log::trace::IRegistration* registration = nullptr);

  DlResult setTokenCheck(bool boEnable);

  void loadConfig(const Variant& persistenceParam);
  void saveConfig();

  enum class ServerSetting
  {
    IDLE_PING_TIMEOUT,
    WAIT_RESPONSE_TIMEOUT,
    MAX_MESSAGE_SIZE,
    MAX_RT_SIZE,
  };

  uint32_t getSetting(ServerSetting setting);

protected:
private:
  static std::string getTmpPath();

  void* m_zmqContext = nullptr;
  Factory* m_factory = nullptr;
  Broker* m_broker = nullptr;
  FlatbufferJson* m_converter = nullptr;
  PersistenceHelper* m_persistenceHelper = nullptr;
  ComplianceChecker* m_complianceChecker = nullptr;
  RTDebug* m_rtdebug = nullptr;
  LoadSaveProvider* m_loadSave = nullptr;
  WatchlistProvider* m_watchlist = nullptr;
  ServerSettingsProvider* m_serverSettings = nullptr;
  remote::C2CMain* m_remote = nullptr;
  std::string m_ipcPath = "";
  DatalayerCItf m_datalayerCItf;
  FlatbuffersCItf m_flatbuffersCItf;
  RealtimeBroker* m_rtBroker = nullptr;
};

}
}
