// SENDER SOURCE
#include"include/MsgSender.h"

MsgSender::MsgSender()
{
    openMsg();
}

void MsgSender::openMsg()
{

    md = msgget(KEY, IPC_CREAT | 0644);
    std::cout<< "\nmd: "<< md<<std::endl;
    if(md<1)
        perror("MD ERROR");
}

int MsgSender::msgStatus()
{
    if(md>0)
        return 1;
    return 0;
}

void MsgSender::send(const std::string &msgStr)
{
    mObj.mtype = KEY;
    memcpy(mObj.mtext, (void*)msgStr.c_str(), msgStr.length());
    int rcode = msgStatus();
    if(rcode == 0)
        return;
    msgsnd(md, &mObj, msgStr.length(), 0);
    perror("SEND STATUS");
}

MsgSender::~MsgSender()
{

}
