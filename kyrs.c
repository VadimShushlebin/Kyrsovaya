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
    char name[50]; // Название системы
    Level ai; // Уровень ИИ
    int proc; // Количество процессов
    char monitor[100]; // Возможности мониторинга
    float accuracy; // Точность выполнения
    double cost; // Стоимость лицензии
    char erp[100]; // Интеграция с ERP
    Level difficulty; // Сложность настройки
} rpa_sys;

// Прототипы функций
rpa_sys input_data(); // Ввод данных с клавиатуры
void output_data(rpa_sys system);  // Вывод данных на экран
int show_menu(); // Отображение меню
int load_from_file(rpa_sys* systems); // Загрузка из файла
void view_all_records(rpa_sys* systems, int count); // Просмотр всех записей
int search_by_range(rpa_sys* systems, int count); // Поиск по диапазону стоимости
void sort_data(rpa_sys* systems, int count); // Сортировка данных
int add_new_record(rpa_sys* systems, int count); // Добавление новой записи
int save_to_file(rpa_sys* systems, int count); // Сохранение в файл
int compare(const void* a, const void* b); // Функция сравнения для qsort
int getRandomNumber(int min, int maxxx); // Генерация случайного числа
int generate_random_data(rpa_sys* systems, int count); // Генерация случайных данных

// Главная функция
int main() {
    system("chcp 1251");
    rpa_sys systems[MAX];  // Массив структур
    int count = 0;         // Количество записей
    int choice = 0;        // Выбор пользователя в меню

    srand(time(NULL));  // Инициализация генератора случайных чисел

    // Главный цикл программы
    while (choice != 8) {
        choice = show_menu();

        switch (choice) {
        case 1:  // Загрузка данных из файла
            count = load_from_file(systems);
            break;
        case 2:  // Просмотр всех записей
            view_all_records(systems, count);
            break;
        case 3:  // Поиск по диапазону
        {
            int found = search_by_range(systems, count);
            if (found == 0) {
                printf("Не найдено записей в указанном диапазоне.\n");
            }
            else {
                printf("Найдено записей: %d\n", found);
            }
        }
        break;
        case 4:  // Сортировка данных
            sort_data(systems, count);
            break;
        case 5:  // Добавление новой записи
            count = add_new_record(systems, count);
            break;
        case 6:  // Сохранение в файл
        {
            int saved = save_to_file(systems, count);
            if (saved == count) {
                printf("\nУспешно сохранено %d записей в файл 'rpa_systems.txt'.\n", count);
            }
            else {
                printf("\nОшибка при сохранении данных! Сохранено только %d из %d записей.\n", saved, count);
            }
        }
        break;
        case 7:  // Генерация случайных данных
            count = generate_random_data(systems, count);
            break;
        case 8:  // Выход
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
    FILE* file = fopen("rpa_systems.txt", "rb");
    int count = 0;

    if (file == NULL) {
        printf("\nФайл 'rpa_systems.txt' не найден.\n");
        return 0;
    }

    // Чтение данных из файла в массив структур
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

// Просмотр всех записей
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

// Поиск записей по диапазону стоимости
int search_by_range(rpa_sys* systems, int count) {
    double min, maxx;
    int found = 0;

    if (count == 0) {
        printf("Сначала добавьте запись\n");
        return 0;
    }

    printf("Введите первое число диапазона: ");
    scanf("%lf", &min);
    printf("Введите второе число диапазона: ");
    scanf("%lf", &maxx);

    // Поиск записей, стоимость которых входит в диапазон
    for (int i = 0; i < count; i++) {
        if (systems[i].cost <= maxx && systems[i].cost >= min) {
            printf("\n--- Запись %d ---\n", found + 1);
            output_data(systems[i]);
            found++;
        }
    }

    return found;
}

// Функция сравнения для сортировки (по кубическому корню точности)
int compare(const void* a, const void* b) {
    const rpa_sys* system1 = (const rpa_sys*)a;
    const rpa_sys* system2 = (const rpa_sys*)b;

    // Вычисление кубического корня из точности
    double cubicA = pow(system1->accuracy / 100, 1.0 / 3.0);
    double cubicB = pow(system2->accuracy / 100, 1.0 / 3.0);

    // Сортировка по убыванию
    if (cubicA < cubicB) return 1;
    if (cubicA > cubicB) return -1;
    return 0;
}

// Сортировка данных с помощью qsort
void sort_data(rpa_sys* systems, int count) {
    if (count == 0) {
        printf("Нет данных для сортировки.\n");
        return;
    }

    qsort(systems, count, sizeof(rpa_sys), compare);
    printf("Данные отсортированы по кубическому значению точности!\n");
}

// Добавление новой записи
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

// Сохранение данных в бинарный файл
int save_to_file(rpa_sys* systems, int count) {
    FILE* file = fopen("rpa_systems.txt", "wb");
    int result = 0;

    if (file == NULL) {
        printf("\nОшибка при создании файла 'rpa_systems.txt'!\n");
        return 0;
    }

    // Запись массива структур в файл
    result = fwrite(systems, sizeof(rpa_sys), count, file);
    fclose(file);

    return result;
}

// Генерация случайного числа в заданном диапазоне
int getRandomNumber(int min, int maxxx) {
    return rand() % (maxxx - min + 1) + min;
}

// Генерация заданного количества случайных записей
int generate_random_data(rpa_sys* systems, int count) {
    int num_r;
    char* names[] = { "UiPath", "AutomationAnywhere", "BluePrism", "Primo" };
    char* monitors[] = {
        "мониторинг в реальном времени",
        "аналитика производительности",
        "оповещения об ошибках",
        "отчеты о выполнениях"
    };
    char* erps[] = { "Галактика", "1C", "Odoo", "Oracle" };

    printf("Сколько записей сгенерировать? ");
    scanf("%d", &num_r);

    if (count + num_r > MAX) {
        printf("Нельзя добавить %d записей. Максимум можно добавить %d записей.\n", num_r, MAX - count);
        return count;
    }

    for (int i = 0; i < num_r; i++) {
        int index = count + i;

        // Генерация случайных строк
        int name_index = rand() % 4;
        int monitor_index = rand() % 4;
        int erp_index = rand() % 4;

        strcpy(systems[index].name, names[name_index]);
        systems[index].ai = (Level)(rand() % 3);
        systems[index].proc = getRandomNumber(0, 100);
        strcpy(systems[index].monitor, monitors[monitor_index]);
        systems[index].accuracy = getRandomNumber(0, 100);
        systems[index].cost = getRandomNumber(10, 1000);
        strcpy(systems[index].erp, erps[erp_index]);
        systems[index].difficulty = (Level)(rand() % 3);
    }

    count += num_r;
    printf("Добавлено %d случайных записей. Всего записей: %d\n", num_r, count);
    return count;
}
