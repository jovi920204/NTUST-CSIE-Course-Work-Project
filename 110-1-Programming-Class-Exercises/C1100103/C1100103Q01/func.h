#pragma once
#include <string.h>
#include <stdlib.h>
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

    // Pointer to next student
    // Parameter: next (pointer)
    struct student* next;
};

/// <summary>
/// Convert the given 2 arrays into a linked list using 'student' structure.
/// </summary>
/// <param name="names">The name list.</param>
/// <param name="scores">The score list</param>
/// <returns>The first node of the created linked list.</returns>
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

// 雙指標是pointer to pointer意思是用指標去紀錄指標的位址
// 感覺就是真正的值外面包了兩層的指標
// 最外面那層就是雙指標