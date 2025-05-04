#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_LOCATIONS 100
#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    int row;
    int col;
    char direction;
} Location;

int read_input(int *rows, int *cols, int *num_hydrants, int *num_drains,
               Location *hydrants, Location *drains,
               int pipe_grid[MAX_ROWS][MAX_COLS]) {
    char line[MAX_LINE_LENGTH];
    int i, j;

    // reads firs line
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
        fprintf(stderr, "error: invalid data\n");
        return 0;
    }
    if (sscanf(line, "%d %d %d %d", rows, cols, num_hydrants, num_drains) != 4 ||
        *rows <= 0 || *cols <= 0 || *num_hydrants < 0 || *num_drains < 0 ||
        *rows > MAX_ROWS || *cols > MAX_COLS) {
        fprintf(stderr, "error: invalid data\n");
        return 0;
    }

    // Read blank line
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL || line[0] != '\n') {
        fprintf(stderr, "error: invalid data\n");
        return 0;
    }

    // Read hydrant locations
    for (i = 0; i < *num_hydrants; i++) {
        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            fprintf(stderr, "error: invalid data\n");
            return 0;
        }
        if (sscanf(line, "%d %d %c", &hydrants[i].row, &hydrants[i].col, &hydrants[i].direction) != 3 ||
            hydrants[i].row <= 0 || hydrants[i].col <= 0 ||
            (hydrants[i].direction != 'N' && hydrants[i].direction != 'E' &&
             hydrants[i].direction != 'S' && hydrants[i].direction != 'W')) {
            fprintf(stderr, "error: invalid data\n");
            return 0;
        }
        hydrants[i].row--;    // adapts to 0
        hydrants[i].col--;
    }

    // read drain locations
    for (i = 0; i < *num_drains; i++) {
        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            fprintf(stderr, "error: invalid data\n");
            return 0;
        }
        if (sscanf(line, "%d %d %c", &drains[i].row, &drains[i].col, &drains[i].direction) != 3 ||
            drains[i].row <= 0 || drains[i].col <= 0 ||
            (drains[i].direction != 'N' && drains[i].direction != 'E' &&
             drains[i].direction != 'S' && drains[i].direction != 'W')) {
            fprintf(stderr, "error: invalid data\n");
            return 0;
        }
        drains[i].row--;
        drains[i].col--;
    }

    // Read blank line before the matrix
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL || line[0] != '\n') {
        fprintf(stderr, "error: invalid data\n");
        return 0;
    }

    // Read pipe matrix in hexadecimal
    for (i = 0; i < *rows; i++) {
        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            fprintf(stderr, "error: invalid data\n");
            return 0;
        }
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        char *token = strtok(line, " ");
        for (j = 0; j < *cols && token != NULL; j++) {
            if (strlen(token) != 1 || !isxdigit(token[0])) {
                fprintf(stderr, "error: invalid data\n");
                return 0;
            }
            sscanf(token, "%x", &pipe_grid[i][j]);
            token = strtok(NULL, " ");
        }
        if (j != *cols || token != NULL) {
            fprintf(stderr, "error: invalid data\n");
            return 0;
        }
    }

    return 1;
}

int main() {
    int rows, cols, num_hydrants, num_drains;
    Location hydrants[MAX_LOCATIONS];
    Location drains[MAX_LOCATIONS];
    int pipe_grid[MAX_ROWS][MAX_COLS];

    if (read_input(&rows, &cols, &num_hydrants, &num_drains, hydrants, drains, pipe_grid)) {
        printf("Rows: %d, Columns: %d, Hydrants: %d, Drains: %d\n", rows, cols, num_hydrants, num_drains);

        printf("Hydrant Locations:\n");
        for (int i = 0; i < num_hydrants; i++) {
            printf("[%d, %d] %c\n", hydrants[i].row + 1, hydrants[i].col + 1, hydrants[i].direction);
        }

        printf("Drain Locations:\n");
        for (int i = 0; i < num_drains; i++) {
            printf("[%d, %d] %c\n", drains[i].row + 1, drains[i].col + 1, drains[i].direction);
        }

        printf("Pipe Matrix (hexadecimal values):\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%X ", pipe_grid[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
