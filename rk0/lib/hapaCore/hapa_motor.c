#include "hapa_robotics.h"

void hapa_motor_init(void)
{
#if KIT_VERSION == HAPA_RK0


    GPIO_InitTypeDef motor_gpio = {
        .Pin = MOTOR_ENABLE | LEFT_IN1 | LEFT_IN2 | RIGHT_IN1 | RIGHT_IN2,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };

    HAL_GPIO_Init(MOTOR_PORT, &motor_gpio);

    hapa_move(HAPA_STOP, HAPA_STOP);

#elif KIT_VERSION == HAPA_RK1
    // RK1 motor GPIO init goes here later
#endif
}

#if KIT_VERSION == HAPA_RK0

    void hapa_move(hapa_motor_state_t left, hapa_motor_state_t right)
    {
        if (left == HAPA_STOP && right == HAPA_STOP)
        {
            HAL_GPIO_WritePin(MOTOR_PORT,
                            MOTOR_ENABLE | LEFT_IN1 | LEFT_IN2 | RIGHT_IN1 | RIGHT_IN2,
                            GPIO_PIN_RESET);
            hapa_motion_light_toggle(HAPA_MOTION_LIGHT_OFF);
            return;
        }

        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_ENABLE, GPIO_PIN_SET);

        switch (left)
        {
            case HAPA_REVERSE:
                HAL_GPIO_WritePin(MOTOR_PORT, LEFT_IN1, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_PORT, LEFT_IN2, GPIO_PIN_RESET);
                hapa_motion_light_toggle(HAPA_MOTION_LIGHT_RV);
                break;

            case HAPA_FORWARD:
                HAL_GPIO_WritePin(MOTOR_PORT, LEFT_IN1, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(MOTOR_PORT, LEFT_IN2, GPIO_PIN_SET);
                hapa_motion_light_toggle(HAPA_MOTION_LIGHT_FD);

                break;

            case HAPA_STOP:
            default:
                HAL_GPIO_WritePin(MOTOR_PORT, LEFT_IN1 | LEFT_IN2, GPIO_PIN_RESET);
                break;
        }

        switch (right)
        {
            case HAPA_REVERSE:
                HAL_GPIO_WritePin(MOTOR_PORT, RIGHT_IN1, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_PORT, RIGHT_IN2, GPIO_PIN_RESET);
                hapa_motion_light_toggle(HAPA_MOTION_LIGHT_RV);
                break;

            case HAPA_FORWARD:
                HAL_GPIO_WritePin(MOTOR_PORT, RIGHT_IN1, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(MOTOR_PORT, RIGHT_IN2, GPIO_PIN_SET);
                hapa_motion_light_toggle(HAPA_MOTION_LIGHT_FD);
                break;

            case HAPA_STOP:
            default:
                HAL_GPIO_WritePin(MOTOR_PORT, RIGHT_IN1 | RIGHT_IN2, GPIO_PIN_RESET);
                break;
        }
    }

#elif KIT_VERSION == HAPA_RK1

    void hapa_move(
        hapa_motor_state_t lf,
        hapa_motor_state_t rf,
        hapa_motor_state_t lb,
        hapa_motor_state_t rb
    )
    {
        // RK1 four-wheel independent control goes here later
    }

#endif