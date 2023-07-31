#pragma once

// ---------------------------------------------------------------------------
//! @file       persistence_helper.h
//! @author     DC-AE/ESW2
//! @copyright  Bosch Rexroth Corporation http://www.boschrexroth.com
//! @version    1.0.0
//! @date       2019
// ---------------------------------------------------------------------------
//! This file is part of the persistence library
//! for other bundles for C.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include "datalayer.h"
#include "datalayer_system.h"
#include "persistence_helper_itf.h"

namespace comm {
  namespace datalayer {

    // forward references
    class Persistence;
    class DatalayerSystem;

    //! @brief This is the persistence helper class.
    //!
    //! Interpretation of 'path' or 'directory'
    //! If you want to save or load your data into the solution the persistence helper adds this path.
    //! Therefor you use just the file or directory you want to store your data.
    //! E.g. the path 'scheduler/programs.json' will be evaluated to e.g.
    //! '(SNAP_COMMON)/solutions/activeConfiguration/scheduler/programs.json'.
    //! You can also save and load the data to/from other locations.
    //! For relative path use '.' or '~' as first char.
    //! For absolute path use '/', '\' or '*:' as first char.
    //!
    //! \anchor <persistenceParam>
    //! Interpretation of 'persistenceParam'
    //! The configuration path within 'persistenceParam' will be merged with 'path' or 'directory'.
    //! E.g. the configuration path 'solutions/defaultConfig' and the path 'scheduler/programs.json' will
    //! be evaluated to '(SNAP_COMMON)/solutions/defaultConfig/scheduler/programs.json'
    //! The path shouldn't be relative or an absolute paths.
    //! If the variant type of 'persistenceParam' is unknown then the configuration path will be ignored
    //! and only 'path' is used.
    //!
    
    class PersistenceHelper
    {
    public:
      PersistenceHelper(DatalayerSystem* datalayer);
      virtual ~PersistenceHelper();

      //! @brief This method returns the pointer to the persistence helper C interface.
      const PersistenceHelperItf* getCInterface() const;

      //! @brief This method sets the pointer to a datalayer client.
      //! To set the datalayer client is necessary to read and write data via the datalayer
      //! and you run not within the same process as the datalayer.
      //! @param[in] client    pointer to datalayer client
      void setDatalayerClient(comm::datalayer::IClient* client);

      //! @brief This method starts the persistence helper.
      void start();

      //! @brief This method stops the persistence helper.
      void stop();

      //! @brief This method saves flatbuffer data into a given path.
      //! A json file will be created including a persistence header to be able to restore the date.
      //! Also a schema file will be created from the type and stored in types directory.
      //! A bfbs file will be created and stored in bfbs directory.
      //! This method is called within c interface function 'saveDataType'.
      //! @param[in]  data      data as flatbuffer
      //! @param[in]  type      flatbuffer type
      //! @param[in]  typeName  name of type (necessary for schema file name)
      //! @param[in]  path      path to store file (file is stored in persistence root path appended by this path)
      //! @return               Success or error
      //!
      //! @par Example:
      //! @code
      //!  comm::datalayer::Variant dataToken;
      //!  comm::datalayer::Variant dataTypeToken;
      //!  // create flatbuffers -> then save
      //!  auto result = persistenceHelper.save(dataToken, dataTypeToken, "token", "test/token.json");
      //!  if (comm::datalayer::STATUS_FAILED(result))
      //!  {
      //!    PersistenceDetailDiag diagnosis;
      //!    persistenceHelper.getLastError(diagnosis);
      //!    error(L"Failed to save, result: '%ls", A2W16(diagnosis.detailDiag.c_str()));
      //!  }
      //! @endcode
      comm::datalayer::DlResult save(const comm::datalayer::Variant& data, const comm::datalayer::Variant& type, const std::string& typeName, const std::string& path) const;

      //! @brief This method saves flatbuffer data into a given path.
      //! This method is called within c interface function 'saveDataTypeaddress'.
      //! The data type will be read via datalayer from the given address
      //! @param[in]  data          data as flatbuffer
      //! @param[in]  typeAddress   datalayer address to read flatbuffer type from
      //! @param[in]  path          path to store file (file is stored in persistence root path appended by this path)
      //! @return                   Success or error
      //!
      //! @par Example:
      //! @code
      //!  comm::datalayer::Variant dataToken;
      //!  // create flatbuffers -> then save
      //!  persistenceHelper.save(dataToken, "types/datalayer/token", "test/token.json");
      //! @endcode
      comm::datalayer::DlResult save(const comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path) const;

