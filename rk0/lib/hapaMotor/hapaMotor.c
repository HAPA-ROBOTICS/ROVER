#include "hapa_robotics.h"






hapa_err_t hapa_motor_init(void){

    #if KIT_VERSION == HAPA_RK0
        GPIO_InitTypeDef motor_gpio = {
            .Pin = ENA | IN1 | IN2 | IN3 | IN4 | ENB,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW
        };

        HAL_GPIO_Init(MOTOR_PORT, &motor_gpio);
        
    #endif

    return HAPA_OK;
}