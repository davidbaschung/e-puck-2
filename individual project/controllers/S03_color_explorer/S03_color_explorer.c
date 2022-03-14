
#define SIMULATION 0

#if SIMULATION
#include "../API/webots/webotsAPI.h"  
#else
#include "../API/epuck/epuckAPI.h"
#endif

#define WAIT_STEPS 20 
#define MAX_SAMPLES 10

void robot_setup() {
    init_robot();
    init_camera();
    init_sensors();
    calibrate_prox();
}

void robot_loop() {
    short int prox_values[8];
	
    unsigned char red[CAMERA_WIDTH * CAMERA_HEIGHT];
    unsigned char green[CAMERA_WIDTH * CAMERA_HEIGHT];
    unsigned char blue[CAMERA_WIDTH * CAMERA_HEIGHT];
    

    while (robot_go_on()) {

        get_prox_calibrated(prox_values);

        double prox_left = (4 * prox_values[7] + 2 * prox_values[6] + prox_values[5]) / 7.;
        double prox_right = (4 * prox_values[0] + 2 * prox_values[1] + prox_values[2]) / 7.;

        double ds_left = (NORM_SPEED * prox_left) / MAX_PROX;
        double ds_right = (NORM_SPEED * prox_right) / MAX_PROX;
        
        double speed_left = bounded_speed(NORM_SPEED - ds_right);
        double speed_right = bounded_speed(NORM_SPEED - ds_left);

        set_speed(speed_left, speed_right);
        
        
        
        // COLOR DETECTION
        get_camera(red,green,blue);
      
        int red_count=0;
        int green_count=0;
        int blue_count=0;
        int custom_width = CAMERA_WIDTH; int custom_height = CAMERA_HEIGHT*0.1f;
        for (int n=(int)((((float)CAMERA_HEIGHT)-custom_height)/2); n<(int)((((float)CAMERA_HEIGHT)+custom_height)/2); n++) {
            for (int m=0; m<CAMERA_WIDTH; m++) {
                int redpixel = (int) red[n * CAMERA_WIDTH + m];
                int greenpixel = (int) green[n * CAMERA_WIDTH + m];
                int bluepixel = (int) blue[n * CAMERA_WIDTH + m];
                red_count += redpixel;
                green_count += greenpixel;
                blue_count += bluepixel;
                
              printf("R:%d G:%d B:%d\n",red[0],green[0],blue[0]);
            }
        }
        
        float threshold_ratio = 17.0/16;
        green_count *= 97.25/100;
        
        printf("Rc:%d Gc:%d Bc:%d\n",red_count,green_count,blue_count);
        
        if ( 2*red_count > ((green_count+blue_count)*threshold_ratio) ) {
            enable_led(3); disable_led(2); disable_led(1);
            printf("red\n");
        }
        else if ( 2*green_count > ((red_count+blue_count)*threshold_ratio) ) {
            disable_led(3); enable_led(2); disable_led(1);
            printf("green\n");
        }
        else if ( 2*blue_count > ((red_count+green_count)*threshold_ratio) ) {
            disable_led(3); disable_led(2); enable_led(1);
            printf("blue\n");
        }
        else {
            for (int i=0; i<LED_COUNT; i++) {
              disable_led(i);
            }
              printf("none\n");
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




