#pragma once
#include "variant.h"
#include "subscription.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void *DLR_PROVIDER_NODE;
  typedef void *DLR_PROVIDER_NODE_CALLBACKDATA;

  //! Type definition for a callback
  //! A node has to call this method if a request is done
  //! @param[in] callbackdata      Forwarded same data as in DLR_PROVIDER_NODE_FUNCTION or DLR_PROVIDER_NODE_FUNCTION_DATA
  //! @param[in] result            Status result of the request
  //! @param[in] data              Result data of the request
  typedef void(*DLR_PROVIDER_NODE_CALLBACK)(DLR_PROVIDER_NODE_CALLBACKDATA callbackdata, DLR_RESULT result, const DLR_VARIANT data);

  //! Type definition for a request function (without data)
  //! @param[in] userData          User data to identify Node - same value as in DLR_PROVIDER_NODE_CALLBACKS.userData
  //! @param[in] address           Requested node address
  //! @param[in] callback          Callback to be called if request is done
  //! @param[in] callbackdata      Callback data to give with callback function
  //! @return Result will be ignored
  typedef DLR_RESULT(*DLR_PROVIDER_NODE_FUNCTION) (void* userData, const char* address, DLR_PROVIDER_NODE_CALLBACK callback, DLR_PROVIDER_NODE_CALLBACKDATA callbackdata);

  //! Type definition for a request function (with data)
  //! @param[in] userData          User data to identify Node - same value as in DLR_PROVIDER_NODE_CALLBACKS.userData
  //! @param[in] address           Requested node address
  //! @param[in] data              Data for the request. After calling this method content of data is not valid anymore.
  //! @param[in] callback          Callback to be called if request is done
  //! @param[in] callbackdata      Callback data to give with callback function
  //! @return Result will be ignored
  typedef DLR_RESULT(*DLR_PROVIDER_NODE_FUNCTION_DATA)(void* userData, const char* address, DLR_VARIANT data, DLR_PROVIDER_NODE_CALLBACK callback, DLR_PROVIDER_NODE_CALLBACKDATA callbackdata);

  //! Type definition for a subscription function
  //! @param[in] userData          User data to identify Node - same value as in DLR_PROVIDER_NODE_CALLBACKS.userData
  //! @param[in] subscription      Reference to the subscription
  //! @param[in] address           Subscribed address
  //! @return Result will be ignored
  typedef DLR_RESULT(*DLR_PROVIDER_SUBSCRIPTION_FUNCTION)(void* userData, DLR_SUBSCRIPTION subscription, const char* address);

  //! Type to define callback functions for a node
  typedef struct DLR_PROVIDER_NODE_CALLBACKS
  {
    void* userData;                                   // userData to identify the node - this user data will be given with all functions below as userData
    DLR_PROVIDER_NODE_FUNCTION_DATA    onCreate;      // function to call for a create request
    DLR_PROVIDER_NODE_FUNCTION         onRemove;      // function to call for a remove request
    DLR_PROVIDER_NODE_FUNCTION         onBrowse;      // function to call for a browse request
    DLR_PROVIDER_NODE_FUNCTION_DATA    onRead;        // function to call for a read request
    DLR_PROVIDER_NODE_FUNCTION_DATA    onWrite;       // function to call for a write request
    DLR_PROVIDER_NODE_FUNCTION         onMetadata;    // function to call for a metadata request
    DLR_PROVIDER_SUBSCRIPTION_FUNCTION onSubscribe;   // function to call for a subscription request - nullptr if not supported
    DLR_PROVIDER_SUBSCRIPTION_FUNCTION onUnsubscribe; // function to call for a unsubscription request - nullptr if not supported
  }DLR_PROVIDER_NODE_CALLBACKS;

  //! Creates a node
  //! @param[in] callbacks    Callbacks for the node
  //! @return Created node
  DLR_PROVIDER_NODE DLR_providerNodeCreate(DLR_PROVIDER_NODE_CALLBACKS callbacks);

  //! Deletes a node
  //! @param[in] providerNode Node to delete
  void DLR_providerNodeDelete(DLR_PROVIDER_NODE providerNode);

#ifdef __cplusplus
}
#endif
