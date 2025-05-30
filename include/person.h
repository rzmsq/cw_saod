#ifndef PERSON_H
#define PERSON_H

// Класс описывающий человека-сотрудника
class Person {
    std::string name{};
    int32_t salary{};

public:
    // переопределение конструкторов
    Person() = default;

    Person(std::string name, const int32_t &salary) : name(std::move(name)), salary(salary) {
    }

    // геттер поля имени
    [[nodiscard]] std::string get_name() const {
        return name;
    }

    // геттер поля зп
    [[nodiscard]] int32_t get_salary() const {
        return salary;
    }

    // сеттер поля имени
    void set_name(const std::string &name) {
        this->name = name;
    }

    // сеттер поля зп
    void set_salary(const int32_t &salary) {
        this->salary = salary;
    }
};

#endif //PERSON_H