      //! @brief This method saves flatbuffer data into a given path.
      //! The data will be read from the give datalayer address.
      //! The data type address will be read from the metadata.
      //! This method is called within c interface function 'saveDataaddress'.
      //! @param[in]  dataAddress   datalayer address to read flatbuffer
      //! @param[in]  path          path to store file (file is stored in persistence root path appended by this path)
      //! @return                   Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.save("myComp/token", "test/token.json");
      //! @endcode
      comm::datalayer::DlResult save(const std::string& dataAddress, const std::string& path) const;

      //! @brief This method saves a json string as it is into a given path.
      //! This method is called within c interface function 'saveJson'.
      //! @param[in]  jsonString    json string
      //! @param[in]  path          path to store file (file is stored in persistence root path appended by this path)
      //! @return                   Success or error
      //!
      //! @par Example:
      //! @code
      //!  nlohmann::json j = {
      //!    {"test123", {
      //!      {"myKey", 123456},
      //!      {"myFavConrol", "ctrlX"}
      //!    }}
      //!  };
      //!  
      //!  std::string jsonString = j.dump(4);
      //!  persistenceHelper.saveJson(jsonString, "myJsonFile.json");
      //! @endcode
      comm::datalayer::DlResult saveJson(const std::string& jsonString, const std::string& path) const;


      //! @brief This method saves a file from source into destination.
      //! This method is called within c interface function 'saveFile'.
      //! @param[in]  destinationPath   path to store file
      //! @param[in]  sourcePath        path to to get file from
      //! @return                       Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.saveFile("testDir/datasave.json", "var/tmp/datasave.json");
      //! @endcode
      comm::datalayer::DlResult saveFile(const std::string& destinationPath, const std::string& sourcePath) const;

      //! @brief This method saves files from source into destination.
      //! This method is called within c interface function 'saveFiles'.
      //! @param[in]  files   map including the files to save (key = destinationPath, value = sourcePath)
      //! @return             Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::map<std::string, std::string> files = {
      //!    {"/AllDataTypes_copy.fbs", "/AllDataTypes.fbs"},
      //!    {"/token_copy.json", "/token.json"},
      //!    {"/myDir/token_copy.json", "/token.json"},
      //!    {"/AllDataTypes_copy2.fbs", "/AllDataTypes.fbs"}
      //!  };
      //!  persistenceHelper.saveFiles(files);
      //! @endcode
      comm::datalayer::DlResult saveFiles(const std::map<std::string, std::string>& files) const;

      //! @brief This method copies a source directory into destination.
      //! This method is called within c interface function 'saveDirectory'.
      //! @param[in]  destinationDirectory   destination directory
      //! @param[in]  sourceDirectory        source directory
      //! @return                            Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.saveDirectory("testDir/", "var/tmp/test/");
      //! @endcode
      comm::datalayer::DlResult saveDirectory(const std::string& destinationDirectory, const std::string& sourceDirectory) const;

      //! @brief This method loads a file from source into destination.
      //! This method is called within c interface function 'loadFile'.
      //! @param[in]  destinationPath   path to store file
      //! @param[in]  sourcePath        path to to get file from
      //! @return                       Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.loadFile("var/tmp/datasave.json", "testDir/datasave.json");
      //! @endcode
      comm::datalayer::DlResult loadFile(const std::string& destinationPath, const std::string& sourcePath) const;

      //! @brief This method loads a files from source into destination.
      //! This method is called within c interface function 'loadFiles'.
      //! @param[in]  files   map including the files to save (key = destinationPath, value = sourcePath)
      //! @return             Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::map<std::string, std::string> files = {
      //!    {"/AllDataTypes_copy.fbs", "/AllDataTypes.fbs"},
      //!    {"/token_copy.json", "/token.json"},
      //!    {"/myDir/token_copy.json", "/token.json"},
      //!    {"/AllDataTypes_copy2.fbs", "/AllDataTypes.fbs"}
      //!  };
      //!  persistenceHelper.loadFiles(files);
      //! @endcode
      comm::datalayer::DlResult loadFiles(const std::map<std::string, std::string>& files) const;

