#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// The string length of name
#define LEN_NAME 50

// A structure represents the information of each student
struct student
{
    // The name string
    // Parameter: name (string)
    char name[LEN_NAME];

    // The score of English
    // Parameter: english (integer)
	int english;
    // The score of Math
    // Parameter: math (integer)
	int math;
    // The score of History
    // Parameter: history (integer)
	int history;
    // The score of Physics
    // Parameter: physics (integer)
	int physics;
    // Pointer to next student
    // Parameter: next (struct pointer)
	struct student* next;
};

/// <summary>
/// Convert the given CSV format string into a linked list using 'student' structure.
/// </summary>
/// <param name="data">The data string.</param>
/// <returns>The first node of the created linked list.</returns>

///char* data =
///"Caspar Murray,50,25,100,80\n"
///"Rory Gordon,50,50,100,60\n"
///"Winnie Randolph,50,100,50,20\n";
struct student* convert(char* data)
{
	struct student* first = malloc(sizeof(struct student));
	int index = 0;
	while (index < strlen(data)) {
		struct student* newNode = malloc(sizeof(struct student));
		if (index == strlen(data) - 1) break;
		if (data[index] == '\n' && index != strlen(data)-1) index++;
		
		char name[50] = { 0 }, eng[3] = { 0 }, mat[3] = { 0 }, his[3] = { 0 }, phy[3] = {0};
		int i = 0;
		while (data[index] != ',') {
			newNode->name[i] = data[index];
			i++;
			index++;
		}
		newNode->name[strlen(name)] = '\0';
		index++;
		i = 0;
		while (data[index] != ',') {
			eng[i] = data[index];
			i++;
			index++;
		}
		eng[i] = '\0';
		int temp = 0;
		int base = 1;
		for (int i = strlen(eng) - 1; i >= 0; i--) {
			temp += base * eng[i];
			base *= 10;
		}
		newNode->english = temp;
		index++;
		i = 0;
		while (data[index] != ',') {
			mat[i] = data[index];
			i++;
			index++;
		}
		mat[i] = '\0';
		temp = 0;
		 base = 1;
		for (int i = strlen(mat) - 1; i >= 0; i--) {
			temp += base * mat[i];
			base *= 10;
		}
		newNode->math = temp;
		index++;
		i = 0;
		while (data[index] != ',') {
			his[i] = data[index];
			i++;
			index++;
		}
		his[i] = '\0';
		 temp = 0;
		 base = 1;
		for (int i = strlen(his) - 1; i >= 0; i--) {
			temp += base * his[i];
			base *= 10;
		}
		newNode->history = temp;
		index++;
		i = 0;
		while (data[index] != '\n') {
			phy[i] = data[index];
			index++;
			i++;
		}
		phy[i] = '\0';
		 temp = 0;
		 base = 1;
		for (int i = strlen(phy) - 1; i >= 0; i--) {
			temp += base * phy[i];
			base *= 10;
		}
		newNode->physics = temp;
		newNode->next = first;
		first = newNode;
		
	}
	return first;
}

/// <summary>
/// Calculate the total score of each student, and return the average of all total scores.
/// </summary>
/// <param name="node">The starter node of linked list.</param>
/// <returns>The average value.</returns>
float average(struct student* node)
{
	int size = 0;
	float total = 0;
	while (node) {
		total += node->english;
		total += node->math;
		total += node->history;
		total += node->physics;
		node = node->next;
	}
	return (total) / 4 / size;
}
