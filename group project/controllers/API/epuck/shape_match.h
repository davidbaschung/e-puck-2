
// FICHIER PERMETTANT D'EFFECTUER LA RECONNAISSANCE DES FORMES

#define EVENTS_COUNT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define ANGLE 0														// colonnes des signatures
#define BLOCK 1
#define TIME 2
#define DIST 3
#define LEFT 4
#define RIGHT 5
#define TO_DEG(x) (x/M_PI*180)
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)
#define RATIO(a,b) ( (MIN(a,b)!=0) ? (((double)MAX(a,b)) / MIN(a,b)) : 9999 )

#define DISTANCE_IMPRECISION 1.48
#define ANGLE_IMPRECISION 1.22

double **events;													 // événements réels enregistrés

double compute_angle(int left_wheel, int right_wheel, double delta_time);						 // angle parcouru par le robot dans une courbe.
void record_event(double angle, double along_block, double time, double distance, double left_wheel, double righ_wheel); // enregistrement d'un événement (ligne/joint) par le robot.
void compare_events(char* name, double** shape_events, int nb_shape_ev, double** real_events, int nb_real_ev);		 // comparer tous les événements réels et signés
_Bool event_match(double* A, double* B, int z);										 // les deux événements en paramètre sont-ils compatibles?
