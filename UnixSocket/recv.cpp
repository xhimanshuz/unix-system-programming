// RECEIVER WHICH RECEIVE MESSAGE ON PERTICULAR PORT
// 1-1024 PORTS ARE RESERVES FOR SYS PROGRAM, TO USE IT USE SUDO PERMISSION

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<memory.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<memory.h>
#include<unistd.h>
#include<random>
#include<string>
#include<time.h>

char user[INET6_ADDRSTRLEN];

void printIp(struct addrinfo *res)
{
    char ipstr[INET6_ADDRSTRLEN];
    struct sockaddr_in *ipv4 = (struct sockaddr_in*)res->ai_addr;
    void *addr = &ipv4->sin_addr;
    inet_ntop(res->ai_family, addr, ipstr, INET6_ADDRSTRLEN);
    strcpy(user, ipstr);
    std::cout<<"IPv4: "<<user<<'\n';
}

void printIp(struct sockaddr_in *ipv4)
{
    char ipstr[INET6_ADDRSTRLEN];
    void *addr = &ipv4->sin_addr;
    inet_ntop(AF_INET, addr, ipstr, INET6_ADDRSTRLEN);
    std::cout<<"Connected with IPv4: "<<ipstr<<'\n';
    strcpy(user, ipstr);
}

void createNBind(int &sd, struct addrinfo *res)
{
    sd = socket(res->ai_family, res->ai_socktype, 0);
    std::cout<<"\nSD: "<<sd<<std::endl;
    int yes = 1;
    if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))!=-1)
    {
        perror("REUSING");
    }
    int bd = bind(sd, res->ai_addr, res->ai_addrlen);
    perror("BIND");
}

void openRequest(int &sd, struct addrinfo *res, int &newSd)
{
    std::cout<<"openRequest"<<std::endl;
    struct sockaddr_storage clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    newSd = accept(sd, (struct sockaddr*)&clientAddr, &clientSize);
    struct sockaddr_in peerSockadrr;
    socklen_t addrlen = sizeof(peerSockadrr);
    int pn = getpeername(newSd, (struct sockaddr *)&peerSockadrr, &addrlen); 
    printIp(&peerSockadrr);
    std::cout<<"~openRequest"<<std::endl;
    // std::cout<<"New SD: "<<newSd<<std::endl;
    fork();
}

void fetchData(int &sd, struct addrinfo *res)
{
    std::cout<<"fetchData()"<<std::endl;
    char buff[1024];
    while(strcmp(buff, ".exit")!=0)
    {
    int rsize = recv(sd, (void*)&buff, 1024, 0);
    // perror("RECEIVED: ");
    if(rsize==0)
        return;
    std::cout<<user<<"> "<< buff<<std::endl;
    memset(&buff, 0, 1024);
    }
    close(sd);
    std::cout<<"~fetchData()"<<std::endl;
}

int  main(int argc, char* argv[])
{
    std::string port = ((argc>1)?argv[1]:"8080");
    std::cout<<"PORT: "<<port<<std::endl;
    struct addrinfo handler, *res;
    memset(&handler, 0, sizeof handler);
    handler.ai_family = AF_INET;
    handler.ai_socktype = SOCK_STREAM;
    handler.ai_flags = AI_PASSIVE;
    
    int status = getaddrinfo(nullptr, port.c_str(), &handler, &res);
    std::cout<<"ADDRESS: "<<strerror(status);

    int sd{-1}, newSd;
    createNBind(sd, res);

    int ld = listen(sd, 100);
    std::cout<<"LISTEN: "<< strerror(ld) <<std::endl;
    openRequest(sd, res, newSd);

    while(1)
    {
        fetchData(newSd, res);
        std::cout<<user<<" DISCONNECTED! "<<newSd<<std::endl;
        std::cout<<"============"<<std::endl;
        openRequest(sd,res, newSd);
    }

    return 0;
}