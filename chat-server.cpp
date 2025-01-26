#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>


using namespace std;

class makeServer{
    public:
    string ip;
    int port;
    int server;
    int client;
    int clientsocket;
    vector<int> clients;

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
        cout<<"Chat Server Running At "<<ip<<":"<<port<<endl;
        int l=listen(server,1);
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
        clients.push_back(client);
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
      char name[4096];
      recv(clientsocket,name,4096,0);
      string str;
      string temp1=name;
      str=temp1+" has joined the chat!";
      cout<<str<<endl;
      sendtoclients(str);
      while(buffer!="exit")
      {
        memset(buffer, 0, sizeof(buffer));
        int r=recv(clientsocket,buffer,4096,0);
        string temp2=buffer;
        if(temp2=="exit")
        break;
        if(r>0)
        {
          str=temp1+" : "+temp2;
          sendtoclients(str);
          cout<<str<<endl;
        }
      }
      str=temp1+" has left the chat!";
      cout<<str<<endl;
      sendtoclients(str);
    }

    void sendtoclients(string str)
    {
        for(auto& i: clients)
        {
          int s=send(i,str.c_str(),str.length(),0);
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