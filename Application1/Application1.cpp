#include <stdio.h>
#include <omp.h>
#include <iostream>

int main(){
	for (size_t i = 0; i < 20; i++)
	{
		long long n = 2000000000;
		int i;
		double pi, h, sum, x;
		double tim;

		h = 1.0 / (double)n;
		sum = 0.0;

		omp_set_num_threads(i);
		tim = omp_get_wtime();
#pragma omp parallel default (none) private (i,x) shared (n,h) reduction(+:sum)

		{
			int id = omp_get_thread_num();
			int numt = omp_get_num_threads();
			for (i = id + 1; i <= n; i = i + numt) {
				x = h * ((double)i - 0.5);
				sum += (4.0 / (1.0 + x * x));
			}
		}

		pi = h * sum;
		tim = omp_get_wtime() - tim;

		printf("pi is approximately %.16f\n", pi);
		printf("time of execution %.6f\n", tim);
	}

	//std::cin >> n;

	return 0;
}