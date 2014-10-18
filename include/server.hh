// -*- C++ -*-
// Automatically generated from include/server.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_INCLUDE_SERVER_HH_INCLUDED__
#define __XDR_INCLUDE_SERVER_HH_INCLUDED__ 1

#include <xdrpp/types.h>

enum rpc_error_code : std::uint32_t {
  SUCCESS = 0,
  KEY_NOT_FOUND = 1,
  NO_PARENT = 2,
  HAS_CHILDREN = 3,
  MALFORMED_KEY = 4,
};
namespace xdr {
template<> struct xdr_traits<::rpc_error_code>
  : xdr_integral_base<::rpc_error_code, std::uint32_t> {
  static constexpr bool is_enum = true;
  static constexpr bool is_numeric = false;
  static const char *enum_name(::rpc_error_code val) {
    switch (val) {
    case ::SUCCESS:
      return "SUCCESS";
    case ::KEY_NOT_FOUND:
      return "KEY_NOT_FOUND";
    case ::NO_PARENT:
      return "NO_PARENT";
    case ::HAS_CHILDREN:
      return "HAS_CHILDREN";
    case ::MALFORMED_KEY:
      return "MALFORMED_KEY";
    default:
      return nullptr;
    }
  }
};
}

using longstring = xdr::xstring<>;

struct kvpair {
  xdr::xstring<512> key{};
  xdr::xstring<> val{};
};
namespace xdr {
template<> struct xdr_traits<::kvpair>
  : xdr_struct_base<field_ptr<::kvpair,
                              decltype(::kvpair::key),
                              &::kvpair::key>,
                    field_ptr<::kvpair,
                              decltype(::kvpair::val),
                              &::kvpair::val>> {
  template<typename Archive> static void
  save(Archive &ar, const ::kvpair &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
  }
  template<typename Archive> static void
  load(Archive &ar, ::kvpair &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
  }
};
}

struct val_or_err {
private:
  std::uint32_t status_;
  union {
    xdr::xstring<> val_;
    rpc_error_code err_;
  };

public:
  static_assert (sizeof (int) <= 4, "union discriminant must be 4 bytes");

  static constexpr int _xdr_field_number(std::uint32_t which) {
    return which == SUCCESS ? 1
      : 2;
  }
  template<typename _F, typename...A> static bool
  _xdr_with_mem_ptr(_F &_f, std::uint32_t which, A&&...a) {
    switch (which) {
    case SUCCESS:
      _f(&val_or_err::val_, std::forward<A>(a)...);
      return true;
    default:
      _f(&val_or_err::err_, std::forward<A>(a)...);
      return true;
    }
  }

