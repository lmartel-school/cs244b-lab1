enum rpc_error_code {
    E_SUCCESS = 0,
    E_KEY_NOT_FOUND = 1,
    E_NO_PARENT = 2,
    E_HAS_CHILDREN = 3,
    E_MALFORMED_KEY = 4,
    E_KEY_EXISTS = 5
};

typedef string longstring<>;
typedef string keystring<512>;

struct kvpair {
    string key<512>;
    string val<>;
};

union val_or_err switch (bool success) {
    case true:
        longstring val;
    default:
        rpc_error_code err;
};

union keys_or_err switch (bool success) {
    case true:
        keystring vals<>;
    default:
        rpc_error_code err;
};

program server_api {
  version api_v1 {
    rpc_error_code create(kvpair) = 1;
    rpc_error_code remove(longstring) = 2;
    rpc_error_code set(kvpair) = 3;
    val_or_err get(longstring) = 4;
    keys_or_err list(longstring) = 5;
} = 1;
} = 0x40048086;

