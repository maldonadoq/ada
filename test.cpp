#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;
 
int lps(string seq, int i, int j){
	if (i==j)	
		return 1;
	
	if(seq[i]==seq[j] && i+1==j)	
		return 2;

	if(seq[i]==seq[j])	
		return lps(seq,i+1,j-1)+2;

	return max(lps(seq,i,j-1),lps(seq,i+1,j));
}

int main(int argc, char const *argv[]){
	string seq = "percy";
	int n = seq.size();
	printf ("The length of the LPS is %d\n", lps(seq, 0, n-1));
	return 0;
}