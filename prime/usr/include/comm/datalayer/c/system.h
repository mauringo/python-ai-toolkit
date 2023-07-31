#pragma once

#include "factory.h"
#include "converter.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void *DLR_SYSTEM;

  //! Creates a datalayer system
  //! @param[in] ipcPath    Path for interprocess communication - use null pointer for automatic detection
  //! @return datalayer system
  DLR_SYSTEM DLR_systemCreate(const char* ipcPath);

  //! Deletes a datalayer system
  //! @param[in] system  Datalayer system to delete
  void DLR_systemDelete(DLR_SYSTEM system);

  //! Returns the datalayer factory
  //! @param[in] system  Datalayer system
  //! @return Datalayer factory
  DLR_FACTORY DLR_systemFactory(DLR_SYSTEM system);

  //! Returns the datalayer json converter
  //! @param[in] system  Datalayer system
  //! @return Datalayer json converter
  DLR_CONVERTER DLR_systemJsonConverter(DLR_SYSTEM system);

  //! Starts a dalayer system
  //! @param[in] system  Datalayer system
  //! @param[in] boStartBroker  Use true to start a broker. If you are a user of the datalayer - call with false!
  //! @return Datalayer json converter
  void DLR_systemStart(DLR_SYSTEM system, bool boStartBroker);

  //! Stops a dalayer system
  //! @param[in] system  Datalayer system
  //! @param[in] boForceProviderStop   Force stop off all created providers for this datalayer system
  bool DLR_systemStop(DLR_SYSTEM system, bool boForceProviderStop);

  //! Sets the base path to bfbs files
  //! @param[in] system  Datalayer system
  //! @param[in] path    Base path to bfbs files
  void DLR_systemSetBfbsPath(DLR_SYSTEM system, const char* path);

#ifdef __cplusplus
}
#endif
