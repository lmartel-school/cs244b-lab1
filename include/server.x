enum rpc_error_code {
    SUCCESS = 0,
    /*
     * Set, Get or Remove failed because they key was not found.
     */
    KEY_NOT_FOUND = 1,
    /*
     * Create operation failed because the key has no parent.
     */
    NO_PARENT = 2,
    /*
     * The key has children so it cannot be deleted.
     */
    HAS_CHILDREN = 3,
    /*
     * The key path violates our formatting rules
     */
    MALFORMED_KEY = 4
};

typedef string longstring<>;

struct kvpair {
    string key<512>;
    string val<>;
};

union val_or_err switch (int status) {
    case SUCCESS:
        string val<>;
    default:
        rpc_error_code err;
};

program server_api {
  version api_v1 {
    rpc_error_code create(kvpair) = 1;
    rpc_error_code remove(longstring) = 2;
    rpc_error_code set(kvpair) = 3;
    retpair get(longstring) = 4;
    // TODO list
} = 1;
} = 0x40048086;

