// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WATCHLIST_COMM_DATALAYER_H_
#define FLATBUFFERS_GENERATED_WATCHLIST_COMM_DATALAYER_H_

#include "flatbuffers/flatbuffers.h"

namespace comm {
namespace datalayer {

struct Watchlist;
struct WatchlistBuilder;
struct WatchlistT;

struct WatchlistT : public flatbuffers::NativeTable {
  typedef Watchlist TableType;
  std::string name{};
  std::vector<std::string> items{};
};

struct Watchlist FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef WatchlistT NativeTableType;
  typedef WatchlistBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_ITEMS = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  flatbuffers::String *mutable_name() {
    return GetPointer<flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *items() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_ITEMS);
  }
  flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *mutable_items() {
    return GetPointer<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_ITEMS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_ITEMS) &&
           verifier.VerifyVector(items()) &&
           verifier.VerifyVectorOfStrings(items()) &&
           verifier.EndTable();
  }
  WatchlistT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(WatchlistT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Watchlist> Pack(flatbuffers::FlatBufferBuilder &_fbb, const WatchlistT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct WatchlistBuilder {
  typedef Watchlist Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Watchlist::VT_NAME, name);
  }
  void add_items(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> items) {
    fbb_.AddOffset(Watchlist::VT_ITEMS, items);
  }
  explicit WatchlistBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Watchlist> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Watchlist>(end);
    return o;
  }
};

inline flatbuffers::Offset<Watchlist> CreateWatchlist(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> items = 0) {
  WatchlistBuilder builder_(_fbb);
  builder_.add_items(items);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<Watchlist> CreateWatchlistDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *items = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto items__ = items ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*items) : 0;
  return comm::datalayer::CreateWatchlist(
      _fbb,
      name__,
      items__);
}

flatbuffers::Offset<Watchlist> CreateWatchlist(flatbuffers::FlatBufferBuilder &_fbb, const WatchlistT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline WatchlistT *Watchlist::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<WatchlistT>(new WatchlistT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void Watchlist::UnPackTo(WatchlistT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = name(); if (_e) _o->name = _e->str(); }
  { auto _e = items(); if (_e) { _o->items.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->items[_i] = _e->Get(_i)->str(); } } }
}

inline flatbuffers::Offset<Watchlist> Watchlist::Pack(flatbuffers::FlatBufferBuilder &_fbb, const WatchlistT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateWatchlist(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Watchlist> CreateWatchlist(flatbuffers::FlatBufferBuilder &_fbb, const WatchlistT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const WatchlistT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  auto _items = _o->items.size() ? _fbb.CreateVectorOfStrings(_o->items) : 0;
  return comm::datalayer::CreateWatchlist(
      _fbb,
      _name,
      _items);
}

inline const comm::datalayer::Watchlist *GetWatchlist(const void *buf) {
  return flatbuffers::GetRoot<comm::datalayer::Watchlist>(buf);
}

inline const comm::datalayer::Watchlist *GetSizePrefixedWatchlist(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<comm::datalayer::Watchlist>(buf);
}

inline Watchlist *GetMutableWatchlist(void *buf) {
  return flatbuffers::GetMutableRoot<Watchlist>(buf);
}

inline bool VerifyWatchlistBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<comm::datalayer::Watchlist>(nullptr);
}

inline bool VerifySizePrefixedWatchlistBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<comm::datalayer::Watchlist>(nullptr);
}

inline void FinishWatchlistBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<comm::datalayer::Watchlist> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedWatchlistBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<comm::datalayer::Watchlist> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<comm::datalayer::WatchlistT> UnPackWatchlist(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<comm::datalayer::WatchlistT>(GetWatchlist(buf)->UnPack(res));
}

inline std::unique_ptr<comm::datalayer::WatchlistT> UnPackSizePrefixedWatchlist(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<comm::datalayer::WatchlistT>(GetSizePrefixedWatchlist(buf)->UnPack(res));
}

}  // namespace datalayer
}  // namespace comm

#endif  // FLATBUFFERS_GENERATED_WATCHLIST_COMM_DATALAYER_H_
