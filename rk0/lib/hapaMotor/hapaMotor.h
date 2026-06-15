#ifndef HAPA_MOTOR
#define HAPA_MOTOR

#include "hapa_robotics.h"


// HAPA Rover Kit Hardware Configuration
#if KIT_VERSION == HAPA_RK0

    #define MOTOR_PORT GPIOA

    // Motor A == LEFT
    #define ENA GPIO_PIN_0
    #define IN1 GPIO_PIN_1
    #define IN2 GPIO_PIN_2

    // Motor B == RIGHT
    #define IN3 GPIO_PIN_3
    #define IN4 GPIO_PIN_4
    #define ENB GPIO_PIN_5


#elif KIT_VERSION == HAPA_RK1

    // RK1 pinout

#else
    #error "Unknown KIT_VERSION"
#endif





#endif