// Scaffolding originally generated from include/server.x.
// Edit to add functionality.

#include <iostream>

#include "server/serverimpl.hh"

api_v1_server::api_v1_server() {
  db = std::unique_ptr<ServerDB>(new ServerDB("kvstore.db"));
  // db->set("/", ""); // dummy entry to allow `list /`
}

std::unique_ptr<rpc_error_code>
api_v1_server::create(std::unique_ptr<kvpair> arg)
{
  std::unique_ptr<rpc_error_code> res(new rpc_error_code);

  std::string key = arg->key;
  std::string val = arg->val;

  // Check valid path
  if(!validate_path(key)){
    (*res) = E_MALFORMED_KEY;
    std::cout << "Created " << key << " Failed, MALFORMED KEY" << std::endl;
    return res;
  }

  // Check parent exists
  std::string parent(key);
  while(parent.length() > 0){
    char back = parent.back();
    parent.pop_back();
    if(back == '/') break;
  }
  if(parent != "" && !db->hasKey(parent)){
    (*res) = E_NO_PARENT;
    std::cout << "Created " << key << " Failed, PARENT [" << parent << "] NOT FOUND" << std::endl;
    return res;
  }

  bool hasKey = db->hasKey(arg.get()->key);
  if (hasKey) {
    (*res) = E_KEY_EXISTS;
    std::cout << "Created " << key << " Failed, KEY ALREADY EXISTS" << std::endl;
  } else {
    (*res) = E_SUCCESS;
    db->set(key, val);
    std::cout << "Created " << key << " Succeeded" << std::endl;
  }

  return res;
}

std::unique_ptr<rpc_error_code>
api_v1_server::remove(std::unique_ptr<longstring> arg)
{
  std::unique_ptr<rpc_error_code> res(new rpc_error_code);

  std::string key = *arg;

  // Check valid path
  if(!validate_path(key)){
    (*res) = E_MALFORMED_KEY;
    std::cout << "Delete " << key << " Failed, MALFORMED KEY" << std::endl;
    return res;
  }

  bool hasKey = db->hasKey(key);
  if (!hasKey) {
    (*res) = E_KEY_NOT_FOUND;
    std::cout << "Delete " << key << " Failed, KEY NOT FOUND" << std::endl;
    return res;
  }

  (*res) = E_SUCCESS;
  db->remove(key);
  std::cout << "Delete " << key << " Succeeded" << std::endl;

  return res;
}

std::unique_ptr<rpc_error_code>
api_v1_server::set(std::unique_ptr<kvpair> arg)
{
  std::unique_ptr<rpc_error_code> res(new rpc_error_code);

  std::string key = arg->key;
  std::string val = arg->val;

  // Check valid path
  if(!validate_path(key)){
    (*res) = E_MALFORMED_KEY;
    std::cout << "Set " << key << " Failed, MALFORMED KEY" << std::endl;
    return res;
  }

  bool hasKey = db->hasKey(key);
  if (!hasKey) {
    (*res) = E_KEY_NOT_FOUND;
    std::cout << "Set " << key << " Failed, KEY NOT FOUND" << std::endl;
    return res;
  }

  (*res) = E_SUCCESS;
  db->set(key, val);
  std::cout << "Set " << key << " Succeeded" << std::endl;

  return res;
}

std::unique_ptr<val_or_err>
api_v1_server::get(std::unique_ptr<longstring> arg)
{
  std::unique_ptr<val_or_err> res(new val_or_err(false));
  res->success(false);
  
  std::string key = *arg;

  // Check valid path
  if(!validate_path(key)){
    res->err() = E_MALFORMED_KEY;
    std::cout << "Get " << key << " Failed, MALFORMED KEY" << std::endl;
    return res;
  }

  bool hasKey = db->hasKey(key);
  if (!hasKey) {
    res->err() = E_KEY_NOT_FOUND;
    std::cout << "Get " << key << " Failed, KEY NOT FOUND" << std::endl;
    return res;
  }

  res->success(true);
  res->val() = db->get(key);
  std::cout << "Get " << key << " Succeeded" << std::endl;
  
  return res;
}

std::unique_ptr<keys_or_err>
api_v1_server::list(std::unique_ptr<longstring> arg)
{
  std::unique_ptr<keys_or_err> res(new keys_or_err(false));
  res->success(false);

  std::string key = *arg;

  // Check valid path. `list /` is a special (allowed) case
  if(key == "/") key = "";
  if(key != ""){
    if(!validate_path(key)){
      res->err() = E_MALFORMED_KEY;
      std::cout << "List " << key << " Failed, MALFORMED KEY" << std::endl;
      return res;
    }

    if (!db->hasKey(key)) {
      res->err() = E_KEY_NOT_FOUND;
      std::cout << "List " << key << " failed, KEY NOT FOUND" << std::endl;
      return res;
    }
  }

  res->success(true);
  res->vals() = xdr::xvector<keystring>();
  for(auto subkey : db->list(key)){
    std::cout << "Listing " << subkey << std::endl;
    subkey.erase(0, key.length() + 1); // chop prefix and leading slash
    res->vals().push_back(subkey);
  }

  std::cout << "List " << key << " succeeded:" << res->vals().size() << " items found" << std::endl;
  return res;
}

// Private:

bool
api_v1_server::validate_path(const std::string & path)
{
  bool valid = (
    path[0] == '/'                    // Must start with /
    && path[path.length() - 1] != '/' // Cannot end with /
  );

  // Alphanumeric + _ + /
  for(char ch : path) valid = valid && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '/');

  // No double slashes
  valid = valid && (path.find("//") == std::string::npos);

  return valid;
}
