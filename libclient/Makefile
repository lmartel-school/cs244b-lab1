
LIBCLIENT_SRC := libclient/client.cc

LIBCLIENT_OBJ := $(LIBCLIENT_SRC:.cc=.o)

libclient/%.o: libclient/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

libclient/libclient.a: $(LIBCLIENT_OBJ) include/server.h
	$(AR) -r $@ $(LIBCLIENT_OBJ)