      //! @brief This method loads a source directory into a destination directory.
      //! This method is called within c interface function 'loadDirectory'.
      //! @param[in]  destinationDirectory   destination directory
      //! @param[in]  sourceDirectory        source directory
      //! @return                            Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.loadDirectory("var/tmp/testDir/", "test/");
      //! @endcode
      comm::datalayer::DlResult loadDirectory(const std::string& destinationDirectory, const std::string& sourceDirectory) const;

      //! @brief This method deletes a file.
      //! This method is called within c interface function 'deleteFile'.
      //! @param[in]  path   path of file to delete
      //! @return            Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.deleteFile("testDir/datasave.json");
      //! @endcode
      comm::datalayer::DlResult deleteFile(const std::string& path) const;

      //! @brief This method deletes files.
      //! This method is called within c interface function 'deleteFiles'.
      //! @param[in]  paths  vector of paths to delete
      //! @return            Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::vector<std::string> paths = { "/AllDataTypes_copy.fbs", "/myDir/token_copy.json" };
      //!  persistenceHelper.deleteFiles(paths);
      //! @endcode
      comm::datalayer::DlResult deleteFiles(const std::vector<std::string>& paths) const;

      //! @brief This method deletes a directory.
      //! This method is called within c interface function 'deleteDirectory'.
      //! @param[in]  directory   directory to delete
      //! @return                 Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.deleteDirectory("testDir/");
      //! @endcode
      comm::datalayer::DlResult deleteDirectory(const std::string& directory) const;

      //! @brief This method checks if a directory exists.
      //! This method is called within c interface function 'directoryExists'.
      //! @param[in]  directory   directory to check
      //! @return                 'true' if directory exists
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.directoryExists("testDir/");
      //! @endcode
      bool directoryExists(const std::string& directory) const;

      //! @brief This method checks if a file exists.
      //! This method is called within c interface function 'fileExists'.
      //! @param[in]  path   file to check
      //! @return            'true' if file exists
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.fileExists("testDir/testfile.json");
      //! @endcode
      bool fileExists(const std::string& path) const;


      //! @brief This method loads from a saved json file into flatbuffer data and flatbuffer type.
      //! The loaded file has to be a valid persistence helper json file.
      //! To restore the data the argument type is used.
      //! This method is called within c interface function 'loadData'.
      //! @param[in]  path      path to load file from
      //! @param[in]  type      flatbuffer type
      //! @param[out] data      flatbuffer data
      //! @return               Success or error
      //!
      //! @par Example:
      //! @code
      //!  comm::datalayer::Variant dataToken;
      //!  comm::datalayer::Variant dataTypeToken;
      //!  persistenceHelper.load("test/token.json", dataTypeToken, dataToken);
      //! @endcode
      comm::datalayer::DlResult loadData(const std::string& path, const comm::datalayer::Variant& type, comm::datalayer::Variant& data) const;

      //! @brief This method loads from a saved json file into flatbuffer data and flatbuffer type.
      //! The loaded file has to be a valid persistence helper json file.
      //! To restore the data the original data type, saved in the bfbs file, is used and returned.
      //! This method is called within c interface function 'loadDataType'.
      //! @param[in]  path      path to load file from
      //! @param[out] data      flatbuffer data
      //! @param[out] type      flatbuffer type
      //! @return               Success or error
      //!
      //! @par Example:
      //! @code
      //!  comm::datalayer::Variant dataToken;
      //!  comm::datalayer::Variant dataTypeToken;
      //!  persistenceHelper.load("test/token.json", dataToken, dataTypeToken);
      //! @endcode
      comm::datalayer::DlResult load(const std::string& path, comm::datalayer::Variant& data, comm::datalayer::Variant& type) const;

      //! @brief This method loads from a saved json file and writes the data via datalayer.
      //! The loaded file has to be a valid persistence helper json file.
      //! This method is called within c interface function 'loadDataaddress'.
      //! @param[in]  path          path to load file from
      //! @param[in]  dataAddress   datalayer address to write the data to
      //! @return                   Success or error
      //!
      //! @par Example:
      //! @code
      //!  persistenceHelper.load("test/token.json", "myComp/token/load");
      //! @endcode
      comm::datalayer::DlResult load(const std::string& path, const std::string& dataAddress) const;

      //! @brief This method loads from a saved json file and returns the data as json string.
      //! The loaded file has to be a valid persistence helper json file.
      //! This method is called within c interface function 'loadJson'.
      //! @param[in]  path        path to load file from
      //! @param[out] jsonString  string to store the data
      //! @return                 Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::string jsonString;
      //!  persistenceHelper.loadJson("test/token.json", jsonString);
      //! @endcode
      comm::datalayer::DlResult loadJson(const std::string& path, std::string& jsonString) const;


