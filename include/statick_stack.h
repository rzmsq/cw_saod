#ifndef STATICK_STACK_H
#define STATICK_STACK_H


// стек на основе статического выделения памяти
template<typename T>
class Static_stack {
    // индекс вершины стека
    int32_t top{my_var_and_const::stack_empty};
    // массив-стек
    T data[my_var_and_const::max_size_stack];

    [[nodiscard]] bool is_empty() const {
        return top == my_var_and_const::stack_empty;
    }

    [[nodiscard]] bool is_full() const {
        return top == my_var_and_const::max_size_stack - 1;
    }

    // поиск индекса элемента
    int32_t find(const std::string &name) {
        for (int32_t i = 0; i < my_var_and_const::max_size_stack; ++i) {
            if (data[i].get_name() == name) {
                return i;
            }
        }
        return my_var_and_const::el_not_found;
    }

public:
    // Добавление в стек
    void push(const T &new_data) {
        if (is_full()) {
            std::cerr << "Ошибка добавления\n";
            return;
        }

        ++top;
        if (top < my_var_and_const::max_size_stack) {
            data[top] = new_data;
        }
    }

    // Удаление из стека
    void delete_el(const std::string &name) {
        if (is_empty()) {
            std::cerr << "Ошибка удаления\n";
            return;
        }
        const int32_t index = find(name);
        if (index != my_var_and_const::el_not_found) {
            if (index != top) {
                data[index] = data[top];
            }
            data[top] = T();
            --top;
        } else {
            throw std::runtime_error("Элемент не найден");
        }
    }

    // поиск заданного элемента
    T &find_el(const std::string &name) {
        const int32_t index = find(name);
        if (index != my_var_and_const::el_not_found) {
            return data[index];
        }
        throw std::runtime_error("Элемент не найден");
    }

    // Обработка каждого элемента стека переданной функцией
    template<typename Func>
    void for_each(Func func) const {
        for (int32_t i = 0; i <= top; ++i) {
            func(data[i]);
        }
    }
};

#endif //STATICK_STACK_H
