#include "hapa_robotics.h"



#if KIT_VERSION == HAPA_RK0
    uint32_t hapa_ir_ctrl[3] ={0};
        
#endif

#if KIT_VERSION == HAPA_RK0

    static TIM_HandleTypeDef htim2;
    static void hapa_ir_timer_init(void){
        __HAL_RCC_TIM2_CLK_ENABLE();

        htim2.Instance = TIM2;
        htim2.Init.Prescaler = (SystemCoreClock / 1000000) - 1; // 1 us tick
        htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim2.Init.Period = 0xFFFF;
        htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

        HAL_TIM_Base_Init(&htim2);
        HAL_TIM_Base_Start(&htim2);
    }

    static uint16_t micros_now(void){
        return __HAL_TIM_GET_COUNTER(&htim2);
    }

    static uint8_t wait_for_state(GPIO_PinState state, uint32_t timeout_us, uint32_t *duration){
        uint16_t start = micros_now();

        while (HAL_GPIO_ReadPin(IR_PORT, IR_PIN) != state)
        {
            if ((uint16_t)(micros_now() - start) > timeout_us)
                return 0;
        }

        start = micros_now();

        while (HAL_GPIO_ReadPin(IR_PORT, IR_PIN) == state)
        {
            if ((uint16_t)(micros_now() - start) > timeout_us)
                return 0;
        }

        *duration = (uint16_t)(micros_now() - start);
        return 1;
    }

    uint8_t hapa_ir_read_nec(uint32_t *code){
        uint32_t duration = 0;
        uint32_t data = 0;

        // NEC starts with ~9ms LOW
        if (!wait_for_state(GPIO_PIN_RESET, 12000, &duration)) return 0;
        if (duration < 8000 || duration > 10000) return 0;

        // Then ~4.5ms HIGH
        if (!wait_for_state(GPIO_PIN_SET, 7000, &duration)) return 0;
        if (duration < 3500 || duration > 5500) return 0;

        for (uint8_t i = 0; i < 32; i++)
        {
            // 560us LOW
            if (!wait_for_state(GPIO_PIN_RESET, 2000, &duration)) return 0;

            // HIGH length determines bit
            if (!wait_for_state(GPIO_PIN_SET, 3000, &duration)) return 0;

            if (duration > 1000)
            {
                data |= (1UL << i);
            }
        }

        *code = data;
        return 1;
    }

    static void hapa_ir_init(void){
    GPIO_InitTypeDef ir_gpio = {
        .Pin = IR_PIN,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_LOW
    };

    HAL_GPIO_Init(IR_PORT, &ir_gpio);
    hapa_ir_timer_init();

    for (uint32_t index = 0; index < 3; index++)
    {
        uint32_t code = 0;

        hapa_motion_light_toggle(HAPA_MOTION_LIGHT_RV);

        while (!hapa_ir_read_nec(&code))
        {
            // Wait for valid IR button
        }

        hapa_ir_ctrl[index] = code;

        hapa_motion_light_toggle(HAPA_MOTION_LIGHT_FD);
        HAL_Delay(1000);
    }

    hapa_motion_light_toggle(HAPA_MOTION_LIGHT_OFF);
}

#endif
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