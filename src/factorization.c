#include "../include/factorization.h"


static ulli modularPow(ulli a, ulli b, const ulli mod) { 
	ulli res = 0;
	ulli tmp;
	b %= mod;

	while (a) {
		if (a & 1) {
			if (b >= mod - res) {
				res -= mod;
			}
			res += b;
		}
		a >>= 1;
		if ((tmp = b) >= mod - b) {
			tmp -= mod;
		}
		b += tmp;
	}

	return res % mod;
}

static int isPrime(ulli inputNumber) { // Pollard Rho algorithm
	ulli a = 0, b, c, d, e, f, g;
	int h, i;

	if ((inputNumber == 1) == (inputNumber & 1))
		return inputNumber == 2;

	b = c = inputNumber - 1;
	h = 0;
	while (!(b & 1)) {
		b >>= 1;
		++h;
	}

	g = 0;
	while (g < sizeof(ulli)) {
		((char*)&a)[g++] = rand();
	}

	d = e = 1 + a % c;
	f = inputNumber;
	while (d > 1 && f > 1) {
		while ((d %= f) && (f %= d));
	}

	d = f = 1;
	while (f <= b)
		f <<= 1;

	while(f >>= 1) {
		d = modularPow(d, d, inputNumber);
		f & b && (d = modularPow(e, d, inputNumber));
	}

	i = h;
	while (i-- && d != c) 
		d = modularPow(d, d, inputNumber);

	if (d != c)
		return 0;
	
	return 1;
}

ulli newFactor(const ulli inputNumber) {
	size_t a = -1, b = 2;
	ulli c;
	ulli d = 1 + rand();
	ulli e, f;

	c = d %= inputNumber;
	e = inputNumber;
	do {
		if (++a == b) { // handle timeout when (a == 1 << 20) or another power of two.
			d = c, b <<= 1, a = 0;
		}
		c = modularPow(c, c, inputNumber);

        ++c;

        c *= c != inputNumber;
        e = inputNumber;

        if (c > d) {
            f = c - d;
        } else {
            f = d - c;
        }

        while((f %= e) && (e %= f));

	} while ((f |= e) == 1);

	return f;
}

// fill the given array with prime factors of n, result will be zero terminated.
ulli* factor(ulli inputNumber, ulli* array, bool prime) {
	ulli a, b; size_t s;
	#pragma omp parallel 
	{
	while (inputNumber > 1) {
		if (!prime) { // Find all factors

			ulli i = 1;

			while (i * i <= inputNumber) {
				if (inputNumber % i == 0)
				{
					*array++ = inputNumber;

					if (inputNumber / i != i)
						*array++ = inputNumber / i;
				}
				i++;
			}
			inputNumber = 1;
		}
		else { // Find prime factors
			if (inputNumber < 4) {
				*array++ = inputNumber, inputNumber = 1;
			}
			else if (inputNumber & 1) {
				b = inputNumber >> 1;
				a = (b + inputNumber / b) >> 1;

				while (a < b) {
					b = a;
					a = (b + inputNumber / b) >> 1;
				}

				if (b * b == inputNumber) {
					s = factor(b, array, true) - array;
					memcpy(array + s, array, s * sizeof(ulli));
					array += s + s;
					inputNumber = 1;
				}
				else {
					if (isPrime(inputNumber)) // number of Miller-Rabin iterations.
						*array++ = inputNumber, inputNumber = 1;
					else {
						a = newFactor(inputNumber); // can't be called with a prime - seg fault
						#pragma omp critical
						array = factor(a, array, true);
						inputNumber /= a;
					}
				}
			}
			else {
				while (!(inputNumber & 1)) { // Based on LSB
					*array++ = 2;
					inputNumber >>= 1;
				}
			}
		}
	}
	}

	*array = 0;
	return array;
}