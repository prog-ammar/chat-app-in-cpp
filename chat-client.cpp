#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

class makeClient
{
  public:
  string ip;
  int port;
  int server;
  int client;
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
    send_recv();
  }
  void send_recv()
  {
      
      string str;
      while(str!="exit")
      {
        cout<<"Enter : ";
        getline(cin,str);
        int r=send(server,str.c_str(),sizeof(str),0);
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        r=recv(server,buffer,4096,0);
        cout<<buffer<<endl; 
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
    makeClient server("192.168.1.85",1234);
}