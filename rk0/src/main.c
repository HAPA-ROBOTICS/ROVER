#include "globalVar.h"

// select kit version
#define KIT_VERSION HAPA_RK0

void SysTick_Handler(void) //init clock
{
    HAL_IncTick();
}

int _write(int file, char *ptr, int len) //init uart call
{
    HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}

int main(void)
{
    hapa_init_system();

    printf("\n");
    printf("=====================================\n");
    printf(" HAPA Robotics - RK0\n");
    printf(" Rover Kit 0 Booting...\n");
    printf("=====================================\n");

    uint32_t code;

    while (1){

        if(HAL_GPIO_ReadPin(IR_PORT, IR_PIN)){ //only when pin is high 
            if(hapa_ir_read_nec(&code)){
                if(code == hapa_ir_ctrl[HAPA_IR_FD])hapa_move(HAPA_FORWARD, HAPA_FORWARD);
                if(code == hapa_ir_ctrl[HAPA_IR_RV])hapa_move(HAPA_REVERSE, HAPA_REVERSE);
                if(code == hapa_ir_ctrl[HAPA_IR_N])hapa_move(HAPA_STOP, HAPA_STOP);
            }
        }

        HAL_Delay(10);
        
        // hapa_move(HAPA_FORWARD, HAPA_FORWARD);
        // HAL_Delay(2000);
        // hapa_move(HAPA_STOP, HAPA_STOP);
        // HAL_Delay(500);
        // hapa_move(HAPA_FORWARD, HAPA_STOP);
        // HAL_Delay(2000);
        // hapa_move(HAPA_STOP, HAPA_STOP);
        // HAL_Delay(500);
        // hapa_move(HAPA_STOP, HAPA_FORWARD);
        // HAL_Delay(2000);
        // hapa_move(HAPA_STOP, HAPA_STOP);
        // HAL_Delay(500);
        // hapa_move(HAPA_STOP, HAPA_FORWARD);
        // hapa_move(HAPA_STOP, HAPA_STOP);
        // HAL_Delay(500);
        // hapa_move(HAPA_REVERSE, HAPA_REVERSE);
        // HAL_Delay(5000);
        // hapa_move(HAPA_STOP, HAPA_STOP);
        // HAL_Delay(500);
    }
}