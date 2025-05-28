#ifndef PERSON_H
#define PERSON_H

class Person {
    std::string name{};
    int32_t salary{};

public:
    Person() = default;

    Person(std::string name, const int32_t &salary) : name(std::move(name)), salary(salary) {
    }

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] int32_t get_salary() const {
        return salary;
    }

    void set_name(const std::string &name) {
        this->name = name;
    }

    void set_salary(const int32_t &salary) {
        this->salary = salary;
    }
};

#endif //PERSON_H