  std::uint32_t _xdr_discriminant() const { return status_; }
  void _xdr_discriminant(std::uint32_t which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of status in val_or_err");
    if (fnum != _xdr_field_number(status_)) {
      this->~val_or_err();
      status_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, status_, *this);
    }
  }
  val_or_err(std::int32_t which = std::int32_t{}) : status_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, status_, *this);
  }
  val_or_err(const val_or_err &source) : status_(source.status_) {
    _xdr_with_mem_ptr(xdr::field_constructor, status_, *this, source);
  }
  val_or_err(val_or_err &&source) : status_(source.status_) {
    _xdr_with_mem_ptr(xdr::field_constructor, status_, *this,
                      std::move(source));
  }
  ~val_or_err() { _xdr_with_mem_ptr(xdr::field_destructor, status_, *this); }
  val_or_err &operator=(const val_or_err &source) {
    if (_xdr_field_number(status_) 
        == _xdr_field_number(source.status_))
      _xdr_with_mem_ptr(xdr::field_assigner, status_, *this, source);
    else {
      this->~val_or_err();
      status_ = std::uint32_t(-1);
      _xdr_with_mem_ptr(xdr::field_constructor, status_, *this, source);
    }
    status_ = source.status_;
    return *this;
  }
  val_or_err &operator=(val_or_err &&source) {
    if (_xdr_field_number(status_)
         == _xdr_field_number(source.status_))
      _xdr_with_mem_ptr(xdr::field_assigner, status_, *this,
                        std::move(source));
    else {
      this->~val_or_err();
      status_ = std::uint32_t(-1);
      _xdr_with_mem_ptr(xdr::field_constructor, status_, *this,
                        std::move(source));
    }
    status_ = source.status_;
    return *this;
  }

  std::int32_t status() const { return std::int32_t(status_); }
  val_or_err &status(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xstring<> &val() {
    if (_xdr_field_number(status_) == 1)
      return val_;
    throw xdr::xdr_wrong_union("val_or_err: val accessed when not selected");
  }
  const xdr::xstring<> &val() const {
    if (_xdr_field_number(status_) == 1)
      return val_;
    throw xdr::xdr_wrong_union("val_or_err: val accessed when not selected");
  }
  rpc_error_code &err() {
    if (_xdr_field_number(status_) == 2)
      return err_;
    throw xdr::xdr_wrong_union("val_or_err: err accessed when not selected");
  }
  const rpc_error_code &err() const {
    if (_xdr_field_number(status_) == 2)
      return err_;
    throw xdr::xdr_wrong_union("val_or_err: err accessed when not selected");
  }
};
namespace xdr {
template<> struct xdr_traits<::val_or_err> : xdr_traits_base {
  static constexpr bool is_class = true;
  static constexpr bool is_union = true;
  static constexpr bool has_fixed_size = false;

  using union_type = ::val_or_err;
  using discriminant_type = decltype(std::declval<union_type>().status());

  static constexpr const char *union_field_name(std::uint32_t which) {
    return which == SUCCESS ? "val"
      : "err";
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::val_or_err &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of status in val_or_err");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::val_or_err &obj) {
    xdr::archive(ar, obj.status(), "status");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.status(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of status in val_or_err");
  }
  template<typename Archive> static void
  load(Archive &ar, ::val_or_err &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "status");
    obj.status(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.status(), ar, obj,
                          union_field_name(which));
  }
};
}

struct api_v1 {
  static constexpr std::uint32_t program = 1074036870;
  static constexpr const char *program_name = "server_api";
  static constexpr std::uint32_t version = 1;
  static constexpr const char *version_name = "api_v1";

  struct create_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 1;
    static constexpr const char *proc_name = "create";
    using arg_type = kvpair;
    using arg_wire_type = kvpair;
    using res_type = rpc_error_code;
    using res_wire_type = rpc_error_code;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.create(std::forward<A>(a)...)) {
      return c.create(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.create(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.create(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct remove_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 2;
    static constexpr const char *proc_name = "remove";
    using arg_type = longstring;
    using arg_wire_type = longstring;
    using res_type = rpc_error_code;
    using res_wire_type = rpc_error_code;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.remove(std::forward<A>(a)...)) {
      return c.remove(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.remove(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.remove(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct set_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 3;
    static constexpr const char *proc_name = "set";
    using arg_type = kvpair;
    using arg_wire_type = kvpair;
    using res_type = rpc_error_code;
    using res_wire_type = rpc_error_code;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.set(std::forward<A>(a)...)) {
      return c.set(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.set(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.set(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct get_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 4;
    static constexpr const char *proc_name = "get";
    using arg_type = longstring;
    using arg_wire_type = longstring;
    using res_type = retpair;
    using res_wire_type = retpair;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.get(std::forward<A>(a)...)) {
      return c.get(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.get(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.get(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  template<typename T, typename...A> static bool
  call_dispatch(T &&t, std::uint32_t proc, A &&...a) {
    switch(proc) {
    case 1:
      t.template dispatch<create_t>(std::forward<A>(a)...);
      return true;
    case 2:
      t.template dispatch<remove_t>(std::forward<A>(a)...);
      return true;
    case 3:
      t.template dispatch<set_t>(std::forward<A>(a)...);
      return true;
    case 4:
      t.template dispatch<get_t>(std::forward<A>(a)...);
      return true;
    }
    return false;
  }

  template<typename _XDRBASE> struct client : _XDRBASE {
    using _XDRBASE::_XDRBASE;

    template<typename..._XDRARGS> auto
    create(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<create_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<create_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    remove(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<remove_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<remove_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    set(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<set_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<set_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    get(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<get_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<get_t>(_xdr_args...);
    }
  };
};

#endif // !__XDR_INCLUDE_SERVER_HH_INCLUDED__
