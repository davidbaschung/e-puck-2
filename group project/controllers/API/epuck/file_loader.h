
// CHARGEMENT DES FICHIERS CSV CONTENANT LES EVENEMENTS

#define SIMULATION 0

#if SIMULATION
#include "../API/webots/webotsAPI.h"
#else
#include "../API/epuck/epuckAPI.h"
#endif

#include "../API/epuck/myAPI.h"
#include <dirent.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

#define WAIT_STEPS 20
#define MAX_SAMPLES 10

typedef struct file_values {char* name; double **events; int events_size; } shape_struct;
shape_struct *shapes;
int number_of_shapes;

void load_files();
void scan_wheels();
void discrete_capture();
void last_captures_average();
void scan_shapes();
bool check_compatibilty;
