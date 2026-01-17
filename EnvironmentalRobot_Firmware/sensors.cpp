#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobot_ICP10111.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "sensors.h"

OneWire oneWire(PIN_ONE_WIRE);
DallasTemperature tempSensors(&oneWire);
DFRobot_ICP10111 icp;
Adafruit_NeoPixel strip(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

float R0, R0_CO;

float calculateResistance(int raw) { return (float)RL_VALUE * (1023 - raw) / raw; }

float calibrate(int pin) {
    float val = 0;
    for(int i=0; i<CALIB_SAMPLES; i++) {
        val += calculateResistance(analogRead(pin));
        delay(CALIB_INTERVAL);
    }
    return (val / CALIB_SAMPLES) / FACTEUR_R0;
}

long getPercentage(float ratio, const float *curve) {
    return pow(10, ((log10(ratio) - curve[1]) / curve[2]) + curve[0]);
}

void initSensors() {
    tempSensors.begin();
    while(icp.begin() != 0) { Serial.println("ICP Error"); delay(500); }
    icp.setWorkPattern(icp.eNormal);
    
    strip.begin();
    strip.show();

    Serial.println("Calibrating Gas Sensors...");
    R0 = calibrate(PIN_GAZ_MQ);
    R0_CO = calibrate(PIN_GAZ_CO);
}

void updateAndSendData() {
    tempSensors.requestTemperatures();
    float rs_mq = 0, rs_co = 0;
    for(int i=0; i<READ_SAMPLES; i++) {
        rs_mq += calculateResistance(analogRead(PIN_GAZ_MQ));
        rs_co += calculateResistance(analogRead(PIN_GAZ_CO));
        delay(READ_INTERVAL);
    }
    rs_mq /= READ_SAMPLES; rs_co /= READ_SAMPLES;

    Serial1.print(tempSensors.getTempCByIndex(0)); Serial1.print("|");
    Serial1.print(icp.getAirPressure()); Serial1.print("|");
    Serial1.print(getPercentage(rs_co/R0_CO, CourbeCO)); Serial1.print("|");
    Serial1.print(getPercentage(rs_mq/R0, CourbeFUMEE)); Serial1.print("|");
    Serial1.println(getPercentage(rs_mq/R0, CourbeCH4));
}

void setLeds(bool active) {
    for(int i=0; i<NUM_PIXELS; i++) 
        strip.setPixelColor(i, active ? strip.Color(255,255,255) : 0);
    strip.show();
}