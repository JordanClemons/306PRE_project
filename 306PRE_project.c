#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

static int ROWCOUNT;
static int COLCOUNT;
static int HSTATE = 0;

char*** ReadCSV(FILE* csvFile);
void f(char*** csvInfo);
void r(char*** csvInfo);
void h();
int MaxValue(int index, char*** csvInfo);
int MinValue(int index, char*** csvInfo);
int mean(int index, char*** csvInfo);
int records(int index, char feild[], char*** csvInfo);
int GetIndex(char field[], char*** csvInfo);
void Deallocate(char*** csvInfo);

int main(int argc, char*argv[]){
	
	if(argc < 2){ 		//IF NOT ENOUGH ARGUEMENTS PROVIDED
		printf("No argument provided\n");
		exit(1);
	}
	
	FILE * csvFile;
	char*** csvContents;
	csvFile = fopen(argv[argc-1], "r");
	if (csvFile == NULL){
		printf("Error Opening File\n");
		exit(1);
	}else{
		csvContents = ReadCSV(csvFile);	//READ CSV FILE BEFORE ANYTHING
	}

	fclose(csvFile);
	int fcom = 0; int reccom = 0 ; int rcom = 0; int hcom = 0; int maxcom = 0; int mincom = 0; int meancom = 0;   //Used to prevent repeating commands. 0 if not used yet. 1 if used.
	for(int x = 1; x < argc; x++){
		if (strncmp("-f", argv[x], 2) == 0 && fcom == 0){
			f(csvContents);
			fcom = 1;
		}
        else if (strncmp("-records", argv[x], 8) == 0 && reccom == 0){
            x++;
                if (records(GetIndex(argv[x], csvContents), argv[x+1], csvContents) == 1){
                    Deallocate(csvContents);
                    exit(1);
                }
			x++;
            reccom = 1;
        }
		else if (strncmp("-r", argv[x], 2) == 0 && rcom == 0){
			r(csvContents);
			rcom = 1;
		}
		else if (strncmp("-h", argv[x], 2) == 0 && hcom == 0){
			h();
			hcom = 1;
		}
		else if (strncmp("-max", argv[x], 4) == 0 && maxcom == 0){
		    maxcom = 1;
			x++;
			if (MaxValue(GetIndex(argv[x], csvContents), csvContents) == 1){
				Deallocate(csvContents);
				exit(1);
			}
		}
		else if (strncmp("-min", argv[x], 4) == 0 && mincom == 0){
		    mincom = 1;
			x++;
			if (MinValue(GetIndex(argv[x], csvContents), csvContents) == 1){
				Deallocate(csvContents);
				exit(1);
			}
		}
		else if (strncmp("-mean", argv[x], 5) == 0 && meancom == 0){
		    meancom = 1;
			x++;
			if (mean(GetIndex(argv[x], csvContents), csvContents) == 1){
				Deallocate(csvContents);
				exit(1);
			}
		}
        else if (x != (argc -1)) {
            printf("Unrecognized command: %s\n", argv[x]);
			Deallocate(csvContents);
            exit(1);
        }
	}

	Deallocate(csvContents);
	exit(0);
}



char*** ReadCSV(FILE* csvFile){
	// allocate 3-d array
	char*** csvInfo = malloc(16384);
	int rows = 0;
	char line[4096];
	int pos = 0; // marks position of char array for values
	while (fgets(line, 4096, csvFile) != NULL){
		// allocate space for columns
		csvInfo[rows] = malloc(4096);
		int cols = 0;
		// allocate space for values
		csvInfo[rows][cols] = malloc(4096);
		// isString is 0 when no quotes and 1 when quotes are read
		int isString = 0;
		for (int i = 0; i < strlen(line); i++){
			if (line[i] == '\"'){
				isString = 1 - isString;
				i +=1;
			}

			if (isString == 1){
				csvInfo[rows][cols][pos] = line[i];
				pos +=1;
			}else if (isString == 0){
				if (line[i] == ','){
					csvInfo[rows][cols][pos] = '\0';
					pos = 0;
					cols +=1;
                    COLCOUNT = cols;
					csvInfo[rows][cols] = malloc(4096);
				}else if(line[i] == '\r'){
					csvInfo[rows][cols][pos] = '\0'; // removes \n from end of csv file
					pos = 0;
					i++;
				}else{
					csvInfo[rows][cols][pos] = line[i];
					pos +=1;
				}
                       
			}
		}
		
		rows+=1;
        ROWCOUNT+=1;
                
	}
        
	return csvInfo;
}

void f(char*** csvInfo){
    printf("%i\n", COLCOUNT + 1);
}

void r(char*** csvInfo){
    printf("%i\n", ROWCOUNT - HSTATE);
}

void h(){
	// Treat the first record of file as a header record rather than a data record
    HSTATE = 1;
}

int MaxValue(int index, char*** csvInfo){
	// Display the maximum value in the indicated field of the data records
	if (index == -1){
		return 1;
	}

	double max = DBL_MIN;
	for (int i = HSTATE; i < ROWCOUNT; i++){
		if (!isdigit(csvInfo[i][index][0])){
			printf("Invalid field for '-max' function\n");
			return 1;
		}

		double temp = atof(csvInfo[i][index]);
		if (temp > max){
			max = temp;
		}
	}

	printf("Max: %f\n", max);
	return 0;
}

int MinValue(int index, char*** csvInfo){
	// Display the minimum value in the indicated field of the data records
	if (index == -1){
		return 1;
	}

	double min = DBL_MAX;
	for (int i = HSTATE; i < ROWCOUNT; i++){
		if (!isdigit(csvInfo[i][index][0])){
			printf("Invalid field for '-min' function\n");
			return 1;
		}

		double temp = atof(csvInfo[i][index]);
		if (temp < min){
			min = temp;
		}
	}

	printf("Min: %f\n", min);
	return 0;
}

int mean(int index, char*** csvInfo){
	// Display the mean value in the indicated field of the data records
	if (index == -1){
		return 1;
	}

	double sum = 0;
	for (int i = HSTATE; i < ROWCOUNT; i++){
		if (!isdigit(csvInfo[i][index][0])){
			printf("Invalid field for '-mean' function\n");
			return 1;
		}

		double temp = atof(csvInfo[i][index]);
		sum = sum + temp;
	}
	double mean = sum / (ROWCOUNT - HSTATE);
	printf("Mean: %f\n", mean);
	return 0;
}

int records(int index, char field[], char*** csvInfo){
	//Display the records from file containing value in the the indicated field
    //Iterate through value until match
    //Display that row - iterate through and display all fields
	for (int j = HSTATE; j < ROWCOUNT; j++){
		if(strcmp(field, csvInfo[j][index]) == 0){
			for(int k = 0; k < COLCOUNT+1; k++){
				if(k <  COLCOUNT){
					printf("%s, ", csvInfo[j][k]);
				}else{
					printf("%s\n", csvInfo[j][k]);
				}
			}
		}
	}

	return 0;
}

// Gets index from field
int GetIndex(char field[], char*** csvInfo){
	if (isdigit(field[0])){
		return atoi(field);
	}else{
		for (int i = 0; i < COLCOUNT + 1; i++){
			if (strcmp(field, csvInfo[0][i]) == 0){
				return i;
			}
		}
	}

	printf("Invalid field name: %s\n", field);
	return -1;
}

void Deallocate(char*** csvInfo){
	for (int i = 0; i < ROWCOUNT; i++){
		for (int j = 0; j < COLCOUNT + 1; j++){
			free(csvInfo[i][j]);
		}

		free(csvInfo[i]);
	}

	free(csvInfo);
}

