// MESSAGE SETUO ABSTRACT CLASS
#ifndef MESSAGESETTUP_H
#define MESSAGESETTUP_H

#include<string>
#include<iostream>
#include<string>
#include<sys/msg.h>
#include<assert.h>
#include<stdlib.h>
#include<memory.h>

#define KEY 992
#define MSG_MAX 255

class MsgSettup
{
    virtual void openMsg() = 0;
    virtual int msgStatus() = 0;
};

#endif