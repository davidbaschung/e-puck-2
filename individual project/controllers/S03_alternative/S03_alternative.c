
#define SIMULATION 0

#if SIMULATION
#include "../API/webots/webotsAPI.h"  
#else
#include "../API/epuck/epuckAPI.h"
#endif

// messages
#define MSG_START "GOGO"
#define STOP 0
#define EXPLORER 1
#define LOVER 2

void robot_setup() {
    init_robot();
    init_sensors();
    init_communication();
}



void robot_loop() {
    char rcv[4];
    short int prox_values[8];
      
    int id = get_robot_ID();
    
    int state = LOVER;
    
    int counter = 0;

    while (robot_go_on()) {
    
    
        get_prox_calibrated(prox_values);

        double prox_left = (prox_values[7] + prox_values[6] + prox_values[5] + prox_values[4]) / 4.;
        double prox_right = (prox_values[0] + prox_values[1] + prox_values[2] + prox_values[3]) / 4.;

        double ds_left = (NORM_SPEED * prox_left) / MAX_PROX;
        double ds_right = (NORM_SPEED * prox_right) / MAX_PROX;
        
        double speed_left = bounded_speed(NORM_SPEED - ds_right);
        double speed_right = bounded_speed(NORM_SPEED - ds_left);
        


          
        // strcmp returns 0 when strings are equal
        
       receive_msg(rcv);
        
       if (state == STOP) {
         set_speed(0, 0);
         if (strcmp(rcv, MSG_START) == 0) {
           counter++;
         }
         if (counter > 1) {
         set_speed(speed_left, speed_right);
           state = EXPLORER;
           counter = 0;
         }
       }
       
       else if (state == EXPLORER) {
         set_speed(speed_left, speed_right);
         if ((prox_values[0] + prox_values[1] + prox_values[2] + prox_values[3] + prox_values[7] + prox_values[6] + prox_values[5] + prox_values[4])/8 < (0.2 * MAX_PROX)) {
           set_speed(speed_right, speed_left);
           state = LOVER;
         }
       }
       
       else if (state == LOVER){
         set_speed(speed_right, speed_left);
         if (speed_left < 0 && speed_right < 0) {
           set_speed(0, 0);
           send_msg(MSG_START);
           state = STOP;
         }
       }
    }
}

int main (int argc, char **argv) {
    #if SIMULATION
    #else
    ip = argv[1];
    #endif
    
    robot_setup();
    robot_loop();   
}




