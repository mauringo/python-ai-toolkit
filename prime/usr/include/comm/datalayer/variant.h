#pragma once

#include "flatbuffers/flatbuffers.h"
#include "datalayer_defs.h"
#include <cmath>

//! Namespace for datalayer
namespace comm {
namespace datalayer {

//! Types for Variant
typedef enum class VariantType {
  UNKNOWN,            //! unknown data type
  BOOL8,              //! bool 8 bit
  INT8,               //! signed int 8 bit
  UINT8,              //! unsigned int 8 bit
  INT16,              //! signed int 16 bit
  UINT16,             //! unsigned int 16 bit
  INT32,              //! signed int 32 bit
  UINT32,             //! unsigned int 32 bit
  INT64,              //! signed int 64 bit
  UINT64,             //! unsigned int 64 bit
  FLOAT32,            //! float 32 bit
  FLOAT64,            //! float 64 bit
  STRING,             //! string (UTF-8)

  ARRAY_OF_BOOL8,     //! array of bool 8 bit
  ARRAY_OF_INT8,      //! array of signed int 8 bit
  ARRAY_OF_UINT8,     //! array of unsigned int 8 bit
  ARRAY_OF_INT16,     //! array of signed int 16 bit
  ARRAY_OF_UINT16,    //! array of unsigned int 16 bit
  ARRAY_OF_INT32,     //! array of signed int 32 bit
  ARRAY_OF_UINT32,    //! array of unsigned int 32 bit
  ARRAY_OF_INT64,     //! array of signed int 64 bit
  ARRAY_OF_UINT64,    //! array of unsigned int 64 bit
  ARRAY_OF_FLOAT32,   //! array of float 32 bit
  ARRAY_OF_FLOAT64,   //! array of float 64 bit
  ARRAY_OF_STRING,    //! array of string (UTF-8)
  
  RAW,                //! raw bytes
  FLATBUFFERS,        //! bytes as a complex data type encoded as a flatbuffer
  TIMESTAMP,          //! timestamp (FILETIME) 64 bit 100ns since 1.1.1601 (UTC)
  ARRAY_OF_TIMESTAMP, //! array of timestamp (FILETIME) 64 bit 100ns since 1.1.1601 (UTC)
}VariantType;

constexpr auto DATALAYER_TYPE_BASE_ADDRESS = "types/datalayer/";

constexpr auto DATALAYER_TYPE_UNKNOWN = "unknown";
constexpr auto DATALAYER_TYPE_BOOL8 = "bool8";
constexpr auto DATALAYER_TYPE_INT8 = "int8";
constexpr auto DATALAYER_TYPE_UINT8 = "uint8";
constexpr auto DATALAYER_TYPE_INT16 = "int16";
constexpr auto DATALAYER_TYPE_UINT16 = "uint16";
constexpr auto DATALAYER_TYPE_INT32 = "int32";
constexpr auto DATALAYER_TYPE_UINT32 = "uint32";
constexpr auto DATALAYER_TYPE_INT64 = "int64";
constexpr auto DATALAYER_TYPE_UINT64 = "uint64";
constexpr auto DATALAYER_TYPE_FLOAT = "float";
constexpr auto DATALAYER_TYPE_DOUBLE = "double";
constexpr auto DATALAYER_TYPE_FLOAT32 = "float32";
constexpr auto DATALAYER_TYPE_FLOAT64 = "float64";
constexpr auto DATALAYER_TYPE_STRING = "string";
constexpr auto DATALAYER_TYPE_ARBOOL8 = "arbool8";
constexpr auto DATALAYER_TYPE_ARIN8 = "arint8";
constexpr auto DATALAYER_TYPE_ARUINT8 = "aruint8";
constexpr auto DATALAYER_TYPE_ARINT16 = "arint16";
constexpr auto DATALAYER_TYPE_ARUINT16 = "aruint16";
constexpr auto DATALAYER_TYPE_ARINT32 = "arint32";
constexpr auto DATALAYER_TYPE_ARUINT32 = "aruint32";
constexpr auto DATALAYER_TYPE_ARINT64 = "arint64";
constexpr auto DATALAYER_TYPE_ARUINT64 = "aruint64";
constexpr auto DATALAYER_TYPE_ARFLOAT = "arfloat";
constexpr auto DATALAYER_TYPE_ARDOUBLE = "ardouble";
constexpr auto DATALAYER_TYPE_ARFLOAT32 = "arfloat32";
constexpr auto DATALAYER_TYPE_ARFLOAT64 = "arfloat64";
constexpr auto DATALAYER_TYPE_ARSTRING = "arstring";
constexpr auto DATALAYER_TYPE_RAW = "raw";
constexpr auto DATALAYER_TYPE_FLATBUFFERS = "flatbuffers";
constexpr auto DATALAYER_TYPE_TIMESTAMP = "timestamp";
constexpr auto DATALAYER_TYPE_ARTIMESTAMP = "artimestamp";

//! Complex data type based on flatbuffer
typedef struct TBuffer
{
  uint8_t* buffer; // buffer
  size_t size;     // size of buffer in bytes
} TBuffer;

//! Union for all data
typedef union UVariantUnion
{
  // Scalar data value
  bool b8;
  uint8_t ui8;
  int8_t i8;
  uint16_t ui16;
  int16_t i16;
  uint32_t ui32;
  int32_t i32;
  uint64_t ui64;
  int64_t i64;
  float f;
  double d;

  TBuffer buffer;
  TBuffer raw;
} UVariantUnion;

//! Is type a simple data type
//! @param[in]  type     Type to check
//! @return true if type is a simple data type
inline bool isSimpleType(VariantType type) { return (((type >= VariantType::BOOL8) && (type <= VariantType::STRING)) || type == VariantType::TIMESTAMP); }

//! Is type an array data type
//! @param[in]  type     Type to check
//! @return true if type is an array data type
inline bool isArrayType(VariantType type) { return (((type >= VariantType::ARRAY_OF_BOOL8) && (type <= VariantType::ARRAY_OF_STRING)) || type == VariantType::ARRAY_OF_TIMESTAMP); }

//! Is type a buffer data type
//! @param[in]  type     Type to check
//! @return true if type is a buffer data type
inline bool isBufferType(VariantType type) { return ((type == VariantType::FLATBUFFERS) || (type == VariantType::STRING) || (type == VariantType::RAW) || isArrayType(type)); }

//! Get VariantType out of C data type
//! @tparam T   C data type
//! @return VarantType of C data type
template <typename T> VariantType getVariantTypeID() { return VariantType::UNKNOWN; }
template <> inline VariantType getVariantTypeID<bool>() { return VariantType::BOOL8; }
template <> inline VariantType getVariantTypeID<int8_t>() { return VariantType::INT8; }
template <> inline VariantType getVariantTypeID<uint8_t>() { return VariantType::UINT8; }
template <> inline VariantType getVariantTypeID<int16_t>() { return VariantType::INT16; }
template <> inline VariantType getVariantTypeID<uint16_t>() { return VariantType::UINT16; }
template <> inline VariantType getVariantTypeID<int32_t>() { return VariantType::INT32; }
template <> inline VariantType getVariantTypeID<uint32_t>() { return VariantType::UINT32; }
template <> inline VariantType getVariantTypeID<int64_t>() { return VariantType::INT64; }
template <> inline VariantType getVariantTypeID<uint64_t>() { return VariantType::UINT64; }
template <> inline VariantType getVariantTypeID<float>() { return VariantType::FLOAT32; }
template <> inline VariantType getVariantTypeID<double>() { return VariantType::FLOAT64; }

template <> inline VariantType getVariantTypeID<bool*>() { return VariantType::ARRAY_OF_BOOL8; }
template <> inline VariantType getVariantTypeID<int8_t*>() { return VariantType::ARRAY_OF_INT8; }
template <> inline VariantType getVariantTypeID<uint8_t*>() { return VariantType::ARRAY_OF_UINT8; }
template <> inline VariantType getVariantTypeID<int16_t*>() { return VariantType::ARRAY_OF_INT16; }
template <> inline VariantType getVariantTypeID<uint16_t*>() { return VariantType::ARRAY_OF_UINT16; }
template <> inline VariantType getVariantTypeID<int32_t*>() { return VariantType::ARRAY_OF_INT32; }
template <> inline VariantType getVariantTypeID<uint32_t*>() { return VariantType::ARRAY_OF_UINT32; }
template <> inline VariantType getVariantTypeID<int64_t*>() { return VariantType::ARRAY_OF_INT64; }
template <> inline VariantType getVariantTypeID<uint64_t*>() { return VariantType::ARRAY_OF_UINT64; }
template <> inline VariantType getVariantTypeID<float*>() { return VariantType::ARRAY_OF_FLOAT32; }
template <> inline VariantType getVariantTypeID<double*>() { return VariantType::ARRAY_OF_FLOAT64; }

template <> inline VariantType getVariantTypeID<char*>() { return VariantType::STRING; }
template <> inline VariantType getVariantTypeID<const char*>() { return VariantType::STRING; }
template <> inline VariantType getVariantTypeID<std::string>() { return VariantType::STRING; }
template <> inline VariantType getVariantTypeID<const std::string>() { return VariantType::STRING; }

template <> inline VariantType getVariantTypeID<char**>() { return VariantType::ARRAY_OF_STRING; }
template <> inline VariantType getVariantTypeID<const char**>() { return VariantType::ARRAY_OF_STRING; }

inline VariantType getBaseTypeFromArrayType(VariantType arrayType)
{
  VariantType result;
  switch (arrayType)
  {
    case ::comm::datalayer::VariantType::ARRAY_OF_BOOL8:
      result = VariantType::BOOL8;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_INT8:
      result = VariantType::INT8;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_UINT8:
      result = VariantType::UINT8;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_INT16:
      result = VariantType::INT16;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_UINT16:
      result = VariantType::UINT16;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_INT32:
      result = VariantType::INT32;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_UINT32:
      result = VariantType::UINT32;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_INT64:
      result = VariantType::INT64;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_UINT64:
      result = VariantType::UINT64;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_FLOAT32:
      result = VariantType::FLOAT32;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_FLOAT64:
      result = VariantType::FLOAT64;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_STRING:
      result = VariantType::STRING;
      break;
    case ::comm::datalayer::VariantType::ARRAY_OF_TIMESTAMP:
      result = VariantType::TIMESTAMP;
      break;
    default:
      result = VariantType::UNKNOWN;
      break;
  }
  return result;
}

//! Get length of data in bytes
//! @tparam T   C data type
//! @return Length of data in bytes
template <typename T> inline size_t getDataLength(const T value) { return sizeof(value); }
template <> inline size_t getDataLength<char*>(char* value) { return strlen(value) + 1; }
template <> inline size_t getDataLength<const char*>(const char* value) { return strlen(value) + 1; }
template <> inline size_t getDataLength<std::string>(const std::string value) { return value.length() + 1; }
template <> inline size_t getDataLength<const std::string>(const std::string value) { return value.length() + 1; }

//! copy a value to Variant union
//! @tparam     T       C data type
//! @param[in]  dest    Destination of copy
//! @param[in]  source  Source for copy
//! @param[in]  size    size to copy
//! @return Length of data in bytes
template <typename T> inline void copyValue(UVariantUnion &dest, const T source, size_t size) { memcpy(&dest, &source, size); }
template <> inline void copyValue<char*>(UVariantUnion &dest, char* source, size_t size) { memcpy(dest.buffer.buffer, source, size); }
template <> inline void copyValue<const char*>(UVariantUnion &dest, const char* source, size_t size) { memcpy(dest.buffer.buffer, source, size); }
template <> inline void copyValue<std::string>(UVariantUnion &dest, const std::string source, size_t size) { memcpy(dest.buffer.buffer, source.c_str(), size); }
template <> inline void copyValue<const std::string>(UVariantUnion &dest, const std::string source, size_t size) { memcpy(dest.buffer.buffer, source.c_str(), size); }

//! Type to hold a data with a variant type
class Variant final {
public:

