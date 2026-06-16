#include "hapa_robotics.h"




static void hapa_ir_init(void){
    GPIO_InitTypeDef ir_gpio = {
        .Pin = IR_PIN,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };

    HAL_GPIO_Init(IR_PORT, &ir_gpio);
}


void hapa_init_system(void)
{
    HAL_Init();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    hapa_motor_init();
    hapa_uart_init();


    #if KIT_VERSION == HAPA_RK0
        hapa_ir_init();
    #endif
}


