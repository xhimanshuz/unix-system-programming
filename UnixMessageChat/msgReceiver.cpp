// RECEIVER SOURCE
#include"include/MsgReceiver.h"

MsgReceiver::MsgReceiver()
{
    openMsg();
}

void MsgReceiver::openMsg()
{
    md = msgget(KEY, 0);
    std::cout<<"md: "<<md<<std::endl;
    if(md < 0)
        perror("MD ERROR");
}

int MsgReceiver::msgStatus()
{
    return (md>1)?1:0;
}

void MsgReceiver::receive()
{
    std::cout<<std::flush;
    memset(&mObj.mtext, '\0', MSG_MAX);
    int len = msgrcv(md, &mObj, MSG_MAX, 0, MSG_NOERROR);
    if(strcmp(mObj.mtext, "clear()")==0)
        system("clear");
    if(len<1)
    {
        perror("RECEIVE MSG ERROR");
        return;
    }
    struct msqid_ds msds;
    int mscode = msgctl(md, IPC_STAT, &msds);
    struct tm *ctm = localtime(&msds.msg_stime);
    std::cout<<ctm->tm_hour <<":"<<ctm->tm_min<<":"<<ctm->tm_sec<<"-"<<msds.msg_lspid <<"$ "<<mObj.mtext<<std::endl;
}
