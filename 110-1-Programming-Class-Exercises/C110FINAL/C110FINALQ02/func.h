#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// A structure represents the value of each point
struct point
{
    // Axis values of x and y
    float x, y;

    // Pointer to next point
    struct point* next;
};

/// <summary>
/// Convert the given point list into a linked list using 'point' structure.
/// </summary>
/// <param name="size">The size of list.</param>
/// <param name="data">The point list.</param>
/// <returns>The first node of the created linked list.</returns>
struct point* convert(int size, float data[][2])
{
	struct point* first = malloc(sizeof(struct point));
	first = NULL;
	for (int i=0;i<size;i++){
		struct point* newNode = malloc(sizeof(struct point));
		newNode->x = data[i][0];
		newNode->y = data[i][1];
		newNode->next = first;
		first = newNode;
		i++;
	}
	return first;
}

/// <summary>
/// Sort points in ascending order prioritizing on the x value.
/// </summary>
/// <param name="size">The first node of the linked list.</param>
/// <returns>The first node of the sorted linked list.</returns>
struct point* sort(struct point* list)
{
	int size = 0;
	while (list) {
		size++;
		list = list->next;
	}
	float data[][2] = { 0 };
	int i = 0;
	while (list) {
		data[i][0] = list->x;
		data[i][1] = list->y;
		i++;
		list = list->next;
	}
	for (int i = 0; i < size-1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			float temp = 0;
			if (data[j][0] > data[j + 1][0]) {
				temp = data[j+1][0];
				data[j + 1][0] = data[j][0];
				data[j][0] = temp;
			}
			else if (data[j][0] == data[j + 1][0]) {
				if (data[j][1] > data[j + 1][1]) {
					temp = data[j + 1][1];
					data[j + 1][1] = data[j][1];
					data[j][1] = temp;
				}
			}
		}
	}
	struct point* first = malloc(sizeof(struct point));
	first = NULL;
	i = 0;
	while (i < size) {
		struct point* newNode = malloc(sizeof(struct point));
		newNode->x = data[i][0];
		newNode->y = data[i][1];
		newNode->next = first;
		first = newNode;
		i++;
	}
	return first;
}


/*
struct student* convert(char names[][50], int scores[][2])
{
    struct student* first = malloc(sizeof(struct student));
    struct student** curr = malloc(sizeof(struct student*));
    curr = &first;
    int i = 0;
    while(strlen(names[i]) != 0){
        struct student* newNode = malloc(sizeof(struct student));
        strcpy(newNode->name, names[i]);
        newNode->english = scores[i][0];
        newNode->math = scores[i][1];
        newNode->next = NULL;
        *curr = newNode;
        curr = &(newNode->next);
        i++;
    }
    
    return first;
}
*/