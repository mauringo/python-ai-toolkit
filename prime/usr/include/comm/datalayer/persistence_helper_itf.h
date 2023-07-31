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


//!  @par List of available functions in persistence helper interface. 
//! <TABLE>
//! <TR><TH>           Function                                         </TH><TH> Interface version </TH></TR>
//! <TR><TD id="st_e"> @ref saveDataType                                </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataTypeaddress                         </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataaddress                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveJson                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadData                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataType                                </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataaddress                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadJson                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFile                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFiles                                   </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDirectory                               </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFile                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFiles                                   </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDirectory                               </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFile                                  </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFiles                                 </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteDirectory                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref directoryExists                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref fileExists                                  </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref getRootPath                                 </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref getLastError                                </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectory                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectoryRegex                        </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataType2                               </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataTypeaddress2                        </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataaddress2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveJson2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadData2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataType2                               </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataaddress2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFile2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFiles2                                  </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDirectory2                              </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFile2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFiles2                                  </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDirectory2                              </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFile2                                 </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFiles2                                </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteDirectory2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref directoryExists2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref fileExists2                                 </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectory2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectoryRegex2                       </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref getAbsolutePath                             </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref persistNvram                                </TD><TD> 0.2.0             </TD></TR>
//! <TR><TD id="st_e"> @ref getPersistenceHeader                        </TD><TD> 0.3.0             </TD></TR>
//! </TABLE>
//!

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include <map>
#include "datalayer.h"

// ---------------------------------------------------------------------------
// Declaration of symbolic constants
// ---------------------------------------------------------------------------

