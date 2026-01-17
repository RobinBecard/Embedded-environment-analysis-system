#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- PINS ---
#define PIN_NEOPIXEL 24
#define PIN_ONE_WIRE 22
#define PIN_GAZ_MQ   0
#define PIN_GAZ_CO   1

// --- SENSORS CONFIG ---
const int NUM_PIXELS = 8;
const int RL_VALUE = 1;
const float FACTEUR_R0 = 9.8;

const int CALIB_SAMPLES = 50;
const int CALIB_INTERVAL = 500;
const int READ_SAMPLES = 5;
const int READ_INTERVAL = 50;

// --- GAS IDENTIFIERS ---
enum GasType { GPL, CO, FUMEE, CH4, PROPANE, ALCOOL };

// --- CALIBRATION CURVES ---
const float CourbeCO[3]    = {3.91, -2.4, -0.667};
const float CourbeFUMEE[3] = {2.3, 0.5, -0.45};
const float CourbeCH4[3]   = {2.3, 0.47, -0.37};
const float CourbePROP[3]  = {2.3, 0.23, -0.46};

#endif