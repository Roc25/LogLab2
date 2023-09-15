#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <random>


void shell(int* items, int count) {

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) {//вызов функции: qs(items, 0, count-1);
    int i, j;
    int x, y;



    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}


void randitems(int* mas, int size) {
    for (int i = 0; i < size; i++){
        mas[i] = rand() % 100;
    }
}


int main() {
    srand(time(NULL));
    int sizes[7] = { 100, 250, 500, 1000, 2500, 5000, 10000 };

    int* mas = (int*)malloc(sizes[6] * sizeof(int));

    clock_t start, end;

    for (int i = 0; i < 7; i++){
        randitems(mas, sizes[i]);
        start = clock();
        shell(mas,sizes[i]);
        end = clock();
        printf("Сортировка Шеллом\nВремя: %d\nЭлементов:%d\n",(end-start)/CLOCKS_PER_SEC,sizes[i]);


        randitems(mas, sizes[i]);
        start = clock();
        qs(mas,0,sizes[i]-1);
        end = clock();
        printf("Быстрая сортировка\nВремя: %d\nЭлементов:%d\n\n", (end - start) / CLOCKS_PER_SEC, sizes[i]);

    }

    return 0;
}