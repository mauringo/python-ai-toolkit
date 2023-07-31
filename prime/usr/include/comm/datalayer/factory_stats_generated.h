// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_FACTORYSTATS_COMM_DATALAYER_H_
#define FLATBUFFERS_GENERATED_FACTORYSTATS_COMM_DATALAYER_H_

#include "flatbuffers/flatbuffers.h"

namespace comm {
namespace datalayer {

struct FactoryStats;
struct FactoryStatsBuilder;
struct FactoryStatsT;

struct FactoryStatsT : public flatbuffers::NativeTable {
  typedef FactoryStats TableType;
  uint32_t numClients = 0;
  uint32_t numProviders = 0;
  uint32_t openClientRequests = 0;
  uint32_t openProviderRequests = 0;
};

struct FactoryStats FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FactoryStatsT NativeTableType;
  typedef FactoryStatsBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NUMCLIENTS = 4,
    VT_NUMPROVIDERS = 6,
    VT_OPENCLIENTREQUESTS = 8,
    VT_OPENPROVIDERREQUESTS = 10
  };
  uint32_t numClients() const {
    return GetField<uint32_t>(VT_NUMCLIENTS, 0);
  }
  bool mutate_numClients(uint32_t _numClients) {
    return SetField<uint32_t>(VT_NUMCLIENTS, _numClients, 0);
  }
  uint32_t numProviders() const {
    return GetField<uint32_t>(VT_NUMPROVIDERS, 0);
  }
  bool mutate_numProviders(uint32_t _numProviders) {
    return SetField<uint32_t>(VT_NUMPROVIDERS, _numProviders, 0);
  }
  uint32_t openClientRequests() const {
    return GetField<uint32_t>(VT_OPENCLIENTREQUESTS, 0);
  }
  bool mutate_openClientRequests(uint32_t _openClientRequests) {
    return SetField<uint32_t>(VT_OPENCLIENTREQUESTS, _openClientRequests, 0);
  }
  uint32_t openProviderRequests() const {
    return GetField<uint32_t>(VT_OPENPROVIDERREQUESTS, 0);
  }
  bool mutate_openProviderRequests(uint32_t _openProviderRequests) {
    return SetField<uint32_t>(VT_OPENPROVIDERREQUESTS, _openProviderRequests, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_NUMCLIENTS) &&
           VerifyField<uint32_t>(verifier, VT_NUMPROVIDERS) &&
           VerifyField<uint32_t>(verifier, VT_OPENCLIENTREQUESTS) &&
           VerifyField<uint32_t>(verifier, VT_OPENPROVIDERREQUESTS) &&
           verifier.EndTable();
  }
  FactoryStatsT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(FactoryStatsT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<FactoryStats> Pack(flatbuffers::FlatBufferBuilder &_fbb, const FactoryStatsT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct FactoryStatsBuilder {
  typedef FactoryStats Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_numClients(uint32_t numClients) {
    fbb_.AddElement<uint32_t>(FactoryStats::VT_NUMCLIENTS, numClients, 0);
  }
  void add_numProviders(uint32_t numProviders) {
    fbb_.AddElement<uint32_t>(FactoryStats::VT_NUMPROVIDERS, numProviders, 0);
  }
  void add_openClientRequests(uint32_t openClientRequests) {
    fbb_.AddElement<uint32_t>(FactoryStats::VT_OPENCLIENTREQUESTS, openClientRequests, 0);
  }
  void add_openProviderRequests(uint32_t openProviderRequests) {
    fbb_.AddElement<uint32_t>(FactoryStats::VT_OPENPROVIDERREQUESTS, openProviderRequests, 0);
  }
  explicit FactoryStatsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FactoryStats> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FactoryStats>(end);
    return o;
  }
};

inline flatbuffers::Offset<FactoryStats> CreateFactoryStats(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t numClients = 0,
    uint32_t numProviders = 0,
    uint32_t openClientRequests = 0,
    uint32_t openProviderRequests = 0) {
  FactoryStatsBuilder builder_(_fbb);
  builder_.add_openProviderRequests(openProviderRequests);
  builder_.add_openClientRequests(openClientRequests);
  builder_.add_numProviders(numProviders);
  builder_.add_numClients(numClients);
  return builder_.Finish();
}

flatbuffers::Offset<FactoryStats> CreateFactoryStats(flatbuffers::FlatBufferBuilder &_fbb, const FactoryStatsT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline FactoryStatsT *FactoryStats::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<FactoryStatsT>(new FactoryStatsT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void FactoryStats::UnPackTo(FactoryStatsT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = numClients(); _o->numClients = _e; }
  { auto _e = numProviders(); _o->numProviders = _e; }
  { auto _e = openClientRequests(); _o->openClientRequests = _e; }
  { auto _e = openProviderRequests(); _o->openProviderRequests = _e; }
}

inline flatbuffers::Offset<FactoryStats> FactoryStats::Pack(flatbuffers::FlatBufferBuilder &_fbb, const FactoryStatsT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateFactoryStats(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<FactoryStats> CreateFactoryStats(flatbuffers::FlatBufferBuilder &_fbb, const FactoryStatsT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const FactoryStatsT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _numClients = _o->numClients;
  auto _numProviders = _o->numProviders;
  auto _openClientRequests = _o->openClientRequests;
  auto _openProviderRequests = _o->openProviderRequests;
  return comm::datalayer::CreateFactoryStats(
      _fbb,
      _numClients,
      _numProviders,
      _openClientRequests,
      _openProviderRequests);
}

inline const comm::datalayer::FactoryStats *GetFactoryStats(const void *buf) {
  return flatbuffers::GetRoot<comm::datalayer::FactoryStats>(buf);
}

inline const comm::datalayer::FactoryStats *GetSizePrefixedFactoryStats(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<comm::datalayer::FactoryStats>(buf);
}

inline FactoryStats *GetMutableFactoryStats(void *buf) {
  return flatbuffers::GetMutableRoot<FactoryStats>(buf);
}

inline bool VerifyFactoryStatsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<comm::datalayer::FactoryStats>(nullptr);
}

inline bool VerifySizePrefixedFactoryStatsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<comm::datalayer::FactoryStats>(nullptr);
}

inline void FinishFactoryStatsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<comm::datalayer::FactoryStats> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedFactoryStatsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<comm::datalayer::FactoryStats> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<comm::datalayer::FactoryStatsT> UnPackFactoryStats(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<comm::datalayer::FactoryStatsT>(GetFactoryStats(buf)->UnPack(res));
}

inline std::unique_ptr<comm::datalayer::FactoryStatsT> UnPackSizePrefixedFactoryStats(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<comm::datalayer::FactoryStatsT>(GetSizePrefixedFactoryStats(buf)->UnPack(res));
}

}  // namespace datalayer
}  // namespace comm

#endif  // FLATBUFFERS_GENERATED_FACTORYSTATS_COMM_DATALAYER_H_
