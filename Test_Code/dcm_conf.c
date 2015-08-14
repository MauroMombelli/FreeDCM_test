/*
 * dcm_conf.c
 *
 *  Created on: 16/mag/2015
 *      Author: mauro
 */

#include "dcm_conf.h"

struct Vector3f gyroValue = { 0, 0, 0 };
struct Vector3f acceValue = { 0, 0, 0 };
struct Vector3f magneValue = { 0, 0, 0 };

uint8_t get_next_acce(struct Vector3f* const result){
    //TODO:
    result->x = acceValue.x;
    result->y = acceValue.y;
    result->z = acceValue.z;
	return 0;
}

uint8_t get_next_magne(struct Vector3f* const result){
    //TODO:
    result->x = magneValue.x;
    result->y = magneValue.y;
    result->z = magneValue.z;
	return 0;
}

const struct sensors sensor_array = {
        (const struct error_estimator[]){
            {NULL, &get_next_acce, &get_estimated_error_acce},
            {NULL, &get_next_magne, &get_estimated_error_magne}
        },
        sizeof(sensor_array.sensors)/sizeof(sensor_array.sensors[0]),
    };
