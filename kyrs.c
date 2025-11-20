#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

typedef struct {
    char name[50];
    char ai_level[20];
    int process_count;
    char monitoring_capabilities[100];
    float accuracy;
    double license_cost;
    char erp_integration[100];
    char setup_complexity[20];
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

    printf("Уровень ИИ (низкий/средний/высокий): ");
    scanf("%19s", system.ai_level);

    printf("Количество процессов: ");
    scanf("%d", &system.process_count);

    printf("Возможности мониторинга: ");
    scanf(" %[^\n]", system.monitoring_capabilities);

    printf("Точность выполнения (в процентах): ");
    scanf("%f", &system.accuracy);

    printf("Стоимость лицензии: ");
    scanf("%lf", &system.license_cost);

    printf("Интеграция с ERP: ");
    scanf(" %[^\n]", system.erp_integration);

    printf("Сложность настройки (низкая/средняя/высокая): ");
    scanf("%19s", system.setup_complexity);

    return system;
}

void output_data(RPA_System system) {
    printf("Название: %s\n", system.name);
    printf("Уровень ИИ: %s\n", system.ai_level);
    printf("Количество процессов: %d\n", system.process_count);
    printf("Возможности мониторинга: %s\n", system.monitoring_capabilities);
    printf("Точность выполнения: %.1f%%\n", system.accuracy);
    printf("Стоимость лицензии: %.2f\n", system.license_cost);
    printf("Интеграция с ERP: %s\n", system.erp_integration);
    printf("Сложность настройки: %s\n", system.setup_complexity);
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
