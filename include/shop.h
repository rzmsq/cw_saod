#ifndef SHOP_H
#define SHOP_H

class Shop {
    std::string name;
    Dynamic_list<Department> list_departments;

public:
    Shop() : name("unknown") {
    }

    explicit Shop(std::string n) : name(std::move(n)) {
    }

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    void set_name(const std::string &s) {
        name = s;
    }

    void add_department(const std::string &name) {
        list_departments.insert_element(name);
    }

    void remove_department(const std::string &name) {
        list_departments.delete_element(name);
    }

    [[nodiscard]] Department &find_department(const std::string &name) const {
        return list_departments.find_node(name);
    }

    [[nodiscard]] const Dynamic_list<Department> &get_list_departments() const {
        return list_departments;
    }
};

#endif //SHOP_H
