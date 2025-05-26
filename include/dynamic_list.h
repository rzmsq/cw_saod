//
// Created by rzms on 23.05.25.
//

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

// динамический упорядоченный двунаправленный список
template<typename T>
class Dynamic_list {
    struct Node {
        Node *next, *prev;
        T data;

        Node(): next(nullptr), prev(nullptr) {
            data = T();
        }

        explicit Node(const std::string &name) {
            next = prev = nullptr;
            data = T(name);
        }
    };

    Node *head = nullptr;

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

        // вставка в начало
        if (!current || new_node->data.get_name() < current->data.get_name()) {
            new_node->next = current;
            new_node->prev = head;
            if (current) {
                current->prev = new_node;
            }
            head->next = new_node;
            return;
        }


        // поиск позиции для вставки
        while (current->next && current->data.get_name() < new_node->data.get_name()) {
            current = current->next;
        }

        if (current->data.get_name() < new_node->data.get_name()) {
            // вставка между current и current->next
            new_node->next = current->next;
            new_node->prev = current;
            if (current->next) {
                current->next->prev = new_node;
            }
            current->next = new_node;
        } else {
            // вставка перед current
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
        }
    }

    // поиска заданного узла
    [[nodiscard]] Node *search(const std::string &name) const {
        Node *current = head->next;
        while (current && current->data.get_name() != name) {
            current = current->next;
        }
        return current;
    }

    // удаление заданного узла
    [[nodiscard]] std::string delete_element(const std::string &name) {
        if (const Node *node_for_del = search(name)) {
            node_for_del->prev->next = node_for_del->next;
            if (node_for_del->next) {
                node_for_del->next->prev = node_for_del->prev;
            }
            const std::string name_deleted = node_for_del->data.get_name();
            delete node_for_del;
            return name_deleted;
        }
        return "";
    }

    // вывод узлов
    void print_nodes() const {
        const Node *current = head->next;
        while (current) {
            std::cout << current->data.get_name() << "\n";
            current = current->next;
        }
    }
};

#endif //DYNAMIC_LIST_H
