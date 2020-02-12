#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

char*** ReadCSV(FILE* csvFile);
void f();
void r();
void h();
int MaxValue(int index, char*** csvInfo);
void MinValue(char field[]);
void mean(char field[]);
int records(int index, char feild[], char*** csvInfo);
int GetIndex(char field[], char*** csvInfo);

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
		csvContents = ReadCSV(csvFile);	//READ CSV FILE BEFORE ANYTHING
	}
		
	int isHeader = 0; // for -h, 0 == false, 1 == true
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
			if (isHeader == 1){
				if (MaxValue(GetIndex(argv[x], csvContents), csvContents) == 1){
					return 1;
				}
			}else{
				printf("Must use -h to use -max\n");
			}
		}
		
		else if (strncmp("-min", argv[x], 4) == 0){
			x++;
			MinValue(argv[x]);
		}
		
		else if (strncmp("-mean", argv[x], 5) == 0){
			x++;
			mean(argv[x]);
		}
	
		else if (strncmp("-records", argv[x], 8) == 0){
			x++;
			if (isHeader == 1){
			  if (records(GetIndex(argv[x], csvContents), argv[x+1], csvContents) == 1){
					return 1;
				}
			}else{
				printf("Must use -h to use -records\n");
			}
		}
	}

	exit(0);
}



char*** ReadCSV(FILE* csvFile){
	// allocate 3-d array
	char*** csvInfo = malloc(4096);
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
		for (int i = 0; i <= strlen(line); i++){
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
					csvInfo[rows][cols] = malloc(4096);
				}else if(line[i] == '\0'){
					csvInfo[rows][cols][pos] = '\0';
					pos = 0;
				}else{
					csvInfo[rows][cols][pos] = line[i];
					pos +=1;
				}
			}
		}
		
		rows+=1;
	}

	return csvInfo;
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

int MaxValue(int index, char*** csvInfo){
		// Display the maximum value in the indicated field of the data records
		if (index == -1){
			return 1;
		}

		double max = DBL_MIN;
		for (int i = 1; i < sizeof(csvInfo); i++){
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

void MinValue(char field[]){
		///TODO: Display the minimum value in the indicated field of the data records
}

void mean(char field[]){
		///TODO: Display the arithmetic mean (average) value in the indicated field of the data records
}

int records(int index, char field[], char*** csvInfo){
		///TODO: Display the records from file containing value in the the indicated field
                ///Iterate through value until match
                ///Display that row - iterate through and display all fields
                for (int i = 0; i < sizeof(csvInfo); i++){
		        if(index == csvInfo[0][i]){
		                 for (int j = 1; j < sizeof(csvInfo); j++){
		                         if(field == csvInfo[j][i]){
					        for(int k = 0; k < sizeof(csvInfo); k++){
			                               printf("%s, ", csvInfo[j][k]);
		                         	}
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
		for (int i = 0; i < sizeof(csvInfo); i++){
			if (strcmp(field, csvInfo[0][i]) == 0){
				return i;
			}
		}
	}

	printf("Invalid field name: %s", field);
	return -1;
}
