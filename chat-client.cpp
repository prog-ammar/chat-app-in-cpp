#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

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
  }
  void makeSocket()
  {
    server=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_add;
    server_add.sin_family=AF_INET;
    server_add.sin_port=htons(1235);
    inet_pton(AF_INET,ip.c_str(),&server_add);
    client=connect(server,(struct sockaddr*)&server_add,sizeof(server_add));
    send_recv();
  }
  void send_recv()
  {
    char buffer[4096];
    do
    {
        int r=recv(client,buffer,4096,0);
        cout<<buffer<<endl;

    } while();
    
  }
}

int main()
{
    makeClient server("192.168.1.85",1235);
}