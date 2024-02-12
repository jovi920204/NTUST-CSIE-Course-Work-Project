#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char* data =
		"Caspar Murray,50,25,100,80\n"
		"Rory Gordon,50,50,100,60\n"
		"Winnie Randolph,50,100,50,20\n";

	int index = 0;
	char name[30] = {0};
	while (index < strlen(data)) {
		int i = 0;
		while (data[index] != ',') {
			name[i] = data[index];
			index++;
			i++;
		}
		printf("%d QQ\n",index);
		break;
	}
	name[strlen(name)] = '\0';
	printf("%s\n", name);

	return 0;
}