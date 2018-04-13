#include <omp.h>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;

void show(double* a, int st, int n){
	for (int i = st; i < n; i++){
		cout << a[i] << "  ";
	}
	cout << endl;
}

void shellsort(double*a, int st, int n){

	int size_b = n - st;
	double* b = new double[size_b];

	for (int i = 0; i < size_b; i++){
		b[i] = a[i + st];
	}

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

	//show(b, 0, size_b);
	
	double x;
	int gap;
	int j;
	for (k = 0; k < m; k++) { // seq
		gap = seq[k];
		for (int i = gap; i < size_b; ++i) {
			x = b[i];
			for (j = i - gap; (x < b[j]) && (j >= 0); j = j - gap)
				b[j + gap] = b[j];
			b[j + gap] = x;
			
		}
	}

	for (int i = 0; i < size_b; i++){
		 a[i + st]=b[i];
	}

	//show(b, 0, size_b);

}

double* merge(double* left, int size_l, double* right, int size_r)
 {
	 int size_res = size_l + size_r;
	 double* result = new double[size_res];
	 int k = 0;
	 int left_it = 0, right_it = 0;
	
	 while (left_it < size_l && right_it < size_r)
		 {
		if (left[left_it] < right[right_it])
			 {
			result[k] = left[left_it];
			k++;
			left_it++;
			}
		else
			 {
				 result[k] = right[right_it];
				 k++;
			right_it++;
			}
		}
	
	 while (left_it < size_l)
		 {
			 result[k] = left[left_it];
			 k++;
		left_it++;
		}
	
	 while (right_it < size_r)
		 {
			 result[k] = right[right_it];
			 k++;
			 right_it++;
		}

		return result;
	}


void OmpShellSort(double* a, int n, int thread_count) {

	omp_set_num_threads(thread_count);
	int parts = n / thread_count;
	int left, rigth;

#pragma omp parallel for schedule(static) shared(parts, n) \
  private(left, rigth)

	//sorting
	for (int i = 0; i < thread_count ; ++i) {

		left = i * parts;
		if (i == (thread_count - 1)) {
			rigth = n;
		}
		else{

			rigth = left + parts;
		}

		cout << left << rigth << endl;
		shellsort(a, left, rigth);
		show(a, left, rigth);
		cout << endl;
	}

//	double* one;
//	double* two;
//	left = 0;
//	rigth = 0;
//	int left1, rigth1;
//
//#pragma omp parallel for schedule(static) shared(parts, n) \
//  private(left, rigth, left1, rigth1)
//	left1 = 0;
//	rigth1 = 0;
//
//
//
//	for (int i = 0; i < thread_count; ++i) {
//
//		left = i * parts;
//
//		if (i == (thread_count - 1)) {
//			rigth = n;
//		}
//		else{
//			rigth = left + parts;
//			left1 = left + parts + 1;
//			rigth1 = left + parts * 2 + 1;
//		}
//		cout << endl;
//		cout << "  " << left << "  " << rigth<<"  "  << left1<< "  " << rigth1;
//		cout << endl;
//		
//	}
//	

}


int main(){
	int n = 12;
	double* a;
	a = new double[n];

	//for (int i = 0; i < n; i++){
	//	a[i] = (double) (rand() % 100) /10;
		//a[i] = (double)(rand() % 100);
		//}

	for (int i = 0; i < n; i++){
		a[i] = n- i;
	}

	 show(a, 0, n);

	 //shellsort(a, 3, 8 );

	 //show(a, 0, n);

	OmpShellSort(a, n, 4);

//	show(a, 0, n);

	_getch();
	return 0;
}