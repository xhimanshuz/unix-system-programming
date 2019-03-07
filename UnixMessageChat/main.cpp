// MAIN SOURCE
#include"include/MsgSender.h"
#include"include/MsgReceiver.h"

void senderCall()
{
    MsgSender *sender = new MsgSender;
    std::string msg;
    while(1)
    {
    std::cout<<">> ";
    std::getline(std::cin, msg);
    if(msg == "clear()")
    {
        system("clear");
    }
    sender->send(msg);
    }
}

void receiverCall()
{
    MsgReceiver *receiver = new MsgReceiver;
    while(1)
    {
    receiver->receive();
    }
}

void render()
{
    int ch;
    std::cout<< "MESSAGE SENDER/RECEIVER\n1.RECEIVER\n2.SENDER\nEnter your choice: ";
    std::cin>> ch;
    switch(ch)
    {
        case 1:
            receiverCall();
            break;
        case 2:
            senderCall();
            break;
        default:
            abort();
    }
}

int main()
{
    render();
    return 0;
}