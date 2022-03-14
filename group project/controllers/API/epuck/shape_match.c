
// FICHIER PERMETTANT D'EFFECTUER LA RECONNAISSANCE DES FORMES

#include "shape_match.h"

int events_count = 0;
int first_records = 0;

// angle parcouru par le robot dans une courbe.
double compute_angle(int left_wheel, int right_wheel, double delta_time) {
    double real_left_speed = ((double)left_wheel)/1000 * 4.1 * M_PI; // in cm/s
    double real_right_speed = ((double)right_wheel)/1000 * 4.1 * M_PI; // in cm/s
    double angle_rad = (real_right_speed - real_left_speed) / 5.3 * delta_time;
    return angle_rad;
}

// enregistrement d'un événement (ligne/joint) par le robot.
void record_event(double angle, double along_block, double time, double distance, double
 left_wheel, double right_wheel) {

    if (first_records<3) {
	first_records++;
	return;
    }

    events = (double **) realloc(events, (events_count+1) * sizeof(events));	// la liste d'événements enregistrés par le robot augmente régulièrement.
    if (events == NULL) {
	printf("REALLOC FAILED\n");
    } else {
	double event[] = {angle*ANGLE_IMPRECISION,along_block,time,distance,left_wheel,right_wheel};
	events[events_count] = (double *) malloc(6 * sizeof(double));
	memcpy(events[events_count],event,sizeof(event));
    }

	events_count++;
}


// comparer tous les événements réels et signés
void compare_events(char* name, double** shape_events, int nb_shape_ev, double** real_events, int nb_real_ev) {
    if (nb_shape_ev==0 || nb_real_ev==0) return;


    int regular_match_count = 0, reverse_match_count = 0;
    _Bool success=false;
    if (nb_real_ev==nb_shape_ev) {						// pour chaque fichier, les événements ne sont parcourus que s'il y a autant d'événements dans le fichier et les enregistrements
        printf("\nChecking the shape : %s (%d events)\n",name,nb_shape_ev);
	for (int h=0; h<nb_shape_ev; h++) {					// on prend chaque événement signé un à un

	    for (int i=0, i_ev=h; i<nb_shape_ev; i++, i_ev++) {			// puis on compare leurs éléments suivants pour toute la signature
		printf("h:%d i2:%d i_ev:%d\n",h,i);
	        if (i_ev==nb_shape_ev)
	            i_ev=0;
	        if (event_match(shape_events[i], real_events[i_ev], i)) {
		    regular_match_count++;
	        } else break;
	    }
	    if (regular_match_count>=nb_shape_ev) { success=true; break; }

	    for (int i=nb_shape_ev-1, i_ev=h; i>0; i--, i_ev--) {		// on fait de même pour les précédents en sens inversé. Le robot peut parcourir la forme dans les 2 sens.
		printf("h:%d i2:%d i_ev:%d\n",h,i);
	        if (i_ev==-1) {
	            i_ev=nb_shape_ev-1;
		}
		double inverse_event[] = {-real_events[i_ev][0], real_events[i_ev][1], real_events[i_ev][2], real_events[i_ev][3], real_events[i_ev][5], real_events[i_ev][4]};
	        if (event_match(shape_events[i], inverse_event, i)) {
		    reverse_match_count++;
	        } else break;
	    }
	    if (regular_match_count>=nb_shape_ev || reverse_match_count>=nb_shape_ev) success=true;
	
	}
	if (success) {								// si une série couvre toute la suite d'événements signés, elle est validée.
            printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
            printf("THE SHAPE NAMED \" %s \" HAS BEEN FOUND !\n", name);
            printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
        }
    }

}


// les deux événements en paramètre sont-ils compatibles?
_Bool event_match(double* A, double* B, int z) {
    
    if ( ((int)TO_DEG(A[ANGLE]-B[ANGLE])) > 30 ) {	// pour le line following, nous n'utiliserons que le temps et...
	return false;

    } else if (false/*A[BLOCK] != B[BLOCK]*/) {
	return false;
    } else if (false) {
	return false;
    } else if (RATIO(A[DIST],B[DIST])>1.3f) {		// la distance.
	return false;
    } else if (false) {
	return false;
    } else if (false) {
	return false;
    } else {
	return true;
    }
}









