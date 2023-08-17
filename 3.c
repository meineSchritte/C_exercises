#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

void draw_path(char map[MAX_WIDTH][MAX_HEIGHT], int x, int y) {
    map[y][x] = 'O';
}

void print_map(char map[MAX_WIDTH][MAX_HEIGHT], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return -1;
    }

    char map[MAX_HEIGHT][MAX_WIDTH];
    int width, height, x, y;

    FILE* fptr = fopen(argv[1], "r");
    if (!fptr) {
        return -1;
    }

    fscanf(fptr, "width = %d\nheight = %d\nx = %d\ny = %d\n", &width, &height, &x, &y);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = ' ';
        }
    }

    draw_path(map, x, y);

    char action;
    int steps = 0, angle = 0;

    fscanf(fptr, "%c", &action);
    if (action == 'L') {
        angle = 270;
    } else {
        fseek(fptr, -1, SEEK_CUR);
    }

    while (fscanf(fptr, "%c%d\n", &action, &steps) != EOF) {
        if (action == 'L') {
            angle = (angle - 90 + 360) % 360;
        } else if (action == 'R') {
            angle = (angle + 90) % 360;
        } else if (action == 'S') {
            switch (angle) {
                case 0:
                    for (int i = y; i >= y - steps; i--) map[i][x] = 'O';
                    y -= steps;
                    break;
                case 90:
                    for (int i = x; i <= x + steps; i++) map[y][i] = 'O';
                    x += steps;
                    break;
                case 180:
                    for (int i = y; i <= y + steps; i++) map[i][x] = 'O';
                    y += steps;
                    break;
                case 270:
                    for (int i = x; i >= x - steps; i--) map[y][i] = 'O';
                    x -= steps;
                    break;
            }
        }
        steps = 0;
    }

    fclose(fptr);

    print_map(map, width, height);

    return 0;
}

