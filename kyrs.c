#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX 100

typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Level;

typedef struct {
    char name[50];
    Level ai;
    int proc;
    char monitor[100];
    float accuracy;
    double cost;
    char erp[100];
    Level difficulty;
} rpa_sys;

rpa_sys input_data();
void output_data(rpa_sys system);
int show_menu();
int load_from_file(rpa_sys* systems);
void view_all_records(rpa_sys* systems, int count);
void search_by_range(rpa_sys* systems, int count);
void sort_data(rpa_sys* systems, int count);
int add_new_record(rpa_sys* systems, int count);
int save_to_file(rpa_sys* systems, int count);
int compare(const void* a, const void* b);
int getRandomNumber(int min, int maxxx);
int generate_random_data(rpa_sys* systems, int count);
void generate_random_name(char* name);
void generate_random_monitor(char* monitor);
void generate_random_erp(char* erp);

int main() {
    system("chcp 1251");
    rpa_sys systems[MAX];
    int count = 0;
    int choice = 0;

    srand(time(NULL));

    while (choice != 8) {
        choice = show_menu();

        switch (choice) {
        case 1:
            count = load_from_file(systems);
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
            count = add_new_record(systems, count);
            break;
        case 6: {
            int result = save_to_file(systems, count);
            if (result) {
                printf("\nУспешно сохранено %d записей в файл 'rpa_systems.txt'.\n", count);
            }
            else {
                printf("\nОшибка при сохранении данных!\n");
            }
            break;
        }
        case 7:
            count = generate_random_data(systems, count);
            break;
        case 8:
            printf("\nВыход из программы\n");
            break;
        default:
            printf("\nНеверный выбор\n");
        }

        if (choice != 8) {
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
    printf("7. Заполнение случайными данными\n");
    printf("8. Выход\n");
    printf("Выберите пункт меню: ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    return choice;
}

rpa_sys input_data() {
    rpa_sys system;
    int choice;

    printf("Название системы: ");
    scanf("%49s", system.name);

    printf("Уровень ИИ (1-низкий, 2-средний, 3-высокий): ");
    scanf("%d", &choice);
    if (choice >= 1 && choice <= 3) {
        system.ai = (Level)(choice - 1);
    }
    else {
        printf("Неверный выбор, установлено значение по умолчанию (низкий)\n");
        system.ai = LOW;
    }

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

    printf("Сложность настройки (1-низкая, 2-средняя, 3-высокая): ");
    scanf("%d", &choice);
    if (choice >= 1 && choice <= 3) {
        system.difficulty = (Level)(choice - 1);
    }
    else {
        printf("Неверный выбор, установлено значение по умолчанию (низкая)\n");
        system.difficulty = LOW;
    }

    return system;
}

void output_data(rpa_sys system) {
    printf("Название: %s\n", system.name);

    printf("Уровень ИИ: ");
    switch (system.ai) {
    case LOW: printf("низкий"); break;
    case MEDIUM: printf("средний"); break;
    case HIGH: printf("высокий"); break;
    }
    printf("\n");

    printf("Количество процессов: %d\n", system.proc);
    printf("Возможности мониторинга: %s\n", system.monitor);
    printf("Точность выполнения: %.1f%%\n", system.accuracy);
    printf("Стоимость лицензии: %.2f\n", system.cost);
    printf("Интеграция с ERP: %s\n", system.erp);

    printf("Сложность настройки: ");
    switch (system.difficulty) {
    case LOW: printf("низкая"); break;
    case MEDIUM: printf("средняя"); break;
    case HIGH: printf("высокая"); break;
    }
    printf("\n");
}

int load_from_file(rpa_sys* systems) {
    FILE* file = fopen("rpa_systems.txt", "rb");
    int count = 0;

    if (file == NULL) {
        printf("\nФайл 'rpa_systems.txt' не найден.\n");
        return 0;
    }

    count = fread(systems, sizeof(rpa_sys), MAX, file);
    fclose(file);

    if (count > 0) {
        printf("\nУспешно загружено %d записей из файла 'rpa_systems.txt'.\n", count);
    }
    else {
        printf("\nФайл пуст или содержит некорректные данные.\n");
    }

    return count;
}

void view_all_records(rpa_sys* systems, int count) {
    printf("\nПросмотр всех записей\n");
    if (count == 0) {
        printf("Записей нет. Сначала добавьте запись.\n");
        return;
    }

    printf("\nВсе записи (%d)\n", count);
    for (int i = 0; i < count; i++) {
        printf("\n--- Запись %d ---\n", i + 1);
        output_data(systems[i]);
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

    double cubicA = pow(system1->accuracy / 100, 1.0 / 3.0);
    double cubicB = pow(system2->accuracy / 100, 1.0 / 3.0);

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

int add_new_record(rpa_sys* systems, int count) {
    printf("\nДобавление новой записи\n");
    if (count < MAX) {
        systems[count] = input_data();
        count++;
        printf("Запись успешно добавлена! Всего записей: %d\n", count);
    }
    else {
        printf("Достигнут максимальный лимит записей (%d)!\n", MAX);
    }
    return count;
}

int save_to_file(rpa_sys* systems, int count) {
    FILE* file = fopen("rpa_systems.txt", "wb");
    int result = 0;

    if (file == NULL) {
        printf("\nОшибка при создании файла 'rpa_systems.txt'!\n");
        return 0;
    }

    result = fwrite(systems, sizeof(rpa_sys), count, file);
    fclose(file);

    if (result == count) {
        return 1;
    }
    else {
        return 0;
    }
}

int getRandomNumber(int min, int maxxx) {
    return rand() % (maxxx - min + 1) + min;
}

void generate_random_name(char* name) {
    char* names[] = { "UiPath", "AutomationAnywhere", "BluePrism", "Primo" };
    int index = rand() % 4;
    strcpy(name, names[index]);
}

void generate_random_monitor(char* monitor) {
    char* monitors[] = { "мониторинг в реальном времени", "аналитика производительности", "оповещения об ошибках", "отчеты о выполнениях" };
    int index = rand() % 4;
    strcpy(monitor, monitors[index]);
}

void generate_random_erp(char* erp) {
    char* erps[] = { "Галактика", "1C", "Odoo", "Oracle" };
    int index = rand() % 4;
    strcpy(erp, erps[index]);
}

int generate_random_data(rpa_sys* systems, int count) {
    int num_r;

    printf("Сколько записей сгенерировать? ");
    scanf("%d", &num_r);

    if (count + num_r > MAX) {
        printf("Нельзя добавить %d записей. Максимум можно добавить %d записей.\n", num_r, MAX - count);
        return count;
    }

    for (int i = 0; i < num_r; i++) {
        int index = count + i;

        generate_random_name(systems[index].name);

        systems[index].ai = (Level)(rand() % 3);

        systems[index].proc = getRandomNumber(0, 100);
        generate_random_monitor(systems[index].monitor);
        systems[index].accuracy = getRandomNumber(0, 100);
        systems[index].cost = getRandomNumber(10, 1000);
        generate_random_erp(systems[index].erp);

        systems[index].difficulty = (Level)(rand() % 3);
    }

    count += num_r;
    printf("Добавлено %d случайных записей. Всего записей: %d\n", num_r, count);
    return count;
}
