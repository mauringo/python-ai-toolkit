#pragma once
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void *DLR_CONVERTER;

  typedef enum DLR_SCHEMA {
    DLR_SCHEMA_METADATA = 0,
    DLR_SCHEMA_REFLECTION = 1,
    DLR_SCHEMA_MEMORY = 2,
    DLR_SCHEMA_MEMORY_MAP = 3,
    DLR_SCHEMA_TOKEN = 4,
    DLR_SCHEMA_PROBLEM = 5,
    DLR_SCHEMA_DIAGNOSIS = 6,
  }DLR_SCHEMA;

  //! This function generate a JSON string out of a Variant witch have a simple data type
  //! @param[in]  converter   A IFlatbufferJson* object which will do the actual conversion
  //! @param[in]  data        Variant which contains data with simple data type
  //! @param[out] json        Generated JSON as Variant (string)
  //! @param[in]  indentStep  Indentation length for json string
  //! @return result status of the function
  DLR_RESULT DLR_converterGenerateJsonSimple(DLR_CONVERTER converter, const DLR_VARIANT data, DLR_VARIANT json, int32_t indentStep);

  //! This function generate a JSON string out of a Variant with complex type (flatbuffers) and the metadata of this data
  //! @param[in]  converter   A IFlatbufferJson* object which will do the actual conversion
  //! @param[in]  data        Varaint which contains data of complex data type (flatbuffers) if data is empty (VariantType::UNKNOWN) type is converted to json schema
  //! @param[in]  type        Variant which contains type of data (Variant with flatbuffers BFBS)
  //! @param[out] json        Generated JSON string
  //! @param[in]  indentStep  Indentation length for json string
  //! @return result status of the function
  DLR_RESULT DLR_converterGenerateJsonComplex(DLR_CONVERTER converter, const DLR_VARIANT data, const DLR_VARIANT type, DLR_VARIANT json, int32_t indentStep);

  //! This function generates a Variant out of a JSON string containing the (simple) data 
  //! @param[in]  converter   A IFlatbufferJson* object which will do the actual conversion
  //! @param[in]  json        Data of the Variant as a json string
  //! @param[out] data        Variant which contains the data
  //! @param[out] error       Error as Variant (string)
  //! @return result status of the function
  DLR_RESULT DLR_converterParseJsonSimple(DLR_CONVERTER converter, const char* json, DLR_VARIANT data, DLR_VARIANT error);

  //! This function generates a Variant out of a JSON string containing the (complex) data
  //! @param[in]  converter   A IFlatbufferJson* object which will do the actual conversion
  //! @param[in]  json        Data of the Variant as a json string
  //! @param[in]  type        Variant which contains type of data (Variant with bfbs flatbuffer content)
  //! @param[out] data        Variant which contains the data
  //! @param[out] error       Error as Variant (string)
  //! @return result status of the function
  DLR_RESULT DLR_converterParseJsonComplex(DLR_CONVERTER converter, const char* json, const DLR_VARIANT type, DLR_VARIANT data, DLR_VARIANT error);

  //! This function returns the type (schema)
  //! @param[in]  converter   A IFlatbufferJson* object which will retrieve the actual type
  //! @param[in]  schema      Requested schema
  //! @param[out] data        Variant which contains the type (schema)
  //! @return result status of the function
  DLR_RESULT DLR_converterGetSchema(DLR_CONVERTER converter, DLR_SCHEMA schema, DLR_VARIANT data);

#ifdef __cplusplus
}
#endif
