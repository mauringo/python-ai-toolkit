#pragma once

#include "datalayer.h"


#include "metadata_helper.h"

//! Namespace for datalayer
namespace comm {
namespace datalayer {

#define SNAP_DATA "SNAP_DATA"
#define SNAP_NAME "SNAP_NAME"
#define TOKEN_DIR "/service-token/"
#define TOKEN_EXTENSION ".token"


//! Helper class for clients
class ServicetokenHelper
{
public:
  virtual ~ServicetokenHelper() = default;

  static DlResult getServiceToken(std::string& token)
  {
    Variant tokenVariant;

    auto snapData = std::getenv(SNAP_DATA);
    auto snapName = std::getenv(SNAP_NAME);
    std::string filename;
    if (snapData && snapName)
    {
      filename = std::string(snapData) + TOKEN_DIR + snapName + "/" + snapName + TOKEN_EXTENSION;
    }
    else
    {
      filename = std::string("token") + TOKEN_EXTENSION;
    }
    DlResult result = MetadataHelper::getFileContent(filename, tokenVariant);
    if (STATUS_SUCCEEDED(result))
    {
      token = std::string(reinterpret_cast<const char*>(tokenVariant.getData()), tokenVariant.getCount());
    }

    return result;
  }
};

}
}
