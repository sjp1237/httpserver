httpserver:main.cc
	g++ -o httpserver main.cc  Log.cc HttpProtocol.cc ReactorServer.cc App_interface.cc tool.cc -std=c++11 -lpthread -g

clean:
	rm -f httpserver