  //! constructor
  Variant()
  {
    memset(&m_value, 0, sizeof(m_value));
  }

  //! copy constructor
  Variant(const Variant& other)
  {
    *this = other;
  }

  //! destructor
  ~Variant()
  {
    setType(VariantType::UNKNOWN);
    m_strArray = nullptr;
  }

  //! copy assignment operator
  Variant& operator=(const Variant& other)
  {
    if (this != &other) {
      setType(other.getType(), other.getSize());
      if (isBufferType(m_type)) {
        memcpy(m_value.buffer.buffer, other.m_value.buffer.buffer, m_value.buffer.size);
      }
      else {
        memcpy(&m_value, &other.m_value, 8);
      }

      buildStringArray();
    }
    return *this;
  }

  typedef std::function<void(uint8_t*, size_t)> CopyFunction;
  DlResult setValue(CopyFunction &copy, size_t size)
  {
    setType(VariantType::ARRAY_OF_UINT8, size);
    copy(m_value.buffer.buffer, size);
    return DlResult::DL_OK;
  }

  //! Set a vector of strings to this variant
  //! @param[in]  setValue    Set of strings to set
  //! @return Success status of function
  DlResult setValue(const std::set<std::string> &setValue)
  {
    size_t dataSize = 0;
    for (auto value = setValue.begin(); value != setValue.end(); value++) {
      dataSize += strlen(value->c_str()) + 1;
    }

    setType(VariantType::ARRAY_OF_STRING, dataSize);

    m_strArrayCount = setValue.size();
    if (m_strArrayCount == 0) {
      return DlResult::DL_OK;
    }
    m_strArray = new char*[m_strArrayCount];

    char* buffer = reinterpret_cast<char*>(m_value.buffer.buffer);
    size_t count = 0;
    size_t buffersize = m_value.buffer.size;
    for (auto value = setValue.begin(); value != setValue.end(); value++)
    {
      *buffer = 0;
      stringcat_s(buffer, buffersize, value->c_str());
      m_strArray[count] = buffer;
      buffer += strlen(value->c_str()) + 1;
      buffersize -= strlen(value->c_str()) + 1;
      count++;
    }
    return DlResult::DL_OK;
  }

