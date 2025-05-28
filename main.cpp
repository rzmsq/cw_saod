// динамический упорядоченный двунаправленный список статических стеков

#include <iostream>
#include <string>

#include "./include/my_const.h"
#include "./include/dynamic_list.h"
#include "./include/statick_stack.h"
#include "./include/person.h"
#include "./include/department.h"
#include "./include/shop.h"

void print_all_data(const Shop &shop) {
    std::cout << "Список отделов:\n";
    shop.get_list_departments().for_each([](const Department &department) {
        std::cout << department.get_name() << "\n";
        std::cout << " Список сотрудников отдела:\n";
        department.get_stack_persons().for_each([](const Person &person) {
            std::cout << "\t";
            if (!person.get_name().empty()) {
                std::cout << "ФИО: Зарплата\n";
                std::cout << "\t" << person.get_name() << ": " << person.get_salary() << "\n";
            }
        });
        std::cout << "\n";
    });
}

void remove_person(const Shop &shop, const std::string &dep, const std::string &name) {
    try {
        shop.find_department(dep).remove_person(name);
    } catch (const std::exception &e) {
        std::cout << "Ошибка удаления сотрудника\n";
    }
}

void remove_department(Shop &shop, const std::string &dep) {
    try {
        shop.remove_department(dep);
    } catch (const std::exception &e) {
        std::cout << "Ошибка удаления отдела\n";
    }
}

int main(int argc, char *argv[]) {
    Shop shop = Shop("Amazon");

    shop.add_department("pc");
    shop.find_department("pc").add_person("rostislav", 300);
    shop.add_department("books");
    shop.find_department("books").add_person("Ivan", 229);
    shop.add_department("wym");
    shop.find_department("wym").add_person("Max", 77);

    print_all_data(shop);

    shop.find_department("pc").find_person("rostislav").set_name("Vlad");

    remove_person(shop, "pc", "rostislav");
    remove_department(shop, "pc");

    print_all_data(shop);

    remove_department(shop, "pc");
    return EXIT_SUCCESS;
}
