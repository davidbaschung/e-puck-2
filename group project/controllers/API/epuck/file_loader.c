
// CHARGEMENT DES FICHIERS CSV CONTENANT LES EVENEMENTS

#include "file_loader.h"

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

void scan_wheels() {
    discrete_capture();
    last_captures_average();
}
void discrete_capture() {
    
}
void last_captures_average() {

}

void scan_shapes() {

}
bool check_compatibility(double **event, double **averages_sample) {
	
	return 0;
}




void load_files() {
    printf("\nload_files()\n\n");
    char *folder_path = "./data/line/";
    DIR *d;
    struct dirent *directory;
    d = opendir(folder_path);
    
    shapes = (struct file_values*) malloc(sizeof(shapes)*sizeof(shapes[0]));
    
    /* open files and copy names */
    char file_names[255][255];
    int i=0, size=0;
    if (d) {
        while ((directory = readdir(d)) != NULL) {
            if ( strcmp(directory->d_name,".")!=0 && strcmp(directory->d_name,"..")!=0 && strcmp(directory->d_name,"")!=0 ) {
                strcpy(file_names[i],directory->d_name);;
                printf("file found : %s\n", file_names[i]);
                i++;
                size++;
            }
        }
    }
    closedir(d);
    number_of_shapes = size;
           
    /* store shape name and events from files */
    i=0;
    for(int i=0; i<size; i++ ) {
        char shape_name[255];// = file_names[i];
        strncpy(shape_name, file_names[i], strlen(file_names[i])-4);
	int name_len = strlen(file_names[i])-4;
        shape_name[name_len] = '\0';
	shapes[i].name = malloc(name_len*sizeof(char));
        strcpy(shapes[i].name, shape_name);
        
        /* store events */     
        printf("\n\nloading file : %s\n\n", file_names[i]);
        FILE *file_pointer;
        char file_name[255];
        sprintf(file_name,"%s%s",folder_path,file_names[i]);
        file_pointer = fopen(file_name, "r");        
        if (file_pointer==NULL) {
            char str2[255];
            sprintf(str2,"Error reading : %s%s",folder_path,file_name);
            perror(str2);
            exit(EXIT_FAILURE);
        }
        
        double temp_events[(int)pow(400,1)][6];  
        char ch, word[255];
        int line=0, column=0, columns_size=0;
        while ( (ch = fgetc(file_pointer)) != EOF ) {
            if (line == 0) {
                if (ch==',' || ch=='\n') columns_size++;
            } else {
                if ( ! (ch==',' || ch=='\n')) {
                    char current_ch[2];
                    current_ch[0] = ch;
                    current_ch[1] = '\0';
                    strcat(word,current_ch);
                } else {
                    temp_events[line-1][column] = strtod(word,NULL);
                    memset(word, 0, sizeof(word));
                    column++;
                }
            }
            if (ch=='\n') {
                column=0;            
                line++;
            }
        }
        fclose(file_pointer);

        
        /* store events to shape */
	shapes[i].events = (double **) malloc(line *sizeof(double *));
        for (int j=0; j<line-1 ; j++) {
	        shapes[i].events[j] = malloc(columns_size*sizeof(double));
	        for (int k=0; k<columns_size ; k++ ) {
		    shapes[i].events[j][k] = temp_events[j][k];
		    printf(" s:%f",shapes[i].events[j][k]);
	        }
		printf("\n");
        }
	shapes[i].events_size = line-1;
	printf("shape name : %s,  events size : %d\n", shapes[i].name, shapes[i].events_size);
    }

    printf("\nend of loadfiles()\n\n");
}




