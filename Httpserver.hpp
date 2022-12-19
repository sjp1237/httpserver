#pragma once
#include"TcpServer.hpp"
#include"App_interface.hpp"
#include"ReactorServer.hpp"

namespace Server{
  class HttpServer{
    private:
    int listen_sock;
    int port;
    TcpServer* server=nullptr;
    EpollServer* _epoll; 
    public: 
      HttpServer(int _port):port(_port){
       server=TcpServer::GetTcpServer(port);
       listen_sock=server->Sock();
       _epoll=new EpollServer();
    }

    void InitServer(){
       _epoll->InitServer();//初始化epoll
       SetNonBlocking(listen_sock);
    }

    void Run(){
      Event_item* newitem=new Event_item(listen_sock,accepter,nullptr);
      newitem->R=_epoll;
      _epoll->Addevent(listen_sock,EPOLLIN|EPOLLET,newitem);
      LOG(success,"server run");    
      while(true){
         _epoll->Run();
      }
    }
  };
}
