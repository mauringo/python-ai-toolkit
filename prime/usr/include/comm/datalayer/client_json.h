#pragma once

#include "metadata_helper.h"

//! Namespace for datalayer
namespace comm {
namespace datalayer {

class ClientJson
{
public:
  ClientJson(IClient &client, IFlatbufferJson &converter)
    : m_client(client)
    , m_converter(converter)
  {
  }

  virtual ~ClientJson()
  {
  }

  //! This function reads a value from datalayer
  //! @param[in] addr         Address for the request
  //! @param[in/out] json     Json to read (will be transmitted and result will be converted back)
  //! @param[in]  error       Error while parsing json
  //! @param[in]  indentStep  Indentation length for json string
  //! @param[in]  token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DlResult readJsonSync(const std::string &addr, std::string &json, std::string *error = nullptr, int32_t indentStep = 0, const std::string &token = "")
  {
    DlResult result;
    Variant typeIn;
    Variant typeOut;
    Variant data;

    if (STATUS_FAILED(result = ParseJson(addr, json, data, typeIn, DL_REF_READINTYPE, error, token))) {
      return result;
    }
    if (STATUS_FAILED(result = m_client.readSync(addr, &data, token))) {
      return result;
    }
    if (STATUS_FAILED(result = generateJson(addr, json, data, typeOut, DL_REF_READOUTTYPE, error, indentStep, token))) {
      return result;
    }

    return result;
  }

  //! This function writes a value to datalayer
  //! @param[in] addr         Address for the request
  //! @param[in/out] json     Json to write (will be transmitted and result will be converted back)
  //! @param[in]  error       Error while parsing json
  //! @param[in]  indentStep  Indentation length for json string
  //! @param[in]  token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DlResult writeJsonSync(const std::string &addr, std::string &json, std::string *error = nullptr, int32_t indentStep = 0, const std::string &token = "")
  {
    DlResult result;
    Variant typeIn;
    Variant typeOut;
    Variant data;

    if (STATUS_FAILED(result = ParseJson(addr, json, data, typeIn, DL_REF_WRITEINTYPE, error, token))) {
      return result;
    }
    if (STATUS_FAILED(result = m_client.writeSync(addr, &data))) {
      return result;
    }
    if (STATUS_FAILED(result = generateJson(addr, json, data, typeOut, DL_REF_WRITEOUTTYPE, error, indentStep, token))) {
      return result;
    }
    return result;
  }

  //! This function creates a value in datalayer
  //! @param[in] addr         Address for the request
  //! @param[in/out] json     Json to create (will be transmitted and result will be converted back)
  //! @param[in]  error       Error while parsing json
  //! @param[in]  indentStep  Indentation length for json string
  //! @param[in]  token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DlResult createJsonSync(const std::string &addr, std::string &json, std::string *error = nullptr, int32_t indentStep = 0, const std::string &token = "")
  {
    DlResult result;
    Variant type;
    Variant data;

    if (STATUS_FAILED(result = ParseJson(addr, json, data, type, DL_REF_CREATETYPE, error, token))) {
      return result;
    }
    if (STATUS_FAILED(result = m_client.createSync(addr, &data))) {
      return result;
    }
    if (STATUS_FAILED(result = generateJson(addr, json, data, type, DL_REF_CREATETYPE, error, indentStep, token))) {
      return result;
    }
    return result;
  }

  //! This function writes a value to datalayer - the result value will be ignored
  //! @param[in] addr         Address for the request
  //! @param[in] json         Json to write
  //! @param[in]  error       Error while parsing json
  //! @param[in]  indentStep  Indentation length for json string
  //! @param[in]  token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DlResult writeJsonSync(const std::string& addr, const std::string& json, std::string* error = nullptr, int32_t indentStep = 0, const std::string& token = "")
  {
    DlResult result;
    Variant typeIn;
    Variant typeOut;
    Variant data;

    if (STATUS_FAILED(result = ParseJson(addr, json, data, typeIn, DL_REF_WRITEINTYPE, error, token)))
    {
      return result;
    }
    if (STATUS_FAILED(result = m_client.writeSync(addr, &data)))
    {
      return result;
    }
    return result;
  }

  //! This function creates a value in datalayer - result value will be ignored
  //! @param[in] addr         Address for the request
  //! @param[in] json         Json to create 
  //! @param[in]  error       Error while parsing json
  //! @param[in]  indentStep  Indentation length for json string
  //! @param[in]  token       Security access &token for authentication as JWT payload (optional)
  //! @return result status of the function
  DlResult createJsonSync(const std::string& addr, const std::string& json, std::string* error = nullptr, int32_t indentStep = 0, const std::string& token = "")
  {
    DlResult result;
    Variant type;
    Variant data;

    if (STATUS_FAILED(result = ParseJson(addr, json, data, type, DL_REF_CREATETYPE, error, token)))
    {
      return result;
    }
    if (STATUS_FAILED(result = m_client.createSync(addr, &data)))
    {
      return result;
    }
    return result;
  }

  DlResult ParseJson(const std::string &addr, const std::string &json, Variant &data, Variant &type, const std::string &reference, std::string *error, const std::string & token)
  {
    DlResult result = DlResult::DL_OK;
    if (json.length() == 0)
    {
      data.setType(VariantType::UNKNOWN);
      return result;
    }
    if (STATUS_FAILED(result = m_converter.parseJson(json, &data, error)))
    {
      if (STATUS_FAILED(result = MetadataHelper::readReferenceSync(&m_client, addr, reference, &type, token)))
      {
        if (error) { *error = "can't read type"; }
        return result;
      }
      if (STATUS_FAILED(m_converter.parseJson(json, type, &data, error)))
      {
        return result;
      }
    }
    if (error) { *error = ""; }
    return result;
  }

  DlResult generateJson(const std::string &addr, std::string &json, Variant &data, Variant &type, const std::string &reference, std::string *error, int32_t indentStep, const std::string & token)
  {
    DlResult result = DlResult::DL_OK;
    if (data.getType() != VariantType::UNKNOWN)
    {
      if (STATUS_FAILED(m_converter.generateJson(data, &json, indentStep)))
      {
        if (type.getType() == VariantType::UNKNOWN)
        {
          if (STATUS_FAILED(result = MetadataHelper::readReferenceSync(&m_client, addr, reference, &type, token)))
          {
            if (error) { *error = "can't read type"; }
            return result;
          }
        }
        if (STATUS_SUCCEEDED(result = m_converter.generateJson(data, type, &json, indentStep)))
        {
          if (error) { *error = "unable to generate json"; }
          return result;
        }
      }
    }
    if (error) { *error = ""; }
    return result;
  }

protected:
private:
  IClient &m_client;
  IFlatbufferJson &m_converter;
};

}
}