  //! Set a vector of strings to this variant
  //! @param[in]  setValue    Vector of strings to set
  //! @return Success status of function
  DlResult setValue(const std::vector<std::string> &setValue)
  {

    size_t dataSize = 0;
    for (auto value = setValue.begin(); value != setValue.end(); value++) {
      dataSize += strlen(value->c_str()) + 1;
    }

    setType(VariantType::ARRAY_OF_STRING, dataSize);

    m_strArrayCount = setValue.size();
    if (m_strArrayCount == 0) {
      return DlResult::DL_OK;
    }
    m_strArray = new char*[m_strArrayCount];

    char* buffer = reinterpret_cast<char*>(m_value.buffer.buffer);
    size_t count = 0;
    size_t buffersize = m_value.buffer.size;
    for (auto value = setValue.begin(); value != setValue.end(); value++)
    {
      *buffer = 0;
      stringcat_s(buffer, buffersize, value->c_str());
      m_strArray[count] = buffer;
      buffer += strlen(value->c_str()) + 1;
      buffersize -= strlen(value->c_str()) + 1;
      count++;
    }
    return DlResult::DL_OK;
  }

  //! Set a value to this variant
  //! @tparam     T           Type of setValue
  //! @param[in]  setValue    Value to set
  //! @return Success status of function
  template <typename T> DlResult setValue(const T setValue)
  {
    VariantType type = getVariantTypeID<T>();
    size_t dataSize = getDataLength<T>(setValue);
    setType(type, dataSize);
    copyValue<T>(m_value, setValue, dataSize);

    return DlResult::DL_OK;
  }

  //! Set a vector of values to this variant
  //! @tparam     T           Type of each vector entry values
  //! @param[in]  values      Values to set
  //! @return Success status of function
  template <typename T> DlResult setValue(const std::vector <T> &values)
  {
    VariantType type = getVariantTypeID<T*>();
    size_t dataSize = sizeof(T);
    setType(type, dataSize * values.size());
    T* tmp = reinterpret_cast<T*>(m_value.buffer.buffer);
    for (size_t i = 0; i < values.size(); i++) {
      tmp[i] = values[i];
    }
    return DlResult::DL_OK;
  }

  //! Set an array of values to this variant
  //! @tparam     T           Type of each array entry values
  //! @param[in]  arrayValue  Array of values
  //! @param[in]  count       Count of values in arrayValues
  //! @return Success status of function
  template <typename T> DlResult setValue(const T* arrayValue, size_t count)
  {
    VariantType type = getVariantTypeID<T*>();
    size_t dataSize = sizeof(T);
    setType(type, dataSize * count);
    memcpy(m_value.buffer.buffer, reinterpret_cast<const void*>(arrayValue), m_value.buffer.size);
    return DlResult::DL_OK;
  }

  template <typename T, size_t _Size>
  DlResult setValue(const T(&arrayValue)[_Size])
  {
    VariantType type = getVariantTypeID<T*>();
    if (type == VariantType::STRING)
    {
      const char* value = reinterpret_cast<const char*>(arrayValue);
      return setValue(value);
    }
    if (!isArrayType(type))
    {
      return DlResult::DL_TYPE_MISMATCH;
    }
    size_t dataSize = getDataLength<T>(*arrayValue);
    setType(type, dataSize * _Size);
    memcpy(m_value.buffer.buffer, reinterpret_cast<const void*>(arrayValue), m_value.buffer.size);
    return DlResult::DL_OK;
  }

  //! Set a array of strings to this variant
  //! @param[in]  arrayValue  Array of strings
  //! @param[in]  count       Count of values in arrayValues
  //! @return Success status of function
  DlResult setValue(const char** arrayValue, size_t count)
  {
    size_t dataSize = 0;
    for (size_t i = 0; i < count; i++) {
      dataSize += strlen(arrayValue[i]) + 1;
    }

    setType(VariantType::ARRAY_OF_STRING, dataSize);

    m_strArrayCount = count;
    if (m_strArrayCount == 0) {
      return DlResult::DL_OK;
    }
    m_strArray = new char*[m_strArrayCount];

    char* buffer = reinterpret_cast<char*>(m_value.buffer.buffer);
    *buffer = 0;
    size_t buffersize = m_value.buffer.size;
    for (size_t i = 0; i < count; i++)
    {
      *buffer = 0;
      stringcat_s(buffer, buffersize, arrayValue[i]);
      m_strArray[i] = buffer;
      buffer += strlen(arrayValue[i]) + 1;
      buffersize -= strlen(arrayValue[i]) + 1;
    }
    return DlResult::DL_OK;
  }

  DlResult setTimestamp(const uint64_t timestamp)
  {
    setType(VariantType::TIMESTAMP, 8);
    m_value.ui64 = timestamp;
    return DlResult::DL_OK;
  }

  DlResult setTimestamp(const uint64_t* timestamp, const size_t count)
  {
    auto size = sizeof(uint64_t) * count;
    setType(VariantType::ARRAY_OF_TIMESTAMP, size);
    memcpy(m_value.buffer.buffer, timestamp, size);
    return DlResult::DL_OK;
  }

  DlResult setTimestamp(const std::vector <uint64_t>& values)
  {
    setType(VariantType::ARRAY_OF_TIMESTAMP, sizeof(uint64_t) * values.size());
    uint64_t* tmp = reinterpret_cast<uint64_t*>(m_value.buffer.buffer);
    for (size_t i = 0; i < values.size(); i++)
    {
      tmp[i] = values[i];
    }
    return DlResult::DL_OK;
  }

