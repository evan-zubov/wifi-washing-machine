#ifndef CHATS
#define CHATS
const char *chatsFileName = "/config.txt";
LinkedList<String> *chats = new LinkedList<String>();
File chatsFile;

void saveChats()
{
  chatsFile = SPIFFS.open(chatsFileName, "w");
  int chatsSize = chats->size();
  for (int i = 0; i < chatsSize; i++)
  {
    chatsFile.print(chats->get(i));
    chatsFile.print(";");
  }
  chatsFile.close();
}

void getChats()
{
  File f = SPIFFS.open(chatsFileName, "r");
  if (!f)
  {
    Serial.println("File doesn't exist yet. Creating it");

    // open the file in write mode
    File f = SPIFFS.open(chatsFileName, "w");
    if (f)
    {
      Serial.println("File has been successfully created");
    }
    else
    {
      Serial.print("File creation failed, formatting FS... ");
      SPIFFS.format();
      Serial.println("DONE");
    }
  }
  else
  {
    // we could open the file
    while (f.available())
    {
      //Lets read line by line from the file
      String line = f.readStringUntil(';');
      if (line.length() > 0)
      {
        chats->add(line);
      }
    }
  }
  f.close();
}

int indexOfChat(String chatid)
{
  int chatsSize = chats->size();
  for (int i = 0; i < chatsSize; i++)
  {
    if (chats->get(i) == chatid)
    {
      return i;
    }
  }
  return -1;
}

void clearChats()
{
  while (chats->size() > 0)
  {
    chats->remove(0);
  }
  saveChats();
}

void removeChat(String chatid)
{
  int index = indexOfChat(chatid);
  if (index > -1)
  {
    chats->remove(index);
    saveChats();
  }
}

void addChat(String chatid)
{
  if (indexOfChat(chatid) == -1)
  {
    chats->add(chatid);
    saveChats();
  }
  else
  {
    Serial.println("Chat " + chatid + " already exist");
  }
}
#endif /* CHATS */