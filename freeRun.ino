/* Rover Free Run - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define BUZZER_ON 0xC0
#define BUZZER_OFF 0xC1
#define RED_LED_COLOR 0xC2
#define GREEN_LED_COLOR 0xC3
#define BLUE_LED_COLOR 0xC4

Modular rover; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  rover.steerBotBegin(4); //steering motors connected at port 4
  rover.bluetoothBegin(1); // bluetooth connected at port 1
}

void loop() {
  //check if a command is received from app via bluetooth
  if (rover.bluetoothCheck() > 0) {
    char message = rover.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        rover.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        rover.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        rover.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        rover.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        rover.haltBot(4);
        break;
    }
  }
}
