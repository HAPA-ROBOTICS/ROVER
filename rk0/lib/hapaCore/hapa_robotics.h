#ifndef HAPA_ROBOTICS
#define HAPA_ROBOTICS



#include "globalVar.h"
#include "hapa_motor.h"
#include "hapa_uart.h"

//Kit version
#define HAPA_RK0 0
#define HAPA_RK1 1
#define HAPA_RK2 2


typedef enum{
    HAPA_OK = 0,
    HAPA_ERR = !HAPA_OK
} hapa_err_t;


void hapa_init_system(void);



#if KIT_VERSION == HAPA_RK0

    //IR REMOTE
    #define IR_PORT GPIOB
    #define IR_PIN  GPIO_PIN_0

#endif

#endif