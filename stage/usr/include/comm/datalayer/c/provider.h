#pragma once

#include "provider_node.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void *DLR_PROVIDER;

  //! Deletes a provider
  //! @param[in]  provider  Reference to the provider
  void DLR_providerDelete(DLR_PROVIDER provider);

  //! Register a type to the datalayer
  //! @param[in]  provider  Reference to the provider
  //! @param[in]  address   Address of the node to register (no wildcards allowed)
  //! @param[in]  pathname  Path to flatbuffer bfbs
  //! @result status of function call
  DLR_RESULT DLR_providerRegisterType(DLR_PROVIDER provider, const char* address, const char* pathname);

  //! Register a type to the datalayer
  //! @param[in]  provider  Reference to the provider
  //! @param[in]  address   Address of the node to register (no wildcards allowed)
  //! @param[in]  data      Variant with flatbuffer type
  //! @result status of function call
  DLR_RESULT DLR_providerRegisterTypeVariant(DLR_PROVIDER provider, const char* address, DLR_VARIANT data);

  //! Unregister a type from the datalayer
  //! @param[in]  provider  Reference to the provider
  //! @param[in]  address   Address of the node to register (wildcards allowed)
  //! @result status of function call
  DLR_RESULT DLR_providerUnregisterType(DLR_PROVIDER provider, const char* address);

  //! Register a node to the datalayer
  //! @param[in]  provider  Reference to the provider
  //! @param[in]  address   Address of the node to register (wildcards allowed)
  //! @param[in]  node      Node to register
  //! @result status of function call
  DLR_RESULT DLR_providerRegisterNode(DLR_PROVIDER provider, const char* address, DLR_PROVIDER_NODE node);

  //! Unregister a node from the datalayer
  //! @param[in]  provider  Reference to the provider
  //! @param[in]  address   Address of the node to register (wildcards allowed)
  //! @result status of function call
  DLR_RESULT DLR_providerUnregisterNode(DLR_PROVIDER provider, const char* address);

  //! Set timeout for a node for asynchron requests (default value is 1000ms)
  //! @param[in]  provider  Reference to the provider
  //! @param[in]  node      Node to set timeout for
  //! @param[in]  timeoutMS Timeout in milliseconds for this node
  //! @result status of function call
  DLR_RESULT DLR_providerSetTimeoutNode(DLR_PROVIDER provider, DLR_PROVIDER_NODE node, uint32_t timeoutMS);

  //! Start the provider
  //! @param[in]  provider  Reference to the provider
  //! @result status of function call
  DLR_RESULT DLR_providerStart(DLR_PROVIDER provider);

  //! Stop the provider
  //! @param[in]  provider  Reference to the provider
  //! @result status of function call
  DLR_RESULT DLR_providerStop(DLR_PROVIDER provider);

  //! returns whether provider is connected
  //! @param[in]  provider  Reference to the provider
  //! @return status of connection
  bool DLR_providerIsConnected(DLR_PROVIDER provider);

  //! return the current token of the current request
  //! you can call this function during your onRead, onWrite, ... methods of
  //! your ProviderNodes.
  //! if there is no current request the method return an empty token
  //! @param[in]  provider  Reference to the provider
  //! @return current token
  DLR_VARIANT DLR_providerGetToken(DLR_PROVIDER provider);

  //! return the current registered node paths
  //! @param[in]  provider  Reference to the provider
  //! @param[out] data      Variant which includes the registered node paths after this function
  //! @return status of the function call
  DLR_RESULT DLR_providerGetRegisteredNodePaths(DLR_PROVIDER provider, DLR_VARIANT data);

#ifdef __cplusplus
}
#endif
