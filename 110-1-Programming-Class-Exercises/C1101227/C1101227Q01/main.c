#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>

char maze[13][13];
enum direction {
    up,
    down,
    right,
    left
};
struct pointer {
    int x;
    int y;
    enum direction dir;
};
int FrontIsWall(struct pointer p) {
    switch (p.dir) {
    case up:
        return (maze[p.x - 1][p.y] == '#');
    case down:
        return (maze[p.x + 1][p.y] == '#');
    case right:
        return (maze[p.x][p.y + 1] == '#');
    case left:
        return (maze[p.x][p.y - 1] == '#');
    }
}
int LeftIsWall(struct pointer p) {
    switch (p.dir) {
    case up:
        return (maze[p.x][p.y - 1] == '#');
    case down:
        return (maze[p.x][p.y + 1] == '#');
    case right:
        return (maze[p.x - 1][p.y] == '#');
    case left:
        return (maze[p.x + 1][p.y] == '#');
    }
}
void TurnLeft(struct pointer* p) {
    switch (p->dir) {
    case up:
        //p->y--;
        p->dir = left;
        break;
    case down:
        //p->y++;
        p->dir = right;
        break;
    case right:
        //p->x--;
        p->dir = up;
        break;
    case left:
        //p->x++;
        p->dir = down;
        break;
    }
}
void TurnRight(struct pointer* p) {
    switch (p->dir) {
    case up:
        //p->y++;
        p->dir = right;
        break;
    case down:
        //p->y--;
        p->dir = left;
        break;
    case right:
        //p->x++;
        p->dir = down;
        break;
    case left:
        //p->x--;
        p->dir = up;
        break;
    }
}
void MoveFront(struct pointer* p) {
    switch (p->dir) {
        case up:
            p->x--;
            break;
        case down:
            p->x++;
            break;
        case right:
            p->y++;
            break;
        case left:
            p->y--;
            break;
    }
}

int main()
{
    
    for (int i = 0; i < 12; i++) {
        gets(maze[i]);
    }

    struct pointer p = {
        .x = 0,
        .y = 0,
        .dir = right
    };    while (maze[p.x][p.y] != 'X') {
        p.x++;

    maze[p.x][p.y] = 'R';
    p.y++;
    while (p.y != 11 && p.y != 0) {
        if (maze[p.x][p.y] == 'X') maze[p.x][p.y] = 'R';
        if (!LeftIsWall(p)) {
            TurnLeft(&p);
        }
        if (!FrontIsWall(p)){
            MoveFront(&p);
        }
        else {
            TurnRight(&p);
        }
    }
    if (p.y == 11) maze[p.x][p.y] = 'R';
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    if (p.y == 0) printf("This maze has no solution\n");
    
    return 0;
}
/*

############
##XXXXX#XXX#
##X###X###X#
##X#XXXXXXX#
##X#######X#
#XX#X####XX#
XX##XXXXXX##
####X##X##X#
#X#X#XXX##X#
#X#X##X#XXX#
#XXX##XXX#XX
############



*/