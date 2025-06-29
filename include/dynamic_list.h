#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

// динамический упорядоченный двунаправленный список
template<typename T>
class Dynamic_list {
    // узел, содержащий ссылку на следующий и предыдущий узел и саму информацию
    struct Node {
        Node *next, *prev;
        T data;

        // переопределение конструкторов структуры
        Node(): next(nullptr), prev(nullptr) {
            data = T();
        }

        explicit Node(const std::string &name) {
            next = prev = nullptr;
            data = T(name);
        }
    };

    // указатель головного элемента
    Node *head = nullptr;

    // поиска заданного узла
    [[nodiscard]] Node *search(const std::string &name) const {
        Node *current = head->next;
        while (current && current->data.get_name() != name) {
            current = current->next;
        }
        return current;
    }

public:
    Dynamic_list() {
        head = new Node();
    }

    // копирующий конструктор
    Dynamic_list(const Dynamic_list &other) {
        head = new Node();
        Node *current = head;
        Node *other_current = other.head->next;

        while (other_current) {
            current->next = new Node(other_current->data.get_name());
            current->next->prev = current;
            current = current->next;
            other_current = other_current->next;
        }
    }

    // оператор присваивания
    Dynamic_list &operator=(const Dynamic_list &other) {
        if (this != &other) {
            Node *current = head;
            while (current) {
                Node *temp = current->next;
                delete current;
                current = temp;
            }
            head = new Node();
            current = head;
            Node *other_current = other.head->next;

            while (other_current) {
                current->next = new Node(other_current->data.get_name());
                current->next->prev = current;
                current = current->next;
                other_current = other_current->next;
            }
        }
        return *this;
    }

    ~Dynamic_list() {
        Node *current = head;
        while (current) {
            Node *temp = current->next;
            delete current;
            current = temp;
        }
    }

    // вставка нового узла
    void insert_element(const std::string &name) {
        Node *new_node = new Node(name);
        Node *current = head->next;
        Node *prev = head;

        try {
            // Вставка в начало
            if (!current || new_node->data.get_name() < current->data.get_name()) {
                new_node->next = current;
                new_node->prev = head;
                if (current) {
                    current->prev = new_node;
                }
                head->next = new_node;
                return;
            }

            // Поиск позиции для вставки
            while (current && current->data.get_name() < new_node->data.get_name()) {
                prev = current;
                current = current->next;
            }

            // Вставка перед current (или в конец, если current == nullptr)
            new_node->next = current;
            new_node->prev = prev;
            prev->next = new_node;
            if (current) {
                current->prev = new_node;
            }
        } catch (...) {
            std::cerr << "Ошибка добавления отдела\n";
            delete new_node;
        }
    }

    // удаление заданного узла
    void delete_element(const std::string &name) {
        if (Node *node_for_del = search(name)) {
            node_for_del->prev->next = node_for_del->next;
            if (node_for_del->next) {
                node_for_del->next->prev = node_for_del->prev;
            }
            delete node_for_del;
        } else {
            throw std::runtime_error("Отдел не найден");
        }
    }

    // поиск заданного узла
    T &find_node(const std::string &name) const {
        if (Node *node_for_find = search(name)) {
            return node_for_find->data;
        }
        throw std::runtime_error("Отдел не найден");
    }

    // поэлементное применение переданной функции
    template<typename Func>
    void for_each(Func func) const {
        Node *current = head->next;
        while (current) {
            func(current->data);
            current = current->next;
        }
    }
};

#endif //DYNAMIC_LIST_H
