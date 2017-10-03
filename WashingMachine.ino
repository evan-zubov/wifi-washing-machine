#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <LinkedList.h>
#include "user_interface.h"
#include "FS.h"
#include "./chats.h";
#include "./setup.h";
#include "./jsonTools.h";
#include "./messaging.h";
#include "./settings.h";

const int WM_OFF = 0;
const int WM_ON = 1;
const int WM_BLINKING = 2;
const int WM_BLINK_DURATION = 20;

bool oldState = false;
int wmState = WM_OFF;
int wmOldState = WM_OFF;
int sameValueCycles = 0;
int getUpdateInterval = 50; //10s
int getUpdateCounter = 0;

unsigned long lastUpdateId = 0;

void processUpdate(long updateId, String chatId, String text)
{
  Serial.println("");
  Serial.print("Chat:");
  Serial.println(chatId);
  Serial.print("Text:");
  Serial.println(text);
  lastUpdateId = updateId + 1;

  if (text == "/start")
  {
    sendMessage(chatId, MESSAGES::HELLO);
  }
  if (text == "/start" || text == "/help")
  {
    Serial.print("Providing help to ");
    Serial.println(chatId);
    sendMessage(chatId, MESSAGES::HELP);
  }
  if (text == "/state")
  {
    if (wmState == WM_OFF)
    {
      sendMessage(chatId, MESSAGES::IDLE);
    }
    if (wmState == WM_ON)
    {
      sendMessage(chatId, MESSAGES::WASHING);
    }
    if (wmState == WM_BLINKING)
    {
      sendMessage(chatId, MESSAGES::BLINKING);
    }
  }
  if (text == "/subscribe")
  {
    addChat(chatId);
    sendMessage(chatId, MESSAGES::SUBSCRIBED);
  }
  if (text == "/unsubscribe")
  {
    removeChat(chatId);
    sendMessage(chatId, MESSAGES::UNSUBSCRIBED);
  }
  if (text == "/list")
  {
    String message = MESSAGES::SUBSCRIBERS;
    for (int i = 0; i < chats->size(); i++)
    {
      message += chats->get(i) + "\n";
    }
    sendMessage(chatId, message);
  }
}

void getUpdates()
{
  String url = "/getUpdates?offset=" + String(lastUpdateId);
  Serial.println("GET:" + url);
  TeleResponse response = getRequest(url);
  if (response.success)
  {
    String result = getLastJSONValue(response.body, "\"result\":");
    if (result == "[")
    {
      Serial.println("No updates");
    }
    else
    {
      String text = getLastJSONValue(response.body, "\"text\":");
      text = text.substring(1, text.length() - 1);
      long updateId = getLastJSONValue(response.body, "\"update_id\":").toInt();
      String chatId = getLastJSONValue(response.body, "chat\":{\"id\":");
      processUpdate(updateId, chatId, text);
    }
  }
}

void loop()
{
  getUpdateCounter++;
  if (getUpdateCounter == getUpdateInterval)
  {
    getUpdateCounter = 0;
    digitalWrite(LED_BUILTIN, HIGH);
    getUpdates();
    digitalWrite(LED_BUILTIN, LOW);
  }

  bool state = digitalRead(D7);
  if (state != oldState)
  {
    if (sameValueCycles <= WM_BLINK_DURATION && wmOldState == WM_ON)
    {
      wmState = WM_BLINKING;
    }
    sameValueCycles = 0;
    oldState = state;
  }
  else
  {
    sameValueCycles++;
    if (sameValueCycles > WM_BLINK_DURATION)
    {
      wmState = state ? WM_ON : WM_OFF;
    }
  }

  if (wmState != wmOldState)
  {
    String message;
    if (wmState == WM_OFF)
    {
      message = MESSAGES::SWITCHED_TO_IDLE;
    }
    if (wmState == WM_ON)
    {
      message = MESSAGES::SWITCHED_TO_WASHING;
    }
    if (wmState == WM_BLINKING)
    {
      message = MESSAGES::SWITCHED_TO_WASH_IS_OVER;
    }
    notifyUsers(message);
    wmOldState = wmState;
  }

  delay(100);
}
