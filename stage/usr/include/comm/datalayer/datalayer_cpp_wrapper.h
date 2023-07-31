#pragma once

#include "datalayer.h"
#include "c/variant.h"

namespace comm {
namespace datalayer {

#define DATALAYER_CHECK_FUNC(func) \
if(m_cInterface.handle == nullptr || m_cInterface.func == nullptr) \
{ \
  return DL_INVALID_HANDLE; \
}

//! Client class wrapper for celix C interface
class ClientCpp : public IClient3
{
public:

  ClientCpp(DatalayerCItf& cInterface, const std::string& remote = DL_INPROC_FRONTEND_SERVER)
    :m_cInterface(cInterface)
  {
    createClient(remote);
  };

  virtual ~ClientCpp()
  {
    deleteClient();
  }

  DlResult createSubscriptionSync(const Variant& ruleset, const PublishCallback& publishCallback = {}, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(createSubscriptionSync);
    return m_cInterface.createSubscriptionSync(m_client, ruleset, publishCallback, token);
  }

  DlResult subscribeSync(const std::string& id, const std::string& address) override
  {
    DATALAYER_CHECK_FUNC(subscribeSyncAddress);
    return m_cInterface.subscribeSyncAddress(m_client, id, address);
  }

  DlResult subscribeSync(const std::string& id, const std::set<std::string>& address) override
  {
    DATALAYER_CHECK_FUNC(subscribeSyncAddressSet);
    return m_cInterface.subscribeSyncAddressSet(m_client, id, address);
  }

  DlResult unsubscribeSync(const std::string& id, const std::string& address) override
  {
    DATALAYER_CHECK_FUNC(unsubscribeSyncAddress);
    return m_cInterface.unsubscribeSyncAddress(m_client, id, address);
  }

  DlResult unsubscribeSync(const std::string& id, const std::set<std::string>& address) override
  {
    DATALAYER_CHECK_FUNC(unsubscribeSyncAddressSet);
    return m_cInterface.unsubscribeSyncAddressSet(m_client, id, address);
  }

  DlResult unsubscribeSync(const std::string& id) override
  {
    DATALAYER_CHECK_FUNC(unsubscribeSync);
    return m_cInterface.unsubscribeSync(m_client, id);
  }

  DlResult createSubscriptionAsync(const Variant& ruleset, const PublishCallback& publishCallback, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(createSubscriptionAsync);
    return m_cInterface.createSubscriptionAsync(m_client, ruleset, publishCallback, callback, token);
  }

  DlResult subscribeAsync(const std::string& id, const std::string& address, const ResponseCallback& callback) override
  {
    DATALAYER_CHECK_FUNC(subscribeAsyncAddress);
    return m_cInterface.subscribeAsyncAddress(m_client, id, address, callback);
  }

  DlResult subscribeAsync(const std::string& id, const std::set<std::string>& address, const ResponseCallback& callback) override
  {
    DATALAYER_CHECK_FUNC(subscribeAsyncAddressSet);
    return m_cInterface.subscribeAsyncAddressSet(m_client, id, address, callback);
  }

  DlResult unsubscribeAsync(const std::string& id, const std::string& address, const ResponseCallback& callback) override
  {
    DATALAYER_CHECK_FUNC(unsubscribeAsyncAddress);
    return m_cInterface.unsubscribeAsyncAddress(m_client, id, address, callback);
  }

  DlResult unsubscribeAsync(const std::string& id, const std::set<std::string>& address, const ResponseCallback& callback) override
  {
    DATALAYER_CHECK_FUNC(unsubscribeAsyncAddressSet);
    return m_cInterface.unsubscribeAsyncAddressSet(m_client, id, address, callback);
  }

  DlResult unsubscribeAsync(const std::string& id, const ResponseCallback& callback) override
  {
    DATALAYER_CHECK_FUNC(unsubscribeAsync);
    return m_cInterface.unsubscribeAsync(m_client, id, callback);
  }

  DlResult pingAsync(const ResponseCallback& callback) override
  {
    DATALAYER_CHECK_FUNC(pingAsync);
    return m_cInterface.pingAsync(m_client, callback);
  }

  DlResult createAsync(const std::string& address, const Variant& data, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(createAsync);
    return m_cInterface.createAsync(m_client, address, data, callback, token);
  }

  DlResult removeAsync(const std::string& address, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(removeAsync);
    return m_cInterface.removeAsync(m_client, address, callback, token);
  }

  DlResult browseAsync(const std::string& address, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(browseAsync);
    return m_cInterface.browseAsync(m_client, address, callback, token);
  }

  DlResult readAsync(const std::string& address, const Variant& data, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(readAsync);
    return m_cInterface.readAsync(m_client, address, data, callback, token);
  }

  DlResult writeAsync(const std::string& address, const Variant& data, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(writeAsync);
    return m_cInterface.writeAsync(m_client, address, data, callback, token);
  }

  DlResult metadataAsync(const std::string& address, const ResponseCallback& callback, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(metadataAsync);
    return m_cInterface.metadataAsync(m_client, address, callback, token);
  }

  DlResult pingSync() override
  {
    DATALAYER_CHECK_FUNC(pingSync);
    return m_cInterface.pingSync(m_client);
  }

  DlResult createSync(const std::string& address, Variant* data, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(createSync);
    return m_cInterface.createSync(m_client, address, data, token);
  }

