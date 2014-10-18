enum rpc_error_code {
    E_SUCCESS = 0,
    E_KEY_NOT_FOUND = 1,
    E_NO_PARENT = 2,
    E_HAS_CHILDREN = 3,
    E_MALFORMED_KEY = 4,
    E_KEY_EXISTS = 5
};

typedef string longstring<>;

struct kvpair {
    string key<512>;
    string val<>;
};

union val_or_err switch (int status) {
    case E_SUCCESS:
        string val<>;
    default:
        rpc_error_code err;
};

struct string_list_node {
    string val<>;
    string_list_node *next;
};
typedef string_list* string_list;

union vals_or_err switch (int status) {
    case E_SUCCESS:
        string_list vals;
    default:
        rpc_error_code err;
};


program server_api {
  version api_v1 {
    rpc_error_code create(kvpair) = 1;
    rpc_error_code remove(longstring) = 2;
    rpc_error_code set(kvpair) = 3;
    val_or_err get(longstring) = 4;
    vals_or_err list(longstring) = 5;
} = 1;
} = 0x40048086;

