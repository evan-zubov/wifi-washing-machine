# wifi-washing-machine
Arduino/ESP-8266 sketch for a module reading washing machine current state and sending it to user's telegram

Contolls state of the washing machine status LED, detects current state with the following logic:

LED OFF - idle
LED ON - washing is in progress
LED BLINKS - washing process is over

# Getting started

1. Set correct name and password for your wifi AP in settings.h.  
2. Create a telegram bot for your washing machine using BotFather telegram bot.
3. Copy the token of your new bot from BotFather and paste it into settings.h file.
4. Change the pin that you will connect to washing machine LED positive leg in the same settings file if you want to use another pin instead of D7.
5. Upload the sketch to the ESP8266 D1 Mini board.
6. Connect to the terminal, reset the board using reset button and make sure that it connects to your wifi ap and gets ip address.
7. Add the bot you created to your telegram accounts, and tell him /subscribe, which will add you to it's subscribers list. Now you will receive status notification from your board.
8. You can also change the messages which your bot will send you in the same settings file.

# Testing

To trick it into thinking that it's connected to the washing machine, try connecting 3.3v pin and LED sensor pin, that you configured(D7 by default) and hold it like that for 10 seconds. Make sure, your bot sends you WASHING_STARTED message 