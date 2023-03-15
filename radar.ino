/* Space Rover Radar - Source Code
   Board - MiniCore 168 or Arduino Uno
*/

#include <modular.h> // include modular library

// bluetooth commands for the mobile app - bixchamp
#define MOVE_BOT_FWD 0xB0
#define MOVE_BOT_BWD 0xB1
#define MOVE_BOT_LT 0xB2
#define MOVE_BOT_RT 0xB3
#define BOT_STOP 0xB4
#define SERVO_1_ANGLE 0xBB
#define ULTRASONIC_READ 0xD0

Modular radar; //create a object to access library functions

// initialise the hardware port connections
void setup() {

  radar.steerBotBegin(4); //steering motors connected at port 4
  radar.servoOneBegin(3); //servo motor 1 for radar strike, connected at port 3
  radar.sonarBegin(2); // sonar sensor connected at port 2
  radar.bluetoothBegin(1); // bluetooth connected at port 1

}

void loop() {
  //check if a command is received from app via bluetooth
  if (radar.bluetoothCheck() > 0) {
    char message = radar.bluetoothRead(); //save the command received

    switch (message) { //do action as per the command received
      case MOVE_BOT_FWD :
        radar.steerBotForward(4);
        break;
      case MOVE_BOT_BWD :
        radar.steerBotBackward(4);
        break;
      case MOVE_BOT_LT :
        radar.steerBotLeftAxial(4);
        break;
      case MOVE_BOT_RT :
        radar.steerBotRightAxial(4);
        break;
      case BOT_STOP :
        radar.haltBot(4);
        break;
      case ULTRASONIC_READ :
        byte distance = radar.sonarRead(2); //read distance in centimeter
        radar.bluetoothWrite(distance); //send distance to app
        break;
      case SERVO_1_ANGLE :
        while (radar.bluetoothCheck() <= 0); //wait for the servo angle value from the app
        message = radar.bluetoothRead(); //save servo angle received from bluetooth
        radar.servoOneMove(message); //set angle with the value received
        break;
    }
  }
}
