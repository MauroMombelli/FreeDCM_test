/*
 * dcm_conf.c
 *
 *  Created on: 16/mag/2015
 *      Author: mauro
 */

#include "dcm_conf.h"

struct Vector3f gyroValue = { 1, 1, 1 };
struct Vector3f acceValue = { 1, 1, 1 };
struct Vector3f magneValue = { 1, 1, 1 };

const struct sensors sensor_array = {
        (struct error_estimator[]){
            {ACCELEROMETER, &acceValue},
            {MAGNETOMETER, &magneValue}
        },
        2,
    };
