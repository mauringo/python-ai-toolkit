#pragma once
#include "datalayer_defs.h"
#include <string>
#include "variant.h"

//! Namespace for datalayer
namespace comm {
namespace datalayer {

//! Class to convert between JSON and Variant
class IFlatbufferJson
{
public:

  enum class AccessType {
    READ = 0,
    WRITE = 1,
    CREATE = 2,
  };

  enum class Schema {
    METADATA = 0,
    REFLECTION = 1,
    MEMORY = 2,
    MEMORY_MAP = 3,
    TOKEN = 4,
    PROBLEM = 5,
    DIAGNOSIS = 6,
    DEBUGCHANNEL = 7,
    SUBSCRIPTION_PROPERTIES = 8,
    SUBSCRIPTION_DATA = 9,
    SUBSCRIPTION_SETTINGS = 10,
    SUBSCRIPTION = 11,
    PERSISTENCE_PARAM = 12,
    SERVER_SETTINGS = 13,
    WATCHLISTS = 14,
    SCOPES = 15,
    REMOTE_CONFIG = 16,
  };

  //! This function generate a JSON string out of a flatbuffer idl and a flatbuffer definition
  //! @param[in]  idl        Flatbuffer idl string describing the type of the flatbuffer
  //! @param[in]  buffer     Data of the flatbuffer
  //! @param[out] json       Generated JSON string
  //! @param[in]  indentStep Indentation level in generated JSON file
  //! @return result status of the function
  virtual DlResult generateJson(const std::string &idl, void* buffer, std::string *json, int32_t indentStep = 0) = 0;

  //! This function generate a flatbuffer out of a flatbuffer idl and a json string containing the data
  //! @param[in]  idl     Flatbuffer idl string describing the type of the flatbuffer
  //! @param[in]  json    Data of the flatbuffer as a json file
  //! @param[out] buffer  Pointer to the flatbuffer (this function will allocate memory and return it)
  //! @param[out] size    Size of the flatbuffer
  //! @param[out] error   Detailed error information.
  //! @return result status of the function
  virtual DlResult parseJson(const std::string &idl, const std::string &json, uint8_t **buffer, size_t *size, std::string *error = nullptr) = 0;

  //! This function generate a JSON string out of a Variant witch have a simple data type
  //! @param[in]  data    Variant which contains data with simple data type
  //! @param[out] json    Generated JSON string
  //! @return result status of the function
  virtual DlResult generateJson(const Variant &data, std::string *json, int32_t indentStep = 0) = 0;

  //! This function generates a Variant out of a JSON string containing the data
  //! @param[in]  json    Data of the Variant as a json file
  //! @param[out] data    Variant which contains the data
  //! @param[out] error   Detailed error information.
  //! @return result status of the function
  virtual DlResult parseJson(const std::string &json, Variant *data, std::string *error = nullptr) = 0;

  //! This function generate a JSON string out of a Variant with complex type (flatbuffers) and the metadata of this data
  //! @param[in]  data     Varaint which contains data of complex data type (flatbuffers) if data is empty (VariantType::UNKNOWN) type is converted to json schema
  //! @param[in]  type     Variant which contains type of data
  //! @param[out] json     Generated JSON string
  //! @return result status of the function
  virtual DlResult generateJson(const Variant &data, const Variant &type, std::string *json, int32_t indentStep = 0) = 0;

  //! This function generates a Variant out of a JSON string containing the data
  //! @param[in]  json     Data of the Variant as a json file
  //! @param[in]  metadata Variant which contains type of data
  //! @param[out] data     Variant which contains the data
  //! @param[out] error    Detailed error information.
  //! @return result status of the function
  virtual DlResult parseJson(const std::string &json, const Variant &metadata, Variant *data, std::string *error = nullptr) = 0;

  //! This function returns the type (schema)
  //! @param[in]  schema   Requested schema
  //! @param[out] data     Variant which contains the type (schema)
  //! @return result status of the function
  virtual DlResult getType(Schema schema, Variant *data) = 0;
protected:
private:
};

}
}
