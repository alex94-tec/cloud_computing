

#include <iostream> 
#include <omp.h>
#include <random>
#include <chrono>


int main()
{
	const int size = 1000;
	const int sub_size = 100;
	const int show = 10;


	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 eng(seed);
	std::uniform_int_distribution<int> dist(1, 1000);
	int random_number = dist(eng);

	std::cout << "Inicializa arreglos a y b con valores aleatorios. \n";
	float a[size], b[size], c[size];
	int i;
	for (i = 0; i < size; i++)
	{
		a[i] = dist(eng);
		b[i] = dist(eng);

	}
	int count = 0;


	#pragma omp parallel for \
	shared (a, b, c, sub_size) private(i) \
	schedule(static, sub_size)
	for (i = 0; i < size; i++) {
		c[i] = a[i] + b[i];

		if (count == 50) {
			count = 0;
			printf("Sumando desde el hilo %d\n", omp_get_thread_num());
		}
		count++;
	}

	printf("Primeros 10 valores de los arreglos a, b y c:");
	for (int i = 0; i < 10; ++i) {
		std::cout << "a[" << i << "] = " << a[i]
			<< ", b[" << i << "] = " << b[i]
			<< ", sum[" << i << "] = " << c[i] << std::endl;
	}
}

