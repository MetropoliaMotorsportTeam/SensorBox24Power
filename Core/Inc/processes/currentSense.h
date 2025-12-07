/*
 * currentSense.h
 *
 *  Created on: Nov 16, 2025
 *      Author: dovlatib
 */

#ifndef INC_CURRENTSENSE_H_
#define INC_CURRENTSENSE_H_

#include <stdint.h>

void ReadADCValues(uint16_t *adc1_values, uint16_t *adc2_values);
void CurrentSenseProcess();
void CurrentSenseRead();
uint16_t CurrentSenseRawTomA(uint16_t raw);

#endif /* INC_CURRENTSENSE_H_ */
