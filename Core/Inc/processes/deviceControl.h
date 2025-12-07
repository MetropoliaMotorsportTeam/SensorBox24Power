
#ifndef INC_DEVICECTL_H_
#define INC_DEVICECTL_H_

#include <stdint.h>
#include "stm32g4xx_hal.h"

void SwitchOnOff(GPIO_TypeDef *port, uint16_t pin, uint8_t state);
void SwitchOutput();

#endif
