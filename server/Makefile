
SERVER_SRC := server/server.cc \
			  server/serverimpl.cc \
			  server/sqlite3.c

SERVER_OBJ := $(SERVER_SRC:.c=.o)
SERVER_OBJ := $(SERVER_OBJ:.cc=.o)

server/%.o: server/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

server/%.o: server/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

generatexdrc: include/server.x
	$(XDRC) -serverhh -o server/serverimpl.h $<
	$(XDRC) -servercc -o server/serverimpl.cc $<

server/server: $(SERVER_OBJ)
	$(LD) -o $@ $(LDFLAGS) $(SERVER_OBJ) $(LIBS)
