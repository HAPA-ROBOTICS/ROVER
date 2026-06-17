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

    while (1){
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