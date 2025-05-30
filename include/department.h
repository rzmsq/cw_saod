#ifndef DEPARTMENT_H
#define DEPARTMENT_H

// Класс описывающий отдел магазина
class Department {
    std::string name;
    Static_stack<Person> persons; // статичный стек менеджеров

public:
    // переопределение конструкторов
    Department() : name("Unknown") {
    }

    explicit Department(std::string name) : name(std::move(name)) {
    }

    // добавление менеджера
    void add_person(const std::string &name, const int32_t &salary) {
        persons.push(Person(name, salary));
    }

    // удаление менеджера
    void remove_person(const std::string &name) {
        persons.delete_el(name);
    }

    // поиск менеджера
    [[nodiscard]] Person &find_person(const std::string &name) {
        return persons.find_el(name);
    }

    // геттер поля имени
    [[nodiscard]] std::string get_name() const {
        return name;
    }

    // геттер стека сотрудников
    [[nodiscard]] const Static_stack<Person> &get_stack_persons() const {
        return persons;
    }

    // поэлементный итератор
    template <typename Func>
    void for_each_person(Func func) const {
        persons.for_each(func);
    }
};

#endif //DEPARTMENT_H
