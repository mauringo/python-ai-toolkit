#pragma once

#include <stdint.h>
#include <string.h>



//! Namespace for datalayer
namespace comm {
namespace datalayer {


//! Result data type for all function calls
struct DlResult
{

#include "c/datalayer_facility.h"

  // additional error codes can be added if they are useable for all components
  enum Value : uint32_t
  {
#include "c/datalayer_error_codes.h"
  };

  Value value;

  DlResult() = default;
  constexpr DlResult(Value result) : value(result) {}
  constexpr DlResult(uint32_t result) : value(static_cast<Value>(result)) {}
  
  friend inline bool operator==(const DlResult& lhs, const DlResult& rhs) {
    return lhs.value == rhs.value;
  }

  friend inline bool operator!=(const DlResult& lhs, const DlResult& rhs) {
    return lhs.value != rhs.value;
  }

  const char* toString() const 
  {
#define IDS(id)   case Value::id: return (#id);
    switch (static_cast<uint32_t>(value)) {
      //! facility: common
      IDS(DL_OK)
      IDS(DL_OK_NO_CONTENT)
      IDS(DL_FAILED)

      //! facility: application
      IDS(DL_INVALID_ADDRESS)
      IDS(DL_UNSUPPORTED)
      IDS(DL_OUT_OF_MEMORY)
      IDS(DL_LIMIT_MIN)
      IDS(DL_LIMIT_MAX)
      IDS(DL_TYPE_MISMATCH)
      IDS(DL_SIZE_MISMATCH)
      IDS(DL_INVALID_FLOATINGPOINT)
      IDS(DL_INVALID_HANDLE)
      IDS(DL_INVALID_OPERATION_MODE)
      IDS(DL_INVALID_CONFIGURATION)
      IDS(DL_INVALID_VALUE)
      IDS(DL_SUBMODULE_FAILURE)
      IDS(DL_TIMEOUT)
      IDS(DL_ALREADY_EXISTS)
      IDS(DL_CREATION_FAILED)
      IDS(DL_VERSION_MISMATCH)
      IDS(DL_DEPRECATED)
      IDS(DL_PERMISSION_DENIED)
      IDS(DL_NOT_INITIALIZED)
      IDS(DL_MISSING_ARGUMENT)
      IDS(DL_TOO_MANY_ARGUMENTS)
      IDS(DL_RESOURCE_UNAVAILABLE)
      IDS(DL_COMMUNICATION_ERROR)
      IDS(DL_TOO_MANY_OPERATIONS)
      IDS(DL_WOULD_BLOCK)

      //! facility: communication
      IDS(DL_COMM_PROTOCOL_ERROR)
      IDS(DL_COMM_INVALID_HEADER)

      //! facility: client
      IDS(DL_CLIENT_NOT_CONNECTED)

      //! facility: provider
      IDS(DL_PROVIDER_RESET_TIMEOUT)
      IDS(DL_PROVIDER_UPDATE_TIMEOUT)

      //! facility: realtime
      IDS(DL_RT_NOTOPEN)
      IDS(DL_RT_INVALIDOBJECT)
      IDS(DL_RT_WRONGREVISON)
      IDS(DL_RT_NOVALIDDATA)
      IDS(DL_RT_MEMORYLOCKED)
      IDS(DL_RT_INVALIDMEMORYMAP)
      IDS(DL_RT_INVALID_RETAIN)
      IDS(DL_RT_INTERNAL_ERROR)

      IDS(DL_SEC_NOTOKEN)
      IDS(DL_SEC_INVALIDSESSION)
      IDS(DL_SEC_INVALIDTOKENCONTENT)
      IDS(DL_SEC_UNAUTHORIZED)
      IDS(DL_SEC_PAYMENT_REQUIRED)

      default: return("unknown");
    }
  }
};

//! Return whether status code is an error status code
//! @param[in]  status     Status code
//! @return true if status code is an error status code
inline bool STATUS_FAILED(DlResult status)
{
  return (static_cast<uint32_t>(status.value) & (1 << 31));
}

//! Return whether status code is a successfull status code
//! @param[in]  status     Status code
//! @return true if status code is a successfull status code
inline bool STATUS_SUCCEEDED(DlResult status)
{
  return !STATUS_FAILED(status);
}

#if defined(_MSC_VER)
//! @brief save string cat (will not overwrite the destination)
//! @param[in]   dest pointer to the null-terminated byte string to append to
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   destSize the size of the destination buffer
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX).
inline int32_t stringcat_s(char* dest, size_t destSize, const char* src)
{
  return strncat_s(dest, destSize, src, _TRUNCATE);
}

//! @brief save string copy (will not overwrite the destination)
//! @param[in]   dest pointer to the character array to copy to
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   copyCount  maximum number of characters to copy
//! @param[in]   destSize the size of the destination buffer 
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX) and may clobber the rest of the destination array with unspecified values.
inline int32_t stringcpy_s(char* dest, size_t destSize, const char* src, size_t copyCount)
{
  return strncpy_s(dest, destSize, src, copyCount);
}
#else
//! @brief save string cat (will not overwrite the destination)
//! @param[in]   dest pointer to the null-terminated byte string to append to
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   destSize the size of the destination buffer
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX).
inline int32_t stringcat_s(char* dest, size_t destSize, const char* src)
{
  strncat(dest, src, destSize - strlen(dest) - 1);
  return 0;
}

//! @brief save string copy (will not overwrite the destination)
//! @param[in]   dest pointer to the character array to copy to
//! @param[in]   destSize the size of the destination buffer 
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   copyCount  maximum number of characters to copy
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX) and may clobber the rest of the destination array with unspecified values.
inline int32_t stringcpy_s(char* dest, size_t destSize, const char* src, size_t copyCount)
{
  if (destSize < (copyCount + 1)) {
    copyCount = destSize;
  }
  strncpy(dest, src, copyCount);
  return 0;
}
#endif // _MSC_VER

}
}
