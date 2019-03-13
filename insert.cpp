#include <iostream>
#include <stdio.h>
#include "src/sws.h"

FILE *data;

using namespace std;

void insert_sort(int *a, int t){
	int j;
	for(int i=0; i<t; i++){
		j = i;
		while(j>0 and (*(a+j)<*(a+j-1))){
			swap_((a+j), (a+j-1));
			j--;
		}
	}
}



int main(int argc, char const *argv[]){

	data = fopen("../datos/ada_insert.dat","w");	//open archive, "w"[write] if exist! delete and create .dat, if not! create .dat
	int t = 25, s = 1000;		//t = number of test | s = jump
	for(int r=s, i=0; i<t; i++, r+=s){
		fprintf(data, "%d\t", r);
		int *a = new int[r];	int *b = new int[r];	int *c = new int[r];	//create pointer to integer
		rand_(a,r);			//put random number
		min_to_max(b,r);	//put in order, min -> max
		max_to_min(c,r);	//put in order, max -> min

		//dat_t| write time of execution in "ada_insert.dat"
		//code in "src/sws.h"
		dat_t(data,a,r,insert_sort);
		dat_t(data,b,r,insert_sort);
		dat_t(data,c,r,insert_sort);
		delete a; delete b; delete c;
		fprintf(data, "%s", "\n");
	}
	fclose(data);
	return 0;
}