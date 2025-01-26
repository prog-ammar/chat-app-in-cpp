#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

using namespace std;

class makeServer{
    public:
    string ip;
    int port;
    int server;
    int client;
    int clientsocket;

    makeServer(string address,int portt)
    {
        ip=address;
        port=portt;
        make_socket();
    }

    void error_check(int input)
    {
        if(input==-1)
        {
            cout<<"There is Some Error";
            close(server);
            exit(0);
        }
    }

    void make_socket()
    {
        server=socket(AF_INET,SOCK_STREAM,0);
        error_check(server);
        binder();
    }

    void binder()
    {
      struct sockaddr_in address;
      address.sin_family=AF_INET;
      address.sin_port=htons(port);
      inet_pton(AF_INET,ip.c_str(),&address.sin_addr);
      int b=bind(server,(struct sockaddr*)&address,sizeof(address));
      error_check(b);
      listening();
    }

    void listening()
    {
        cout<<"Listening At "<<ip<<":"<<port<<endl;
        int l=listen(server,1);
        cout<<"Connection Established"<<endl;
        error_check(l);
        while(true)
        AcceptConnection();
    }

    void AcceptConnection()
    {
        struct sockaddr_in clientadd;
        socklen_t length=sizeof(clientadd);
        client=accept(server,(struct sockaddr*)&clientadd,&length);
        error_check(client);
        thread client_thread(&makeServer::recivingData,this,client);
        client_thread.detach();
    }

    void recivingData(int clientsocket)
    {
        // char output[4096];
        // char sending[3]="hi";
        // int r;
        // r=send(client,sending,sizeof(sending),0);
      char buffer[4096];
      while(buffer!="exit")
      {
        memset(buffer, 0, sizeof(buffer));
        int r=recv(clientsocket,buffer,4096,0);
        if(r>0)
        cout<<buffer<<endl;
        error_check(r);
      }
    }

    ~makeServer()
    {
     close(server);
     close(client);
    }

};

int main()
{
  makeServer server("192.168.1.85",1234);
}