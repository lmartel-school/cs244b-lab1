// -*- C++ -*-
// Scaffolding originally generated from include/server.x.
// Edit to add functionality.

#ifndef __XDR_SERVER_SERVERIMPL_HH_INCLUDED__
#define __XDR_SERVER_SERVERIMPL_HH_INCLUDED__ 1

#include "include/server.hh"

class api_v1_server {
public:
  using rpc_interface_type = api_v1;

  api_v1_server();

  std::unique_ptr<rpc_error_code> create(std::unique_ptr<kvpair> arg);
  std::unique_ptr<rpc_error_code> remove(std::unique_ptr<longstring> arg);
  std::unique_ptr<rpc_error_code> set(std::unique_ptr<kvpair> arg);
  std::unique_ptr<val_or_err> get(std::unique_ptr<longstring> arg);
  std::unique_ptr<keys_or_err> list(std::unique_ptr<longstring> arg);

private:
  std::unique_ptr<ServerDB> db;
  bool validate_path(const std::string & path);
};

#endif // !__XDR_SERVER_SERVERIMPL_HH_INCLUDED__
