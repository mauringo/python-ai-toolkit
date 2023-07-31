#pragma once
#include <map>
#include <string>
#include "datalayer.h"

namespace comm {
namespace datalayer{

class Rule;
class Logger;
class DatalayerSystem;

class ComplianceChecker
{
public:
  ComplianceChecker(DatalayerSystem* system);
  virtual ~ComplianceChecker();

  //! Target of a log message
  enum class Target
  {
    TARGET_MESSAGE, //! informational message
    TARGET_WARNING, //! warning message
    TARGET_ERROR    //! error message
  };

  //! The ignore list is a map of rule ids and a set of strings which contains node names.
  //! All error and warning messages will be converted to info messages if a node is in this list for a particular rule id.
  typedef std::map<uint32_t, std::set<std::string>> IgnoreList;

  //! Log callback. For each message a LogCallback will be called
  //! @param[in] target   Log target
  //! @param[in] node     Node address for the log
  //! @param[in] text     Log message
  //! @return none
  typedef std::function<void(Target target, const std::string& node, const std::string& text)> LogCallback;

  //! Sets a log callback. All log messages of compliance checker will be forwarded
  //! to this callback.
  //! @param[in] callback   Callback all messages will be forwarded
  //! @return none
  void setLogCallback(const LogCallback& callback);

  //! Sets a ignore list for warnings and messages. 
  //! to this callback.
  //! @param[in] callback   Callback all messages will be forwarded
  //! @return none
  void setIgnoreList(const IgnoreList& ignoreList);

  //! Print all rules using set log callback
  //! @param[in] detail    If true - detailed information for each rule will be loged
  //! @return none
  void printRules(bool detail = false);

  //! Get count of rules
  //! @return Count of rules
  size_t getRulesCount();

  //! Get count of checked paths
  //! @return Count of checked paths
  size_t getPathCount();

  //! Checks a datalayer path (recursive) for compliance
  //! @param[in] connection   Connection string for datalayer client
  //! @param[in] path         Path to be checked for complience
  //! @return none
  void check(const std::string& connection, const std::string& path);

  void setVerbose(bool verbose);
protected:
private:
  void checkRecursive(const std::string& path, std::vector<Rule*>& rules);
  std::function<void(Target, uint32_t, const std::string&)> logCallback();

  std::string m_connectionString;
  std::string& m_curPath;
  DatalayerSystem* m_system;

  Logger* m_logger;
  LogCallback m_logCallback;
  IgnoreList m_ignoreList;
  size_t m_pathCount = 0;
  bool m_verbose = false;
};

}
}
