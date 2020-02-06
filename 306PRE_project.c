# include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	
	if(argc < 2){ 		//IF NOT ENOUGH ARGUEMENTS PROVIDED
		printf("No argument provided");
		exit(1);
	}
		
	readcvs(argv[argc-1]);	//READ CSV FILE BEFORE ANYTHING
		
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
		
		exit(0);
		}
}



void readcvs(char field[]){
		///TODO: READ AND PARSE CSV FILE
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
}
