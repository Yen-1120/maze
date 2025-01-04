#ifndef MAZE_H
#define MAZE_H

const int WIDTH = 12;
const int HEIGHT = 12;

// 第一關迷宮
const char* maze1[HEIGHT][WIDTH] = {
    {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
    {"牆", "我", "　", "　", "牆", "　", "　", "　", "　", "　", "　", "牆"},
    {"牆", "牆", "牆", "　", "牆", "　", "牆", "牆", "牆", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "　", "　", "牆", "　", "　", "牆", "　", "牆"},
    {"牆", "　", "牆", "牆", "牆", "　", "牆", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "牆", "　", "　", "　", "　", "牆", "　", "牆"},
    {"牆", "牆", "牆", "　", "牆", "牆", "牆", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "　", "　", "　", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "牆", "牆", "牆", "牆", "　", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "　", "牆", "　", "　", "　", "牆", "門", "牆"},
    {"牆", "牆", "牆", "牆", "　", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
    {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
};

// 第二關迷宮
const char* maze2[HEIGHT][WIDTH] = {
    {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
    {"牆", "我", "　", "　", "牆", "　", "　", "　", "　", "　", "　", "牆"},
    {"牆", "牆", "牆", "　", "牆", "　", "牆", "牆", "牆", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "　", "　", "牆", "　", "　", "牆", "　", "牆"},
    {"牆", "　", "牆", "牆", "牆", "　", "牆", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "牆", "　", "　", "　", "　", "牆", "　", "牆"},
    {"牆", "牆", "牆", "　", "牆", "牆", "牆", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "　", "　", "　", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "牆", "牆", "牆", "牆", "　", "牆", "　", "牆", "　", "牆"},
    {"牆", "　", "　", "　", "　", "牆", "　", "　", "　", "牆", "門", "牆"},
    {"牆", "牆", "牆", "牆", "　", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
    {"牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆", "牆"},
};

int A[2][2] = {
    {0, 1},
    {1, 0}
};

#endif // MAZE_H