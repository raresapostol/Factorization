#include "../include/factorization.h"


int main(void) {
	ulli* factorsList = (ulli*)calloc(100, sizeof(ulli)), inputNumber = 0; // allocate memory
	int n_bits = 63;
	bool isPrimeNo = true;
	size_t k = 0;
	unsigned sr = (size_t)factorsList; 
	srand(sr);

	// Create random 64 bit number
	while (k < sizeof(ulli))
		((char*)&inputNumber)[k++] = rand();

	//inputNumber = 1259837672346; // test purpose - delete later
	printf("\n\n%2d bit number: %22llu = \n", n_bits+1, inputNumber);

	// true - prime numbers; false - all numbers
    auto start = std::chrono::high_resolution_clock::now();
	factor(inputNumber, factorsList, isPrime); // fill the "factors" array with the prime factors
    auto stop = std::chrono::high_resolution_clock::now();    

	printf("Prime factorization done in %llu us\n", std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count());

	for (int j = 0; factorsList[j]; ++j) { // iterate over the factors
		if (factorsList[j] != inputNumber && factorsList[j] != 0) {
	//		printf("%llu\n", factorsList[j]);
			if (isPrimeNo)
				assert(inputNumber % factorsList[j] == 0);
		}
	}
	
	for (int i = 0; factorsList[i]; i++) { // print factors in the desired form
			printf("%llu^%c * ", factorsList[i], 0x61 + i);
	}

	free(factorsList); // free memory.
}
