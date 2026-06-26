#ifndef HAPA_MOTOR_H
#define HAPA_MOTOR_H

#include "hapa_robotics.h"

/**
 * @brief Motor direction
 */
typedef enum{
    HAPA_REVERSE = -1,
    HAPA_STOP    = 0,
    HAPA_FORWARD = 1
} hapa_motor_state_t;


// HAPA Rover Kit Hardware Configuration
#if KIT_VERSION == HAPA_RK0

    #define MOTOR_PORT     GPIOA
    #define MOTOR_ENABLE   GPIO_PIN_11

    // Motor A == RIGHT
    #define RIGHT_IN1 GPIO_PIN_0
    #define RIGHT_IN2 GPIO_PIN_1

    // Motor B == LEFT
    #define LEFT_IN1 GPIO_PIN_2
    #define LEFT_IN2 GPIO_PIN_4 //ON CURRENT BOARD GPIO3 IS NOT WORKING WILL SWITCH

#elif KIT_VERSION == HAPA_RK1

    #define MOTOR_PORT     GPIOA
    #define MOTOR_ENABLE   GPIO_PIN_11

    // Motor LF == LEFT FRONT
    #define IN1 GPIO_PIN_0
    #define IN2 GPIO_PIN_1

    // Motor RF == RIGHT FRONT
    #define IN3 GPIO_PIN_2
    #define IN4 GPIO_PIN_3

    // Motor LB == LEFT BACK
    #define IN1 GPIO_PIN_4
    #define IN2 GPIO_PIN_5

    // Motor RB == RIGHT BACK
    #define IN3 GPIO_PIN_6
    #define IN4 GPIO_PIN_7

#else
    #error "Unknown KIT_VERSION"

#endif


#if KIT_VERSION == HAPA_RK0

/**
    * Move rover motors.
    *
    * @param left Left motor direction
    *          -1 = Reverse
    *           0 = Stop
    *           1 = Forward
    *
    * @param right Right motor direction
    *          -1 = Reverse
    *           0 = Stop
    *           1 = Forward
    */
    void hapa_move(
        hapa_motor_state_t right,
        hapa_motor_state_t left
    );

#elif KIT_VERSION == HAPA_RK1

 /**
    * Move rover motors.
    *
    * @param lf Left_front motor direction
    *          -1 = Reverse
    *           0 = Stop
    *           1 = Forward
    *
    * @param rf Right_front motor direction
    *          -1 = Reverse
    *           0 = Stop
    *           1 = Forward
    *
    * @param lb Left_back motor direction
    *          -1 = Reverse
    *           0 = Stop
    *           1 = Forward
    *
    * @param rb Right_back motor direction
    *          -1 = Reverse
    *           0 = Stop
    *           1 = Forward
    */
    void hapa_move(
        hapa_motor_state_t lf,
        hapa_motor_state_t rf,
        hapa_motor_state_t lb,
        hapa_motor_state_t rb
    );

#endif


void hapa_motor_init(void);

#endif