#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include "FreeDCM/dcm.h"
#include "dcm_conf.h"
#include "original_implementations/MahonyAHRS.h"
#include "TrigonomeC/my_math.h"

extern struct Vector3f gyroValue;
extern struct Vector3f acceValue;
extern struct Vector3f magneValue;
struct Quaternion4f ris;

clock_t start = 0;

void do_step(int i) {
    DCM.dcm_step(&gyroValue, &sensor_array);
    DCM.dcm_get_quaternion(&ris);

    MahonyAHRSupdate(gyroValue.x, gyroValue.y, gyroValue.z, acceValue.x, acceValue.y, acceValue.z, magneValue.x, magneValue.y, magneValue.z);

    if (ris.w != q0 || ris.x != q1 || ris.y != q2 || ris.z != q3) {
        printf("\nstep %i", i);
        printf(" my_quat(%.9g,%.9g,%.9g,%.9g)", ris.w, ris.x, ris.y, ris.z);
        printf(" Mahony (%.9g,%.9g,%.9g,%.9g)", q0, q1, q2, q3);

        printf("\nERROR!");
        exit(1);
    }

    if (i % 1000000 == 0) {
        float duration = (float) (clock() - start) / CLOCKS_PER_SEC;

        printf("\nstep %i OK, step frequency: %f ", i, 1000000 / duration);

        printf(" quat (%f,%f,%f,%f)", ris.w, ris.x, ris.y, ris.z);

        start = clock();
    }
}

int main() {
    printf("check config: %d sensors", sensor_array.sensors_number);

    uint32_t i;

    printf("\ninitializingDCM");
    DCM.dcm_init();


    size_t a;

    const uint32_t iteration = 10000;

    printf("\ntesting speed against mahony algoritm DCM");
    start = clock();
    for (i = 0; i < iteration; i++) {
        DCM.dcm_step(&gyroValue, &sensor_array);
    }
    start = clock() - start;
    DCM.dcm_get_quaternion(&ris);

    printf("\nFreeDCM iteration speed: %f Hz, resulting quaternion: %.9g,%.9g,%.9g,%.9g", iteration / ((float) start / CLOCKS_PER_SEC), ris.w, ris.x, ris.y, ris.z);

    start = clock();
    for (i = 0; i < iteration; i++) {
        MahonyAHRSupdate(gyroValue.x, gyroValue.y, gyroValue.z, acceValue.x, acceValue.y, acceValue.z, magneValue.x, magneValue.y, magneValue.z);
    }
    start = clock() - start;
    printf("\nMahony iteration speed: %f Hz, resulting quaternion: %.9g,%.9g,%.9g,%.9g", iteration / ((float) start / CLOCKS_PER_SEC), q0, q1, q2, q3);


    printf("\ntesting results against mahony algoritm DCM");
    //DCM.dcm_init();
    //MahonyAHRSreset();
    for (i = 0; i < 10; i++) {
        gyroValue.x = i;
        acceValue.y = i;
        magneValue.z = i;

        printf("\nacce: %f,%f,%f", sensor_array.sensors[0].last_data->x, sensor_array.sensors[0].last_data->y, sensor_array.sensors[0].last_data->z);
        printf("\nmagne: %f,%f,%f", sensor_array.sensors[1].last_data->x, sensor_array.sensors[1].last_data->y, sensor_array.sensors[1].last_data->z);

        do_step(i);
    }

    DCM.dcm_get_quaternion(&ris);
    printf("\nQuaternion: %.9g,%.9g,%.9g,%.9g", ris.w, ris.x, ris.y, ris.z);

    i=0;
    DCM.dcm_init();
    MahonyAHRSreset();

    const float halfMax = RAND_MAX / 2.0f;
    start = clock();

    printf("\nQuaternion: %.9g,%.9g,%.9g,%.9g", ris.w, ris.x, ris.y, ris.z);
    while (1) {
        gyroValue.x = rand() - halfMax;
        gyroValue.y = rand() - halfMax;
        gyroValue.z = rand() - halfMax;
        acceValue.x = rand() - halfMax;
        acceValue.y = rand() - halfMax;
        acceValue.z = rand() - halfMax;
        magneValue.x = rand() - halfMax;
        magneValue.y = rand() - halfMax;
        magneValue.z = rand() - halfMax;
        do_step(i++);
    }

    while (1) {
        i++;
        /* ask for gyro */
        scanf("%f, %f, %f", &(gyroValue.x), &(gyroValue.y), &(gyroValue.z));
        /* ask for acce */
        scanf("%f, %f, %f", &(acceValue.x), &(acceValue.y), &(acceValue.z));
        /* ask for magne */
        scanf("%f, %f, %f", &(magneValue.x), &(magneValue.y), &(magneValue.z));

        do_step(i);
    }
    return 0;
}
