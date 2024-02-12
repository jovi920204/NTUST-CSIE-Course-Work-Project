#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// <summary>
/// Apply Caesar cipher to the message.
/// </summary>
/// <param name="msg">The message string for encryption.</param>
/// <param name="shift">The shift amount.</param>
void caesar_cipher(char* msg, int shift)
{
	int n = shift%26;
	for (int i = 0; i < strlen(msg); i++) {
		if (msg[i] >= 'a' && msg[i] <= 'z') {
			if (msg[i] + n > 'z') {
				msg[i] = msg[i] + n - 'z' + 'a' - 1;
			}
			else if (msg[i] + n < 'a') {
				msg[i] = msg[i] + n + 'z' - 'a' + 1;
			}
			else msg[i] += n;
		}
		if (msg[i] >= 'A' && msg[i] <= 'Z') {
			if (msg[i] + n > 'Z') {
				msg[i] = msg[i] + n - 'Z' + 'A' - 1;
			}
			else if (msg[i] + n < 'A') {
				msg[i] = msg[i] + n + 'Z' - 'A' + 1;
			}
			else msg[i] += n;
		}
		else continue;
	}
}

/// <summary>
/// Print the result.
/// </summary>
/// <param name="msg">A message string.</param>
void print_result(char* msg)
{
	puts(msg);
}
/*#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

int main()
{
	char s[105];
	int n;
	gets(s);
	scanf("%d", &n);
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			if (s[i] + n > 'z') {
				s[i] = s[i] + n - 'z' + 'a' - 1;
			}
			else s[i] += n;
		}
		if (s[i] >= 'A' && s[i] <= 'Z') {
			if (s[i] + n > 'Z') {
				s[i] = s[i] + n - 'Z' + 'A' - 1;
			}
			else s[i] += n;
		}
		else continue;
	}
	for (int i = 0; i < strlen(s); i++) {
		printf("%c", s[i]);
	}
	return 0;
}*/