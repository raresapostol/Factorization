#include <gtest/gtest.h>
#include <../../src/factorization.h>

typedef unsigned long long int ulli;

ulli* factorsList;

TEST(FactorizationTest, isPrimeFactor) {
	ASSERT_EQ(1259837672346, factorsList, true);
}

int main(int argc, char** argv) {

	factorsList = (ulli*)calloc(100, sizeof(ulli)); // allocate memory


	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}