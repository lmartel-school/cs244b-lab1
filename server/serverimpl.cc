// Scaffolding originally generated from include/server.x.
// Edit to add functionality.

#include "server/serverimpl.hh"

rpc_error_code 

std::unique_ptr<rpc_error_code>
api_v1_server::create(std::unique_ptr<kvpair> arg)
{
  std::unique_ptr<rpc_error_code> res(new rpc_error_code);
  
  std::string key = arg->key;
  std::string val = arg->val;
  std::unique_ptr<bool> res(new bool);

  // Check valid path
  if(!validate_path(key)){
    (*res) = MALFORMED_KEY;
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
  if(!db.hasKey(parent)){
    (*res) = NO_PARENT;
    std::cout << "Created " << key << " Failed, PARENT NOT FOUND" << std::endl;
    return res;
  }

  bool hasKey = db.hasKey(arg.get()->key);
  if (hasKey) {
    (*res) = KEY_EXISTS;
    std::cout << "Created " << key << " Failed, KEY ALREADY EXISTS" << std::endl;
  } else {
    (*res) = SUCCESS;
    db.set(key, val);
    std::cout << "Created " << key << " Succeeded" << std::endl;
  }

  return res;
}

std::unique_ptr<rpc_error_code>
api_v1_server::remove(std::unique_ptr<longstring> arg)
{
  std::unique_ptr<rpc_error_code> res(new rpc_error_code);
  
  // Fill in function body here
  
  return res;
}

std::unique_ptr<rpc_error_code>
api_v1_server::set(std::unique_ptr<kvpair> arg)
{
  std::unique_ptr<rpc_error_code> res(new rpc_error_code);
  
  // Fill in function body here
  
  return res;
}

std::unique_ptr<retpair>
api_v1_server::get(std::unique_ptr<longstring> arg)
{
  std::unique_ptr<retpair> res(new retpair);
  
  // Fill in function body here
  
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
