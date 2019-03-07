//SEND MESSAGES TO ENTERED HOST AND PORT
//ACCEPT MULTIPLE REQUEST AND SHOW IT ON TERMINAL
//IT CAN ALSO TRACK OTHER APPLICATION SOCKET REQUEST LIKE WEB SSH VNC ETC
//EXPERIMENTAL PERPOSE ONLY

#include<iostream>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<memory.h>
#include<unistd.h>

void createNBind(int &sd, struct addrinfo *res)
{
    sd = socket(res->ai_family, res->ai_socktype, 0);
    std::cout<<"\nSD: "<<sd<<std::endl;
}

void sendMsg(int &sd)
{
    std::string msg;
    std::cout<<"> ";
    std::getline(std::cin, msg);
    int sendSize = send(sd,(void*)msg.c_str(), msg.size(), 0);
    std::cout<< "SENDED SIZE: "<<sendSize<<std::endl;
}

int main(int argc, char** argv)
{
    int ch;
    int flag_p = 0, flag_h = 0;
    std::string host, port;
    while((ch= getopt(argc, argv, "h:p:"))!=-1)
    {
        switch (ch)
        {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            default:
                    break;
        }
    }

    std::cout<< "Host: "<< host<< " Port: "<<port<<'\n';

    struct addrinfo handler, *res;
    memset(&handler, 0,sizeof(handler));
    handler.ai_family = AF_INET;
    handler.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host.c_str() , port.c_str(), &handler, &res);
    std::cout<<"ADDRESS: "<< strerror(status);

    int sd{-1};
    createNBind(sd, res);
    int c = connect(sd, res->ai_addr, res->ai_addrlen);
    perror("CONNECT:");
    if(c==-1)
        return -1;
    while(1)
        sendMsg(sd);

    return 0;
}
