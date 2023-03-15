/* Rover Obstacle Avoider - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define ULTRASONIC_READ 0xD0

Modular avoider; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  avoider.steerBotBegin(4); //steering motors connected at port 4
  avoider.bluetoothBegin(1); // bluetooth connected at port 1
  avoider.sonarBegin(2); // sonar sensor connected at port 2
  avoider.rgbBegin(3, CA); // rgb led connected at port 3
  avoider.buzzerBegin(3); // buzzer connected at port 3
}

void loop() {
  //check if a command is received from app via bluetooth
  if (avoider.bluetoothCheck() > 0) {
    char message = avoider.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        avoider.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        avoider.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        avoider.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        avoider.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        avoider.haltBot(4);
        break;
      case ULTRASONIC_READ :
        byte distance = avoider.sonarRead(2); //read distance in centimeter
        avoider.bluetoothWrite(distance); //send distance to app
        break;
    }
  }
}