  //! Set a array of values to this variant. Data will not be copied. It will hold as a reference.
  //! @param[in]  arrayValue  Array of values
  //! @param[in]  count       Count of values in arrayValue
  //! @return Success status of function
  template <typename T> DlResult shareValue(T* arrayValue, size_t count)
  {
    setSharedPointer(getVariantTypeID<T*>(), reinterpret_cast<uint8_t*>(arrayValue), count * getDataLength<T>(*arrayValue));
    return DlResult::DL_OK;
  }

  //! Set a flatbuffers to this variant
  //! @param[in]  builder     Builder of the flatbuffers
  //! @return Success status of function
  DlResult copyFlatbuffers(flatbuffers::FlatBufferBuilder &builder)
  {
    setType(VariantType::FLATBUFFERS, builder.GetSize());
    if (builder.GetSize() > m_value.buffer.size) {
      return DlResult::DL_SIZE_MISMATCH;
    }

    memcpy(m_value.buffer.buffer, builder.GetBufferPointer(), builder.GetSize());

    return DlResult::DL_OK;
  }

  //! Set a flatbuffers to this variant. Data will not be copied. It will hold as a reference.
  //! @param[in]  builder     Builder of the flatbuffers
  //! @return Success status of function
  DlResult shareFlatbuffers(flatbuffers::FlatBufferBuilder &builder)
  {
    setSharedPointer(VariantType::FLATBUFFERS, builder.GetBufferPointer(), builder.GetSize());
    return DlResult::DL_OK;
  }

  //! Set a raw bytes to this variant. 
  //! @param[in]  data        Data to set to the variant
  //! @param[in]  size        Size of data
  //! @return Success status of function
  DlResult copyRaw(const uint8_t* data, size_t size)
  {
    if (size > m_value.buffer.size) {
      return DlResult::DL_SIZE_MISMATCH;
    }
    memcpy(m_value.buffer.buffer, data, size);
    buildStringArray();

    return DlResult::DL_OK;
  }

  //! Verifys this variant against a flatbuffers verifier
  //! @param[in]  verify    Flatbuffer verifier
  //! @return Success status of function
  DlResult verifyFlatbuffers(bool(*verify)(flatbuffers::Verifier &verifier)) const
  {
    if (m_type != VariantType::FLATBUFFERS) {
      return DlResult::DL_TYPE_MISMATCH;
    }

    // First, verify the buffers integrity (optional)
    flatbuffers::Verifier verifier(m_value.buffer.buffer, m_value.buffer.size);
    if (!verify(verifier)) {
      return DlResult::DL_TYPE_MISMATCH;
    }

    return DlResult::DL_OK;
  }

  //! Set an value by a data and size
  //! @param[in]  type        Type of data to set
  //! @param[in]  data        Data to set
  //! @param[in]  size        size of data in byte
  //! @return Success status of function
  DlResult setSharedPointer(VariantType type, uint8_t* data, size_t size = 0)
  {
    if (!isBufferType(type)) {
      return DlResult::DL_TYPE_MISMATCH;
    }

    setType(type);

    m_type = type;
    m_boShared = true;
    m_value.buffer.buffer = data;
    m_value.buffer.size = size;
    buildStringArray();
    return DlResult::DL_OK;
  }

  //! Set type and size of this variant. Value will be zeroed.
  //! @param[in]  type        Type of data to set
  //! @param[in]  size        size of data in byte
  //! @return Success status of function
  DlResult setType(VariantType type, size_t size = 0)
  {
    if (isBufferType(m_type) && !m_boShared)
    {
      delete[] m_value.buffer.buffer;
    }
    m_value.buffer.buffer = nullptr;
    m_value.buffer.size = 0;
    m_boShared = false;
    delete[] m_strArray; m_strArray = nullptr;
    m_type = type;
    if (isBufferType(m_type) & (size > 0))
    {
      m_value.buffer.buffer = new uint8_t[size];
      m_value.buffer.size = size;
      memset(m_value.buffer.buffer, 0, m_value.buffer.size);
    }
    return DlResult::DL_OK;
  }

  //! Get type of variant
  //! @return Type of variant
  VariantType getType() const
  {
    return m_type;
  }

  //! Get serialized size of variant.
  //! @param[in]  type        Type of data to set
  //! @param[in]  size        size of data in byte
  //! @return Success status of function
  size_t getSerializeSize() const
  {
    if (isBufferType(m_type))
    {
      return sizeof(m_type) + m_value.buffer.size;
    }
    else
    {
      return sizeof(m_type) + sizeof(m_value.d);
    }
  }

  //! Get serialized variant.
  //! @param[in]  buffer      Buffer to serialize data to
  //! @param[in]  size        Size of buffer
  //! @return Success status of function
  DlResult serialize(uint8_t* buffer, size_t size) const
  {
    if (size < getSerializeSize()) {
      return DlResult::DL_SIZE_MISMATCH;
    }

    *reinterpret_cast<VariantType*>(buffer) = m_type;
    buffer += sizeof(m_type);
    if (isBufferType(m_type))
    {
      memcpy(buffer, m_value.buffer.buffer, m_value.buffer.size);
    }
    else
    {
      *reinterpret_cast<uint64_t*>(buffer) = m_value.ui64;
    }
    return DlResult::DL_OK;
  }

  //! Deserialize a buffer to a variant
  //! @param[in]  buffer      Pointer to serialized data
  //! @param[in]  size        Size of buffer
  //! @return Success status of function
  DlResult deserialize(uint8_t* buffer, size_t size)
  {
    if (size < 4) {
      return DlResult::DL_SIZE_MISMATCH;
    }

    if (buffer == nullptr) {
      setType(VariantType::UNKNOWN);
      return DlResult::DL_TYPE_MISMATCH;
    }

    VariantType newType = *reinterpret_cast<VariantType*>(buffer);
    if (newType > VariantType::ARRAY_OF_TIMESTAMP) {
      return DlResult::DL_TYPE_MISMATCH;
    }
    buffer += sizeof(VariantType);
    size_t newSize = size - sizeof(VariantType);
    setType(newType, newSize);
    if (isBufferType(m_type))
    {
      copyRaw(buffer, newSize);
    }
    else
    {
      m_value.ui64 = 0;
      memcpy(&m_value.ui64, buffer, newSize);
    }
    return DlResult::DL_OK;
  }

