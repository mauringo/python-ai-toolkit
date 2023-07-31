#pragma once
#include "variant.h"
#include "owner.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void* DLR_USER;

  DLR_RESULT DLR_userBeginAccess(DLR_USER user, uint8_t** data, uint32_t revision);
  DLR_RESULT DLR_userEndAccess(DLR_USER user);
  DLR_RESULT DLR_userGetSize(DLR_USER user, size_t* sizeBytes);
  DLR_RESULT DLR_userGetType(DLR_USER user, DLR_MEMORYTYPE* type);
  DLR_RESULT DLR_userGetMemoryMap(DLR_USER user, DLR_VARIANT memoryMap);

#ifdef __cplusplus
}
#endif
