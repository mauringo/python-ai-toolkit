#pragma once

#include "datalayer.h"
#include "memory_map_generated.h"

//! Namespace for datalayer
namespace comm {
namespace datalayer {

//! Helper class for providers
class MemoryMapHelper
{
public:
  static bool equalTypes(const std::string type1, VariantType type2)
  {
    bool result = false;
    switch (type2)
    {
      case VariantType::BOOL8:
        if (type1 == TYPE_DL_BOOL8 ||
            type1 == TYPE_PLC_BIT  ||
            type1 == TYPE_PLC_BOOL)
        { result = true; }; break;
      case VariantType::INT8:
        if (type1 == TYPE_DL_INT8 ||
            type1 == TYPE_PLC_SINT)
        { result = true; }; break;
      case VariantType::UINT8:
        if (type1 == TYPE_DL_UINT8 ||
            type1 == TYPE_PLC_BYTE ||
            type1 == TYPE_PLC_USINT)
        { result = true; }; break;
      case VariantType::INT16:
        if (type1 == TYPE_DL_INT16 ||
            type1 == TYPE_PLC_INT)
        { result = true; }; break;
      case VariantType::UINT16:
        if (type1 == TYPE_DL_UINT16 ||
            type1 == TYPE_PLC_WORD ||
            type1 == TYPE_PLC_UINT)
        { result = true; }; break;
      case VariantType::INT32:
        if (type1 == TYPE_DL_INT32 ||
            type1 == TYPE_PLC_DINT)
        { result = true; }; break;
      case VariantType::UINT32:
        if (type1 == TYPE_DL_UINT32 ||
            type1 == TYPE_PLC_DWORD ||
            type1 == TYPE_PLC_UDINT)
        { result = true; }; break;
      case VariantType::INT64:
        if (type1 == TYPE_DL_INT64 ||
            type1 == TYPE_PLC_LINT)
        { result = true; }; break;
      case VariantType::UINT64:
        if (type1 == TYPE_DL_UINT64 ||
            type1 == TYPE_PLC_LWORD ||
            type1 == TYPE_PLC_ULINT)
        { result = true; }; break;
      case VariantType::FLOAT32:
        if (type1 == TYPE_DL_FLOAT32 ||
            type1 == TYPE_PLC_REAL)
        { result = true; }; break;
      case VariantType::FLOAT64:
        if (type1 == TYPE_DL_FLOAT64 ||
            type1 == TYPE_PLC_LREAL)
        { result = true; }; break;
      case VariantType::STRING:
        if (type1 == TYPE_DL_STRING)
        { result = true; }; break;
      case VariantType::TIMESTAMP:
        if (type1 == TYPE_DL_TIMESTAMP)
        { result = true; }; break;

      case VariantType::ARRAY_OF_INT8:
        if (type1 == TYPE_DL_ARRAY_OF_INT8 ||
            type1 == TYPE_PLC_ARRAY_OF_SINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_UINT8:
        if (type1 == TYPE_DL_ARRAY_OF_UINT8 ||
            type1 == TYPE_PLC_ARRAY_OF_BYTE ||
            type1 == TYPE_PLC_ARRAY_OF_USINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_INT16:
        if (type1 == TYPE_DL_ARRAY_OF_INT16 ||
            type1 == TYPE_PLC_ARRAY_OF_INT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_UINT16:
        if (type1 == TYPE_DL_ARRAY_OF_UINT16 ||
            type1 == TYPE_PLC_ARRAY_OF_WORD ||
            type1 == TYPE_PLC_ARRAY_OF_UINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_INT32:
        if (type1 == TYPE_DL_ARRAY_OF_INT32 ||
            type1 == TYPE_PLC_ARRAY_OF_DINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_UINT32:
        if (type1 == TYPE_DL_ARRAY_OF_UINT32 ||
            type1 == TYPE_PLC_ARRAY_OF_DWORD ||
            type1 == TYPE_PLC_ARRAY_OF_UDINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_INT64:
        if (type1 == TYPE_DL_ARRAY_OF_INT64 ||
            type1 == TYPE_PLC_ARRAY_OF_LINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_UINT64:
        if (type1 == TYPE_DL_ARRAY_OF_UINT64 ||
            type1 == TYPE_PLC_ARRAY_OF_LWORD ||
            type1 == TYPE_PLC_ARRAY_OF_ULINT)
        { result = true; }; break;
      case VariantType::ARRAY_OF_FLOAT32:
        if (type1 == TYPE_DL_ARRAY_OF_FLOAT32 ||
            type1 == TYPE_PLC_ARRAY_OF_REAL)
        { result = true; }; break;
      case VariantType::ARRAY_OF_FLOAT64:
        if (type1 == TYPE_DL_ARRAY_OF_FLOAT64 ||
            type1 == TYPE_PLC_ARRAY_OF_LREAL)
        { result = true; }; break;
      case VariantType::ARRAY_OF_STRING:
        if (type1 == TYPE_DL_ARRAY_OF_STRING)
        { result = true; }; break;
      case VariantType::ARRAY_OF_TIMESTAMP:
        if (type1 == TYPE_DL_ARRAY_OF_TIMESTAMP)
        { result = true; }; break;

      default:
        break;
    }
    return result;
  }

  static VariantType toVariantType(std::string type)
  {
    VariantType result = VariantType::UNKNOWN;
    
    if (type == TYPE_DL_BOOL8) { result = VariantType::BOOL8; return result; }
    if (type == TYPE_DL_INT8) { result = VariantType::INT8; return result; }
    if (type == TYPE_DL_UINT8) { result = VariantType::UINT8; return result; }
    if (type == TYPE_DL_INT16) { result = VariantType::INT16; return result; }
    if (type == TYPE_DL_UINT16) { result = VariantType::UINT16; return result; }
    if (type == TYPE_DL_INT32) { result = VariantType::INT32; return result; }
    if (type == TYPE_DL_UINT32) { result = VariantType::UINT32; return result; }
    if (type == TYPE_DL_INT64) { result = VariantType::INT64; return result; }
    if (type == TYPE_DL_UINT64)  { result = VariantType::UINT64; return result; }
    if (type == TYPE_DL_FLOAT32) { result = VariantType::FLOAT32; return result; }
    if (type == TYPE_DL_FLOAT64) { result = VariantType::FLOAT64; return result; }
    
    if (type == TYPE_DL_STRING) { result = VariantType::STRING; return result; }
    if (type == TYPE_DL_ARRAY_OF_BOOL8) { result = VariantType::ARRAY_OF_BOOL8; return result; }
    if (type == TYPE_DL_ARRAY_OF_INT8) { result = VariantType::ARRAY_OF_INT8; return result; }
    if (type == TYPE_DL_ARRAY_OF_UINT8) { result = VariantType::ARRAY_OF_UINT8; return result; }
    if (type == TYPE_DL_ARRAY_OF_INT16) { result = VariantType::ARRAY_OF_INT16; return result; }
    if (type == TYPE_DL_ARRAY_OF_UINT16) { result = VariantType::ARRAY_OF_UINT16; return result; }
    if (type == TYPE_DL_ARRAY_OF_INT32) { result = VariantType::ARRAY_OF_INT32; return result; }
    if (type == TYPE_DL_ARRAY_OF_UINT32) { result = VariantType::ARRAY_OF_UINT32; return result; }
    if (type == TYPE_DL_ARRAY_OF_INT64) { result = VariantType::ARRAY_OF_INT64; return result; }
    if (type == TYPE_DL_ARRAY_OF_UINT64) { result = VariantType::ARRAY_OF_UINT64; return result; }
    if (type == TYPE_DL_ARRAY_OF_FLOAT32) { result = VariantType::ARRAY_OF_FLOAT32; return result; }
    if (type == TYPE_DL_ARRAY_OF_FLOAT64) { result = VariantType::ARRAY_OF_FLOAT64; return result; }
    if (type == TYPE_DL_ARRAY_OF_STRING)  { result = VariantType::ARRAY_OF_STRING; return result; }
    if (type == TYPE_DL_RAW) { result = VariantType::RAW; return result; }
    if (type == TYPE_DL_TIMESTAMP)  { result = VariantType::TIMESTAMP; return result; }
    if (type == TYPE_DL_ARRAY_OF_TIMESTAMP)  { result = VariantType::ARRAY_OF_TIMESTAMP; return result; }

    if (type == TYPE_PLC_BIT) { result = VariantType::BOOL8; return result; }
    if (type == TYPE_PLC_BOOL) { result = VariantType::BOOL8; return result; }
    if (type == TYPE_PLC_BYTE) { result = VariantType::UINT8; return result; }
    if (type == TYPE_PLC_WORD) { result = VariantType::UINT16; return result; }
    if (type == TYPE_PLC_DWORD) { result = VariantType::UINT32; return result; }
    if (type == TYPE_PLC_LWORD) { result = VariantType::UINT64; return result; }
    if (type == TYPE_PLC_SINT) { result = VariantType::INT8; return result; }
    if (type == TYPE_PLC_USINT) { result = VariantType::UINT8; return result; }
    if (type == TYPE_PLC_INT) { result = VariantType::INT16; return result; }
    if (type == TYPE_PLC_UINT) { result = VariantType::UINT16; return result; }
    if (type == TYPE_PLC_DINT) { result = VariantType::INT32; return result; }
    if (type == TYPE_PLC_UDINT) { result = VariantType::UINT32; return result; }
    if (type == TYPE_PLC_LINT) { result = VariantType::INT64; return result; }
    if (type == TYPE_PLC_ULINT) { result = VariantType::UINT64; return result; }
    if (type == TYPE_PLC_REAL) { result = VariantType::FLOAT32; return result; }
    if (type == TYPE_PLC_LREAL) { result = VariantType::FLOAT64; return result; }
    if (type == TYPE_PLC_STRING) { result = VariantType::STRING; return result; }
    if (type == TYPE_PLC_WSTRING) { result = VariantType::RAW; return result; }
    if (type == TYPE_PLC_TIME) { result = VariantType::RAW; return result; }
    if (type == TYPE_PLC_TIME_OF_DAY) { result = VariantType::RAW; return result; }
    if (type == TYPE_PLC_DATE) { result = VariantType::RAW; return result; }
    if (type == TYPE_PLC_DATE_AND_TIME) { result = VariantType::RAW; return result; }
    if (type == TYPE_PLC_LTIME) { result = VariantType::RAW; return result; }

    if (type == TYPE_PLC_ARRAY_OF_BYTE)  { result = VariantType::ARRAY_OF_UINT8; return result; }
    if (type == TYPE_PLC_ARRAY_OF_WORD)  { result = VariantType::ARRAY_OF_UINT16; return result; }
    if (type == TYPE_PLC_ARRAY_OF_DWORD) { result = VariantType::ARRAY_OF_UINT32; return result; }
    if (type == TYPE_PLC_ARRAY_OF_LWORD) { result = VariantType::ARRAY_OF_UINT64; return result; }
    if (type == TYPE_PLC_ARRAY_OF_SINT)  { result = VariantType::ARRAY_OF_INT8; return result; }
    if (type == TYPE_PLC_ARRAY_OF_USINT) { result = VariantType::ARRAY_OF_UINT8; return result; }
    if (type == TYPE_PLC_ARRAY_OF_INT)   { result = VariantType::ARRAY_OF_INT16; return result; }
    if (type == TYPE_PLC_ARRAY_OF_UINT)  { result = VariantType::ARRAY_OF_UINT16; return result; }
    if (type == TYPE_PLC_ARRAY_OF_DINT)  { result = VariantType::ARRAY_OF_INT32; return result; }
    if (type == TYPE_PLC_ARRAY_OF_UDINT) { result = VariantType::ARRAY_OF_UINT32; return result; }
    if (type == TYPE_PLC_ARRAY_OF_LINT)  { result = VariantType::ARRAY_OF_INT64; return result; }
    if (type == TYPE_PLC_ARRAY_OF_ULINT) { result = VariantType::ARRAY_OF_UINT64; return result; }
    if (type == TYPE_PLC_ARRAY_OF_REAL)  { result = VariantType::ARRAY_OF_FLOAT32; return result; }
    if (type == TYPE_PLC_ARRAY_OF_LREAL) { result = VariantType::ARRAY_OF_FLOAT64; return result; }

    return result;
  }

};

}
}
