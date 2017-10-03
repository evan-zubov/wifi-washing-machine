#ifndef SETTINGS
#define SETTINGS
const char *ssid = "";
const char *password = "";
const String token = "";
const char *fingerprint = "C6:5B:FA:5B:F7:57:0C:6A:02:85:C1:6F:A7:19:6C:36:32:B4:28:21";
const int SENSOR_PIN = D7;

namespace MESSAGES {
    const char* HELLO = "Привет!";
    const char* HELP = "Доступные команды:\n/subscribe - подписаться\n/unsubscribe - отписаться\n/list - список подписчиков\n/state - проверить текущее состояние";
    const char* IDLE = "Отдыхаю";
    const char* WASHING = "Стираю";
    const char* BLINKING = "Постирала, жду разгрузки";
    const char* SUBSCRIBED = "Теперь вы будете получать уведомления о ходе стирки";
    const char* UNSUBSCRIBED = "Вы не будете получать уведомления о ходе стирки";
    const char* SUBSCRIBERS = "Список подписчиков:\n";
    const char* SWITCHED_TO_IDLE = "До новых встреч";
    const char* SWITCHED_TO_WASHING = "Начинаю стирать";
    const char* SWITCHED_TO_WASH_IS_OVER = "Стирка закончена!";
  }

#endif