      //! @brief This method returns the root path of the persistence helper, which is the path to the active configuration.
      //! This method is called within c interface function 'getRootPath'.
      //! @param[out] rootPath  string to store the root path
      //! @return               Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::string rootPath;
      //!  persistenceHelper.getRootPath(rootPath);
      //! @endcode
      comm::datalayer::DlResult getRootPath(std::string& rootPath) const;


      //! @brief This method returns the last error occurred in the persistence helper.
      //! @note This method is not thread safe. Usage of persistence helper from other threads may
      //! override the last error.
      //! This method is called within c interface function 'getLastError'.
      //! @param[out] diagnosis detail diagnosis 
      //! @return               Success or error
      //!
      //! @par Example:
      //! @code
      //!  comm::datalayer::Variant data;
      //!  auto result = persistenceHelper.save(data, data, "invalid", "invalid");
      //!  if (comm::datalayer::STATUS_FAILED(result))
      //!  {
      //!    PersistenceDetailDiag diagnosis;
      //!    persistenceHelper.getLastError(diagnosis);
      //!    printf("\ndlResult = %ls", A2W16(diagnosis.dlResult.toString()));
      //!    printf("\ndetailDig = %ls", A2W16(diagnosis.detailDiag.c_str()));
      //!    printf("\nError code = %u", diagnosis.errorCode);
      //!    printf("\nError number = %u", diagnosis.errNbr);
      //!  }
      //!
      //!  persistenceHelper.save(data, data, "invalid", "invalid");
      //!  PersistenceDetailDiag diagnosis;
      //!  persistenceHelper.getLastError(diagnosis);
      //!  if (0 != diagnosis.errorCode)
      //!    retrun diagnosis.errorCode;
      //! @endcode
      comm::datalayer::DlResult getLastError(PersistenceDetailDiag& diagnosis) const;

      //! @brief This method browses a directory and returns the containing files.
      //! This method is called within c interface function 'browseDirectory'.
      //! @param[in]  directory               directory to browse
      //! @param[in]  includeDirecotries      subdirectories are found as well
      //! @param[out] files                   list of found files in directory
      //! @return                             Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::vector<std::string> files;
      //!  persistenceHelper.browseDirectory("testDir/", false, files);
      //! @endcode
      comm::datalayer::DlResult browseDirectory(const std::string& directory, bool includeDirecotries, std::vector<std::string>& files) const;

      //! @brief This method browses a directory and returns the files matching a regular expression.
      //! This method is called within c interface function 'browseDirectoryRegex'.
      //! @param[in]  directory               directory to browse
      //! @param[in]  includeDirecotries      subdirectories are found as well
      //! @param[in]  regularExpression       string representing a regular expression
      //! @param[out] files                   list of found files in directory
      //! @return                             Success or error
      //!
      //! @par Example:
      //! @code
      //!  std::vector<std::string> files;
      //!  // find all files matching '(any char(s))axis(any digit(s)).json'
      //!  persistenceHelper.browseDirectory("testDir/", false, "(.*)(axis()\d*).json", files);
      //! @endcode
      comm::datalayer::DlResult browseDirectory(const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files) const;


      //! @brief This method saves flatbuffer data into a given path.
      //! This method is called within c interface function 'saveDataType2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref save(const comm::datalayer::Variant& data, const comm::datalayer::Variant& type, const std::string& typeName, const std::string& path) const "save".
      comm::datalayer::DlResult save2(const ::comm::datalayer::Variant& persistenceParam, const comm::datalayer::Variant& data, const comm::datalayer::Variant& type, const std::string& typeName, const std::string& path) const;

      //! @brief This method saves flatbuffer data into a given path.
      //! This method is called within c interface function 'saveDataTypeaddress2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref save(const comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path) const "save".
      comm::datalayer::DlResult save2(const ::comm::datalayer::Variant& persistenceParam, const comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path) const;

      //! @brief This method saves flatbuffer data into a given path.
      //! This method is called within c interface function 'saveDataaddress2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref save(const std::string& dataAddress, const std::string& path) const "save".
      comm::datalayer::DlResult save2(const ::comm::datalayer::Variant& persistenceParam, const std::string& dataAddress, const std::string& path) const;

