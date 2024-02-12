#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "func.h"

#define LEN 100

int main()
{
    char msg[LEN] = "Hello world!";
	int shift = 7;
	for (shift = 1; shift < 10000000; shift *= 10) {
		// Apply Caesar Cipher

		caesar_cipher(msg, shift);

		// Print the shifted result
		print_result(msg);
	}
    

    return 0;
}
