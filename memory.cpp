#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char const *argv[]){
	unsigned t = 100000;
	for(unsigned i=0; i<t; i+=1000){
		cout << i << "\t" << 8*pow(i,2)/pow(1024,3) << "\t" << 8 << endl;
	}
	return 0;
}