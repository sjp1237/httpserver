#include"tool.hpp"

int main(){
   std::string parameter;  
   GetParameter(parameter);
   std::vector<std::string> parameters;
   //strsub1="qq=3250506022"
   //pasword=sjp3250506022"
   DecParameters(parameter,parameters,"&");
   //拆分qq 
   std::string qq;
   std::string value1;
   CutString(parameters[0],qq,value1,"=");

   cerr<<"parameter0: "<<parameters[0]<<endl;
   cerr<<"parameter1: "<<parameters[1]<<endl;
   cerr<<"qq"<<value1<<endl;
   //拆分密码
   std::string password;
   std::string value2;
   CutString(parameters[1],password,value2,"=");

   MYSQL* my=mysql_init(NULL);
   if(nullptr==mysql_real_connect(my,"127.0.0.1","root","Sjp325050,,,","sjp",3306,nullptr,0)){
     cerr<<"connect mysql fail"<<endl;
     return -1;
   }

  //select qq,pasword from blog where qq="1324432";
   std::string s="select pasword from blog where qq=\"";
   s+=value1;
   s+="\";";

   //cerr<<s<<endl;
   mysql_query(my,s.c_str());
   MYSQL_RES* result=mysql_store_result(my);
   my_ulonglong row=mysql_num_rows(result);
   cerr<<"row: "<<row<<endl;
   if(row>0){     
     MYSQL_ROW mysql_row=mysql_fetch_row(result);
     cerr<<"mysql_row: "<<*mysql_row<<endl;
     if(*(mysql_row)==value2){
       //登录成功
       cout<<"IS-SendPage: trueX";
       cout<<"Page-index: wwwroot/index1.htmlX";
     }
     else{
       //登录失败
     }

   }else{
     //找不到该用户，说明没有注册
     //返回该用户没有注册
     cout<<"IS-SendPage: trueX";
     cout<<"Page-index: wwwwroot/webpage/login-fail.htmlX";
   }
   free(my);
}
