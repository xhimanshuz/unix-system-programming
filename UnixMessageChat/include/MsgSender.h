// SENDER HEADER
#ifndef MSGSENDER_H
#define MSGSENDER_H

#include"MsgSettup.h"


class MsgSender: public MsgSettup
{
    enum {OPENED = 100, CLOSE};
    struct mbuf
    {
        long mtype;
        char mtext[MSG_MAX];
    };

    std::string message;
    
    int md;
    struct mbuf mObj;
public:
    MsgSender();
    virtual ~MsgSender();
    int msgStatus();
    void send(const std::string&);
    void openMsg();
};

#endif