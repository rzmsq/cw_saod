#ifndef DEPARTMENT_H
#define DEPARTMENT_H

class Department {
    std::string name;
    Static_stack<Person> persons;

public:
    Department() : name("Unknown") {
    }

    explicit Department(std::string name) : name(std::move(name)) {
    }

    void add_person(const std::string &name, const int32_t &salary) {
        persons.push(Person(name, salary));
    }

    void remove_person(const std::string &name) {
        persons.delete_el(name);
    }

    [[nodiscard]] Person &find_person(const std::string &name) {
        return persons.find_el(name);
    }

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] const Static_stack<Person> &get_stack_persons() const {
        return persons;
    }

    template <typename Func>
    void for_each_person(Func func) const {
        persons.for_each(func);
    }
};

#endif //DEPARTMENT_H
