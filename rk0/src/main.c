
#include "globalVar.h"


//select kit version
#define KIT_VERSION HAPA_RK0


void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{

    hapa_init_system();

    while (1)
    {
                // Forward
        HAL_GPIO_WritePin(MOTOR_PORT, ENA, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT, IN1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT, IN2, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(MOTOR_PORT, ENB, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT, IN3, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT, IN4, GPIO_PIN_RESET);

        HAL_Delay(5000);

        // Stop
        HAL_GPIO_WritePin(MOTOR_PORT, ENA, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_PORT, ENB, GPIO_PIN_RESET);

        HAL_Delay(2000);

        // Reverse
        HAL_GPIO_WritePin(MOTOR_PORT, IN1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_PORT, IN2, GPIO_PIN_SET);

        HAL_GPIO_WritePin(MOTOR_PORT, IN3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_PORT, IN4, GPIO_PIN_SET);

        HAL_GPIO_WritePin(MOTOR_PORT, ENA, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_PORT, ENB, GPIO_PIN_SET);

        HAL_Delay(5000);

        // Stop
        HAL_GPIO_WritePin(MOTOR_PORT, ENA, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR_PORT, ENB, GPIO_PIN_RESET);

        HAL_Delay(2000);
    }
}