//
// Created by rzms on 26.05.25.
//

#ifndef STATICK_STACK_H
#define STATICK_STACK_H

template<typename T>
class Static_stack {
    int32_t top{my_constants::stack_empty};
    T data[my_constants::max_size_stack];
    // struct Node {
    // int32_t top{0};
    // T data;

    // Node() {
    //     top++;
    //     data = T();
    // }
    //
    // explicit Node(const std::string &name) {
    //     top++;
    //     data = T(name);
    // }

    [[nodiscard]] bool is_empty() const {
        return top == my_constants::stack_empty;
    }

    [[nodiscard]] bool is_full() const {
        return top == my_constants::max_size_stack - 1;
    }

public:
    void push(const std::string &name) {
        if (is_full()) {
            std::cerr << "Ошибка добавления\n";
            return;
        }

        top++;
        if (top < my_constants::max_size_stack) {
            data[top] = T(name);
        }
    }

    void pop() {
        if (is_empty()) {
            std::cerr << "Ошибка удаления\n";
            return;
        }
        top--;
    }
};

#endif //STATICK_STACK_H
