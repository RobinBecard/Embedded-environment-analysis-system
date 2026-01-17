#include <AFMotor.h>
#include "motors.h"

AF_DCMotor m1(1), m2(2), m3(3), m4(4);

void initMotors(int speed) {
    m1.setSpeed(speed); m2.setSpeed(speed);
    m3.setSpeed(speed); m4.setSpeed(speed);
}

void avancer() {
    m1.run(BACKWARD); m2.run(FORWARD);
    m3.run(FORWARD);  m4.run(BACKWARD);
}

void reculer() {
    m1.run(FORWARD);  m2.run(BACKWARD);
    m3.run(BACKWARD); m4.run(FORWARD);
}

void droite() {
    m1.run(FORWARD); m2.run(FORWARD);
    m3.run(FORWARD); m4.run(FORWARD);
}

void gauche() {
    m1.run(BACKWARD); m2.run(BACKWARD);
    m3.run(BACKWARD); m4.run(BACKWARD);
}

void stopMotors() {
    m1.run(RELEASE); m2.run(RELEASE);
    m3.run(RELEASE); m4.run(RELEASE);
}