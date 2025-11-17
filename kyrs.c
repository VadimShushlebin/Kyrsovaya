#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

typedef struct {
    char name[50];
    char process_level[20];
    char capabilities[100];
    double cost;
    char complexity[10];
    int ai;
    int monitoring;
    float accuracy;
    char integration[100];
} RPA_System;

RPA_System input_data();
void output_data(RPA_System system);
int show_menu();
void load_from_file(RPA_System systems[], int* count);
void view_all_records(RPA_System systems[], int count);
void search_by_range(RPA_System systems[], int count);
void sort_data(RPA_System systems[], int count);
void add_new_record(RPA_System systems[], int* count);
void save_to_file(RPA_System systems[], int count);

int main() {
    system("chcp 1251");

    RPA_System systems[MAX_RECORDS];
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
            printf("\nВыход из программы...\n");
            break;

        default:
            printf("\nНеверный выбор! Попробуйте снова.\n");
        }

        if (choice != 7) {
            printf("\nНажмите Enter для продолжения...");
            getchar();
        }
    }

    return 0;
}

int show_menu() {
    int choice;

    printf("\n=== Меню управления RPA-системами ===\n");
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

RPA_System input_data() {
    RPA_System system;

    printf("Название системы: ");
    scanf("%49s", system.name);

    printf("Уровень процессов: ");
    scanf("%19s", system.process_level);

    printf("Возможности выполнения: ");
    scanf(" %[^\n]", system.capabilities);

    printf("Стоимость ERP: ");
    scanf("%lf", &system.cost);

    printf("Сложность настройки (низкая/средняя/высокая): ");
    scanf("%9s", system.complexity);

    printf("Наличие ИИ (1-да, 0-нет): ");
    scanf("%d", &system.ai);

    printf("Количество мониторинга (число): ");
    scanf("%d", &system.monitoring);

    printf("Точность лицензии (в процентах): ");
    scanf("%f", &system.accuracy);

    printf("Интеграция: ");
    scanf(" %[^\n]", system.integration);

    return system;
}

void output_data(RPA_System system) {
    printf("Название: %s\n", system.name);
    printf("Уровень процессов: %s\n", system.process_level);
    printf("Возможности выполнения: %s\n", system.capabilities);
    printf("Стоимость ERP: %.2f\n", system.cost);
    printf("Сложность настройки: %s\n", system.complexity);
    printf("Наличие ИИ: %s\n", system.ai ? "да" : "нет");
    printf("Количество мониторинга: %d\n", system.monitoring);
    printf("Точность лицензии: %.1f%%\n", system.accuracy);
    printf("Интеграция: %s\n", system.integration);
}

void load_from_file(RPA_System systems[], int* count) {
    printf("\n=== Загрузка данных из файла ===\n");
    printf("Функция в разработке\n");
}

void view_all_records(RPA_System systems[], int count) {
    printf("\n=== Просмотр всех записей ===\n");
    if (count == 0) {
        printf("Записей нет. Сначала добавьте запись.\n");
    }
    else {
        printf("\n--- Все записи (%d) ---\n", count);
        for (int i = 0; i < count; i++) {
            printf("\n--- Запись %d ---\n", i + 1);
            output_data(systems[i]);
        }
    }
}

void search_by_range(RPA_System systems[], int count) {
    printf("\n=== Поиск по заданному диапазону ===\n");
    printf("Функция в разработке\n");
}

void sort_data(RPA_System systems[], int count) {
    printf("\n=== Сортировка данных ===\n");
    printf("Функция в разработке\n");
}

void add_new_record(RPA_System systems[], int* count) {
    printf("\n=== Добавление новой записи ===\n");
    if (*count < MAX_RECORDS) {
        systems[*count] = input_data();
        (*count)++;
        printf("Запись успешно добавлена! Всего записей: %d\n", *count);
    }
    else {
        printf("Достигнут максимальный лимит записей (%d)!\n", MAX_RECORDS);
    }
}

void save_to_file(RPA_System systems[], int count) {
    printf("\n=== Сохранение данных в файл ===\n");
    printf("Функция в разработке\n");
}