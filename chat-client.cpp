#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

using namespace std;

class makeClient
{
  public:
  string ip;
  int port;
  int server;
  int client;
  bool same=true;
  makeClient(string address,int portt)
  {
    ip=address;
    port=portt;
    makeSocket();
  }
  void makeSocket()
  {
    server=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_add;
    server_add.sin_family=AF_INET;
    server_add.sin_port=htons(port);
    inet_pton(AF_INET,ip.c_str(),&server_add.sin_addr);
    client=connect(server,(struct sockaddr*)&server_add,sizeof(server_add));
    string name;
    cout<<"Enter Your Name : ";
    getline(cin,name);
    send(server,name.c_str(),sizeof(name),0);
    thread recvi(&makeClient::reciving,this,name);
    recvi.detach();
    sending(name);
  }
  void sending(string name)
  {
      string str;
      while(str!="exit")
      {
        cout<<"You : ";
        getline(cin,str);
        int r=send(server,str.c_str(),str.length(),0);
      }
  }

  void reciving(string name)
  {
    char buffer[4096];
    int r;
    while(true)
    {
       memset(buffer, 0, sizeof(buffer));
       r=recv(server,buffer,4096,0);
       for(int i=0;i<name.length();i++)
       {
          if(name[i]!=buffer[i])
          {
            same=false;
            break;
          }
          else
          {
            same=true;
          }
       }
       if(!same)
       {
        cout<<"\r"<<buffer<<endl;
       } 
    }
      
  }

  ~makeClient()
    {
     close(server);
     close(client);
    }
};

int main()
{
    string ip;
    int port;
    cout<<"Enter IP of Server : ";
    getline(cin,ip);
    cout<<"Enter Port of Server : ";
    cin>>port;
    makeClient server(ip,port);
}