  //! Deserialize a buffer to a variant without copy of the data
  //! @param[in]  buffer      Pointer to serialized data
  //! @param[in]  size        Size of buffer
  //! @return Success status of function
  DlResult deserializeShared(uint8_t* buffer, size_t size)
  {
    if (size < 4) {
      return DlResult::DL_SIZE_MISMATCH;
    }

    VariantType newType = *reinterpret_cast<VariantType*>(buffer);
    if (newType > VariantType::ARRAY_OF_TIMESTAMP) {
      return DlResult::DL_TYPE_MISMATCH;
    }
    buffer += sizeof(VariantType);
    size_t newSize = size - sizeof(VariantType);
    if (isBufferType(newType))
    {
      setSharedPointer(newType, buffer, newSize);
    }
    else
    {
      setType(newType);
      m_value.ui64 = 0;
      memcpy(&m_value.ui64, buffer, newSize);
    }
    return DlResult::DL_OK;
  }

  //! Compares this variant with another variant
  //! @param[in]  var2        Variant to compare to
  //! @return True if variants are equal
  bool operator==(const Variant &var2) const
  {
    if (this == &var2) {
      return true;
    }

    if (m_type != var2.m_type) {
      return false;
    }

    if (isBufferType(m_type))
    {

      if (m_value.buffer.size != var2.m_value.buffer.size) {
        return false;
      }
      return (memcmp(m_value.buffer.buffer, var2.m_value.buffer.buffer, m_value.buffer.size) == 0);
    }
    else
    {
      return (m_value.ui64 == var2.m_value.ui64);
    }
  }

  //! Compares this variant with another variant
  //! @param[in]  var2        Variant to compare to
  //! @return True if variants are not equal
  bool operator!=(const Variant &var2) const
  {
    return !(*this == var2);
  }

  //! Get data of variant
  //! @return Pointer to data of the variant
  uint8_t* getData() const
  {
    if (isBufferType(m_type)) {
      return m_value.buffer.buffer;
    }
    else {
      return (uint8_t*)&m_value;
    }
  }

  //! Get size of data in bytes of variant
  //! @return Size of data in bytes of variant
  size_t getSize() const
  {
    if (isBufferType(m_type)) {
      return m_value.buffer.size;
    }
    else {
      return getByteSize();
    }
  }

  operator bool()         const { bool value = 0; convertToBool(value); return value; }
  operator uint8_t()      const { uint8_t value = 0; convertToUnsigned(value); return value; }
  operator int8_t()       const { int8_t value = 0; convertToSigned(value); return value; }
  operator uint16_t()     const { uint16_t value = 0; convertToUnsigned(value); return value; }
  operator int16_t()      const { int16_t value = 0; convertToSigned(value); return value; }
  operator uint32_t()     const { uint32_t value = 0; convertToUnsigned(value); return value; }
  operator int32_t()      const { int32_t value = 0; convertToSigned(value); return value; }
  operator uint64_t()     const { uint64_t value = 0; convertToUnsigned(value); return value; }
  operator int64_t()      const { int64_t value = 0; convertToSigned(value); return value; }
  operator float()        const { float value = 0; convertToFloat(value); return value; }
  operator double()       const { double value = 0; convertToFloat(value); return value; }
  operator const char*()  const { if (m_type == VariantType::STRING)  { return reinterpret_cast<char*>(m_value.buffer.buffer); } else { return nullptr; } }

  operator const bool*()        const { if (m_type == VariantType::BOOL8)   { return &m_value.b8;   } else { if (m_type == VariantType::ARRAY_OF_BOOL8)   { return reinterpret_cast<bool*>(m_value.buffer.buffer);     } else { return nullptr; } } }
  operator const uint8_t*()     const { if (m_type == VariantType::UINT8)   { return &m_value.ui8;  } else { if (m_type == VariantType::ARRAY_OF_UINT8)   { return reinterpret_cast<uint8_t*>(m_value.buffer.buffer);  } else { return nullptr; } } }
  operator const int8_t*()      const { if (m_type == VariantType::INT8)    { return &m_value.i8;   } else { if (m_type == VariantType::ARRAY_OF_INT8)    { return reinterpret_cast<int8_t*>(m_value.buffer.buffer);   } else { return nullptr; } } }
  operator const uint16_t*()    const { if (m_type == VariantType::UINT16)  { return &m_value.ui16; } else { if (m_type == VariantType::ARRAY_OF_UINT16)  { return reinterpret_cast<uint16_t*>(m_value.buffer.buffer); } else { return nullptr; } } }
  operator const int16_t*()     const { if (m_type == VariantType::INT16)   { return &m_value.i16;  } else { if (m_type == VariantType::ARRAY_OF_INT16)   { return reinterpret_cast<int16_t*>(m_value.buffer.buffer);  } else { return nullptr; } } }
  operator const uint32_t*()    const { if (m_type == VariantType::UINT32)  { return &m_value.ui32; } else { if (m_type == VariantType::ARRAY_OF_UINT32)  { return reinterpret_cast<uint32_t*>(m_value.buffer.buffer); } else { return nullptr; } } }
  operator const int32_t*()     const { if (m_type == VariantType::INT32)   { return &m_value.i32;  } else { if (m_type == VariantType::ARRAY_OF_INT32)   { return reinterpret_cast<int32_t*>(m_value.buffer.buffer);  } else { return nullptr; } } }
  operator const uint64_t*()    const { if (m_type == VariantType::UINT64 || m_type == VariantType::TIMESTAMP)  { return &m_value.ui64; } else { if (m_type == VariantType::ARRAY_OF_UINT64 || m_type == VariantType::ARRAY_OF_TIMESTAMP)  { return reinterpret_cast<uint64_t*>(m_value.buffer.buffer); } else { return nullptr; } } }
  operator const int64_t*()     const { if (m_type == VariantType::INT64)   { return &m_value.i64;  } else { if (m_type == VariantType::ARRAY_OF_INT64)   { return reinterpret_cast<int64_t*>(m_value.buffer.buffer);  } else { return nullptr; } } }
  operator const float*()       const { if (m_type == VariantType::FLOAT32) { return &m_value.f;    } else { if (m_type == VariantType::ARRAY_OF_FLOAT32) { return reinterpret_cast<float*>(m_value.buffer.buffer);    } else { return nullptr; } } }
  operator const double*()      const { if (m_type == VariantType::FLOAT64) { return &m_value.d;    } else { if (m_type == VariantType::ARRAY_OF_FLOAT64) { return reinterpret_cast<double*>(m_value.buffer.buffer);   } else { return nullptr; } } }
  operator const char**()       const { if (m_type == VariantType::STRING) { return (const char**)&m_value.buffer.buffer; } else { if (m_type == VariantType::ARRAY_OF_STRING) { return (const char**)m_strArray; } else { return nullptr; } } }


