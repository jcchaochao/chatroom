#include"json.hpp"
using json=nlohmann::json;
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
string func1(){
    json js;
    js["msg_type"]=2;
    js["from"]="zs";
    js["to"]="ls";
    js["msg"]="hello";
    string sendBuf=js.dump();
   return sendBuf;
}
int main(){
    string recv=func1();
    json jsbuf=json::parse(recv);
    cout<<jsbuf["msg_type"]<<endl;
     cout<<jsbuf["from"]<<endl;
      cout<<jsbuf["to"]<<endl;
       cout<<jsbuf["msg"]<<endl;
}