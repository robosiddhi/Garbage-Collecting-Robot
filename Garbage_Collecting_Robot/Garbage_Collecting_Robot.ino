/*
Code Name:Garbage Collecting Robot
Author: RoboSiddhi

⚠ Warning

This project and its code are shared for learning and personal use only.  
Commercial use, redistribution, or selling (in any form) of this code or
project is not allowed without proper permission.  

                                                                                 .                 
              !^           .   ..   ..            
              ??^~~~^.      ....:....             
             :P5J?7?JY5.   ...^:::^..             
            .BG5JY75&JYG   ...^:::^..             
            .BBBP57?YYYG.   ....::::              
             :YBBGYJ??Y?   .  .^ YGGY.            
              :!BBBBY!:       .G??5BP^            
            ~GP5P5??77!7:    .^J55Y!              
           ^#57!7#5777!?57~:~77JG~                
           ?#G5PB#57777!B5GG5YPJ.                 
          .BGYY&&BPY???J!!Y5Y7:                   
          :7!~!7777!!!!^     
                               
Description:The Garbage Collecting Robot is an Arduino Uno–based autonomous 
cleaning system designed to collect dust and small debris from the floor. 
The robot utilizes an HC-05 Bluetooth module for wireless communication 
and an L298N motor driver to control the movement of the drive motors, 
enabling smooth navigation in forward, backward, left, and right directions.
A relay module is integrated to operate the cleaning motor or suction mechanism
which collects the garbage efficiently. Through Bluetooth connectivity,the robot 
can be remotely controlled using a smartphone or any compatible Bluetooth-enabled
device.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
#define motorA1 5
#define motorA2 6
#define motorB1 9
#define motorB2 10
#define fanRelay 11

#define BT_RX 7
#define BT_TX 8

#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(BT_RX, BT_TX); // RX, TX

char command;

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(fanRelay, OUTPUT);

  digitalWrite(fanRelay, LOW); // Fan off initially
  stopRobot();

  Serial.println("Bluetooth Dust Cleaning Robot Ready");
}

void loop() {
  if (Bluetooth.available()) {
    command = Bluetooth.read();
    Serial.print("Command: ");
    Serial.println(command);

    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopRobot(); break;
      case 'N': digitalWrite(fanRelay, HIGH); break;  // Fan ON
      case 'O': digitalWrite(fanRelay, LOW); break;   // Fan OFF
    }
  }
}

// --- Movement Functions ---
void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void moveBackward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void stopRobot() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
