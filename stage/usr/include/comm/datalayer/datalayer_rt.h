#pragma once
#include "datalayer_defs.h"
#include "memory_generated.h"
#include "memory_map_generated.h"
#include "datalayer_types.h"
#include "variant.h"

namespace comm
{
namespace datalayer
{


class IMemoryOwner {
public:
  IMemoryOwner() = default;
  virtual ~IMemoryOwner() = default;

  // all member functions are realtime capable

  //ID contract to write
  virtual DlResult beginAccess(uint8_t*& data, uint32_t revision) = 0;
  virtual DlResult endAccess() = 0;

  virtual DlResult getSize(size_t& sizeBytes) const = 0;
  virtual DlResult getType(MemoryType& type) const = 0;

  virtual DlResult getMemoryMap(Variant &memMap) = 0;
  virtual DlResult setMemoryMap(const Variant &memoryMap) = 0;
};

class IMemoryUser {
public:
  IMemoryUser() = default;
  virtual ~IMemoryUser() = default;

  // all member functions are realtime capable

  virtual DlResult beginAccess(uint8_t*& data, uint32_t revision) = 0;
  virtual DlResult endAccess() = 0;

  virtual DlResult getSize(size_t& sizeBytes) = 0;
  virtual DlResult getType(MemoryType& type) = 0;

  virtual DlResult getMemoryMap(Variant &memMap) = 0;
};

}
}