      //! @brief This method saves a json string as it is into a given path.
      //! This method is called within c interface function 'saveJson2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref saveJson(const std::string& jsonString, const std::string& path) const "saveJson".
      comm::datalayer::DlResult saveJson2(const ::comm::datalayer::Variant& persistenceParam, const std::string& jsonString, const std::string& path) const;

      //! @brief This method loads from a saved json file into flatbuffer data and flatbuffer type.
      //! This method is called within c interface function 'loadData2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadData(const std::string& path, const comm::datalayer::Variant& type, comm::datalayer::Variant& data) const "loadData".
      comm::datalayer::DlResult loadData2(const ::comm::datalayer::Variant& persistenceParam, const std::string& path, const comm::datalayer::Variant& type, comm::datalayer::Variant& data) const;

      //! @brief This method loads from a saved json file into flatbuffer data and flatbuffer type.
      //! This method is called within c interface function 'loadDataType2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref load(const std::string& path, comm::datalayer::Variant& data, comm::datalayer::Variant& type) const "load".
      comm::datalayer::DlResult load2(const ::comm::datalayer::Variant& persistenceParam, const std::string& path, comm::datalayer::Variant& data, comm::datalayer::Variant& type) const;

      //! @brief This method loads from a saved json file and writes the data via datalayer.
      //! This method is called within c interface function 'loadDataaddress2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref load(const std::string& path, const std::string& dataAddress) const "load".
      comm::datalayer::DlResult load2(const ::comm::datalayer::Variant& persistenceParam, const std::string& path, const std::string& dataAddress) const;

      //! @brief This method loads from a saved json file and returns the data as json string.
      //! This method is called within c interface function 'loadJson2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadJson(const std::string& path, std::string& jsonString) const "loadJson".
      comm::datalayer::DlResult loadJson2(const ::comm::datalayer::Variant& persistenceParam, const std::string& path, std::string& jsonString) const;

      //! @brief This method saves a file from source into destination.
      //! This method is called within c interface function 'saveFile2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref saveFile(const std::string& destinationPath, const std::string& sourcePath) const "saveFile".
      comm::datalayer::DlResult saveFile2(const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationPath, const std::string& sourcePath) const;

      //! @brief This method saves files from source into destination.
      //! This method is called within c interface function 'saveFiles2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref saveFiles(const std::map<std::string, std::string>& files) const "saveFile".
      comm::datalayer::DlResult saveFiles2(const ::comm::datalayer::Variant& persistenceParam, const std::map<std::string, std::string>& files) const;

      //! @brief This method copies a source directory into destination.
      //! This method is called within c interface function 'saveDirectory2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref saveDirectory(const std::string& destinationDirectory, const std::string& sourceDirectory) const "saveDirectory".
      comm::datalayer::DlResult saveDirectory2(const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationDirectory, const std::string& sourceDirectory) const;

      //! @brief This method loads a file from source into destination.
      //! This method is called within c interface function 'loadFile2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadFile(const std::string& destinationPath, const std::string& sourcePath) const "loadFile".
      comm::datalayer::DlResult loadFile2(const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationPath, const std::string& sourcePath) const;

      //! @brief This method loads a files from source into destination.
      //! This method is called within c interface function 'loadFiles2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadFiles(const std::map<std::string, std::string>& files) const "loadFiles".
      comm::datalayer::DlResult loadFiles2(const ::comm::datalayer::Variant& persistenceParam, const std::map<std::string, std::string>& files) const;

      //! @brief This method loads a source directory into a destination directory.
      //! This method is called within c interface function 'loadDirectory2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadDirectory(const std::string& destinationDirectory, const std::string& sourceDirectory) const "loadDirectory".
      comm::datalayer::DlResult loadDirectory2(const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationDirectory, const std::string& sourceDirectory) const;

      //! @brief This method deletes a file.
      //! This method is called within c interface function 'deleteFile2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref deleteFile(const std::string& path) const "deleteFile".
      comm::datalayer::DlResult deleteFile2(const ::comm::datalayer::Variant& persistenceParam, const std::string& path) const;

      //! @brief This method loads a files from source into destination.
      //! This method is called within c interface function 'deleteFiles2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadFiles(const std::map<std::string, std::string>& files) const "deleteFiles".
      comm::datalayer::DlResult deleteFiles2(const ::comm::datalayer::Variant& persistenceParam, const std::vector<std::string>& paths) const;

