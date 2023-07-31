#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef void *DLR_VARIANT;
#include "datalayer_facility.h"
  typedef enum DLR_RESULT {
#include "datalayer_error_codes.h"
  }DLR_RESULT;

  typedef enum DLR_VARIANT_TYPE {
    DLR_VARIANT_TYPE_UNKNOWN,            //! unknown data type
    DLR_VARIANT_TYPE_BOOL8,              //! bool 8 bit
    DLR_VARIANT_TYPE_INT8,               //! signed int 8 bit
    DLR_VARIANT_TYPE_UINT8,              //! unsigned int 8 bit
    DLR_VARIANT_TYPE_INT16,              //! signed int 16 bit
    DLR_VARIANT_TYPE_UINT16,             //! unsigned int 16 bit
    DLR_VARIANT_TYPE_INT32,              //! signed int 32 bit
    DLR_VARIANT_TYPE_UINT32,             //! unsigned int 32 bit
    DLR_VARIANT_TYPE_INT64,              //! signed int 64 bit
    DLR_VARIANT_TYPE_UINT64,             //! unsigned int 64 bit
    DLR_VARIANT_TYPE_FLOAT32,            //! float 32 bit
    DLR_VARIANT_TYPE_FLOAT64,            //! float 64 bit
    DLR_VARIANT_TYPE_STRING,             //! string (UTF-8)

    DLR_VARIANT_TYPE_ARRAY_OF_BOOL8,     //! array of bool 8 bit
    DLR_VARIANT_TYPE_ARRAY_OF_INT8,      //! array of signed int 8 bit
    DLR_VARIANT_TYPE_ARRAY_OF_UINT8,     //! array of unsigned int 8 bit
    DLR_VARIANT_TYPE_ARRAY_OF_INT16,     //! array of signed int 16 bit
    DLR_VARIANT_TYPE_ARRAY_OF_UINT16,    //! array of unsigned int 16 bit
    DLR_VARIANT_TYPE_ARRAY_OF_INT32,     //! array of signed int 32 bit
    DLR_VARIANT_TYPE_ARRAY_OF_UINT32,    //! array of unsigned int 32 bit
    DLR_VARIANT_TYPE_ARRAY_OF_INT64,     //! array of signed int 64 bit
    DLR_VARIANT_TYPE_ARRAY_OF_UINT64,    //! array of unsigned int 64 bit
    DLR_VARIANT_TYPE_ARRAY_OF_FLOAT32,   //! array of float 32 bit
    DLR_VARIANT_TYPE_ARRAY_OF_FLOAT64,   //! array of float 64 bit
    DLR_VARIANT_TYPE_ARRAY_OF_STRING,    //! array of string (UTF-8)

    DLR_VARIANT_TYPE_RAW,                //! raw bytes
    DLR_VARIANT_TYPE_FLATBUFFERS,        //! bytes as a complex data type encoded as a flatbuffer
    DLR_VARIANT_TIMESTAMP,               //! timestamp (FILETIME) 64 bit 100ns since 1.1.1601 (UTC)
    DLR_VARIANT_ARRAY_OF_TIMESTAMP,      //! array of timestamp (FILETIME) 64 bit 100ns since 1.1.1601 (UTC)
  }DLR_VARIANT_TYPE;

  const char* DLR_resultToString(DLR_RESULT result);

  //! Creates a variant
  DLR_VARIANT DLR_variantCreate();

  //! Deletes a variant
  //! @param[in] variant     Variant to delete
  void DLR_variantDelete(DLR_VARIANT variant);

  //! Set a bool value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetBOOL8(DLR_VARIANT variant,   const bool value);

  //! Set a int8 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetINT8(DLR_VARIANT variant,    const int8_t value);

  //! Set a uint8 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetUINT8(DLR_VARIANT variant,   const uint8_t value);

  //! Set a int16 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetINT16(DLR_VARIANT variant,   const int16_t value);

  //! Set a uint16 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetUINT16(DLR_VARIANT variant,  const uint16_t value);

  //! Set a int32 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetINT32(DLR_VARIANT variant,   const int32_t value);

  //! Set a uint32 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetUINT32(DLR_VARIANT variant,  const uint32_t value);

  //! Set a int64 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetINT64(DLR_VARIANT variant,   const int64_t value);

  //! Set a uint64 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetUINT64(DLR_VARIANT variant,  const uint64_t value);

  //! Set a uint64 value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetTimestamp(DLR_VARIANT variant, const uint64_t value);

  //! Set a float value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetFLOAT32(DLR_VARIANT variant, const float value);

  //! Set a double value
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetFLOAT64(DLR_VARIANT variant, const double value);

  //! Set a string
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Value to set
  //! @return Status of set value
  DLR_RESULT DLR_variantSetSTRING(DLR_VARIANT variant,  const char* value);

  //! Set an array of bool
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_BOOL8(DLR_VARIANT variant,   const bool* value, const size_t count);

  //! Set an array of int8
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_INT8(DLR_VARIANT variant,    const int8_t* value, const size_t count);

  //! Set an array of uint8
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_UINT8(DLR_VARIANT variant,   const uint8_t* value, const size_t count);

  //! Set an array of int16
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_INT16(DLR_VARIANT variant,   const int16_t* value, const size_t count);

  //! Set an array of uint16
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_UINT16(DLR_VARIANT variant,  const uint16_t* value, const size_t count);

  //! Set an array of int32
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_INT32(DLR_VARIANT variant,   const int32_t* value, const size_t count);

  //! Set an array of uint32
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_UINT32(DLR_VARIANT variant,  const uint32_t* value, const size_t count);

  //! Set an array of int64
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_INT64(DLR_VARIANT variant,   const int64_t* value, const size_t count);

  //! Set an array of uint64
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_UINT64(DLR_VARIANT variant,  const uint64_t* value, const size_t count);

  //! Set an array of float
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_FLOAT32(DLR_VARIANT variant, const float* value, const size_t count);

  //! Set an array of double
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_FLOAT64(DLR_VARIANT variant, const double* value, const size_t count);

  //! Set an array of strings
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_STRING(DLR_VARIANT variant,  const char** value, const size_t count);

  //! Set an array of timestamps
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Array of Values to set
  //! @param[in] count       Count of array values
  //! @return Status of set value
  DLR_RESULT DLR_variantSetARRAY_OF_TIMESTAMP(DLR_VARIANT variant, const uint64_t* value, const size_t count);

  //! Set an flatbuffers
  //! @param[in] variant     Reference to variant
  //! @param[in] value       Pointer to flatbuffers
  //! @param[in] count       Size of flatbuffers
  //! @return Status of set value
  DLR_RESULT DLR_variantSetFlatbuffers(DLR_VARIANT variant, const int8_t* value, const size_t size);

  //! Returns the value of the variant as a bool (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  bool     DLR_variantGetBOOL8(DLR_VARIANT variant);

  //! Returns the value of the variant as a int8 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  int8_t   DLR_variantGetINT8(DLR_VARIANT variant);

  //! Returns the value of the variant as a uint8 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  uint8_t  DLR_variantGetUINT8(DLR_VARIANT variant);

  //! Returns the value of the variant as a int16 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  int16_t  DLR_variantGetINT16(DLR_VARIANT variant);

  //! Returns the value of the variant as a uint16 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  uint16_t DLR_variantGetUINT16(DLR_VARIANT variant);

  //! Returns the value of the variant as a int32 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  int32_t  DLR_variantGetINT32(DLR_VARIANT variant);

  //! Returns the value of the variant as a uint32 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  uint32_t DLR_variantGetUINT32(DLR_VARIANT variant);

  //! Returns the value of the variant as a int64 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  int64_t  DLR_variantGetINT64(DLR_VARIANT variant);

  //! Returns the value of the variant as a uint64 (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  uint64_t DLR_variantGetUINT64(DLR_VARIANT variant);

  //! Returns the value of the variant as a float (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  float    DLR_variantGetFLOAT32(DLR_VARIANT variant);

  //! Returns the value of the variant as a double (auto convert if possible) otherwise 0
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  double   DLR_variantGetFLOAT64(DLR_VARIANT variant);

  //! Returns the value of the variant as a string otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const char* DLR_variantGetSTRING(DLR_VARIANT variant);

  //! Returns the array of bool8 if the type is a array of bool otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const bool*      DLR_variantGetArrayOfBOOL8(DLR_VARIANT variant);

  //! Returns the array of int8 if the type is a array of int8 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const int8_t*    DLR_variantGetArrayOfINT8(DLR_VARIANT variant);

  //! Returns the array of uint8 if the type is a array of uint8 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const uint8_t*   DLR_variantGetArrayOfUINT8(DLR_VARIANT variant);

  //! Returns the array of int16 if the type is a array of int16 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const int16_t*   DLR_variantGetArrayOfINT16(DLR_VARIANT variant);

  //! Returns the array of uint16 if the type is a array of uint16 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const uint16_t*  DLR_variantGetArrayOfUINT16(DLR_VARIANT variant);

  //! Returns the array of int32 if the type is a array of int32 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const int32_t*   DLR_variantGetArrayOfINT32(DLR_VARIANT variant);

  //! Returns the array of uint32 if the type is a array of uint32 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const uint32_t*  DLR_variantGetArrayOfUINT32(DLR_VARIANT variant);

  //! Returns the array of int64 if the type is a array of int64 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const int64_t*   DLR_variantGetArrayOfINT64(DLR_VARIANT variant);

  //! Returns the array of uint64 if the type is a array of uint64 otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const uint64_t*  DLR_variantGetArrayOfUINT64(DLR_VARIANT variant);

  //! Returns the array of float if the type is a array of float otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const float*     DLR_variantGetArrayOfFLOAT32(DLR_VARIANT variant);

  //! Returns the array of double if the type is a array of double otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const double*    DLR_variantGetArrayOfFLOAT64(DLR_VARIANT variant);

  //! Returns the array of string if the type is a array of string otherwise null
  //! @param[in] variant     Reference to variant
  //! @return Value of the variant
  const char**     DLR_variantGetArrayOfSTRING(DLR_VARIANT variant);

  //! Returns the type of the variant
  //! @param[in] variant     Reference to variant
  //! @return Type of the variant
  DLR_VARIANT_TYPE DLR_variantGetType(DLR_VARIANT variant);

  //! Returns the pointer to the data of the variant
  //! @param[in] variant     Reference to variant
  //! @return Pointer to the data of the variant
  uint8_t* DLR_variantGetData(DLR_VARIANT variant);

  //! Returns the size in bytes of the variant
  //! @param[in] variant     Reference to variant
  //! @return Size in bytes of the variant
  size_t DLR_variantGetSize(DLR_VARIANT variant);

  //! Returns the count of elements in the variant (scalar data types = 1, array = count of elements in array)
  //! @param[in] variant     Reference to variant
  //! @return Size in bytes of the variant
  size_t DLR_variantGetCount(DLR_VARIANT variant);

  //! Checks whether the variant can be converted to another type
  //! @param[in] variant     Reference to variant
  //! @param[in] type        Destination type
  //! @return Result whether the conversion is possible
  DLR_RESULT DLR_variantCheckConvert(DLR_VARIANT variant, DLR_VARIANT_TYPE type);

  //! Converts value of variant to another type if value is convertable in target type
  //! @param[in]  targetType   Target type
  //! @return Success status of function
  DLR_RESULT DLR_variantConvertTo(DLR_VARIANT variant, DLR_VARIANT_TYPE type);

  //! Copies the content of a variant to another variant
  //! @param[in] dest        Destination variant
  //! @param[in] src         Source variant
  //! @return Result of copy
  DLR_RESULT DLR_variantCopy(DLR_VARIANT dest, DLR_VARIANT src);

  //! Compares two variants
  //! @param[in] var1        Variant 1 to compare
  //! @param[in] var2        Variant 2 to compare
  //! @return Result of compare
  bool DLR_variantEqual(DLR_VARIANT var1, DLR_VARIANT var2);

  //! Get type of a variant as string
  //! @param[in] variant     Variant to get type as string
  //! @return Type of the variant as string
  const char* DLR_getTypeAsString(DLR_VARIANT variant);

  //! Get type  by a string
  //! @param[in] typeName    Name of the type
  //! @return Type of the string
  DLR_VARIANT_TYPE DLR_getTypeByName(const char* typeName);

#ifdef __cplusplus
}
#endif
