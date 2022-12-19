#include"App_interface.hpp"


bool SetNonBlocking(int fd){
  int flags=fcntl(fd,F_GETFL,0);
  fcntl(fd,F_SETFL,flags|O_NONBLOCK);
}


//读取请求
int accepter(Event_item* item){
  //std::cout<<"accepter begin"<<endl;
  int listen_sock=item->socket;
  while(true){
    struct sockaddr peer;
    socklen_t len;
    int newfd=accept(listen_sock,&peer,&len);
    //cout<<"accept :"<<newfd<<endl;
    if(newfd>0){
     // LOG(1,"accept success");
      SetNonBlocking(newfd);
      Event_item* newitem=new Event_item(newfd,HanderTask,nullptr);
      newitem->R=item->R;
      newitem->socket=newfd;
      //将读取到文件描述符放进reactor中
      item->R->Addevent(newfd,EPOLLIN|EPOLLET,newitem); 
    }
    else{
      //读取失败
      LOG(WARING,"accepter fail");
        return 0;
        //读取错误
    }
    //cout<<"accepter end"<<endl;
  }
}

//读取http请求的数据，并发送数据给客户端
int HanderTask(Event_item* item){
  LOG(INFO,"recver begin");
  item->RecvRequest();
  item->SendResponse();
  item->R->Deletevent(item->socket);
   close(item->socket);
 // item->writer=writer;
 // item->R->Modevent(item->socket,EPOLLET|EPOLLIN|EPOLLOUT,item);
  return 0;
}

//int writer(Event_item* item){
//  LOG(INFO,"writer begin");
//  item->SendResponse();
//  item->R->Deletevent(item->socket);
//  close(item->socket);
//  return 0;
//}
//
