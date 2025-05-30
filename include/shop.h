#ifndef SHOP_H
#define SHOP_H
#include <sstream>

// класс описывающий Магазин
class Shop {
    std::string name;
    Dynamic_list<Department> list_departments; // динамический двунаправленный список отделов

public:
    // переопределение конструкторов
    Shop() : name("unknown") {
    }

    explicit Shop(std::string n) : name(std::move(n)) {
    }

    // геттер поля имени
    [[nodiscard]] std::string get_name() const {
        return name;
    }

    // сеттер поля имени
    void set_name(const std::string &s) {
        name = s;
    }

    // добавление отдела
    void add_department(const std::string &name) {
        list_departments.insert_element(name);
    }

    // удаление отдела
    void remove_department(const std::string &name) {
        list_departments.delete_element(name);
    }

    // поиск отдела
    [[nodiscard]] Department &find_department(const std::string &name) const {
        return list_departments.find_node(name);
    }

    // геттер списка отделов
    [[nodiscard]] const Dynamic_list<Department> &get_list_departments() const {
        return list_departments;
    }

    // сохранение магазина в файл
    void save_to_file(const std::string &filename) const {
        std::ofstream out_file(filename);
        if (!out_file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }

        // сохраняем имя магазина
        out_file << "Shop: " << name << "\n";

        // сохраняем отделы
        out_file << "Departments:\n";
        list_departments.for_each([&out_file](const Department &dept) {
            out_file << dept.get_name() << "\n";
            // Перебираем сотрудников отдела
            dept.for_each_person([&out_file](const Person &person) {
                out_file << "  " << person.get_name() << " " << person.get_salary() << "\n";
            });
        });

        out_file.close();
    }

    // загрузка магазина из файла
    void load_from_file(const std::string &filename) {
        std::ifstream in_file(filename);
        if (!in_file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
        }
        std::string line;
        // чтение имя магазина
        if (std::getline(in_file, line) && line.find("Shop: ") == 0) {
            name = line.substr(6); // извлечение имени после "Shop: "
        } else {
            throw std::runtime_error("Неверный формат файла: ожидалось 'Shop: <name>'");
        }

        list_departments = Dynamic_list<Department>();

        if (!std::getline(in_file, line) || line != "Departments:") {
            throw std::runtime_error("Неверный формат файла: ожидалось 'Departments:'");
        }

        Department *current_dept = nullptr;
        while (std::getline(in_file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] != ' ') {
                // Новая строка без отступа — это отдел
                add_department(line);
                try {
                    current_dept = &find_department(line);
                } catch (const std::runtime_error &e) {
                    throw std::runtime_error("Ошибка при добавлении отдела: " + line);
                }
            } else if (line[0] == ' ' && line[1] == ' ' && current_dept) {
                // Строка с отступом — это сотрудник
                std::istringstream iss(line.substr(2)); // Убираем два пробела
                std::string person_name;
                if (int32_t salary; iss >> person_name >> salary) {
                    current_dept->add_person(person_name, salary);
                } else {
                    throw std::runtime_error("Неверный формат данных менеджера: " + line);
                }
            }
        }

        in_file.close();
    }
};

#endif //SHOP_H
