// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DIAGNOSIS_COMM_DATALAYER_H_
#define FLATBUFFERS_GENERATED_DIAGNOSIS_COMM_DATALAYER_H_

#include "flatbuffers/flatbuffers.h"

namespace comm {
namespace datalayer {

struct DiagMoreInfo;
struct DiagMoreInfoBuilder;
struct DiagMoreInfoT;

struct Diagnosis;
struct DiagnosisBuilder;
struct DiagnosisT;

struct DiagMoreInfoT : public flatbuffers::NativeTable {
  typedef DiagMoreInfo TableType;
  std::string key{};
  std::string value{};
};

struct DiagMoreInfo FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef DiagMoreInfoT NativeTableType;
  typedef DiagMoreInfoBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_KEY = 4,
    VT_VALUE = 6
  };
  const flatbuffers::String *key() const {
    return GetPointer<const flatbuffers::String *>(VT_KEY);
  }
  flatbuffers::String *mutable_key() {
    return GetPointer<flatbuffers::String *>(VT_KEY);
  }
  bool KeyCompareLessThan(const DiagMoreInfo *o) const {
    return *key() < *o->key();
  }
  int KeyCompareWithValue(const char *val) const {
    return strcmp(key()->c_str(), val);
  }
  const flatbuffers::String *value() const {
    return GetPointer<const flatbuffers::String *>(VT_VALUE);
  }
  flatbuffers::String *mutable_value() {
    return GetPointer<flatbuffers::String *>(VT_VALUE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_KEY) &&
           verifier.VerifyString(key()) &&
           VerifyOffset(verifier, VT_VALUE) &&
           verifier.VerifyString(value()) &&
           verifier.EndTable();
  }
  DiagMoreInfoT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(DiagMoreInfoT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<DiagMoreInfo> Pack(flatbuffers::FlatBufferBuilder &_fbb, const DiagMoreInfoT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct DiagMoreInfoBuilder {
  typedef DiagMoreInfo Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_key(flatbuffers::Offset<flatbuffers::String> key) {
    fbb_.AddOffset(DiagMoreInfo::VT_KEY, key);
  }
  void add_value(flatbuffers::Offset<flatbuffers::String> value) {
    fbb_.AddOffset(DiagMoreInfo::VT_VALUE, value);
  }
  explicit DiagMoreInfoBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<DiagMoreInfo> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DiagMoreInfo>(end);
    fbb_.Required(o, DiagMoreInfo::VT_KEY);
    return o;
  }
};

inline flatbuffers::Offset<DiagMoreInfo> CreateDiagMoreInfo(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> key = 0,
    flatbuffers::Offset<flatbuffers::String> value = 0) {
  DiagMoreInfoBuilder builder_(_fbb);
  builder_.add_value(value);
  builder_.add_key(key);
  return builder_.Finish();
}

inline flatbuffers::Offset<DiagMoreInfo> CreateDiagMoreInfoDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *key = nullptr,
    const char *value = nullptr) {
  auto key__ = key ? _fbb.CreateString(key) : 0;
  auto value__ = value ? _fbb.CreateString(value) : 0;
  return comm::datalayer::CreateDiagMoreInfo(
      _fbb,
      key__,
      value__);
}

flatbuffers::Offset<DiagMoreInfo> CreateDiagMoreInfo(flatbuffers::FlatBufferBuilder &_fbb, const DiagMoreInfoT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct DiagnosisT : public flatbuffers::NativeTable {
  typedef Diagnosis TableType;
  uint32_t mainDiagnosisCode = 0;
  uint32_t detailedDiagnosisCode = 0;
  std::string dynamicDescription{};
  std::string entity{};
  std::vector<std::unique_ptr<comm::datalayer::DiagMoreInfoT>> moreInfo{};
  std::vector<std::unique_ptr<comm::datalayer::DiagnosisT>> cause{};
};

struct Diagnosis FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef DiagnosisT NativeTableType;
  typedef DiagnosisBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MAINDIAGNOSISCODE = 4,
    VT_DETAILEDDIAGNOSISCODE = 6,
    VT_DYNAMICDESCRIPTION = 8,
    VT_ENTITY = 10,
    VT_MOREINFO = 12,
    VT_CAUSE = 14
  };
  uint32_t mainDiagnosisCode() const {
    return GetField<uint32_t>(VT_MAINDIAGNOSISCODE, 0);
  }
  bool mutate_mainDiagnosisCode(uint32_t _mainDiagnosisCode) {
    return SetField<uint32_t>(VT_MAINDIAGNOSISCODE, _mainDiagnosisCode, 0);
  }
  uint32_t detailedDiagnosisCode() const {
    return GetField<uint32_t>(VT_DETAILEDDIAGNOSISCODE, 0);
  }
  bool mutate_detailedDiagnosisCode(uint32_t _detailedDiagnosisCode) {
    return SetField<uint32_t>(VT_DETAILEDDIAGNOSISCODE, _detailedDiagnosisCode, 0);
  }
  const flatbuffers::String *dynamicDescription() const {
    return GetPointer<const flatbuffers::String *>(VT_DYNAMICDESCRIPTION);
  }
  flatbuffers::String *mutable_dynamicDescription() {
    return GetPointer<flatbuffers::String *>(VT_DYNAMICDESCRIPTION);
  }
  const flatbuffers::String *entity() const {
    return GetPointer<const flatbuffers::String *>(VT_ENTITY);
  }
  flatbuffers::String *mutable_entity() {
    return GetPointer<flatbuffers::String *>(VT_ENTITY);
  }
  const flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>> *moreInfo() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>> *>(VT_MOREINFO);
  }
  flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>> *mutable_moreInfo() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>> *>(VT_MOREINFO);
  }
  const flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Diagnosis>> *cause() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Diagnosis>> *>(VT_CAUSE);
  }
  flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Diagnosis>> *mutable_cause() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Diagnosis>> *>(VT_CAUSE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_MAINDIAGNOSISCODE) &&
           VerifyField<uint32_t>(verifier, VT_DETAILEDDIAGNOSISCODE) &&
           VerifyOffset(verifier, VT_DYNAMICDESCRIPTION) &&
           verifier.VerifyString(dynamicDescription()) &&
           VerifyOffset(verifier, VT_ENTITY) &&
           verifier.VerifyString(entity()) &&
           VerifyOffset(verifier, VT_MOREINFO) &&
           verifier.VerifyVector(moreInfo()) &&
           verifier.VerifyVectorOfTables(moreInfo()) &&
           VerifyOffset(verifier, VT_CAUSE) &&
           verifier.VerifyVector(cause()) &&
           verifier.VerifyVectorOfTables(cause()) &&
           verifier.EndTable();
  }
  DiagnosisT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(DiagnosisT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Diagnosis> Pack(flatbuffers::FlatBufferBuilder &_fbb, const DiagnosisT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct DiagnosisBuilder {
  typedef Diagnosis Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_mainDiagnosisCode(uint32_t mainDiagnosisCode) {
    fbb_.AddElement<uint32_t>(Diagnosis::VT_MAINDIAGNOSISCODE, mainDiagnosisCode, 0);
  }
  void add_detailedDiagnosisCode(uint32_t detailedDiagnosisCode) {
    fbb_.AddElement<uint32_t>(Diagnosis::VT_DETAILEDDIAGNOSISCODE, detailedDiagnosisCode, 0);
  }
  void add_dynamicDescription(flatbuffers::Offset<flatbuffers::String> dynamicDescription) {
    fbb_.AddOffset(Diagnosis::VT_DYNAMICDESCRIPTION, dynamicDescription);
  }
  void add_entity(flatbuffers::Offset<flatbuffers::String> entity) {
    fbb_.AddOffset(Diagnosis::VT_ENTITY, entity);
  }
  void add_moreInfo(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>>> moreInfo) {
    fbb_.AddOffset(Diagnosis::VT_MOREINFO, moreInfo);
  }
  void add_cause(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Diagnosis>>> cause) {
    fbb_.AddOffset(Diagnosis::VT_CAUSE, cause);
  }
  explicit DiagnosisBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Diagnosis> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Diagnosis>(end);
    return o;
  }
};

inline flatbuffers::Offset<Diagnosis> CreateDiagnosis(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t mainDiagnosisCode = 0,
    uint32_t detailedDiagnosisCode = 0,
    flatbuffers::Offset<flatbuffers::String> dynamicDescription = 0,
    flatbuffers::Offset<flatbuffers::String> entity = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>>> moreInfo = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<comm::datalayer::Diagnosis>>> cause = 0) {
  DiagnosisBuilder builder_(_fbb);
  builder_.add_cause(cause);
  builder_.add_moreInfo(moreInfo);
  builder_.add_entity(entity);
  builder_.add_dynamicDescription(dynamicDescription);
  builder_.add_detailedDiagnosisCode(detailedDiagnosisCode);
  builder_.add_mainDiagnosisCode(mainDiagnosisCode);
  return builder_.Finish();
}

inline flatbuffers::Offset<Diagnosis> CreateDiagnosisDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t mainDiagnosisCode = 0,
    uint32_t detailedDiagnosisCode = 0,
    const char *dynamicDescription = nullptr,
    const char *entity = nullptr,
    std::vector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>> *moreInfo = nullptr,
    const std::vector<flatbuffers::Offset<comm::datalayer::Diagnosis>> *cause = nullptr) {
  auto dynamicDescription__ = dynamicDescription ? _fbb.CreateString(dynamicDescription) : 0;
  auto entity__ = entity ? _fbb.CreateString(entity) : 0;
  auto moreInfo__ = moreInfo ? _fbb.CreateVectorOfSortedTables<comm::datalayer::DiagMoreInfo>(moreInfo) : 0;
  auto cause__ = cause ? _fbb.CreateVector<flatbuffers::Offset<comm::datalayer::Diagnosis>>(*cause) : 0;
  return comm::datalayer::CreateDiagnosis(
      _fbb,
      mainDiagnosisCode,
      detailedDiagnosisCode,
      dynamicDescription__,
      entity__,
      moreInfo__,
      cause__);
}

