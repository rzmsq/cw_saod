// динамический упорядоченный двунаправленный список статических стеков

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "./include/my_var_and_const.h"
#include "./include/dynamic_list.h"
#include "./include/static_stack.h"
#include "./include/person.h"
#include "./include/department.h"
#include "./include/shop.h"

// функция получения строки от пользователя
std::string get_str(const std::string &str_out) {
    std::string str;
    do {
        std::cout << str_out;
        std::getline(std::cin, str);
        if (str.empty()) {
            std::cout << "Поле не может быть пустым.\n";
        }
    } while (str.empty());
    return str;
}

// проверка допустимости ввода числового значения
bool is_Valid_Int_32(const std::string &str) {
    if (str.empty()) {
        return false;
    }

    try {
        // является ли строка числом
        size_t pos = 0;
        const int64_t value = std::stoll(str, &pos);

        // Проверка на лишние символы
        if (pos != str.length()) {
            return false;
        }

        // Проверяем, что число в пределах int32_t
        if (value < std::numeric_limits<int32_t>::min() ||
            value > std::numeric_limits<int32_t>::max()) {
            return false;
        }

        return true;
    } catch (const std::invalid_argument &) {
        // Если строка не является числом
        return false;
    } catch (const std::out_of_range &) {
        // Если число выходит за пределы int64_t
        return false;
    }
}

// вывод отдельного менеджера
void print_person(const Person &person) {
    std::cout << "\t" << person.get_name() << ": " << person.get_salary() << "\n";
}

// вывод отдела
void print_department(const Department &department) {
    std::cout << department.get_name() << "\n";
    std::cout << " Список менеджеров отдела:\n";
    std::cout << "\tФИО: Зарплата (у.е.)\n";
    department.get_stack_persons().for_each([](const Person &person) {
        if (!person.get_name().empty()) {
            print_person(person);
        }
    });
    std::cout << "\n";
}

// вывод всей информации по магазину
void print_all_data(const Shop *shop) {
    std::cout << shop->get_name() << "\nСписок отделов:\n";
    shop->get_list_departments().for_each([](const Department &department) {
        print_department(department);
    });
}

