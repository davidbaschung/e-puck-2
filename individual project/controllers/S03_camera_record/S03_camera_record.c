
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

  // open files for writing
  FILE *csvR = fopen("cameraValuesRed.csv", "w");
  FILE *csvG = fopen("cameraValuesGreen.csv", "w");
  FILE *csvB = fopen("cameraValuesBlue.csv", "w");
  
  // check if files opened correctly
  if ((csvR == NULL) || (csvG == NULL) || (csvB == NULL)){
    printf("Error opening csv file!\n");
    exit(1);
  }
  
  // write header of files
  fprintf(csvR, "line,");
  fprintf(csvG, "line,");
  fprintf(csvB, "line,");


  for (int i=0; i<CAMERA_WIDTH; i++) {
    fprintf(csvR, "p%d,", i);
    fprintf(csvG, "p%d,", i);
    fprintf(csvB, "p%d,", i);
  }

  fprintf(csvR, "\n");
  fprintf(csvG, "\n");
  fprintf(csvB, "\n");

  // wait for a while 
  for (int step=0; step<WAIT_STEPS; step++)  {
    robot_go_on();
  }

  for (int step=0; step<MAX_SAMPLES; step++)  {
      
    robot_go_on();
    
    get_camera(red, green, blue);
        
    for (int n=0; n<CAMERA_HEIGHT; n++) {
    
      fprintf(csvR, "%d,", n);
      fprintf(csvG, "%d,", n);
      fprintf(csvB, "%d,", n);
      
      for (int m=0;m<CAMERA_WIDTH;m++) {          
        fprintf(csvR, "%d,", (int) red[n * CAMERA_WIDTH + m]);
        fprintf(csvG, "%d,", (int) green[n * CAMERA_WIDTH + m]);
        fprintf(csvB, "%d,", (int) blue[n * CAMERA_WIDTH + m]);
      }
      
      fprintf(csvR, "\n");
      fprintf(csvG, "\n");
      fprintf(csvB, "\n");
    }
  }  
  cleanup_robot();  
}

int main (int argc, char **argv) {
    #if SIMULATION
    #else
    ip = argv[1];
    #endif
    
    robot_setup();

    robot_loop();   
}