flatbuffers::Offset<Diagnosis> CreateDiagnosis(flatbuffers::FlatBufferBuilder &_fbb, const DiagnosisT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline DiagMoreInfoT *DiagMoreInfo::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<DiagMoreInfoT>(new DiagMoreInfoT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void DiagMoreInfo::UnPackTo(DiagMoreInfoT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = key(); if (_e) _o->key = _e->str(); }
  { auto _e = value(); if (_e) _o->value = _e->str(); }
}

inline flatbuffers::Offset<DiagMoreInfo> DiagMoreInfo::Pack(flatbuffers::FlatBufferBuilder &_fbb, const DiagMoreInfoT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateDiagMoreInfo(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<DiagMoreInfo> CreateDiagMoreInfo(flatbuffers::FlatBufferBuilder &_fbb, const DiagMoreInfoT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const DiagMoreInfoT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _key = _fbb.CreateString(_o->key);
  auto _value = _o->value.empty() ? 0 : _fbb.CreateString(_o->value);
  return comm::datalayer::CreateDiagMoreInfo(
      _fbb,
      _key,
      _value);
}

inline DiagnosisT *Diagnosis::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<DiagnosisT>(new DiagnosisT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Diagnosis::UnPackTo(DiagnosisT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = mainDiagnosisCode(); _o->mainDiagnosisCode = _e; }
  { auto _e = detailedDiagnosisCode(); _o->detailedDiagnosisCode = _e; }
  { auto _e = dynamicDescription(); if (_e) _o->dynamicDescription = _e->str(); }
  { auto _e = entity(); if (_e) _o->entity = _e->str(); }
  { auto _e = moreInfo(); if (_e) { _o->moreInfo.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->moreInfo[_i] = std::unique_ptr<comm::datalayer::DiagMoreInfoT>(_e->Get(_i)->UnPack(_resolver)); } } }
  { auto _e = cause(); if (_e) { _o->cause.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->cause[_i] = std::unique_ptr<comm::datalayer::DiagnosisT>(_e->Get(_i)->UnPack(_resolver)); } } }
}

inline flatbuffers::Offset<Diagnosis> Diagnosis::Pack(flatbuffers::FlatBufferBuilder &_fbb, const DiagnosisT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateDiagnosis(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Diagnosis> CreateDiagnosis(flatbuffers::FlatBufferBuilder &_fbb, const DiagnosisT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const DiagnosisT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _mainDiagnosisCode = _o->mainDiagnosisCode;
  auto _detailedDiagnosisCode = _o->detailedDiagnosisCode;
  auto _dynamicDescription = _o->dynamicDescription.empty() ? 0 : _fbb.CreateString(_o->dynamicDescription);
  auto _entity = _o->entity.empty() ? 0 : _fbb.CreateString(_o->entity);
  auto _moreInfo = _o->moreInfo.size() ? _fbb.CreateVector<flatbuffers::Offset<comm::datalayer::DiagMoreInfo>> (_o->moreInfo.size(), [](size_t i, _VectorArgs *__va) { return CreateDiagMoreInfo(*__va->__fbb, __va->__o->moreInfo[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _cause = _o->cause.size() ? _fbb.CreateVector<flatbuffers::Offset<comm::datalayer::Diagnosis>> (_o->cause.size(), [](size_t i, _VectorArgs *__va) { return CreateDiagnosis(*__va->__fbb, __va->__o->cause[i].get(), __va->__rehasher); }, &_va ) : 0;
  return comm::datalayer::CreateDiagnosis(
      _fbb,
      _mainDiagnosisCode,
      _detailedDiagnosisCode,
      _dynamicDescription,
      _entity,
      _moreInfo,
      _cause);
}

inline const comm::datalayer::Diagnosis *GetDiagnosis(const void *buf) {
  return flatbuffers::GetRoot<comm::datalayer::Diagnosis>(buf);
}

inline const comm::datalayer::Diagnosis *GetSizePrefixedDiagnosis(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<comm::datalayer::Diagnosis>(buf);
}

inline Diagnosis *GetMutableDiagnosis(void *buf) {
  return flatbuffers::GetMutableRoot<Diagnosis>(buf);
}

inline bool VerifyDiagnosisBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<comm::datalayer::Diagnosis>(nullptr);
}

inline bool VerifySizePrefixedDiagnosisBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<comm::datalayer::Diagnosis>(nullptr);
}

inline void FinishDiagnosisBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<comm::datalayer::Diagnosis> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedDiagnosisBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<comm::datalayer::Diagnosis> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<comm::datalayer::DiagnosisT> UnPackDiagnosis(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<comm::datalayer::DiagnosisT>(GetDiagnosis(buf)->UnPack(res));
}

inline std::unique_ptr<comm::datalayer::DiagnosisT> UnPackSizePrefixedDiagnosis(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<comm::datalayer::DiagnosisT>(GetSizePrefixedDiagnosis(buf)->UnPack(res));
}

}  // namespace datalayer
}  // namespace comm

#endif  // FLATBUFFERS_GENERATED_DIAGNOSIS_COMM_DATALAYER_H_
