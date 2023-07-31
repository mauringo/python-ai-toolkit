#pragma once

#include "variant.h"
#include "converter.h"

#ifdef __cplusplus
extern "C" {
#endif

  //! The notify item will be sent when the data value has been updated (e.g. in a subscription).
  typedef struct NotifyItem
  {
    DLR_VARIANT data; // data of the notify item
    DLR_VARIANT info; // containing notify_info.fbs
  }NotifyItem;


  //! Structure for bulk request
  typedef struct DLR_BULK_REQUEST
  {
    const char* address;          //! Address for the request
    DLR_VARIANT data;             //! Input data of the request
  }DLR_BULK_REQUEST;

  //! Structure for bulk response
  typedef struct DLR_BULK_RESPONSE
  {
    char* address;                //! Address for the response
    DLR_VARIANT data;             //! Output data of the response
    DLR_RESULT result;            //! Result of the response
    uint64_t timestamp;           //! Timestamp of the response
  }DLR_BULK_RESPONSE;

  //! vector of bulk requests
  typedef struct DLR_VEC_BULK_REQUEST
  {
    size_t count;                 //! count of requests
    DLR_BULK_REQUEST* request;    //! array of bulk requests
  }DLR_VEC_BULK_REQUEST;

  //! vector of bulk response
  typedef struct DLR_VEC_BULK_RESPONSE
  {
    size_t count;                 //! count of requests
    DLR_BULK_RESPONSE* response;  //! array of bulk response
  }DLR_VEC_BULK_RESPONSE;

  typedef void* DLR_CLIENT;

  //! Creates a bulk request
  //! @param[in] count    Count of request
  //! @return Created bulk request
  DLR_VEC_BULK_REQUEST* DLR_createBulkRequest(size_t count);

  //! Deletes a bulk request
  //! @param[in/out] request    Request to be deleted - will be set to nullptr
  void DLR_deleteBulkRequest(DLR_VEC_BULK_REQUEST** request);

  //! Deletes a bulk response. Response was created by a bulk access. It has to be delete by this function
  //! @param[in/out] request    Request to be deleted - will be set to nullptr
  void DLR_deleteBulkResponse(DLR_VEC_BULK_RESPONSE** response);

  //! Response function when a asynchronous call is ready.
  //! @param[in] status     Response status of the call
  //! @param[in] data       Response data
  //! @param[in] userdata   Same userdata as in async request given
  typedef void(*DLR_CLIENT_RESPONSE)(DLR_RESULT status, DLR_VARIANT data, void* userdata);

  //! This callback delivers a vector with the updated nodes of a subscription.
  //! It is usually called in the interval given by the publishInterval which has been set by the creation of the subscription.
  //! The callback may not contain all nodes of the subscription.I.e.when a node did not change.
  //! The callback may contain a node multiple times.I.e.when the node did change multiple times since the last callback.
  //! The sorting order of the items in the vector is undefined.
  //! @param[in] status    Notify status
  //! @param[in] items     Notify data
  //! @param[in] count     count of items
  //! @param[in] userdata   Same userdata as in create subscription given
  typedef void(*DLR_CLIENT_NOTIFY_RESPONSE)(DLR_RESULT status, NotifyItem* items, uint32_t count, void* userdata);

  //! This callback delivers response to a asynchronous bulk requests.
  //! The order of the items in the request is the same.
  //! @param[in] response  Bulk response. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in] userdata   Same userdata as in bulk request given
  typedef void(*DLR_CLIENT_BULK_RESPONSE)(DLR_VEC_BULK_RESPONSE* response, void* userdata);

  //! Settings of different timeout values
  typedef enum DLR_TIMEOUT_SETTING {
    DLR_TIMEOUT_SETTING_IDLE,       // timeout to check whether to broker is still active when client is idle
    DLR_TIMEOUT_SETTING_PING,       // timeout to wait for a response for a request - it timeout exceeds request will be aborted with DL_TIMEOUT
    DLR_TIMEOUT_SETTING_RECONNECT,  // timeout a reconnect attempt will be done if client looses connection to broker
  } DLR_TIMEOUT_SETTING;

  // deletes a client
  //! @param[in]  client    Reference to the client
  void DLR_clientDelete(DLR_CLIENT client);

  //! Ping the next hop. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @result status of function call
  DLR_RESULT DLR_clientPingSync(DLR_CLIENT client);

  //! Create an object. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to create object in
  //! @param[in,out]  variant      Data of the object, result of write
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientCreateSync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token);

  //! Remove an object. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to remove
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientRemoveSync(DLR_CLIENT client, const char* address, const char* token);

  //! Browse an object. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to browse
  //! @param[out] variant   Children of the node. Data will be provided as Variant array of strings.
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientBrowseSync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token);

  //! Read an object. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to read
  //! @param[in,out] variant   Read filter data of the node
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientReadSync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token);

  //! Write an object. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to write
  //! @param[in,out] variant New data of the node, result of write
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientWriteSync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token);

  //! Read metadata of an object. This function is synchronous: It will wait for the answer.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to read metadata of
  //! @param[out] variant   Metadata of the node. Data will be provided as Variant flatbuffers with metadata.fbs data type.
  //! @param[in]  token     Security access &token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientMetadataSync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token);

  //! Bulk read request to read multiple nodes with a single request.
  //! Function will block until all nodes have been read or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Request
  //! @param[out]     response       Response. Will be created by function call. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientReadBulkSync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, DLR_VEC_BULK_RESPONSE** response, const char* token);

  //! Bulk write request to write multiple nodes with a single request.
  //! Function will block until all nodes have been written or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Request
  //! @param[out]     response       Response. Will be created by function call. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientWriteBulkSync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, DLR_VEC_BULK_RESPONSE** response, const char* token);

  //! Bulk create request to create multiple nodes with a single request.
  //! Function will block until all nodes have been created or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Request
  //! @param[out]     response       Response. Will be created by function call. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientCreateBulkSync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, DLR_VEC_BULK_RESPONSE** response, const char* token);

  //! Bulk delete request to delete multiple nodes with a single request.
  //! Function will block until all nodes have been deleted or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Request
  //! @param[out]     response       Response. Will be created by function call. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientDeleteBulkSync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, DLR_VEC_BULK_RESPONSE** response, const char* token);

  //! Bulk browse request to browse multiple nodes with a single request.
  //! Function will block until all nodes have been browsed or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Request
  //! @param[out]     response       Response. Will be created by function call. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientBrowseBulkSync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, DLR_VEC_BULK_RESPONSE** response, const char* token);

  //! Bulk metadata request to read multiple metadata of nodes with a single request.
  //! Function will block until all metadata of all nodes have been read or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Request
  //! @param[out]     response       Response. Will be created by function call. Must be deleted with DLR_deleteBulkResponse.
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientMetadataBulkSync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, DLR_VEC_BULK_RESPONSE** response, const char* token);

  //! Ping the next hop. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! @param[in]  client    Reference to the client
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientPingASync(DLR_CLIENT client, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Create an object. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! Result data may be provided in callback function.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to create object in
  //! @param[in]  data      Data of the object
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientCreateASync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Remove an object. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! Result data may be provided in callback function.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to remove
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientRemoveASync(DLR_CLIENT client, const char* address, const char* token, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Browse an object. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! Result data may be provided in callback function.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to browse
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientBrowseASync(DLR_CLIENT client, const char* address, const char* token, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Read an object. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! Result data may be provided in callback function.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to read
  //! @param[in]  data      Read filter data of the node
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientReadASync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Write an object. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! Result data may be provided in callback function.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to write
  //! @param[in]  data      Data of the object
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientWriteASync(DLR_CLIENT client, const char* address, DLR_VARIANT variant, const char* token, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Read metadata of an object. This function is asynchronous. It will return immediately. Callback will be called if function call is finished.
  //! Result data may be provided in callback function.
  //! @param[in]  client    Reference to the client
  //! @param[in]  address   Address of the node to read metadata
  //! @param[in]  token     Security access token for authentication as JWT payload
  //! @param[in]  callback  Callback to call when function is finished
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientMetadataASync(DLR_CLIENT client, const char* address, const char* token, DLR_CLIENT_RESPONSE callback, void *userdata);

  //! Asynchronous bulk read request to read multiple nodes with a single request.
  //! Function will return immediately.
  //! Response data will be delivered in a single callback when all nodes have been read or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Requests
  //! @param[in]      callback       Callback to call when function is finished
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @param[in]      userdata       User data - will be returned in callback as userdata. You can use this userdata to identify your bulk request
  //! @result status of function call
  DLR_RESULT DLR_clientReadBulkASync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, const char* token, DLR_CLIENT_BULK_RESPONSE callback, void* userdata);


  //! Asynchronous bulk write request to write multiple nodes with a single request.
  //! Function will return immediately.
  //! Response data will be delivered in a single callback when all nodes have been written or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Requests
  //! @param[in]      callback       Callback to call when function is finished
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @param[in]      userdata       User data - will be returned in callback as userdata. You can use this userdata to identify your bulk request
  //! @result status of function call
  DLR_RESULT DLR_clientWriteBulkASync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, const char* token, DLR_CLIENT_BULK_RESPONSE callback, void* userdata);

  //! Asynchronous bulk create request to create multiple nodes with a single request.
  //! Function will return immediately.
  //! Response data will be delivered in a single callback when all nodes have been created or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Requests
  //! @param[in]      callback       Callback to call when function is finished
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @param[in]      userdata       User data - will be returned in callback as userdata. You can use this userdata to identify your bulk request
  //! @result status of function call
  DLR_RESULT DLR_clientCreateBulkASync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, const char* token, DLR_CLIENT_BULK_RESPONSE callback, void* userdata);

  //! Asynchronous bulk delete request to delete multiple nodes with a single request.
  //! Function will return immediately.
  //! Response data will be delivered in a single callback when all nodes have been deleted or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Requests
  //! @param[in]      callback       Callback to call when function is finished
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @param[in]      userdata       User data - will be returned in callback as userdata. You can use this userdata to identify your bulk request
  //! @result status of function call
  DLR_RESULT DLR_clientDeleteBulkASync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, const char* token, DLR_CLIENT_BULK_RESPONSE callback, void* userdata);

  //! Asynchronous bulk browse request to read multiple nodes with a single request.
  //! Function will return immediately.
  //! Response data will be delivered in a single callback when all nodes have been browsed or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Requests
  //! @param[in]      callback       Callback to call when function is finished
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @param[in]      userdata       User data - will be returned in callback as userdata. You can use this userdata to identify your bulk request
  //! @result status of function call
  DLR_RESULT DLR_clientBrowseBulkASync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, const char* token, DLR_CLIENT_BULK_RESPONSE callback, void* userdata);

  //! Asynchronous bulk metadata request to read multiple metadata of nodes with a single request.
  //! Function will return immediately.
  //! Response data will be delivered in a single callback when all metadata of nodes have been read or returned a timeout.
  //! @param[in]      client         Reference to the client
  //! @param[in]      request        Requests
  //! @param[in]      callback       Callback to call when function is finished
  //! @param[in]      token          Security access token for authentication as JWT payload
  //! @param[in]      userdata       User data - will be returned in callback as userdata. You can use this userdata to identify your bulk request
  //! @result status of function call
  DLR_RESULT DLR_clientMetadataBulkASync(DLR_CLIENT client, const DLR_VEC_BULK_REQUEST* request, const char* token, DLR_CLIENT_BULK_RESPONSE callback, void* userdata);


  //! Setup a subscription
  //! @param[in]  client    Reference to the client
  //! @param[in]  ruleset   Variant that describe ruleset of subscription as subscription.fbs
  //! @param[in]  publishCallback  Callback to call when new data is available
  //! @param[in]  userdata  User data - will be returned in publishCallback as userdata. You can use this userdata to identify your subscription
  //! @param[in]  token     Security access &token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientCreateSubscriptionSync(DLR_CLIENT client, DLR_VARIANT ruleset, DLR_CLIENT_NOTIFY_RESPONSE publishCallback, void* userdata, const char* token);

  //! Adds a node to a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Address of a node, that should be added to the given subscription.
  //! @result status of function call
  DLR_RESULT DLR_clientSubscribeSync(DLR_CLIENT client, const char* id, const char* address);

  //! Adds a list of nodes to a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   List of Addresses of a node, that should be added to the given subscription.
  //! @param[in]  count     Count of addresses.
  //! @result status of function call
  DLR_RESULT DLR_clientSubscribeMultiSync(DLR_CLIENT client, const char* id, const char** address, uint32_t count);

  //! Removes a node from a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Address of a node, that should be removed to the given subscription.
  //! @result status of function call
  DLR_RESULT DLR_clientUnsubscribeSync(DLR_CLIENT client, const char* id, const char* address);

  //! Removes a set of nodes from a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Set of addresses of nodes, that should be removed to the given subscription.
  //! @result status of function call
  DLR_RESULT DLR_clientUnsubscribeMultiSync(DLR_CLIENT client, const char* id, const char** address, uint32_t count);

  //! Removes subscription id completely
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        ID of subscription to remove
  //! @result status of function call
  DLR_RESULT DLR_clientUnsubscribeAllSync(DLR_CLIENT client, const char* id);

  //! Setup a subscription
  //! @param[in]  client    Reference to the client
  //! @param[in]  ruleset   Variant that describe ruleset of subscription as subscription.fbs
  //! @param[in]  publishCallback Callback to call when new data is available
  //! @param[in]  callback  Callback to be called when subscription is created
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request and subscription
  //! @param[in]  token     Security access &token for authentication as JWT payload
  //! @result status of function call
  DLR_RESULT DLR_clientCreateSubscriptionAsync(DLR_CLIENT client, DLR_VARIANT ruleset, DLR_CLIENT_NOTIFY_RESPONSE publishCallback, DLR_CLIENT_RESPONSE callback, void* userdata, const char* token);

  //! Setup a subscription to a node
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Address of the node to add a subscription to
  //! @param[in]  callback  Callback to called when data is subscribed
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientSubscribeAsync(DLR_CLIENT client, const char* id, const char* address, DLR_CLIENT_RESPONSE callback, void* userdata);

  //! Setup a subscription to multiple nodes
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Set of addresses of nodes, that should be removed to the given subscription.
  //! @param[in]  count     Count of addresses.
  //! @param[in]  callback  Callback to called when data is subscribed
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientSubscribeMultiAsync(DLR_CLIENT client, const char* id, const char** address, uint32_t count, DLR_CLIENT_RESPONSE callback, void* userdata);

  //! Removes a node from a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Address of a node, that should be removed to the given subscription.
  //! @param[in]  callback  Callback to called when data is subscribed
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientUnsubscribeAsync(DLR_CLIENT client, const char* id, const char* address, DLR_CLIENT_RESPONSE callback, void* userdata);

  //! Removes a set of nodes from a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        Subscription ID, given in creation of the subscription. See createSbscription(A)Sync.
  //! @param[in]  address   Address of a node, that should be removed to the given subscription.
  //! @param[in]  callback  Callback to called when data is subscribed
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  //! @result status of function call
  DLR_RESULT DLR_clientUnsubscribeMultiAsync(DLR_CLIENT client, const char* id, const char** address, uint32_t count, DLR_CLIENT_RESPONSE callback, void* userdata);

  //! Removes all subscriptions from a subscription id
  //! @param[in]  client    Reference to the client
  //! @param[in]  id        ID of subscription to remove
  //! @param[in]  callback  Callback to called when data is subscribed
  //! @result status of function call
  //! @param[in]  userdata  User data - will be returned in callback as userdata. You can use this userdata to identify your request
  DLR_RESULT DLR_clientUnsubscribeAllAsync(DLR_CLIENT client, const char* id, DLR_CLIENT_RESPONSE callback, void* userdata);

  //! Set client timeout value
  //! @param[in]  client    Reference to the client
  //! @param[in]  timeout   Timeout to set (see DLR_TIMEOUT_SETTING)
  //! @param[in]  value     Value to set
  //! @result status of function call
  DLR_RESULT DLR_clientSetTimeout(DLR_CLIENT client, DLR_TIMEOUT_SETTING timeout, uint32_t value);

  //! returns whether client is connected
  //! @param[in]  client    Reference to the client
  //| @return status of connection
  bool DLR_clientIsConnected(DLR_CLIENT client);

  //! Set persistent security access token for authentication as JWT payload
  //! @param[in]  client    Reference to the client
  //! @param[in]  token  Security access &token for authentication
  void DLR_clientSetAuthToken(DLR_CLIENT client, const char* token);

  //! returns persistent security access token for authentication
  //! @param[in]  client    Reference to the client
  //| @return security access token for authentication
  const char* DLR_clientGetAuthToken(DLR_CLIENT client);

  //! This function reads a values as a JSON string
  //! @param[in]  client      Reference to the client
  //! @param[in]  converter   Reference to the converter
  //! @param[in/out] json     Generated JSON as Variant (string)
  //! @param[in]  indentStep  Indentation length for json string
  //! @param[in]  token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DLR_RESULT DLR_clientReadJsonSync(DLR_CLIENT client, DLR_CONVERTER converter, const char* address, DLR_VARIANT json, int32_t indentStep, const char* token);

  //! This function writes a JSON value
  //! @param[in]     client      Reference to the client
  //! @param[in]     converter   Reference to the converter
  //! @param[in]     address     Address of the node to write
  //! @param[in]     json        JSON value to write
  //! @param[in,out] error       Error of conversion as variant string
  //! @param[in]     token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DLR_RESULT DLR_clientWriteJsonSync(DLR_CLIENT client, DLR_CONVERTER converter, const char* address, const char* json, DLR_VARIANT error, const char* token);

#ifdef __cplusplus
}
#endif
