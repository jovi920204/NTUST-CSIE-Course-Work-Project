#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <stdlib.h>
#define TOP strlen(stack)-1
int main()
{
    char infix[55] = { 0 };
    char stack[55] = { 0 }, post[55] = { 0 };
    gets(infix);
    int scan = 0;   //���Vinfix
    int ptr = 0;    //���Vstack
    int now = 0;    //���Vpost
    int top = 0;
    while (scan <= strlen(infix) - 1) {
        //printf("LOOP\n");
        if (infix[scan] == ')') { // ������stack�����Ȧs�Jpost����J��'('
            while (stack[TOP] != '(') {
                post[now++] = stack[TOP];
                stack[TOP] = 0;
                //printf("ERROR\n");
            }
            stack[TOP] = 0; // �M��'('
            scan++;
        }
        else if (infix[scan] == '*') { // �J��*
            if (stack[TOP] == '/') {
                while (stack[TOP] != '/') {
                    post[now++] = stack[TOP];
                    stack[TOP] = 0;
                }
            }
            stack[TOP + 1] = infix[scan++];

        }
        else if (infix[scan] == '/') { // �J��/
            while (stack[TOP] == '/' || stack[TOP] == '*') {
                post[now++] = stack[TOP];
                stack[TOP] = 0;
            }
            stack[TOP + 1] = infix[scan++];
        }
        else if (infix[scan] == '+') {
            while (stack[TOP] == '*' || stack[TOP] == '/' || stack[TOP] == '-' || stack[TOP] == '+') {
                post[now++] = stack[TOP];
                stack[TOP] = 0;
            }
            stack[TOP + 1] = infix[scan++];
            
        }
        else if (infix[scan] == '-') {
            while (stack[TOP] == '*' || stack[TOP] == '/' || stack[TOP] == '+') {
                post[now++] = stack[TOP];
                stack[TOP] = 0;
            }
            stack[TOP + 1] = infix[scan++];
            
        }
        else if (infix[scan] == '(') {
            stack[TOP + 1] = infix[scan++];
        }
        else { // �Ʀr
            post[now++] = infix[scan++];
        }
        //puts(stack);
    }

    while (TOP+1 != 0) {
        //printf("QQ\n");
        post[now++] = stack[TOP];
        stack[TOP] = 0;
    }
    //puts(stack);
    puts(post);
    return 0;
}

/// 1+2*3/4-5
/// (A+B*(C-D))/E
/// A+B*C/D-E
/// ((1+2)*3)/4+5
/// 12+3*4/5+
///
/// (1+2+3*4)/5
/// 
/// 4+2*(9+9)+7/2