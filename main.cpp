// динамический упорядоченный двунаправленный список статических стеков

#include <iostream>
#include <string>

#include "./include/my_const.h"
#include "./include/dynamic_list.h"
#include "./include/statick_stack.h"
#include "./include/department.h"
#include "./include/shop.h"
#include "./include/person.h"

int main(int argc, char *argv[]) {
    Dynamic_list<Shop> list = Dynamic_list<Shop>();
    list.insert_element("Nokia");
    list.insert_element("Dyson");
    list.insert_element("Bosch");
    list.insert_element("Apple");


    std::cout << "list1\n";
    list.print_nodes();
    std::cout << "\n";

    Dynamic_list<Shop> list2 = list;
    std::cout << "list2\n";
    list2.insert_element("Motorolla");
    list2.print_nodes();
    std::cout << "\n";

    // Dynamic_list<Shop> list3 = list;
    // list3.delete_element("Bosh");
    // list3.delete_element("Apple");
    // list3.delete_element("Dyson");
    // list3.delete_element("Bosch");
    // list3.insert_element("Motorolla");
    // list3.delete_element("Motorolla");
    // list3.delete_element("Nokia");


    Dynamic_list<Shop> list3 = Dynamic_list<Shop>();
    list3.insert_element("Amazon");
    list3.insert_element("Tesla");

    list = list3;
    list.insert_element("Abazon");

    // if (!list.delete_element("Dyson").empty()) {
    //     list.print_nodes();
    //     std::cout << "\n";
    // }
    //
    // if (!list.delete_element("Nokia").empty()) {
    //     list.print_nodes();
    //     std::cout << "\n";
    // }
    //
    // if (!list.delete_element("Apple").empty()) {
    //     list.print_nodes();
    //     std::cout << "\n";
    // }


    std::cout << "list1\n";
    list.print_nodes();
    std::cout << "\n";

    std::cout << "list2\n";
    list2.print_nodes();
    std::cout << "\n";

    std::cout << "list3\n";
    list3.print_nodes();
    std::cout << "\n";

    return EXIT_SUCCESS;
}
