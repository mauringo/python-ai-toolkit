#pragma once

#include "datalayer_version.h"
#include "flatbuffers/reflection_generated.h"

#define IFLATBUFFERS_CONSUMER_RANGE "[" IDATALAYER_VERSION_MAJOR ".5.0,2.0.0)"                      //! Version range for users of flatbuffers
#define IFLATBUFFERS_INTERFACE_NAME "com.boschrexroth.common.flatbuffers"                           //! Interface name

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FlatbuffersCItf
{
  bool(*verify)(const reflection::Schema& schema,
                const reflection::Object& root,
                const uint8_t* buf,
                size_t length,
                flatbuffers::uoffset_t max_dept,
                flatbuffers::uoffset_t max_tables
                );

  bool(*deserialize)(void* parser,
                     const uint8_t* buf,
                     const size_t size
                     );

  void* reserved[100];
}FlatbuffersCItf;

#ifdef __cplusplus
}
#endif
