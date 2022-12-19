#include"tool.hpp"
using namespace std;

int main(){
   std::string parameter;  
   GetParameter(parameter);
   std::vector<std::string> parameters;
   //strsub1="qq=3250506022"
   //strsub2="name=sjp&pasword=sjp3250506022"
   DecParameters(parameter,parameters,"&");
   //拆分qq 
   std::string qq;
   std::string value1;
   CutString(parameters[0],qq,value1,"=");

   //拆分昵称
   std::string name;
   std::string value2;
   CutString(parameters[1],name,value2,"=");

   //拆分密码
   std::string password;
   std::string value3;
   CutString(parameters[2],password,value3,"=");

//   std::cerr<<"value1:"<<value1<<std::endl;
//   std::cerr<<"value2:"<<value2<<std::endl;
//   std::cerr<<"value3:"<<value3<<std::endl;
//
   

   MYSQL* my=mysql_init(NULL);
   if(nullptr==mysql_real_connect(my,"127.0.0.1","root","Sjp325050,,,","sjp",3306,nullptr,0)){
     cerr<<"connect mysql fail"<<endl;
     return -1;
   }

   //判断该账号是否存在
   //select qq from blog where qq="123456";
   std::string s="select qq from blog where qq=\"";
   s+=value1;
   s+="\";";
   mysql_query(my,s.c_str());
   MYSQL_RES* result=mysql_store_result(my);
   my_ulonglong row=mysql_num_rows(result);
   if(row>0){
     //说明该账号已经存在，所以注册失败     
     cout<<"IS-SendPage: trueX";
     cout<<"Page-index: wwwroot/webpage/register-fail.htmlX";
     return 0;
   }
   //说明该账号在数据库中没有存在，因此可以注册新账号
   //insert into blog values("123456","张三","fdskj");
   s="insert into blog values(\"";
   s+=value1;
   s+="\",\"";
   s+=value2;
   s+="\",\"";
   s+=value3;
   s+="\");";
   mysql_query(my,s.c_str());
   cout<<"IS-SendPage: trueX";
   cout<<"Page-index: wwwroot/webpage/register-success.htmlX";
}
