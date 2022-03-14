
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
}

void robot_loop() {

    unsigned char red[CAMERA_WIDTH * CAMERA_HEIGHT];
    unsigned char green[CAMERA_WIDTH * CAMERA_HEIGHT];
    unsigned char blue[CAMERA_WIDTH * CAMERA_HEIGHT];
    int counter = 0;
    
    while (robot_go_on()) {
      
    get_camera(red,green,blue);
      
    int red_count=0;
    int green_count=0;
    int blue_count=0;
    int custom_width = CAMERA_WIDTH; int custom_height = CAMERA_HEIGHT*0.1f;
    // int 
      for (int n=(int)((((float)CAMERA_HEIGHT)-custom_height)/2); n<(int)((((float)CAMERA_HEIGHT)+custom_height)/2); n++) {
          for (int m=0; m<CAMERA_WIDTH; m++) {
              int redpixel = (int) red[n * CAMERA_WIDTH + m];
              int greenpixel = (int) green[n * CAMERA_WIDTH + m];
              int bluepixel = (int) blue[n * CAMERA_WIDTH + m];
              // printf("R:%d G:%d B:%d\n",red[0],green[0],blue[0]);
              red_count += redpixel;
              green_count += greenpixel;
              blue_count += bluepixel;
          }
      }
      
      float threshold_ratio = 17.0/16;
      green_count *= 97.25/100;
      
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
      
      printf("Rc:%d Gc:%d Bc:%d\n",red_count,green_count,blue_count);
      
      
      
        // open files for writing
       // FILE *csvR = fopen("cameraValuesRed.csv", "w");
      // FILE *csvG = fopen("cameraValuesGreen.csv", "w");
      // FILE *csvB = fopen("cameraValuesBlue.csv", "w");
  
      // check if files opened correctly
      // if ((csvR == NULL) || (csvG == NULL) || (csvB == NULL)){
      // printf("Error opening csv file!\n");
      // exit(1);
      // }
  
      // write header of files
      // fprintf(csvR, "line,");
      // fprintf(csvG, "line,");
      // fprintf(csvB, "line,");


      // for (int i=0; i<CAMERA_WIDTH; i++) {
        // fprintf(csvR, "p%d,", i);
        // fprintf(csvG, "p%d,", i);
        // fprintf(csvB, "p%d,", i);
      // }
      
      // fprintf(csvR, "\n");
      // fprintf(csvG, "\n");
      // fprintf(csvB, "\n");
      // fprintf(csvR, "\n");
      // fprintf(csvG, "\n");
      // fprintf(csvB, "\n");
      
          counter = 0;
      }
      counter++;



     
     
      // //wait for a while 
      // for (int step=0; step<WAIT_STEPS; step++)  {
        // robot_go_on();
      // }
    
      // for (int step=0; step<MAX_SAMPLES; step++)  {
          
        // robot_go_on();
        
        // get_camera(red, green, blue);
            
        // for (int n=0; n<CAMERA_HEIGHT; n++) {
        
          // fprintf(csvR, "%d,", n);
          // fprintf(csvG, "%d,", n);
          // fprintf(csvB, "%d,", n);
          
          // for (int m=0;m<CAMERA_WIDTH;m++) {          
            // fprintf(csvR, "%d,", (int) red[n * CAMERA_WIDTH + m]);
            // fprintf(csvG, "%d,", (int) green[n * CAMERA_WIDTH + m]);
            // fprintf(csvB, "%d,", (int) blue[n * CAMERA_WIDTH + m]);
          // }
          
          // fprintf(csvR, "\n");
          // fprintf(csvG, "\n");
          // fprintf(csvB, "\n");
         
      // cleanup_robot();  
   // }
}

int main (int argc, char **argv) {
    #if SIMULATION
    #else
    ip = argv[1];
    #endif
    
    robot_setup();
    robot_loop();   
}