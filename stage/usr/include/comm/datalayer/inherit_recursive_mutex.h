#pragma once

#include <mutex>
#ifdef __linux__
#include <pthread.h>
#endif

namespace comm {
namespace datalayer {

class InheritMutex : public std::mutex
{
public:
  InheritMutex()
  {
#ifdef __linux__
    // Destroy the underlying mutex
    ::pthread_mutex_destroy(native_handle());

    // Create mutex attribute with desired protocol and type
    ::pthread_mutexattr_t attr;
    ::pthread_mutexattr_init(&attr);
    ::pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
    // Initialize the underlying mutex
    ::pthread_mutex_init(native_handle(), &attr);
    // The attribute shouldn't be needed any more
    ::pthread_mutexattr_destroy(&attr);
#endif
  };

  virtual ~InheritMutex() {};

protected:
private:
};

class InheritRecursiveMutex : public std::recursive_mutex
{
public:
  InheritRecursiveMutex()
  {
#ifdef __linux__
    // Destroy the underlying mutex
    ::pthread_mutex_destroy(native_handle());

    // Create mutex attribute with desired protocol and type
    ::pthread_mutexattr_t attr;
    ::pthread_mutexattr_init(&attr);
    ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    ::pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
    // Initialize the underlying mutex
    ::pthread_mutex_init(native_handle(), &attr);
    // The attribute shouldn't be needed any more
    ::pthread_mutexattr_destroy(&attr);
#endif
  };

  virtual ~InheritRecursiveMutex() {};

protected:
private:
};

}
}
