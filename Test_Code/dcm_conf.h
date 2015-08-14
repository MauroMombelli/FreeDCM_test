/*
 * dcm_conf.h
 *
 *  Created on: 16/mag/2015
 *      Author: mauro
 */

#ifndef DCM_CONF_H_
#define DCM_CONF_H_

#include "FreeDCM/dcm.h"

#include "FreeDCM/estimators/accelerometer.h"
#include "FreeDCM/estimators/magnetometer.h"

uint8_t get_next_acce(struct Vector3f* const result);

uint8_t get_next_magne(struct Vector3f* const result);

extern const struct sensors sensor_array;

#endif /* DCM_CONF_H_ */
