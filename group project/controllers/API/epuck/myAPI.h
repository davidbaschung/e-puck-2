
// BASE CREEE A PARTIR DU PREMIER CONTROLLEUR

#ifndef PROJET_II_MYAPI_H
#define PROJET_II_MYAPI_H

#include "epuckAPI.h"
#include "shape_match.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdbool.h>

/*** Custom Library Part ***/


#define K 2.6
#define T_I -3000
#define T_D 0
#define PID_WALL_FOLLOW_TARGET 80
#define PID_MAX_DS 200

#define find_block_message "FFFF"

#define TIME_STEP 64

#define FOLLOWER 1
#define TURNING 2
#define REVERSE 3

#define STANDARD_SPEED 200
#define NORM_DISTANCE (((float)STANDARD_SPEED)/1000*M_PI*4.1 * DISTANCE_IMPRECISION)

unsigned char red[CAMERA_HEIGHT*CAMERA_WIDTH];
unsigned char green[CAMERA_HEIGHT*CAMERA_WIDTH];
unsigned char blue[CAMERA_HEIGHT*CAMERA_WIDTH];
short int prox_values[8];
short int IR_ground[GROUND_SENSORS_COUNT];
struct timespec last_event_detected;
struct timespec ultimate_step;
struct timespec current_time;
int last_state;
_Bool first_record;

void love();
void explore();
void line_following();

void forward();
void stop();

void proceed();

/*** End of Custom Library ***/

#endif //PROJET_II_MYAPI_H
