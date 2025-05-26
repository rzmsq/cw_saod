#ifndef SHOP_H
#define SHOP_H

class Shop {
    std::string name;
    Static_stack<Department> stack_departments;

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
};

#endif //SHOP_H
