#define SIMULATION 0

#if SIMULATION
#include "../API/webots/webotsAPI.h"
#else
//#include "../API/epuck/epuckAPI.h"
#include "../API/epuck/myAPI.h"
#endif
#include "../API/epuck/file_loader.h"

#define WAIT_STEPS 20
#define MAX_SAMPLES 10

extern int events_count;

void robot_setup() {
    init_robot();
    init_sensors();
    //init_camera();
    //calibrate_prox();

    load_files();
}

void robot_loop() {

    time_t last_second = time(0);

    while(robot_go_on()) {

        get_ground(IR_ground);
        proceed();
        if (time(0)-last_second >= 1) {
	    last_second = time(0);
	    for (int i=0; i<number_of_shapes; i++) {
		compare_events(shapes[i].name, shapes[i].events, shapes[i].events_size, events, events_count);
	    }
	}
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
