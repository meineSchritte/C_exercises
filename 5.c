#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Lesen des Dateipfads als Kommandozeilenparameter
    if (argc != 2) {
        return 1;
    }
    char *file_path = argv[1];

    // Öffnen der Datei und Lesen der Liste von Ganzzahlen
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        return 1;
    }

    long number;
    long *numbers = NULL;
    int count = 0;
    int capacity = 0;

    while (fscanf(file, "%ld", &number) == 1) {
        if (count >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            numbers = realloc(numbers, capacity * sizeof(long));
            if (numbers == NULL) {
                return 1;
            }
        }
        numbers[count++] = number;
    }

    long minimum = numbers[0];
    long maximum = numbers[0];

    for (int i = 1; i < count; i++) {
        if (numbers[i] < minimum) {
            minimum = numbers[i];
        }
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }

    fclose(file);
    free(numbers);

    printf("count = %d\nmin = %ld\nmax = %ld\n", count, minimum, maximum);

    return 0;
}