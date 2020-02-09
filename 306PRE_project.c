#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*** readCSV(FILE* csvFile);
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
		csvContents = readcvs(csvFile);	//READ CSV FILE BEFORE ANYTHING
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



char*** readCSV(FILE* csvFile){
	// allocate 3-d array
	char*** csvInfo = malloc(sizeof(***csvInfo));
	int rows = 0;
	char line[1024];
	int pos = 0; // marks position of char array for values
	while (fgets(line, 1024, csvFile) != NULL){
		// allocate space for columns
		csvInfo[rows] = malloc(sizeof(**csvInfo));
		int cols = 0;
		// allocate space for values
		csvInfo[rows][cols] = malloc(sizeof(*csvInfo));
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
				if (line[i] == ',' || line[i] == '\0'){
					csvInfo[rows][cols][pos] = '\0';
					pos = 0;
					cols +=1;
					csvInfo[rows][cols] = malloc(sizeof(*csvInfo));
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