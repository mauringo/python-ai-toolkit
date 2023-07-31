#pragma once
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum DLR_MEMORYTYPE
  {
    MemoryType_Unknown = 0,
    MemoryType_Input = 1,
    MemoryType_Output = 2,
    MemoryType_SharedRetain = 3,
    MemoryType_Shared = 4,
  }DLR_MEMORYTYPE;

  typedef void* DLR_OWNER;

  DLR_RESULT DLR_ownerBeginAccess(DLR_OWNER owner, uint8_t** data, uint32_t revision);
  DLR_RESULT DLR_ownerEndAccess(DLR_OWNER owner);
  DLR_RESULT DLR_ownerGetSize(DLR_OWNER owner, size_t* sizeBytes);
  DLR_RESULT DLR_ownerGetType(DLR_OWNER owner, DLR_MEMORYTYPE* type);
  DLR_RESULT DLR_ownerGetMemoryMap(DLR_OWNER owner, DLR_VARIANT memoryMap);
  DLR_RESULT DLR_ownerSetMemoryMap(DLR_OWNER owner, DLR_VARIANT memoryMap);

#ifdef __cplusplus
}
#endif
