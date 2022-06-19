// Large number factorization - given an uint64_t, find all its factors and write it in the form:
//		2^a * 3^b * 5^c ...

// verify with https://www.dcode.fr/prime-factors-decomposition

// gcc -O3 -std=c99 -Wall -pedantic main.c ; ./a.out ;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <stdlib.h>
#include <chrono>

#include <iostream>

typedef unsigned long long int ulli;

// Prototype functions
static ulli modularPow(ulli a, ulli b, const ulli mod);
static int isPrime(ulli inputNumber);
ulli newFactor(const ulli inputNumber);
ulli* factor(ulli inputNumber, ulli* array, bool prime);