#pragma once

#include "datalayer.h"
#include "metadata_generated.h"
#include "flatbuffer_json.h"
#include "notify_info_generated.h"
#include <fstream>
#include <string.h>

//! Namespace for datalayer
namespace comm {
namespace datalayer {

#define DL_REF_READTYPE     "readType"
#define DL_REF_READINTYPE   "readInType"
#define DL_REF_READOUTTYPE  "readOutType"
#define DL_REF_WRITETYPE    "writeType"
#define DL_REF_WRITEINTYPE  "writeInType"
#define DL_REF_WRITEOUTTYPE "writeOutType"
#define DL_REF_CREATETYPE   "createType"

//! Helper class for providers
class MetadataHelper
{
public:

  typedef std::function<void(DlResult status, const NotifyItem &data)> NotifyCallback;

  //! Fills a file to a flatbuffers uint8 vector. You can use this function to load a bfbs file into metadata.
  //! @param[in]  builder     Flatbuffers builder
  //! @param[in]  filename    File to load
  //! @param[out] data        Buffer to load file to
  //! @result Status of function
  static DlResult setTypeFromFile(flatbuffers::FlatBufferBuilder &builder, const char* filename, flatbuffers::Offset<flatbuffers::Vector<uint8_t>> *data)
  {
    if (data == nullptr) {
      return DlResult::DL_FAILED;
    }

    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    if (!in.is_open()) {
      return DlResult::DL_FAILED;
    }

    std::ifstream::pos_type size = in.tellg();
    in.close();

    std::ifstream file(filename, std::fstream::binary | std::fstream::in);
    if (!file.is_open()) {
      return DlResult::DL_FAILED;
    }

    uint8_t* buffer = new uint8_t[static_cast<size_t>(size)];
    file.read(reinterpret_cast<char*>(buffer), size);
    *data = builder.CreateVector(buffer, static_cast<size_t>(size));
    delete[] buffer;
    return DlResult::DL_OK;
  }

  static DlResult getFileContent(const std::string &filename, Variant &data)
  {
    std::ifstream in(filename.c_str(), std::ifstream::ate | std::ifstream::binary);
    if (!in.is_open()) {
      return DlResult::DL_INVALID_ADDRESS;
    }

    std::ifstream::pos_type size = in.tellg();
    in.close();

    std::ifstream file(filename.c_str(), std::fstream::binary | std::fstream::in);
    if (!file.is_open()) {
      return DlResult::DL_INVALID_ADDRESS;
    }

    data.setType(VariantType::FLATBUFFERS, static_cast<size_t>(size));
    file.read(reinterpret_cast<char*>(data.getData()), size);
    return DlResult::DL_OK;
  }

  static DlResult readReferenceAsync(IClient* client, const std::string& address, const std::string& referenceType, const NotifyCallback& callback, const std::string& token = "")
  {
    if (client == nullptr) {
      return DlResult::DL_INVALID_HANDLE;
    }

    IClient::ResponseCallback readCallback = [client, referenceType, callback, token](DlResult status, const Variant* data)
    {
      comm::datalayer::NotifyItem item = {};
      if (STATUS_FAILED(status))
      {
        callback(status, item);
        return;
      }
      
      if (data == nullptr)
      {
        callback(DlResult::DL_RT_NOVALIDDATA, item);
        return;
      }

      if (STATUS_FAILED(data->verifyFlatbuffers(VerifyMetadataBuffer)))
      {
        callback(DlResult::DL_TYPE_MISMATCH, item);
        return;
      }

      auto metadata = comm::datalayer::GetMetadata(data->getData());
      auto references = metadata->references();
      if (references == nullptr)
      {
        callback(DlResult::DL_INVALID_ADDRESS, item);
        return;
      }
      auto ref = MetadataHelper::lookupMetadataReference(references, referenceType);
      if (ref == nullptr)
      {
        callback(DlResult::DL_INVALID_ADDRESS, item);
        return;
      }

      std::string address = ref->targetAddress()->str();
      IClient::ResponseCallback readTypeCallback = [callback, address](DlResult status, const Variant* data) {
        comm::datalayer::NotifyItem item = {};
        flatbuffers::FlatBufferBuilder builder;
        builder.Finish(CreateNotifyInfoDirect(builder, address.c_str(), 0));
        item.info.shareFlatbuffers(builder);
        if (data) {
          item.data = *data;
        }
        callback(status, item);
      };
      client->readAsync(address, *data, readTypeCallback, token);

    };
    return client->metadataAsync(address, readCallback, token);
  }