  DlResult removeSync(const std::string& address, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(removeSync);
    return m_cInterface.removeSync(m_client, address, token);
  }

  DlResult browseSync(const std::string& address, Variant* data, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(browseSync);
    return m_cInterface.browseSync(m_client, address, data, token);
  }

  DlResult readSync(const std::string& address, Variant* data, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(readSync);
    return m_cInterface.readSync(m_client, address, data, token);
  }

  DlResult writeSync(const std::string& address, Variant* data, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(writeSync);
    return m_cInterface.writeSync(m_client, address, data, token);
  }

  DlResult metadataSync(const std::string& address, Variant* data, const std::string& token = {}) override
  {
    DATALAYER_CHECK_FUNC(metadataSync);
    return m_cInterface.metadataSync(m_client, address, data, token);
  }

  DlResult setTimeout(TimeoutSetting timeout, uint32_t value) override
  {
    DATALAYER_CHECK_FUNC(setTimeout);
    return m_cInterface.setTimeout(m_client, timeout, value);
  }

  bool isConnected() const override
  {
    if (m_cInterface.handle == nullptr || m_cInterface.isConnected == nullptr)
    {
      return false;
    }
    return m_cInterface.isConnected(m_client);
  }

  void setAuthToken(const std::string& token) override
  {
    if (m_cInterface.handle == nullptr || m_cInterface.setAuthToken == nullptr)
    {
      return;
    }
    m_cInterface.setAuthToken(m_client, token);
  }

  std::string getAuthToken() const override
  {
    if (m_cInterface.handle == nullptr || m_cInterface.getAuthToken == nullptr)
    {
      return "";
    }
    return m_cInterface.getAuthToken(m_client);
  }

  virtual DlResult readSync(const std::string& address, comm::datalayer::Variant* data, comm::datalayer::Variant* detail, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(readDetailSync);
    return m_cInterface.readDetailSync(m_client, address, data, detail, token);
  }

  virtual DlResult readAsync(const std::string& address, const comm::datalayer::Variant& data, const comm::datalayer::IClient::DetailResponseCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(readDetailAsync);
    return m_cInterface.readDetailAsync(m_client, address, data, callback, token);
  }

  virtual DlResult readBulkSync(const VecBulkRequest& request, VecBulkResponse& response, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(readBulkSync);
    return m_cInterface.readBulkSync(m_client, request, response, token);
  }

  virtual DlResult readBulkAsync(const VecBulkRequest& request, const BulkCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(readBulkAsync);
    return m_cInterface.readBulkAsync(m_client, request, callback, token);
  }

  virtual DlResult writeBulkSync(const VecBulkRequest& request, VecBulkResponse& response, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(writeBulkSync);
    return m_cInterface.writeBulkSync(m_client, request, response, token);
  }

  virtual DlResult writeBulkAsync(const VecBulkRequest& request, const BulkCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(writeBulkAsync);
    return m_cInterface.writeBulkAsync(m_client, request, callback, token);
  }

  virtual DlResult createBulkSync(const VecBulkRequest& request, VecBulkResponse& response, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(createBulkSync);
    return m_cInterface.createBulkSync(m_client, request, response, token);
  }

  virtual DlResult createBulkAsync(const VecBulkRequest& request, const BulkCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(createBulkAsync);
    return m_cInterface.createBulkAsync(m_client, request, callback, token);
  }

  virtual DlResult deleteBulkSync(const VecBulkRequest& request, VecBulkResponse& response, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(deleteBulkSync);
    return m_cInterface.deleteBulkSync(m_client, request, response, token);
  }

  virtual DlResult deleteBulkAsync(const VecBulkRequest& request, const BulkCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(deleteBulkAsync);
    return m_cInterface.deleteBulkAsync(m_client, request, callback, token);
  }

  virtual DlResult browseBulkSync(const VecBulkRequest& request, VecBulkResponse& response, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(browseBulkSync);
    return m_cInterface.browseBulkSync(m_client, request, response, token);
  }

  virtual DlResult browseBulkAsync(const VecBulkRequest& request, const BulkCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(browseBulkAsync);
    return m_cInterface.browseBulkAsync(m_client, request, callback, token);
  }

  virtual DlResult metadataBulkSync(const VecBulkRequest& request, VecBulkResponse& response, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(metadataBulkSync);
    return m_cInterface.metadataBulkSync(m_client, request, response, token);
  }

  virtual DlResult metadataBulkAsync(const VecBulkRequest& request, const BulkCallback& callback, const std::string& token = {})
  {
    DATALAYER_CHECK_FUNC(metadataBulkAsync);
    return m_cInterface.metadataBulkAsync(m_client, request, callback, token);
  }

protected:
private:
  DLR_RESULT createClient(const std::string& remote)
  {
    DATALAYER_CHECK_FUNC(createClient);
    m_client = m_cInterface.createClient(m_cInterface.handle, remote);
    return m_client ? DLR_RESULT::DL_OK : DLR_RESULT::DL_INVALID_HANDLE;
  }

  DLR_RESULT deleteClient()
  {
    DATALAYER_CHECK_FUNC(deleteClient);
    m_cInterface.deleteClient(m_client);
    return DLR_RESULT::DL_OK;
  }

  DatalayerCItf m_cInterface;
  void* m_client;
};

}
}
