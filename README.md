
Lab #1
======

The purpose of Lab #1 is to acquaint you with the concept of Remote
Procedure Calls (RPCs).  You will building a simple key-value store
similar to the Zookeeper paper you read for class, but with just a
single (unreplicated) server.  In the subsequent lab we will make this
reliable and you can use this as the foundation for your group
project.

Build Dependencies
-----------------

 * gmake
 * gcc or clang with C++11
 * bison
 * flex
 * pandoc

Getting Started
---------------

Clone the source code with:

        $ git clone http://cs244b.scs.stanford.edu/labs/lab1.git

XDRPP
-----

<fill me in>

Define RPC Protocol
-------------------

First you will need to define the RPC protocol and use the `xdrc`
compiler to generate the server and client definitions.

Below is a part of the `include/server.x` protocol definition you will
need to modify.  We already filled in APIs for create, remove, set.
It is missing both get and list.  The get call returns a particular
key, and list returns a set of all keys under a given path.

        program server_api {
            version api_v1 {
                bool create(kvpair) = 1;
                bool remove(longstring) = 2;
                bool set(kvpair) = 3;
                // TODO: You will need to fill in more calls here
                // ...
            } = 1;
        } = 0x40048086;

Review `include/client.h` to see what parameters, return values and
error codes you will need to return to the client.  Here is a summary
of the API you will need to implement.

`bool create(string key, string value)`
:   This method creates a key with the specified value.  On success the method 
    returns true.  If the key already exists it should return false.  For any 
    other errors or malformed keys (i.e. keys with spaces, not beginning with a 
    '/') we should throw an exception.
`bool remove(string key)`
:   This method removes a key and returns true on success.  Otherwise it will 
    return a failure.
`string get(string key)`
:   This method returns the value of the specified key.  If the key does not 
    exist it will throw an exception.
`void set(string key, string value)`
:   This method sets the value of the specified key.  If the key does not exist 
    it will throw an exception.
`key_list list(string key)`
:   This method will return a set of all sub-keys.  The strings should contain 
    just the name of sub-key, and not the full path of the key.  If the parent 
    key does not exist it will throw an exception.

Once complete you complete the RPC definition, use the `xdrc` compiler
(located in `xdrpp/xdrc/xdrc`) to create the XDR definitions in
(`include/server.hh`) as follows:

    $ make include/server.hh

The XDR compiler will also generate the server stubs
(`server/serverimpl.{cc,h}`) that you will fill in next.  N.B. If you
later modify the protocol you will need to regenerate and merge these
files by hand.  To generate the server scaffolding, run:

    $ make scaffold

Since you will edit these files, you may want to add them to your git
repository with:

    $ git add server/serverimpl.{cc,hh}

You should choose a unique TCP port number to run your service.  To do this 
modify the define UNIQUE_RPC_PORT in include/rpcconfig.h.  Choose a random 
number above 6100.

RPC Client Library
------------------

The client library provides a useful wrapper around the RPC interface.
RPC only allows functions to pass in a single parameter and single
return value, and thus you will be using structures to pass multiple
parameters.  The include/client.h header file documents the expected
behavior of these functions and you can use shell/shell.cc as a
reference.

RPC Server
----------

With the `xdrc` compiler you should have generated serverimpl.cc
already and you will need to fill in the implementation.  Your
implementation will use the facilities provided to you by XDRPP to
parse the request, and serialize the results.  Your code should do all
the necessary handling to access the database, and return errors when
necessary.

As part of the implementation you will need to instantiate the
database.  We provided you with a simple persistent key-value store in
serverdb.h.  It provides you with hasKey, get, set, remove, and list,
operations that you will use to implement the full system.

ServerDB will not do any sanity checking for you.  For example it is
your responsibility to prevent the client from deleting a key that has
children.  Nor should a client be able to create a key with no parent.
The server should sanity check that key names only contain letters,
numbers, and slashes to divide the hierarchy.


RPC Shell
---------

We provided a simple shell for you to test your program.  In one
terminal run the server.

        # server/server

In another you can run the shell by passing in the IP address of the
server.

        # shell/shell 127.0.0.1
        > create /test abc
        CREATED
        > delete /test
        DELETED
        > list /
        > list /test
        KEY NOT FOUND
        >

You can run a test script using the shell as well

        $ shell/shell 127.0.0.1 test.script

Please do not modify the output of shell/shell.cc or the syntax of
existing commands as we will be using the script interface for
grading.  Note that the interface is a bit brittle and does not
support values with spaces.

