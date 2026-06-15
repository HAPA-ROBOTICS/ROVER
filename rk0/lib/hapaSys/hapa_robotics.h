#ifndef HAPA_ROBOTICS
#define HAPA_ROBOTICS



#include "globalVar.h"
#include "hapaMotor.h"

//Kit version
#define HAPA_RK0 0
#define HAPA_RK1 1
#define HAPA_RK2 2


typedef enum{
    HAPA_OK = 0,
    HAPA_ERR = !HAPA_OK
} hapa_err_t;


hapa_err_t hapa_init_system(void);

#endif