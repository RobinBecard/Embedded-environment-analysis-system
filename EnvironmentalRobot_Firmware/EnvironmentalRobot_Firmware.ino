#include "config.h"
#include "motors.h"
#include "sensors.h"

int current_speed = 230;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    
    initMotors(current_speed);
    initSensors();
    
    Serial.println("System Ready!");
}

void loop() {
    if (Serial1.available() > 0) {
        int state = Serial1.read();
        executeCommand(state);
    }
}

void executeCommand(int state) {
    switch(state) {
        case 1: avancer(); break;
        case 2: reculer(); break;
        case 3: gauche();  break;
        case 4: droite();  break;
        case 5: stopMotors(); break;
        case 6: stopMotors(); updateAndSendData(); break;
        case 7: setLeds(true);  break;
        case 8: setLeds(false); break;
    }
}