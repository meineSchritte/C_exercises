#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NAME 64

typedef struct lecture_hall {
    char name[MAX_LEN_NAME + 1];
    unsigned short size;
    unsigned short num_seats;
} lecture_hall_t;

void print_lecture_hall(lecture_hall_t *hall) {
    printf("%s, %u, %u\n", hall->name, hall->size, hall->num_seats);
}

int name_comparator(const void *a, const void *b) {
    const lecture_hall_t *hall1 = (const lecture_hall_t *)a;
    const lecture_hall_t *hall2 = (const lecture_hall_t *)b;
    return strncmp(hall1->name, hall2->name, MAX_LEN_NAME);
}

int size_comparator(const void *a, const void *b) {
    const lecture_hall_t *hall1 = (const lecture_hall_t *)a;
    const lecture_hall_t *hall2 = (const lecture_hall_t *)b;
    return hall1->size - hall2->size;
}

int num_seats_comparator(const void *a, const void *b) {
    const lecture_hall_t *hall1 = (const lecture_hall_t *)a;
    const lecture_hall_t *hall2 = (const lecture_hall_t *)b;
    return hall1->num_seats - hall2->num_seats;
}

int lecture_hall_comparator(const void *a, const void *b) {
    const lecture_hall_t *hall1 = (const lecture_hall_t *)a;
    const lecture_hall_t *hall2 = (const lecture_hall_t *)b;


    if (hall1->num_seats != hall2->num_seats)
        return hall1->num_seats - hall2->num_seats;

    return hall1->size - hall2->size;
}

void sort_lecture_halls(lecture_hall_t *lecture_halls, const size_t num_lecture_halls, int (*comparator)(const void *, const void *)) {
    qsort(lecture_halls, num_lecture_halls, sizeof(lecture_hall_t), comparator);
}

int main() {
    const size_t num_all_halls = 2;
    lecture_hall_t halls[num_all_halls];
    
    strcpy(halls[0].name, "Hall H");
    halls[0].size = 100;
    halls[0].num_seats = 110;

    strcpy(halls[1].name, "Hall D");
    halls[1].size = 300;
    halls[1].num_seats = 200;

    sort_lecture_halls(halls, num_all_halls, name_comparator);
    printf("Nach Namen sortiert:\n");
    for (size_t i = 0; i < num_all_halls; i++) {
        print_lecture_hall(&halls[i]);
    }

    sort_lecture_halls(halls, num_all_halls, size_comparator);
    printf("Nach Größe sortiert:\n");
    for (size_t i = 0; i < num_all_halls; i++) {
        print_lecture_hall(&halls[i]);
    }
    
    sort_lecture_halls(halls, num_all_halls, num_seats_comparator);
    printf("Nach Anzahl der Sitzplätze sortiert:\n");
    for (size_t i = 0; i < num_all_halls; i++) {
        print_lecture_hall(&halls[i]);
    }
    
    sort_lecture_halls(halls, num_all_halls, lecture_hall_comparator);
    printf("Nach Anzahl der Sitzplätze und Größe sortiert:\n");
    for (size_t i = 0; i < num_all_halls; i++) {
        print_lecture_hall(&halls[i]);
    }

    return 0;
}