//! @brief Interface version of the persistence bundle interface
#define PERSISTENCE_C_INTERFACE_VERSION                   "0.3.0"
//! @brief Consumer range of the persistence bundle interface
#define PERSISTENCE_C_INTERFACE_DEFAULT_CONSUMER_RANGE    "[0.3.0,1.0.0)"
//! @brief Name of the persistence bundle interface
#define PERSISTENCE_C_INTERFACE_NAME                      "com.boschrexroth.comm.datalayer.persistence"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum PersistenceErrorCodes
  {
    PERSISTENCE_DIAG_OK = 0,                  //! everything is okay
    PERSISTENCE_DIAG_ERR_GENERATE_JSON,       //! failed to generate json (maybe wrong data or type?)
    PERSISTENCE_DIAG_ERR_PARSE_JSON,          //! failed to parse json (maybe wrong type?)
    PERSISTENCE_DIAG_ERR_NO_VALID_DIRECTORY,  //! no valid directory found
    PERSISTENCE_DIAG_ERR_NO_VALID_HEADER,     //! no valid header found in json file
    PERSISTENCE_DIAG_ERR_BFBS_NOT_SET,        //! bfbs path in json file missing
    PERSISTENCE_DIAG_ERR_BFBS_NOT_VALID,      //! file is no valid bfbs
    PERSISTENCE_DIAG_ERR_INVAL_TYPENAME,      //! type name is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_TYPEADDR,      //! type address is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_DATAADDR,      //! data address is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_PATH,          //! path is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_JSON,          //! json string is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_FILES,         //! files are not valid (maybe empty list?)
    PERSISTENCE_DIAG_ERR_MKDIR,               //! error during directory create
    PERSISTENCE_DIAG_ERR_FILE_WRITE,          //! error write into a file 
    PERSISTENCE_DIAG_ERR_FILE_OPEN,           //! error opening a file
    PERSISTENCE_DIAG_ERR_FILE_DELETE,         //! error file delete
    PERSISTENCE_DIAG_ERR_FILE_NOT_EXISTS,     //! the given file doesn't exist
    PERSISTENCE_DIAG_ERR_DIR_NOT_EXISTS,      //! the given directory doesn't exist
    PERSISTENCE_DIAG_ERR_DIR_COPY,            //! error during directory copy
    PERSISTENCE_DIAG_ERR_DIR_DELETE,          //! error during directory delete
    PERSISTENCE_DIAG_ERR_SET_PERMISSIONS,     //! unable to set permissions
    PERSISTENCE_DIAG_ERR_DL_READ,             //! error returned from datalayer read
    PERSISTENCE_DIAG_ERR_DL_WRITE,            //! error returned from datalayer write
    PERSISTENCE_DIAG_ERR_DL_METADATA,         //! error returned from datalayer read metadata
    PERSISTENCE_DIAG_ERR_FIND_FILE,           //! find of file failed
    PERSISTENCE_DIAG_ERR_EVALUATE_PATH,       //! can't evaluate path
    PERSISTENCE_DIAG_ERR_NO_REGEX,            //! not a valid regular expression
    PERSISTENCE_DIAG_ERR_EXCEPTION,           //! c++ exception occurred
    PERSISTENCE_DIAG_ERR_VARINAT_TYPE         //! type of variant is invalid
  }PersistenceErrorCodes;

  typedef struct PersistenceDetailDiag
  {
    PersistenceErrorCodes errorCode;          //! persistence helper specific error code
    comm::datalayer::DlResult dlResult;       //! datalayer result
    std::uint32_t errNbr;                     //! errno if available
    std::string detailDiag;                   //! detailed diagnosis text
  }PersistenceDetailDiag;

  //! @brief This is the interface for the persistence helper for other bundles for commands from C.
  //! For detailed documentation see 'persistence_helper.h'.
  typedef struct PersistenceHelperItf
  {
    void *handle;
    std::uint32_t(*saveDataType)(const void* handle, const ::comm::datalayer::Variant& data, const ::comm::datalayer::Variant& type, const std::string& typeName, const std::string& path);
    std::uint32_t(*saveDataTypeaddress)(const void* handle, const ::comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path);
    std::uint32_t(*saveDataaddress)(const void* handle, const std::string& dataAddress, const std::string& path);
    std::uint32_t(*saveJson)(const void* handle, const std::string& jsonString, const std::string& path);

    std::uint32_t(*loadData)(const void* handle, const std::string& path, const ::comm::datalayer::Variant& type, ::comm::datalayer::Variant& data);
    std::uint32_t(*loadDataType)(const void* handle, const std::string& path, ::comm::datalayer::Variant& data, ::comm::datalayer::Variant& type);
    std::uint32_t(*loadDataaddress)(const void* handle, const std::string& path, const std::string& dataAddress);
    std::uint32_t(*loadJson)(const void* handle, const std::string& path, std::string& jsonString);

    std::uint32_t(*saveFile)(const void* handle, const std::string& destinationPath, const std::string& sourcePath);
    std::uint32_t(*saveFiles)(const void* handle, const std::map<std::string, std::string>& files);
    std::uint32_t(*saveDirectory)(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory);
    std::uint32_t(*loadFile)(const void* handle, const std::string& destinationPath, const std::string& sourcePath);
    std::uint32_t(*loadFiles)(const void* handle, const std::map<std::string, std::string>& files);
    std::uint32_t(*loadDirectory)(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory);
    std::uint32_t(*deleteFile)(const void* handle, const std::string& path);
    std::uint32_t(*deleteFiles)(const void* handle, const std::vector<std::string>& paths);
    std::uint32_t(*deleteDirectory)(const void* handle, const std::string& directory);
    bool(*directoryExists)(const void* handle, const std::string& directory);
    bool(*fileExists)(const void* handle, const std::string& path);

    std::uint32_t(*getRootPath)(const void* handle, std::string& rootPath);

    std::uint32_t(*getLastError)(const void* handle, PersistenceDetailDiag& diagnosis);

    std::uint32_t(*browseDirectory)(const void* handle, const std::string& directory, bool includeDirecotries, std::vector<std::string>& files);
    std::uint32_t(*browseDirectoryRegex)(const void* handle, const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files);

    
    std::uint32_t(*saveDataType2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const ::comm::datalayer::Variant& data, const ::comm::datalayer::Variant& type, const std::string& typeName, const std::string& path);
    std::uint32_t(*saveDataTypeaddress2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const ::comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path);
    std::uint32_t(*saveDataaddress2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& dataAddress, const std::string& path);
    std::uint32_t(*saveJson2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& jsonString, const std::string& path);

    std::uint32_t(*loadData2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, const ::comm::datalayer::Variant& type, ::comm::datalayer::Variant& data);
    std::uint32_t(*loadDataType2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, ::comm::datalayer::Variant& data, ::comm::datalayer::Variant& type);
    std::uint32_t(*loadDataaddress2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, const std::string& dataAddress);
    std::uint32_t(*loadJson2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, std::string& jsonString);

    std::uint32_t(*saveFile2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationPath, const std::string& sourcePath);
    std::uint32_t(*saveFiles2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::map<std::string, std::string>& files);
    std::uint32_t(*saveDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationDirectory, const std::string& sourceDirectory);
    std::uint32_t(*loadFile2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationPath, const std::string& sourcePath);
    std::uint32_t(*loadFiles2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::map<std::string, std::string>& files);
    std::uint32_t(*loadDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationDirectory, const std::string& sourceDirectory);
    std::uint32_t(*deleteFile2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path);
    std::uint32_t(*deleteFiles2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::vector<std::string>& paths);
    std::uint32_t(*deleteDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory);
    bool(*directoryExists2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory);
    bool(*fileExists2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path);

    std::uint32_t(*browseDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory, bool includeDirecotries, std::vector<std::string>& files);
    std::uint32_t(*browseDirectoryRegex2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files);

    std::uint32_t(*getAbsolutePath)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, std::string& absolutePath);
    std::uint32_t(*persistNvram)(const void* handle);

    std::uint32_t(*getPersistenceHeader)(const void* handle, const std::string& path, std::string& bfbsPath, std::string& persistenceVersion);

    void *reserved[100];
  } PersistenceHelperItf;

#ifdef __cplusplus
}
#endif
