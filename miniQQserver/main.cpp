#include <iostream>
// #include "USER.h"
#include "SOCKET.h"

int main()
{
	// USER test;
	SOCKET socketserver;
	socketserver.Init();
	socketserver.LISTEN();
	// test.AddUser();

	return 0;
}