  static DlResult readReferenceAsync(IClient* client, const std::string &address, const std::string &referenceType, const IClient::ResponseCallback &callback, const std::string &token = "")
  {
    auto myCallback = [callback](DlResult status, const NotifyItem& data) {
      callback(status, &data.data);
    };
    return readReferenceAsync(client, address, referenceType, myCallback, token);
  }

  static DlResult readReferenceSync(IClient* client, const std::string &address, const std::string &referenceType, Variant *data, const std::string &token = "")
  {
    if (data == nullptr)
    {
      return DlResult::DL_INVALID_VALUE;
    }

    std::string metadataAddress;
    auto result = getMetadataAddressSync(client, address, referenceType, metadataAddress, token);
    if (comm::datalayer::STATUS_FAILED(result))
    {
      return result;
    }

    result = client->readSync(metadataAddress, data, token);
    return result;
  }

  static DlResult getMetadataAddressSync(IClient* client, const std::string& address, const std::string& referenceType, std::string& metadataAddress, const std::string& token = "")
  {
    DlResult result;
    if (client == nullptr)
    {
      return DlResult::DL_INVALID_HANDLE;
    }

    Variant data;
    data.setType(VariantType::UNKNOWN);
    result = client->metadataSync(address, &data, token);
    if (STATUS_FAILED(result))
    {
      return result;
    }

    if (STATUS_FAILED(data.verifyFlatbuffers(VerifyMetadataBuffer)))
    {
      return DlResult::DL_TYPE_MISMATCH;
    }

    auto metadata = comm::datalayer::GetMetadata(data.getData());
    auto references = metadata->references();
    if (references == nullptr)
    {
      return DlResult::DL_INVALID_ADDRESS;
    }

    auto ref = MetadataHelper::lookupMetadataReference(references, referenceType);
    if (ref == nullptr)
    {
      return DlResult::DL_INVALID_ADDRESS;
    }

    metadataAddress = ref->targetAddress()->c_str();

    return result;
  }

  static flatbuffers::Vector<const comm::datalayer::Reference*>::return_type lookupMetadataReference(const flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Reference>>* references, const std::string& referenceType)
  {
    auto ref = references->LookupByKey(referenceType.c_str());
    if (ref == nullptr)
    {
      // fall back to compatible read and write type references
      if (referenceType == DL_REF_READINTYPE || referenceType == DL_REF_READOUTTYPE)
      {
        ref = references->LookupByKey(DL_REF_READTYPE);
      }
      else if (referenceType == DL_REF_WRITEINTYPE || referenceType == DL_REF_WRITEOUTTYPE)
      {
        ref = references->LookupByKey(DL_REF_WRITETYPE);
      }
    }
    return ref;
  }

  static void createMetadata(Variant& data, NodeClass nodeClass, bool read, bool write, bool create, bool del, bool browse, std::vector<std::pair<std::string, std::string>> references = {}, const std::string& description = "")
  {
    flatbuffers::FlatBufferBuilder builder;
    auto emptyString = builder.CreateString("");
    auto descriptionOffset = emptyString;
    if (description.size())
    {
      descriptionOffset = builder.CreateString(description);
    }
    std::vector<flatbuffers::Offset<Reference>> vecReferences;
    for (auto reference : references)
    {
      vecReferences.push_back(CreateReferenceDirect(builder, reference.first.c_str(), reference.second.c_str()));
    }
    auto offsetReferences = builder.CreateVectorOfSortedTables(&vecReferences);

    AllowedOperationsBuilder allowedOperations(builder);
    allowedOperations.add_read(read);
    allowedOperations.add_write(write);
    allowedOperations.add_create(create);
    allowedOperations.add_delete_(del);
    allowedOperations.add_browse(browse);
    auto operations = allowedOperations.Finish();

    comm::datalayer::MetadataBuilder metadata(builder);
    //metadata.add_flatbufferTypes(flatbufferTypesFinished);
    metadata.add_nodeClass(nodeClass);
    metadata.add_description(descriptionOffset);
    metadata.add_descriptionUrl(emptyString);
    metadata.add_operations(operations);
    metadata.add_references(offsetReferences);
    auto metaFinished = metadata.Finish();
    builder.Finish(metaFinished);

    data.copyFlatbuffers(builder);
  }

};


}
}
