
// BASE CREEE A PARTIR DU PREMIER CONTROLLEUR

#include "myAPI.h"
#include "epuckAPI.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/** TODO : WE USED THE ROBOT 4211 FOR THE TESTS, BUT WORKS WELL WITH UNBROKEN ROBOTS*/


void stop() {
    /** STOP THE ROBOT (0cm/s) */
    set_speed(0,0);
}

void forward() {
    set_speed(STANDARD_SPEED, STANDARD_SPEED);
    last_state = FOLLOWER;
}


/** FUNCTION OF LINE FOLLOWER WITH ANGLE DETECTION */

void line_following() {

    /** --------------------------- LINE FOLLOWING DECLARATIONS ---------------------------*/
    double speed = STANDARD_SPEED;
// /3.
    /** THRESHOLD FOR THE SENSORS : ~200 IS MIN (BLACK) ~1000 IS MAX (WHITE) */
    double IR_threshold = 600;

    double IR_left = IR_ground[0];
    double IR_right = IR_ground[2];

    double ds_left = (speed * IR_left) / IR_threshold;
    double ds_right = (speed * IR_right) / IR_threshold;

    double speed_left = bounded_speed(speed + ds_left/2);
    double speed_right = bounded_speed(speed + ds_right/2);
//4
/** ------------------------------ END OF LINE FOLLOWING DECLARATIONS -----------------------*/


    /** TURN ANGLE VALUE (NOT REAL ANGLE) */
    int turnRange = 150;
    //50, works well with 60 and /4., NORM_DISTANCE/2.
    int repeatRange = turnRange * 3;

    /** VARIABLE TO DETERMINE THE TURN ANGLE */
    static int timestep = 0;

    /** ROTATION COUNTERS */
    static int rotateCounter = 0;
    static int addTime = 0;

    /** HOOKING COUNTER */
    static int hookingCounter = 0;

    /** DELAY COUNTER */
    static int delay = 0;
    /** VARIABLES TO LOCK A VARIABLE CHANGE */
    static int lock = 0;
    static int end = 0;

    /** HOW MUCH TIMES TO VERIFY THE FIGURE */
    int verify = 14;

    /** COUNTERS TO GET THE RIGHT FIGURE */
    static int rectangle = 0;
    static int octagon = 0;
    static int diamond = 0;

    static int rectangleTwo = 0;
    static int octagonTwo = 0;
    static int diamondTwo = 0;

    static int cross = 0;

    /** END OF COUNTERS */

    ///////////////////////////////////////////////
    /** FOR TESTING : A VARIABLE TO SEND RESULTS */
    static int test = 0;
    ///////////////////////////////////////////////

    /** SEARCH THE LINE IF LOST */
if (end == 0) {
    if (IR_ground[1] > IR_threshold) {
        hookingCounter = 0;
        test = 0;
        rotateCounter++;
        if (rotateCounter < turnRange) {
            /** ADVANCE FEW SPACES TO CENTER THE ROBOT WITHIN AN ANGLE */
            if (delay < 26) {
                delay++;
                set_speed(STANDARD_SPEED, STANDARD_SPEED);
            }
            else {
		if (timestep==0) {

		    clock_gettime(CLOCK_REALTIME, &current_time);
		    double time = ( (current_time.tv_sec - last_event_detected.tv_sec) * 1e6 + (current_time.tv_nsec - last_event_detected.tv_nsec) / 1e3 ) / 1e6;
		    clock_gettime(CLOCK_REALTIME, &ultimate_step);
		    clock_gettime(CLOCK_REALTIME, &last_event_detected);
		    record_event(0,1,time,time*NORM_DISTANCE,NORM_DISTANCE,NORM_DISTANCE);
		    printf("---- turning ----\n");
		    last_state = TURNING;

		}

                timestep++;

                set_speed(STANDARD_SPEED, -STANDARD_SPEED);
            } /** END OF ADVANCE FUNCTION */

        } else {
            if (lock == 0) {
		printf("---- reverse turning----\n");
                timestep = 0;
                lock = 1;
		clock_gettime(CLOCK_REALTIME, &ultimate_step);
		last_state = REVERSE;
            }
            timestep++;
            set_speed(-STANDARD_SPEED, STANDARD_SPEED);
        }
        /** OTHER SIDE */
        rotateCounter = rotateCounter % repeatRange;

    } else {

        if (test == 0) {
            test = 1;
	    clock_gettime(CLOCK_REALTIME, &current_time);
	    double total_time = ( (current_time.tv_sec - last_event_detected.tv_sec) * 1e6 + (current_time.tv_nsec - last_event_detected.tv_nsec) / 1e3 ) / 1e6;
	    double angle_time = total_time  -  2 * ( (ultimate_step.tv_sec - last_event_detected.tv_sec) * 1e6 + (ultimate_step.tv_nsec - last_event_detected.tv_nsec) / 1e3 ) / 1e6;
	    clock_gettime(CLOCK_REALTIME, &last_event_detected);
	    double dir = last_state==TURNING? -1 : 1 ;
	    record_event(compute_angle(STANDARD_SPEED*(-dir),-STANDARD_SPEED*(-dir),angle_time),0,angle_time,0,-dir*NORM_DISTANCE,dir*NORM_DISTANCE);
            printf("---- line following ----\n");
	    last_state = FOLLOWER;
        }


        ///////////////////////////////////////////////////////
        /** ---------- FIGURE DETECTION -------------------- */
        ///////////////////////////////////////////////////////


        /** OCTAGON */
        if (timestep >= 148 && timestep <= 168) {
            octagon++;
        }
	if (timestep >= 20 && timestep <= 50) {
	    octagonTwo++;
	}

        /** DIAMOND */

        if (timestep >= 170 && timestep <= 188) {
            diamond++;
	} else if (timestep > 200) {
	    diamond++;
	}
        if (timestep >= 52 && timestep <= 70) {
	    diamondTwo++;
	} else if (timestep >= 82 && timestep <= 94) {
	    diamondTwo++;
	}

        /** RECTANGLE */

        if (timestep >= 190 && timestep <= 196) {
            rectangle++;
        }
	if (timestep >= 56 && timestep <= 80) {
	    rectangleTwo++;
	}

        /** CROSS */
						//36
        if ((timestep >= 190 && timestep <= 196) || (timestep >= 40 && timestep <= 78)) {
            cross++;
        }

//        /** --------------- FIGURE CONCLUSION -------------- */
//
//        if (octagon > verify || octagonTwo > verify) {
//            toggle_led(0);
//            stop();
//            printf("------------------\n");
//            printf("THIS IS AN OCTAGON!\n");
//            printf("------------------\n");
//            end = 1;
//        }
//        if (diamond > verify || diamondTwo > verify) {
//	    toggle_led(0);
//            toggle_led(1);
//            stop();
//            printf("------------------\n");
//            printf("THIS IS A DIAMOND!\n");
//            printf("------------------\n");
//            end = 1;
//        }
//        if (rectangle > verify || rectangleTwo > verify) {
//	    toggle_led(0);
//            toggle_led(1);
//            toggle_led(2);
//            stop();
//            printf("------------------\n");
//            printf("THIS IS A RECTANGLE!\n");
//            printf("------------------\n");
//            end = 1;
//        }
//        if (cross > verify + 3) {
//	    toggle_led(0);
//            toggle_led(1);
//            toggle_led(2);
//            toggle_led(3);
//            stop();
//            printf("------------------\n");
//            printf("THIS IS A CROSS!\n");
//            printf("------------------\n");
//            end = 1;
//        }

        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////



        /** RESET THE VARIABLES */
        timestep = 0;
        delay = 0;
        addTime = 0;
        rotateCounter = 0;
        lock = 0;
        //turnRange = 60;

	/** LINE STABILISING DELAY */
        hookingCounter++;
        if (hookingCounter >= 8) {
            /** FOLLOW THE LINE */
            set_speed(speed_left, speed_right);
        }
    }
}
}

/** EXECUTE THE PROGRAM */

void proceed() {


	/** PHASE STATE */
	static int phase = 0;
	/** PHASE STATE VERIFIER */
	static int phaseCounter = 0;

    if (phase == 0) {
	if (IR_ground[1] < 600) {
	    phaseCounter++;
	    if (phaseCounter>=5)
	    phase = 1;
        } else {
	    phaseCounter = 0;
	}
        forward();
    } else {
        line_following();
    }
}

/** END OF CODE */