  //! Get count of elements in Variant.
  //! If variant holds only one value it returns 1.
  //! If varaint holds an array it returns count of array elements.
  //! @return Count of elements in variant
  size_t getCount() const
  {
    if (isBufferType(m_type))
    {
      if (m_type == VariantType::STRING) {
        return 1;
      }
      if (m_type == VariantType::ARRAY_OF_STRING) {
        return m_strArrayCount;
      }
      return m_value.buffer.size / getByteSize();
    }
    else if (m_type == VariantType::UNKNOWN) {
      return 0;
    }
    else {
      return 1;
    }
  }

  //! Get type of this variant as a string
  //! @return Type of this variant as a string
  const char* typeAsCharString() const
  {
    const char* result;
    switch (m_type)
    {
      case VariantType::UNKNOWN:           result = DATALAYER_TYPE_UNKNOWN;     break;
      case VariantType::BOOL8:             result = DATALAYER_TYPE_BOOL8;       break;
      case VariantType::INT8:              result = DATALAYER_TYPE_INT8;        break;
      case VariantType::UINT8:             result = DATALAYER_TYPE_UINT8;       break;
      case VariantType::INT16:             result = DATALAYER_TYPE_INT16;       break;
      case VariantType::UINT16:            result = DATALAYER_TYPE_UINT16;      break;
      case VariantType::INT32:             result = DATALAYER_TYPE_INT32;       break;
      case VariantType::UINT32:            result = DATALAYER_TYPE_UINT32;      break;
      case VariantType::INT64:             result = DATALAYER_TYPE_INT64;       break;
      case VariantType::UINT64:            result = DATALAYER_TYPE_UINT64;      break;
      case VariantType::FLOAT32:           result = DATALAYER_TYPE_FLOAT;       break;
      case VariantType::FLOAT64:           result = DATALAYER_TYPE_DOUBLE;      break;
      case VariantType::STRING:            result = DATALAYER_TYPE_STRING;      break;
      case VariantType::ARRAY_OF_BOOL8:    result = DATALAYER_TYPE_ARBOOL8;     break;
      case VariantType::ARRAY_OF_INT8:     result = DATALAYER_TYPE_ARIN8;       break;
      case VariantType::ARRAY_OF_UINT8:    result = DATALAYER_TYPE_ARUINT8;     break;
      case VariantType::ARRAY_OF_INT16:    result = DATALAYER_TYPE_ARINT16;     break;
      case VariantType::ARRAY_OF_UINT16:   result = DATALAYER_TYPE_ARUINT16;    break;
      case VariantType::ARRAY_OF_INT32:    result = DATALAYER_TYPE_ARINT32;     break;
      case VariantType::ARRAY_OF_UINT32:   result = DATALAYER_TYPE_ARUINT32;    break;
      case VariantType::ARRAY_OF_INT64:    result = DATALAYER_TYPE_ARINT64;     break;
      case VariantType::ARRAY_OF_UINT64:   result = DATALAYER_TYPE_ARUINT64;    break;
      case VariantType::ARRAY_OF_FLOAT32:  result = DATALAYER_TYPE_ARFLOAT;     break;
      case VariantType::ARRAY_OF_FLOAT64:  result = DATALAYER_TYPE_ARDOUBLE;    break;
      case VariantType::ARRAY_OF_STRING:   result = DATALAYER_TYPE_ARSTRING;    break;
      case VariantType::RAW:               result = DATALAYER_TYPE_RAW;         break;
      case VariantType::FLATBUFFERS:       result = DATALAYER_TYPE_FLATBUFFERS; break;
      case VariantType::TIMESTAMP:         result = DATALAYER_TYPE_TIMESTAMP;   break;
      case VariantType::ARRAY_OF_TIMESTAMP:result = DATALAYER_TYPE_ARTIMESTAMP; break;
      default:
        result = "";
        break;
    }
    return result;
  }

  std::string typeAsString() const
  {
    return typeAsCharString();
  }

  //! Get type of this variant by giving a string
  //! @param[in]  type   Type as a string
  //! @return Converted type as VariantType
  VariantType getTypeByName(const std::string &type) const
  {
    if (type == DATALAYER_TYPE_UNKNOWN)     { return VariantType::UNKNOWN; }
    if (type == DATALAYER_TYPE_BOOL8)       { return VariantType::BOOL8; }
    if (type == DATALAYER_TYPE_INT8)        { return VariantType::INT8; }
    if (type == DATALAYER_TYPE_UINT8)       { return VariantType::UINT8; }
    if (type == DATALAYER_TYPE_INT16)       { return VariantType::INT16; }
    if (type == DATALAYER_TYPE_UINT16)      { return VariantType::UINT16; }
    if (type == DATALAYER_TYPE_INT32)       { return VariantType::INT32; }
    if (type == DATALAYER_TYPE_UINT32)      { return VariantType::UINT32; }
    if (type == DATALAYER_TYPE_INT64)       { return VariantType::INT64; }
    if (type == DATALAYER_TYPE_UINT64)      { return VariantType::UINT64; }
    if (type == DATALAYER_TYPE_FLOAT)       { return VariantType::FLOAT32; }
    if (type == DATALAYER_TYPE_FLOAT32)     { return VariantType::FLOAT32; }
    if (type == DATALAYER_TYPE_DOUBLE)      { return VariantType::FLOAT64; }
    if (type == DATALAYER_TYPE_FLOAT64)     { return VariantType::FLOAT64; }
    if (type == DATALAYER_TYPE_STRING)      { return VariantType::STRING; }
    if (type == DATALAYER_TYPE_ARBOOL8)     { return VariantType::ARRAY_OF_BOOL8; }
    if (type == DATALAYER_TYPE_ARIN8)       { return VariantType::ARRAY_OF_INT8; }
    if (type == DATALAYER_TYPE_ARUINT8)     { return VariantType::ARRAY_OF_UINT8; }
    if (type == DATALAYER_TYPE_ARINT16)     { return VariantType::ARRAY_OF_INT16; }
    if (type == DATALAYER_TYPE_ARUINT16)    { return VariantType::ARRAY_OF_UINT16; }
    if (type == DATALAYER_TYPE_ARINT32)     { return VariantType::ARRAY_OF_INT32; }
    if (type == DATALAYER_TYPE_ARUINT32)    { return VariantType::ARRAY_OF_UINT32; }
    if (type == DATALAYER_TYPE_ARINT64)     { return VariantType::ARRAY_OF_INT64; }
    if (type == DATALAYER_TYPE_ARUINT64)    { return VariantType::ARRAY_OF_UINT64; }
    if (type == DATALAYER_TYPE_ARFLOAT)     { return VariantType::ARRAY_OF_FLOAT32; }
    if (type == DATALAYER_TYPE_ARDOUBLE)    { return VariantType::ARRAY_OF_FLOAT64; }
    if (type == DATALAYER_TYPE_ARFLOAT32)   { return VariantType::ARRAY_OF_FLOAT32; }
    if (type == DATALAYER_TYPE_ARFLOAT64)   { return VariantType::ARRAY_OF_FLOAT64; }
    if (type == DATALAYER_TYPE_ARSTRING)    { return VariantType::ARRAY_OF_STRING; }
    if (type == DATALAYER_TYPE_RAW)         { return VariantType::RAW; }
    if (type == DATALAYER_TYPE_FLATBUFFERS) { return VariantType::FLATBUFFERS; }
    if (type == DATALAYER_TYPE_TIMESTAMP)   { return VariantType::TIMESTAMP; }
    if (type == DATALAYER_TYPE_ARTIMESTAMP) { return VariantType::ARRAY_OF_TIMESTAMP; }
    return VariantType::UNKNOWN;
  }

