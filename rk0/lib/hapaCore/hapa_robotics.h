#ifndef HAPA_ROBOTICS
#define HAPA_ROBOTICS



#include "globalVar.h"
#include "hapa_motor.h"
#include "hapa_uart.h"

//Kit version
#define HAPA_RK0 0
#define HAPA_RK1 1
#define HAPA_RK2 2

//LIGHT INDICATOR
#define LED_IND_GPIO_PORT   GPIOB
#define RED_LED_IND         GPIO_PIN_14
#define GREEN_LED_IND       GPIO_PIN_13
#define BLUE_LED_IND        GPIO_PIN_12


typedef enum{ //error type
    HAPA_OK = 0,
    HAPA_ERR = !HAPA_OK
} hapa_err_t;

typedef enum{ //light ind typ
    HAPA_MOTION_LIGHT_OFF = 0,
    HAPA_MOTION_LIGHT_FD  = 1,
    HAPA_MOTION_LIGHT_RV  = 2
}hapa_motion_light_t;

void hapa_init_system(void);
void hapa_motion_light_toggle(hapa_motion_light_t light);


#if KIT_VERSION == HAPA_RK0

    //IR REMOTE
    #define IR_PORT GPIOB
    #define IR_PIN  GPIO_PIN_0

#endif

#endif