      //! @brief This method loads a source directory into a destination directory.
      //! This method is called within c interface function 'deleteDirectory2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref loadDirectory(const std::string& destinationDirectory, const std::string& sourceDirectory) const "deleteDirectory".
      comm::datalayer::DlResult deleteDirectory2(const ::comm::datalayer::Variant& persistenceParam, const std::string& directory) const;

      //! @brief This method checks if a directory exists.
      //! This method is called within c interface function 'directoryExists2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref directoryExists(const std::string& directory) const "directoryExists".
      bool directoryExists2(const ::comm::datalayer::Variant& persistenceParam, const std::string& directory) const;

      //! @brief This method checks if a file exists.
      //! This method is called within c interface function 'fileExists2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref fileExists(const std::string& path) const "fileExists".
      bool fileExists2(const ::comm::datalayer::Variant& persistenceParam, const std::string& path) const;


      //! @brief This method browses a directory and returns the containing files.
      //! This method is called within c interface function 'browseDirectory2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref browseDirectory(const std::string& directory, bool includeDirecotries, std::vector<std::string>& files) const "browseDirectory".
      comm::datalayer::DlResult browseDirectory2(const ::comm::datalayer::Variant& persistenceParam, const std::string& directory, bool includeDirecotries, std::vector<std::string>& files) const;

      //! @brief This method browses a directory and returns the files matching a regular expression.
      //! This method is called within c interface function 'browseDirectoryRegex2'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! For method documentation see \ref browseDirectory(const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files) const "browseDirectory".
      comm::datalayer::DlResult browseDirectory2(const ::comm::datalayer::Variant& persistenceParam, const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files) const;

      //! @brief This method returns the resulting absolute path based on the arguments.
      //! This method is called within c interface function 'getAbsolutePath'.
      //! For description of 'persistenceParam' see \ref persistenceParam. 
      //! @param[in]  persistenceParam        variant of type persistence param, including the configuration path
      //! @param[in]  path                    path to the configuration
      //! @param[out] absolutePath            the resulting absolute path
      //! @return                             Success or error
      //!
      //! @par Example:
      //! @code
      //! comm::datalayer::Variant persistenceParam;
      //! flatbuffers::FlatBufferBuilder builder;
      //! auto offset = comm::datalayer::CreatePersistenceParamDirect(builder, "solution/defaultConfig", "hokuspokus", "fidibus");
      //! builder.Finish(offset); 
      //! persistenceParam.copyFlatbuffers(builder);
      //! std::string absolutePath;
      //! auto result = getAbsolutePath(persistenceParam, "motion/axis.json", absolutePath);
      //! if (comm::datalayer::STATUS_FAILED(result)) // set error
      //! printf("\n%s", absolutePath.c_str()); // (e.g. /var/snap/rexroth-automationcore/current/solutions/defaultConfig/motion/axis.json)
      //! @endcode
      comm::datalayer::DlResult getAbsolutePath(const ::comm::datalayer::Variant& persistenceParam, const std::string& path, std::string& absolutePath) const;

      //! @brief This method starts persist NVRam to hardware. You should call this function at the end of your cycle that uses NVRAM. Persistance of
      //! NVRam is done after this call in hardware and took about 1,5ms
      //! @return                             Success or error
      comm::datalayer::DlResult persistsNvram() const;

      //! @brief This method returns the values of the persistence header.
      //! This method is called within c interface function 'getPersistenceHeader'.
      //! @param[in]  path                    path to the file to get the persistence header from
      //! @param[out] bfbsPath                the path to the bfbs file
      //! @param[out] persistenceVersion      the version of the persistence helper
      //! @return                             Success or error
      //!
      //! @par Example:
      //! @code
      //! std::string bsbfPAth;
      //! std::string persistenceVersion;
      //! auto result = getPersistenceHeader("motion/axis.json", bsbfPAth, persistenceVersion);
      //! if (comm::datalayer::STATUS_FAILED(result)) // set error
      //! printf("\n%s", bsbfPAth.c_str()); // (e.g. ./bfbs/motion.bfbs)
      //! printf("\n%s", persistenceVersion.c_str()); // (e.g. 0.0.1)
      //! @endcode
      comm::datalayer::DlResult getPersistenceHeader(const std::string& path, std::string& bfbsPath, std::string& persistenceVersion) const;

    protected:
    private:
      PersistenceHelperItf m_cItf;
      std::unique_ptr<comm::datalayer::Persistence> m_persistence;
    };
  }
}
