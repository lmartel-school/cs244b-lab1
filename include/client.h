
#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <set>
#include <string>

class Client {
public:
    Client();
    ~Client();
    /*
     * Connect to a server
     */
    void open(const std::string &host);
    /*
     * Disconnect from a server
     */
    void close();
    /*
     * Test if still connected to a server
     *
     * Return Value: true if connected
     */
    bool isConnected();
    /*
     * Creates a key with specified path and value
     *
     * Return Value: true if key was created, false if key already exists
     */
    bool create(const std::string &path, const std::string &val);
    /*
     * Removes a key
     *
     * Return Value: true if key was removed, false if the key does not exist
     */
    bool remove(const std::string &path);
    /*
     * Get the value of the specified key
     *
     * Return Value: Value of the key
     * Throws an exception if the key is not found
     */
    std::string get(const std::string &path);
    /*
     * Set the value of the specified key
     *
     * Throws an exception if the key is not found
     */
    void set(const std::string &path, const std::string &val);
    /*
     * List all sub-keys
     *
     * Return Value: A set of all keys
     * Throws an exception if the key is not found
     */
    std::set<std::string> list(const std::string &path);
private:
    xdr::srpc_client<api_v1> *client;
};

#endif /* __CLIENT_H__ */