  DlResult checkConvert(VariantType targetType) const
  {
    if (m_type == targetType) {
      return DlResult::DL_OK;
    }

    if (isBufferType(targetType)) {
      return DlResult::DL_TYPE_MISMATCH;
    }

    switch (targetType) {
      case VariantType::BOOL8: { bool value = 0; return convertToBool(value); }
      case VariantType::INT8: { int8_t value = 0; return convertToSigned(value); }
      case VariantType::UINT8: { uint8_t value = 0; return convertToUnsigned(value); }
      case VariantType::INT16: { int16_t value = 0; return convertToSigned(value); }
      case VariantType::UINT16: { uint16_t value = 0; return convertToUnsigned(value); }
      case VariantType::INT32: { int32_t value = 0; return convertToSigned(value); }
      case VariantType::UINT32: { uint32_t value = 0; return convertToUnsigned(value); }
      case VariantType::INT64: { int64_t value = 0; return convertToSigned(value); }
      case VariantType::UINT64: { uint64_t value = 0; return convertToUnsigned(value); }
      case VariantType::FLOAT32: { float value = 0; return convertToFloat(value); }
      case VariantType::FLOAT64: { double value = 0; return convertToFloat(value); }
      case VariantType::TIMESTAMP: { uint64_t value = 0; return convertToUnsigned(value); }
      default: return DlResult::DL_TYPE_MISMATCH;
    }
  }

  //! Converts value of variant to another type if value is convertable in target type
  //! @param[in]  targetType   Target type
  //! @return Success status of function
  DlResult convertTo(VariantType targetType)
  {
    if (m_type == targetType)
    {
      return DlResult::DL_OK;
    }

    DlResult result = checkConvert(targetType);
    if (STATUS_FAILED(result)) {
      return result;
    }

    switch (targetType) {
      case VariantType::BOOL8: { bool value = 0; convertToBool(value); setValue(value); break; }
      case VariantType::INT8: { int8_t value = 0; convertToSigned(value); setValue(value); break; }
      case VariantType::UINT8: { uint8_t value = 0; convertToUnsigned(value); setValue(value); break; }
      case VariantType::INT16: { int16_t value = 0; convertToSigned(value); setValue(value); break; }
      case VariantType::UINT16: { uint16_t value = 0; convertToUnsigned(value); setValue(value); break; }
      case VariantType::INT32: { int32_t value = 0; convertToSigned(value); setValue(value); break; }
      case VariantType::UINT32: { uint32_t value = 0; convertToUnsigned(value); setValue(value); break; }
      case VariantType::INT64: { int64_t value = 0; convertToSigned(value); setValue(value); break; }
      case VariantType::UINT64: { uint64_t value = 0; convertToUnsigned(value); setValue(value); break; }
      case VariantType::FLOAT32: { float value = 0; convertToFloat(value); setValue(value); break; }
      case VariantType::FLOAT64: { double value = 0; convertToFloat(value); setValue(value); break; }
      case VariantType::TIMESTAMP: { uint64_t value = 0; convertToUnsigned(value); setValue(value); break; }
      default: return DlResult::DL_TYPE_MISMATCH;
    }
    return DlResult::DL_OK;
  }

private:
  size_t getByteSize() const
  {
    size_t result;
    switch (m_type)
    {
      case VariantType::INT16:
      case VariantType::UINT16:
      case VariantType::ARRAY_OF_INT16:
      case VariantType::ARRAY_OF_UINT16:
        result = 2;
        break;
      case VariantType::INT32:
      case VariantType::UINT32:
      case VariantType::FLOAT32:
      case VariantType::ARRAY_OF_INT32:
      case VariantType::ARRAY_OF_UINT32:
      case VariantType::ARRAY_OF_FLOAT32:
        result = 4;
        break;
      case VariantType::INT64:
      case VariantType::UINT64:
      case VariantType::FLOAT64:
      case VariantType::ARRAY_OF_INT64:
      case VariantType::ARRAY_OF_UINT64:
      case VariantType::ARRAY_OF_FLOAT64:
      case VariantType::TIMESTAMP:
      case VariantType::ARRAY_OF_TIMESTAMP:
        result = 8;
        break;
      case VariantType::UNKNOWN:
      case VariantType::BOOL8:
      case VariantType::INT8:
      case VariantType::UINT8:
      case VariantType::ARRAY_OF_BOOL8:
      case VariantType::ARRAY_OF_INT8:
      case VariantType::ARRAY_OF_UINT8:
      case VariantType::STRING:
      case VariantType::ARRAY_OF_STRING:
      case VariantType::RAW:
      case VariantType::FLATBUFFERS:
      default:
        result = 1;
        break;
    }
    return result;
  }

