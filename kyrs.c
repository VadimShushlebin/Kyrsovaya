#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max 100

typedef struct {
    char name[50];
    char ai[20];
    int proc;
    char monitor[100];
    float accuracy;
    double cost;
    char erp[100];
    char dif[20];
} rpa_sys;

rpa_sys input_data();
void output_data(rpa_sys system);
int show_menu();
void load_from_file(rpa_sys* systems, int* count);
void view_all_records(rpa_sys* systems, int count);
void search_by_range(rpa_sys* systems, int count);
void sort_data(rpa_sys* systems, int count);
void add_new_record(rpa_sys* systems, int* count);
void save_to_file(rpa_sys* systems, int count);
int compare(const void* a, const void* b);

int main() {
    system("chcp 1251");
    rpa_sys systems[max];
    int count = 0;
    int choice = 0;

    while (choice != 7) {
        choice = show_menu();

        switch (choice) {
        case 1:
            load_from_file(systems, &count);
            break;
        case 2:
            view_all_records(systems, count);
            break;
        case 3:
            search_by_range(systems, count);
            break;
        case 4:
            sort_data(systems, count);
            break;
        case 5:
            add_new_record(systems, &count);
            break;
        case 6:
            save_to_file(systems, count);
            break;
        case 7:
            printf("\nВыход из программы\n");
            break;
        default:
            printf("\nНеверный выбор\n");
        }

        if (choice != 7) {
            printf("\nНажмите Enter для продолжения");
            getchar();
        }
    }

    return 0;
}

int show_menu() {
    int choice;
    printf("\nМеню управления RPA-системами\n");
    printf("1. Загрузка данных из файла\n");
    printf("2. Просмотр всех записей\n");
    printf("3. Поиск по заданному диапазону\n");
    printf("4. Сортировка данных\n");
    printf("5. Добавление новой записи\n");
    printf("6. Сохранение данных в файл\n");
    printf("7. Выход\n");
    printf("Выберите пункт меню: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    return choice;
}

rpa_sys input_data() {
    rpa_sys system;
    printf("Название системы: ");
    scanf("%49s", system.name);
    printf("Уровень ИИ (низкий/средний/высокий): ");
    scanf("%19s", system.ai);
    printf("Количество процессов: ");
    scanf("%d", &system.proc);
    printf("Возможности мониторинга: ");
    scanf(" %[^\n]", system.monitor);
    printf("Точность выполнения (в процентах): ");
    scanf("%f", &system.accuracy);
    printf("Стоимость лицензии: ");
    scanf("%lf", &system.cost);
    printf("Интеграция с ERP: ");
    scanf(" %[^\n]", system.erp);
    printf("Сложность настройки (низкая/средняя/высокая): ");
    scanf("%19s", system.dif);
    return system;
}

void output_data(rpa_sys system) {
    printf("Название: %s\n", system.name);
    printf("Уровень ИИ: %s\n", system.ai);
    printf("Количество процессов: %d\n", system.proc);
    printf("Возможности мониторинга: %s\n", system.monitor);
    printf("Точность выполнения: %.1f%%\n", system.accuracy);
    printf("Стоимость лицензии: %.2f\n", system.cost);
    printf("Интеграция с ERP: %s\n", system.erp);
    printf("Сложность настройки: %s\n", system.dif);
}

void load_from_file(rpa_sys* systems, int* count) {
    FILE* file = fopen("rpa_systems.txt", "rb");
    if (file == NULL) {
        printf("\nФайл 'rpa_systems.txt' не найден.\n");
        *count = 0;
        return;
    }
    *count = fread(systems, sizeof(rpa_sys), max, file);
    fclose(file);
    if (*count > 0) {
        printf("\nУспешно загружено %d записей из файла 'rpa_systems.txt'.\n", *count);
    }
    else {
        printf("\nФайл пуст или содержит некорректные данные.\n");
    }
}

void view_all_records(rpa_sys* systems, int count) {
    printf("\nПросмотр всех записей\n");
    if (count == 0) {
        printf("Записей нет. Сначала добавьте запись.\n");
    }
    else {
        printf("\nВсе записи (%d)\n", count);
        for (int i = 0; i < count; i++) {
            printf("\n--- Запись %d ---\n", i + 1);
            output_data(systems[i]);
        }
    }
}

void search_by_range(rpa_sys* systems, int count) {
    double min, maxx;
    int found = 0;
    if (count == 0) {
        printf("Сначала добавьте запись\n");
        return;
    }
    printf("Введите первое число диапазона: ");
    scanf("%lf", &min);
    printf("Введите второе число диапазона: ");
    scanf("%lf", &maxx);

    for (int i = 0; i < count; i++) {
        if (systems[i].cost <= maxx && systems[i].cost >= min) {
            printf("\n--- Запись %d ---\n", found + 1);
            output_data(systems[i]);
            found++;
        }
    }
    if (found == 0) {
        printf("Не найдено записей в указанном диапазоне.\n");
    }
    else {
        printf("Найдено записей: %d\n", found);
    }
}

int compare(const void* a, const void* b) {
    const rpa_sys* system1 = (const rpa_sys*)a;
    const rpa_sys* system2 = (const rpa_sys*)b;

    double cubicA = pow(system1->accuracy / 100.0, 3);
    double cubicB = pow(system2->accuracy / 100.0, 3);

    if (cubicA < cubicB) return 1;
    if (cubicA > cubicB) return -1;
    return 0;
}

void sort_data(rpa_sys* systems, int count) {

    if (count == 0) {
        printf("Нет данных для сортировки.\n");
        return;
    }

    qsort(systems, count, sizeof(rpa_sys), compare);
    printf("Данные отсортированы по кубическому значению точности!\n");
}

void add_new_record(rpa_sys* systems, int* count) {
    printf("\nДобавление новой записи\n");
    if (*count < max) {
        systems[*count] = input_data();
        (*count)++;
        printf("Запись успешно добавлена! Всего записей: %d\n", *count);
    }
    else {
        printf("Достигнут максимальный лимит записей (%d)!\n", max);
    }
}

void save_to_file(rpa_sys* systems, int count) {
    FILE* file = fopen("rpa_systems.txt", "wb");
    if (file == NULL) {
        printf("\nОшибка при создании файла 'rpa_systems.txt'!\n");
        return;
    }
    int written = fwrite(systems, sizeof(rpa_sys), count, file);
    fclose(file);
    if (written == count) {
        printf("\nУспешно сохранено %d записей в файл 'rpa_systems.txt'.\n", count);
    }
    else {
        printf("\nОшибка при сохранении данных!\n");
    }
}
