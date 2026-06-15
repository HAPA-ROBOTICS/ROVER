#include "hapa_robotics.h"





hapa_err_t hapa_init_system(void){

    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    if(hapa_motor_init() != HAPA_OK)return HAPA_ERR;

    return HAPA_OK;
}