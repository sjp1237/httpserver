#pragma once
#include<iostream>
#include<unistd.h>
#include<vector>
#include<fcntl.h>
#include<sys/epoll.h>

#include"ReactorServer.hpp"

using std::cout;
using std::endl;
//声明函数
bool SetNonBlocking(int fd);
int HanderTask(Event_item* item);
int writer(Event_item* item);

int accepter(Event_item* item);




int errnoer(Event_item* item);