  void buildStringArray()
  {
    if (m_type != VariantType::ARRAY_OF_STRING) {
      return;
    }

    m_strArrayCount = 0;
    for (char* pos = reinterpret_cast<char*>(m_value.buffer.buffer); pos < reinterpret_cast<char*>(m_value.buffer.buffer + m_value.buffer.size); pos++)
    {
      if (*pos == 0) {
        m_strArrayCount++;
      }
    }

    if (m_strArrayCount == 0) {
      return;
    }
    m_strArray = new char*[m_strArrayCount];

    size_t count = 0;
    m_strArray[count] = reinterpret_cast<char*>(m_value.buffer.buffer);
    count++;
    for (char* pos = reinterpret_cast<char*>(m_value.buffer.buffer); pos < reinterpret_cast<char*>(m_value.buffer.buffer + m_value.buffer.size - 1); pos++) {
      if (*pos == 0)
      {
        m_strArray[count] = pos + 1;
        count++;
      }
    }

  }

  template <typename T> DlResult convertToSigned(T& dest) const
  {
    uint64_t max =   (uint64_t(1) << ((sizeof(T) * 8) - 1)) - 1;
    int64_t  min =  -( int64_t(1) << ((sizeof(T) * 8) - 1));
    return convertInteger(dest, max, min);
  }

  template <typename T> DlResult convertToUnsigned(T& dest) const
  {
    const T max = (const T)-1;
    static_assert(0 < max, "specified return type seems to be signed...");
    int64_t min = 0;
    return convertInteger(dest, max, min);
  }

  template <typename T> DlResult convertInteger(T& dest, uint64_t max, int64_t min) const
  {
    int64_t value = 0;
    switch (m_type)
    {
      case ::comm::datalayer::VariantType::INT8:
        value = m_value.i8;
        break;
      case ::comm::datalayer::VariantType::INT16:
        value = m_value.i16;
        break;
      case ::comm::datalayer::VariantType::INT32:
        value = m_value.i32;
        break;
      case ::comm::datalayer::VariantType::INT64:
        value = m_value.i64;
        break;
      default:
        break;
    }
    switch (m_type)
    {
      case ::comm::datalayer::VariantType::BOOL8:
        dest = m_value.b8 ? 1 : 0;
        break;
      case ::comm::datalayer::VariantType::INT8:
      case ::comm::datalayer::VariantType::INT16:
      case ::comm::datalayer::VariantType::INT32:
      case ::comm::datalayer::VariantType::INT64:
        if ((max < 0xFFFFFFFFFF) && (value > (int64_t)max)) {
          return DlResult::DL_LIMIT_MAX;
        }
        if (value < min) {
          return DlResult::DL_LIMIT_MIN;
        }
        dest = static_cast<T>(value);
        break;
      case ::comm::datalayer::VariantType::UINT8:
      case ::comm::datalayer::VariantType::UINT16:
      case ::comm::datalayer::VariantType::UINT32:
      case ::comm::datalayer::VariantType::UINT64:
      case ::comm::datalayer::VariantType::TIMESTAMP:
        if (m_value.ui64 > max) {
          return DlResult::DL_LIMIT_MAX;
        }
        dest = static_cast<T>(m_value.i64);
        break;
      case ::comm::datalayer::VariantType::FLOAT32:
      {
        dest = static_cast<T>(m_value.f);
        float test = static_cast<float>(dest);
        if (test != m_value.f)
        {
          return DlResult::DL_INVALID_VALUE;
        }
        break;
      }
      case ::comm::datalayer::VariantType::FLOAT64:
      {
        dest = static_cast<T>(m_value.d);
        double test = static_cast<double>(dest);
        if (test != m_value.d)
        {
          return DlResult::DL_INVALID_VALUE;
        }
        break;
      }
      default:
        return DlResult::DL_TYPE_MISMATCH;
    }
    return DlResult::DL_OK;
  }


  template <typename destType, typename srcType>
  DlResult convertFloatType(destType& dest, srcType& src) const
  {
    dest = static_cast<destType>(src);
    if(!std::isfinite(dest)) {
      return DlResult::DL_INVALID_VALUE;
    }
    if (!std::isnormal(dest)) {
      dest = 0;
    }
    return DlResult::DL_OK;
  }

  template <typename T> DlResult convertToFloat(T& dest) const
  {
    switch (m_type)
    {
      case ::comm::datalayer::VariantType::BOOL8:
        return convertFloatType(dest ,m_value.b8);
      case ::comm::datalayer::VariantType::INT8:
        return convertFloatType(dest, m_value.i8);
      case ::comm::datalayer::VariantType::UINT8:
        return convertFloatType(dest, m_value.ui8);
      case ::comm::datalayer::VariantType::INT16:
        return convertFloatType(dest, m_value.i16);
      case ::comm::datalayer::VariantType::UINT16:
        return convertFloatType(dest, m_value.ui16);
      case ::comm::datalayer::VariantType::INT32:
        return convertFloatType(dest, m_value.i32);
      case ::comm::datalayer::VariantType::UINT32:
        return convertFloatType(dest, m_value.ui32);
      case ::comm::datalayer::VariantType::INT64:
        return convertFloatType(dest, m_value.i64);
      case ::comm::datalayer::VariantType::UINT64:
      case ::comm::datalayer::VariantType::TIMESTAMP:
        return convertFloatType(dest, m_value.ui64);
      case ::comm::datalayer::VariantType::FLOAT32:
        return convertFloatType(dest, m_value.f);
      case ::comm::datalayer::VariantType::FLOAT64:
        return convertFloatType(dest, m_value.d);
      default:
        return DlResult::DL_TYPE_MISMATCH;
    }
    return DlResult::DL_OK;
  }

  inline DlResult convertToBool(bool& dest) const
  {
    switch (m_type)
    {
      case ::comm::datalayer::VariantType::BOOL8:
      case ::comm::datalayer::VariantType::INT8:
      case ::comm::datalayer::VariantType::UINT8:
      case ::comm::datalayer::VariantType::INT16:
      case ::comm::datalayer::VariantType::UINT16:
      case ::comm::datalayer::VariantType::INT32:
      case ::comm::datalayer::VariantType::UINT32:
      case ::comm::datalayer::VariantType::INT64:
      case ::comm::datalayer::VariantType::UINT64:
      case ::comm::datalayer::VariantType::TIMESTAMP:
        dest = (m_value.i64 != 0);
        break;
      case ::comm::datalayer::VariantType::FLOAT32:
        dest = (m_value.f == 0.0) ? 0 : 1;
        break;
      case ::comm::datalayer::VariantType::FLOAT64:
        dest = (m_value.d == 0.0) ? 0 : 1;
        break;
      default:
        return DlResult::DL_TYPE_MISMATCH;
    }
    return DlResult::DL_OK;
  }

  VariantType m_type = VariantType::UNKNOWN;
  UVariantUnion m_value;
  bool m_boShared = false;
  char** m_strArray = nullptr;
  size_t m_strArrayCount = 0;
};

}
}
