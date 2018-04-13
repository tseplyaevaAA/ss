
#pragma once 

#include <vector>
#include "Header.h"

void shellsort(double*a, int n){
	vector<int> seq;
	int k = 0;
	int i = 0;
	int lvl = 0;

	while (k == 0){
		int p = 0;
		int q = 0;
		int powq = 1;
		for (p = lvl; p >= 0; p--){
			i = pow(2, p)*powq;
			powq *= 3;
			if (i <= (n / 2)){ seq.push_back(i); }
			else{
				k++;
				break;
			}
		}
		lvl++;
	}
	int m = seq.size();
	reverse(seq.begin(), seq.end());

	double x;
	int gap;
	int j;
	for (k = 0; k < m; k++) { // seq
		gap = seq[k];
		for (int i = gap; i < n; ++i) {
			x = a[i];
			for (j = i - gap; (x < a[j]) && (j >= 0); j = j - gap)
				a[j + gap] = a[j];
			a[j + gap] = x;
			//show(a,n);
		}
	}

}