// удаление менеджера
void remove_person(const Shop *shop, const std::string &dep, const std::string &name) {
    try {
        shop->find_department(dep).remove_person(name);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

// удаление отдела
void remove_department(Shop *shop, const std::string &dep) {
    try {
        shop->remove_department(dep);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

// сохранение в файл
void save_to_file(const Shop *shop) {
    try {
        shop->save_to_file("shop_data.txt");
        std::cout << "Данные сохранены в shop_data.txt\n";
    } catch (const std::runtime_error &e) {
        std::cerr << "Ошибка сохранения: " << e.what() << "\n";
    }
}

// загрузка из файла
void load_from_file(Shop *shop) {
    try {
        shop->load_from_file("shop_data.txt");
        std::cout << "Данные загружены из shop_data.txt\n";
    } catch (const std::runtime_error &e) {
        std::cerr << "Ошибка загрузки: " << e.what() << "\n";
    }
}

// поиск отдела
Department &find_department(const Shop *shop, const std::string &department) {
    return shop->find_department(department);
}

// поиск менеджера
Person &find_person(const Shop *shop, const std::string &person_to_find) {
    Person *result = nullptr;
    const Department *result_dep = nullptr;
    shop->get_list_departments().for_each([&](Department &department) {
        try {
            result = &department.find_person(person_to_find);
            result_dep = &department;
            std::cout << "Сотрудник найдет в отделе: " << result_dep->get_name() << "\n"
                    << "\tФИО: Зарплата (у.е.)\n";
            print_person(*result);
        } catch (const std::runtime_error &) {
            // Продолжаем поиск в других отделах
        }
    });
    if (!result) {
        throw std::runtime_error("Сотрудник не найден");
    }

    return *result;
}

// создание магазина
Shop *create_new_shop() {
    const std::string name = get_str("Введите название магазина\n");

    return new Shop(name);
}

// добавление отдела
void add_department(Shop *shop) {
    if (shop) {
        const std::string name = get_str("Введите название отдела\n");
        shop->add_department(name);
    } else {
        std::cout << "Ошибка. Магазин не создан\n";
    }
}

// добавление менеджера
void add_person(const Shop *shop, const std::string &person_name, const std::string &salary_str) {
    if (shop) {
        if (is_Valid_Int_32(salary_str)) {
            const int32_t salary = std::stoi(salary_str);
            const std::string dep_name = get_str("Введите Отдел куда добавить менеджера\n");

            try {
                shop->find_department(dep_name).add_person(person_name, salary);
            } catch (const std::runtime_error &e) {
                std::cerr << e.what() << "\n";
            }
        }
    } else {
        std::cout << "Ошибка. Магазин не создан\n";
    }
}

// удаление магазина
void del_shop(Shop *&shop) {
    delete shop;
    shop = nullptr;
}

// обработка введенной операции
void process_operation(Shop *&shop, const my_var_and_const::Operation &op) {
    if (!shop && op != my_var_and_const::Operation::Create_new_magazine &&
        op != my_var_and_const::Operation::Load_file &&
        op != my_var_and_const::Operation::Exit) {
        std::cerr << "Ошибка. Магазин не создан.\n";
        return;
    }
    switch (op) {
        case my_var_and_const::Operation::Create_new_magazine: {
            if (shop) {
                delete shop;
                shop = nullptr;
            }
            shop = create_new_shop();
            break;
        }
        case my_var_and_const::Operation::Add_dep:
            add_department(shop);
            break;
        case my_var_and_const::Operation::Del_dep: {
            const std::string dep_name = get_str("Введите название Отдела\n");
            remove_department(shop, dep_name);
            break;
        }
        case my_var_and_const::Operation::Add_pers: {
            const std::string name = get_str("Введите Фамилию менеджера\n");
            if (name.contains(' ')) {
                std::cout << "Ошибка.Введите фамилию без пробелов\n";
                return;
            }
            const std::string salary_str = get_str("Введите Зарплату менеджера\n");
            add_person(shop, name, salary_str);
            break;
        }
        case my_var_and_const::Operation::Del_pers: {
            const std::string name = get_str("Введите Фамилию менеджера\n");
            try {
                find_person(shop, name);
            } catch (const std::runtime_error &e) {
                std::cerr << e.what() << "\n";
                break;
            }
            const std::string dep_name = get_str("Введите название Отдела\n");
            remove_person(shop, dep_name, name);
            break;
        }
        case my_var_and_const::Operation::Find_dep: {
            const std::string dep_name = get_str("Введите название Отдела\n");
            try {
                print_department(find_department(shop, dep_name));
            } catch (const std::runtime_error &e) {
                std::cerr << e.what() << "\n";
            }
            break;
        }
        case my_var_and_const::Operation::Find_pers: {
            const std::string name = get_str("Введите Фамилию менеджера\n");
            try {
                find_person(shop, name);
            } catch (const std::runtime_error &e) {
                std::cerr << e.what() << "\n";
            }
            break;
        }
        case my_var_and_const::Operation::Print_all:
            print_all_data(shop);
            break;
        case my_var_and_const::Operation::Del_mag: {
            del_shop(shop);
            std::cout << "Магазин удален\n";
            break;
        }
        case my_var_and_const::Operation::Load_file: {
            if (shop) {
                delete shop;
                shop = nullptr;
            }
            shop = new Shop();
            load_from_file(shop);
            break;
        }
        case my_var_and_const::Operation::Save_file:
            save_to_file(shop);
            break;
        case my_var_and_const::Operation::Exit:
            std::cout << "Выход...\n";
            break;
        default: break;
    }
}

int main() {
    Shop *shop = nullptr;
    std::string op{};
    bool isRun{true};

    while (isRun) {
        // вывод допустимых операций и считывание ввода пользователя
        std::cout << my_var_and_const::menu_str;
        std::getline(std::cin, op);

        // обработка введнной строки пользователя
        if (auto it = my_var_and_const::operationMap.find(op); it != my_var_and_const::operationMap.end()) {
            process_operation(shop, it->second);
            if (it->second == my_var_and_const::Operation::Exit) {
                isRun = false;
            }
        }
    }

    delete shop;
    return EXIT_SUCCESS;
}
