#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <random>
#include <locale.h>

int summ(int len) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    clock_t start, end; // объ€вл€ем переменные дл€ определени€ времени выполнени€

    int i = 0, j = 0, r;
    int a[200][200], b[200][200], c[200][200], elem_c;

    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    while (i < len)
    {
        while (j < len)
        {
            a[i][j] = rand() % 100 + 1; // заполн€ем массив случайными числами
            j++;
        }
        i++;
    }
    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    i = 0; j = 0;
    while (i < 200)
    {
        while (j < len)
        {
            b[i][j] = rand() % 100 + 1; // заполн€ем массив случайными числами
            j++;
        }
        i++;
    }
    start = clock();
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len; j++)
        {
            elem_c = 0;
            for (r = 0; r < len; r++)
            {
                elem_c = elem_c + a[i][r] * b[r][j];
                c[i][j] = elem_c;
            }
        }
    }

    end = clock();
    double answer = difftime(end, start);
    printf("начальное врем€: %d\nконечное врем€: %d\nразница (в секундах): %f\n\n", start, end, answer / CLOCKS_PER_SEC);
    return 0;
}

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
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int sizes[7] = { 100, 250, 500, 1000, 2500, 5000, 10000 };
    int mass[5] = { 10, 20, 40, 100, 200 };

    int* mas = (int*)malloc(sizes[6] * sizeof(int));

    clock_t start, end;

    printf("_______задание 1_______\n");
    for (int i = 0; i < 5; i++) {
        summ(mass[i]);
    }
    printf("_______задание 2_______\n");
    for (int i = 0; i < 7; i++){
        randitems(mas, sizes[i]);
        start = clock();
        shell(mas,sizes[i]);
        end = clock();
        printf("—ортировка Ўеллом\nначальное врем€: %d\nконечное врем€: %d\n¬рем€: %f\nЁлементов:%d\n",start, end, difftime(end, start) /CLOCKS_PER_SEC,sizes[i]);


        randitems(mas, sizes[i]);
        start = clock();
        qs(mas,0,sizes[i]-1);
        end = clock();
        printf("Ѕыстра€ сортировка\nначальное врем€: %d\nконечное врем€: %d\n¬рем€: %f\nЁлементов:%d\n\n", start, end,difftime(end, start) / CLOCKS_PER_SEC, sizes[i]);

    }

    return 0;
}