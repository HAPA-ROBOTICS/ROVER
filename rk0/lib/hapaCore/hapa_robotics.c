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

static void hapa_motion_light_ind_init(void){
    
    
    GPIO_InitTypeDef led_ind = {
        .Pin = RED_LED_IND | GREEN_LED_IND | BLUE_LED_IND,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = GPIO_SPEED_FREQ_LOW,
        .Pull = GPIO_NOPULL
    };

    HAL_GPIO_Init(LED_IND_GPIO_PORT, &led_ind);

    HAL_GPIO_WritePin(LED_IND_GPIO_PORT, RED_LED_IND, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_IND_GPIO_PORT, BLUE_LED_IND, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_IND_GPIO_PORT, GREEN_LED_IND, GPIO_PIN_RESET); //indcate we are ready

}


void hapa_init_system(void)
{
    HAL_Init();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    hapa_motor_init();
    hapa_uart_init();
    hapa_motion_light_ind_init();


    #if KIT_VERSION == HAPA_RK0
        hapa_ir_init();
    #endif
}

void hapa_motion_light_toggle(hapa_motion_light_t light){

    switch (light)
    {
    case HAPA_MOTION_LIGHT_OFF: // indicate rover in neutral 
    
        HAL_GPIO_WritePin(LED_IND_GPIO_PORT, BLUE_LED_IND | RED_LED_IND, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_IND_GPIO_PORT, GREEN_LED_IND, GPIO_PIN_RESET); 
        break;

    case HAPA_MOTION_LIGHT_FD: // indicate rover is in drive
        HAL_GPIO_WritePin(LED_IND_GPIO_PORT, GREEN_LED_IND | RED_LED_IND, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_IND_GPIO_PORT, BLUE_LED_IND, GPIO_PIN_RESET); 
        break;

    case HAPA_MOTION_LIGHT_RV: // indicate rover is in reverse
        HAL_GPIO_WritePin(LED_IND_GPIO_PORT, GREEN_LED_IND | BLUE_LED_IND, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_IND_GPIO_PORT, RED_LED_IND, GPIO_PIN_RESET); 
        break;
    
    default:
        break;
    }

}