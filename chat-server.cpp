#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class makeServer{
    public:
    string ip;
    int port;
    int server;
    int client;

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
        error_check(l);
        AcceptConnection();
    }

    void AcceptConnection()
    {
        struct sockaddr_in client;
        socklen_t length=sizeof(client);
        int clientsocket=accept(server,(struct sockaddr*)&client,&length);
        error_check(clientsocket);
        recivingData();
    }

    void recivingData()
    {
        char output[4096];
        int r;
        do
        {
            r=recv(client,output,4096,0);
            cout<<output;
        } while (r!=-1);
        
    }

};

int main()
{
  makeServer server("192.168.1.85",1234);
}