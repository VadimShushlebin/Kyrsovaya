#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX 100

// Перечисление для уровней
typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Level;

// Структура для хранения данных о RPA-системе
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

// Прототипы функций
rpa_sys input_data();
void output_data(rpa_sys system);
int show_menu();
int load_from_file(rpa_sys* systems);
void view_all_records(rpa_sys* systems, int count);
int search_by_range(rpa_sys* systems, int count);
void sort_data(rpa_sys* systems, int count);
int add_new_record(rpa_sys* systems, int count);
int save_to_file(rpa_sys* systems, int count);
int compare(const void* a, const void* b);
int getRandomNumber(int min, int maxxx);
int generate_random_data(rpa_sys* systems, int count);

// Главная функция
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
            if (count == 0) {
                printf("\nФайл не найден или пуст.\n");
            }
            else {
                printf("\nЗагружено %d записей.\n", count);
            }
            break;
        case 2:
            if (count == 0) {
                printf("\nНет данных для отображения.\n");
            }
            else {
                view_all_records(systems, count);
            }
            break;
        case 3:
            if (count == 0) {
                printf("\nНет данных для поиска.\n");
            }
            else {
                int found = search_by_range(systems, count);
                printf("\nНайдено записей: %d\n", found);
            }
            break;
        case 4:
            if (count == 0) {
                printf("\nНет данных для сортировки.\n");
            }
            else {
                sort_data(systems, count);
                printf("\nДанные отсортированы.\n");
            }
            break;
        case 5:
            if (count >= MAX) {
                printf("\nДостигнут максимальный лимит записей.\n");
            }
            else {
                count = add_new_record(systems, count);
                printf("\nЗапись добавлена. Всего записей: %d\n", count);
            }
            break;
        case 6:
            if (count == 0) {
                printf("\nНет данных для сохранения.\n");
            }
            else {
                int saved = save_to_file(systems, count);
                if (saved == count) {
                    printf("\nСохранено %d записей.\n", count);
                }
                else {
                    printf("\nОшибка сохранения.\n");
                }
            }
            break;
        case 7:
            if (count >= MAX) {
                printf("\nДостигнут максимальный лимит записей.\n");
            }
            else {
                count = generate_random_data(systems, count);
            }
            break;
        case 8:
            printf("\nВыход из программы.\n");
            break;
        default:
            printf("\nНеверный выбор.\n");
        }

        if (choice != 8) {
            printf("\nНажмите Enter для продолжения");
            getchar();
        }
    }

    return 0;
}

// Функция отображения меню
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

// Функция ввода данных с клавиатуры
rpa_sys input_data() {
    rpa_sys system;
    int choice;

    printf("Название системы: ");
    scanf("%49s", system.name);

    printf("Уровень ИИ (1-низкий, 2-средний, 3-высокий): ");
    scanf("%d", &choice);
    system.ai = (choice >= 1 && choice <= 3) ? (Level)(choice - 1) : LOW;

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
    system.difficulty = (choice >= 1 && choice <= 3) ? (Level)(choice - 1) : LOW;

    return system;
}

// Функция вывода данных на экран
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

// Загрузка данных из бинарного файла
int load_from_file(rpa_sys* systems) {
    FILE* file = fopen("rpa_systems.bin", "rb");
    if (file == NULL) {
        return 0;
    }

    int count = fread(systems, sizeof(rpa_sys), MAX, file);
    fclose(file);

    return count;
}

// Просмотр всех записей
void view_all_records(rpa_sys* systems, int count) {
    for (int i = 0; i < count; i++) {
        printf("\n--- Запись %d ---\n", i + 1);
        output_data(systems[i]);
    }
}

// Поиск записей по диапазону стоимости
int search_by_range(rpa_sys* systems, int count) {
    double min, maxx;
    int found = 0;

    printf("Введите минимальную стоимость: ");
    scanf("%lf", &min);
    printf("Введите максимальную стоимость: ");
    scanf("%lf", &maxx);

    for (int i = 0; i < count; i++) {
        if (systems[i].cost >= min && systems[i].cost <= maxx) {
            printf("\n--- Запись %d ---\n", found + 1);
            output_data(systems[i]);
            found++;
        }
    }

    return found;
}

// Функция сравнения для сортировки
int compare(const void* a, const void* b) {
    const rpa_sys* system1 = (const rpa_sys*)a;
    const rpa_sys* system2 = (const rpa_sys*)b;

    double cubicA = pow(system1->accuracy / 100, 1.0 / 3.0);
    double cubicB = pow(system2->accuracy / 100, 1.0 / 3.0);

    if (cubicA < cubicB) return 1;
    if (cubicA > cubicB) return -1;
    return 0;
}

// Сортировка данных
void sort_data(rpa_sys* systems, int count) {
    qsort(systems, count, sizeof(rpa_sys), compare);
}

// Добавление новой записи
int add_new_record(rpa_sys* systems, int count) {
    systems[count] = input_data();
    return count + 1;
}

// Сохранение данных в бинарный файл
int save_to_file(rpa_sys* systems, int count) {
    FILE* file = fopen("rpa_systems.bin", "wb");
    if (file == NULL) {
        return 0;
    }

    int result = fwrite(systems, sizeof(rpa_sys), count, file);
    fclose(file);

    return result;
}

// Генерация случайного числа
int getRandomNumber(int min, int maxxx) {
    return rand() % (maxxx - min + 1) + min;
}

// Генерация случайных данных
int generate_random_data(rpa_sys* systems, int count) {
    int num_r;
    char* names[] = { "UiPath", "AutomationAnywhere", "BluePrism", "Primo" };
    char* monitors[] = { "мониторинг в реальном времени","аналитика производительности","оповещения об ошибках", "отчеты о выполнениях"};
    char* erps[] = { "Галактика", "1C", "Odoo", "Oracle" };

    printf("Сколько записей сгенерировать? ");
    scanf("%d", &num_r);

    if (count + num_r > MAX) {
        num_r = MAX - count;
    }

    for (int i = 0; i < num_r; i++) {
        int index = count + i;
        strcpy(systems[index].name, names[rand() % 4]);
        systems[index].ai = (Level)(rand() % 3);
        systems[index].proc = getRandomNumber(0, 100);
        strcpy(systems[index].monitor, monitors[rand() % 4]);
        systems[index].accuracy = (float)getRandomNumber(0, 100);
        systems[index].cost = (double)getRandomNumber(10, 1000);
        strcpy(systems[index].erp, erps[rand() % 4]);
        systems[index].difficulty = (Level)(rand() % 3);
    }

    return count + num_r;
}
