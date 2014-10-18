
#include <unistd.h>
#include <sys/socket.h>

#include <iostream>
#include <set>
#include <string>

#include <xdrpp/srpc.h>
#include <xdrpp/rpcbind.hh>
#include <xdrpp/socket.h>

#include <include/rpcconfig.h>
#include <include/server.hh>
#include <include/client.h>

using namespace std;
using namespace xdr;

Client::Client()
{
    client = NULL;
}

Client::~Client()
{
    this->close();
}

void
Client::open(const std::string &host)
{
    if (isConnected()) {
        cout << "Already connected!" << endl;
        exit(1);
    }

    auto fd = tcp_connect(host.c_str(), UNIQUE_RPC_PORT);
    client = new srpc_client<api_v1>{fd.release()};
}

void
Client::close()
{
    if (isConnected()) {
        delete client;
        client = NULL;
    }
}

bool
Client::isConnected()
{
    return client != NULL;
}

bool
Client::create(const std::string &path, const std::string &val)
{
    kvpair args;

    args.key = path;
    args.val = val;

    std::unique_ptr<rpc_error_code> result = client->create(args);
    throw_from_error_code(*result);
    return *result == E_SUCCESS;
}

bool
Client::remove(const std::string &path)
{
    std::unique_ptr<rpc_error_code> result = client->remove(path);
    return *result == E_SUCCESS;
}

std::string
Client::get(const std::string &path)
{
    std::unique_ptr<val_or_err> result = client->get(path);
    if(!result->success()){
      throw_from_error_code(result->err());
    }

    return result->val();
}

void
Client::set(const std::string &path, const std::string &val)
{
    kvpair args;

    args.key = path;
    args.val = val;

    std::unique_ptr<rpc_error_code> result = client->set(args);
    throw_from_error_code(*result);
}

std::set<string>
Client::list(const string &path)
{
    std::unique_ptr<keys_or_err> result = client->list(path);
    std::set<string> keys;
    if(result->success()){
      for(auto s : result->vals()) keys.insert(s);
    } else {
      throw_from_error_code(result->err());
    }

    return keys;
}

// Private

void
Client::throw_from_error_code(rpc_error_code err){
  switch(err){
    case E_KEY_NOT_FOUND:
      throw ClientException(KEY_NOT_FOUND);
    case E_NO_PARENT:
      throw ClientException(NO_PARENT);
    case E_HAS_CHILDREN:
      throw ClientException(HAS_CHILDREN);
    case E_MALFORMED_KEY:
      throw ClientException(MALFORMED_KEY);
    case E_SUCCESS:
    case E_KEY_EXISTS: // create returns false here but does not throw
      return;
    default:
      throw ClientException(UNKNOWN_ERROR);
  }
}
