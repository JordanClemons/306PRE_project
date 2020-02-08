#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readCSV(FILE* csvFile);
void f();
void r();
void h();
void max(char field[]);
void min(char field[]);
void mean(char field[]);
void records(char field[]);

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
		return 1;
	}else{
		readcvs(csvFile);	//READ CSV FILE BEFORE ANYTHING
	}
		
	for(int x = 1; x < argc; x++){
		if (strncmp("-f", argv[x], 2) == 0){
			f();
		}
		else if (strncmp("-r", argv[x], 2) == 0){
			r();
		}
		
		else if (strncmp("-h", argv[x], 2) == 0){
			h();
		}
		
		else if (strncmp("-max", argv[x], 4) == 0){
			x++;
			max(argv[x]);
		}
		
		else if (strncmp("-min", argv[x], 4) == 0){
			x++;
			min(argv[x]);
		}
		
		else if (strncmp("-mean", argv[x], 5) == 0){
			x++;
			mean(argv[x]);
		}
	
		else if (strncmp("-records", argv[x], 8) == 0){
			x++;
			records(argv[x]);
		}
	}

	exit(0);
}



void readCSV(FILE* csvFile){
	char*** csvInfo = malloc(sizeof(***csvInfo));
	int rows = 0;
	char* line = malloc(sizeof(*line));
	fscanf(csvFile, "%s", line);
	while (line[0] != '\0'){
		csvInfo[rows] = malloc(sizeof(**csvInfo));
		int cols = 0;
		csvInfo[rows][cols] = malloc(sizeof(*csvInfo));
		int pos = 0;
		int isString = 1;
		for (int i = 0; i <= strlen(line); i++){
			if (line[i] == '"'){
				// TODO: ignore ',' in csv reading
			}

			if (line[i] == ',' || line[i] == '\0'){
				csvInfo[rows][cols][pos] = '\0';
				printf("%s\n", csvInfo[rows][cols]);
				pos = 0;
				cols +=1;
				csvInfo[rows][cols] = malloc(sizeof(*csvInfo));
			}else{
				csvInfo[rows][cols][pos] = line[i];
				pos +=1;
			}
		}

		rows+=1;
		fscanf(csvFile, "%s", line);
	}

	printf("%s\n", csvInfo[1][2]);
}

void f(){
		///TODO: Display the number of fields in the first record of file
                ///This will be number of columns
                ///Should be able to use sizeof(readcvs) if returns the matrix
}

void r(){
		///TODO: Display the number of data records in file
                ///This will be reading first row
                ///Should be able to use sizeof(readcvs[0])
}

void h(){
		///TODO: Treat the first record of file as a header record rather than a data record
}

void max(char field[]){
		///TODO: Display the maximum value in the indicated field of the data records
}

void min(char field[]){
		///TODO: Display the minimum value in the indicated field of the data records
}

void mean(char field[]){
		///TODO: Display the arithmetic mean (average) value in the indicated field of the data records
}

void records(char field[]){
		///TODO: Display the records from file containing value in the the indicated field
                ///Iterate through value until match
                ///Display that row - iterate through and display all fields
}