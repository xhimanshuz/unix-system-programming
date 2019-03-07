//SNED RECEIVER
#ifndef MSGRECEIVER_H
#define MSGRECEIVER_H

#include"MsgSettup.h"

class MsgReceiver: public MsgSettup
{
    int md;
    struct  mbuf
    {
        long mtype;
        char mtext[MSG_MAX];
    };
    struct mbuf mObj;

public:
    MsgReceiver();
    void receive();
    int msgStatus();
    void openMsg();
};

#endif