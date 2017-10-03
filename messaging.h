#ifndef MESSAGING
#define MESSAGING
#include "./getRequest.h"

void sendMessage(String chatid, String text)
{
  String url = "/sendMessage?text=" + text + "&chat_id=" + chatid;
  getRequest(url);
}

void notifyUsers(String text)
{
  for (int i = 0; i < chats->size(); i++)
  {
    sendMessage(chats->get(i), text);
  }
}
#endif /* MESSAGING */