//v_shylin

#define SIMULATION 0

#if SIMULATION
#include "../API/webots/webotsAPI.h"
#else
//#include "../API/epuck/epuckAPI.h"
#include "../API/epuck/myAPI.h"
#endif

#define WAIT_STEPS 20
#define MAX_SAMPLES 10




void robot_setup() {
    init_robot();
    init_sensors();
    //init_camera();
    //calibrate_prox();
}

void robot_loop() {

    while(robot_go_on()) {

        get_ground(IR_ground);

        proceed();
    }
    cleanup_robot();
}


int main(int argc, char **argv) {
    #if SIMULATION
    #else
    ip = argv[1];
    #endif

    robot_setup();

    robot_loop();
}