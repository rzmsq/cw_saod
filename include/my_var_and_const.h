#ifndef MY_CONST_H
#define MY_CONST_H

#include <unordered_map>

// пространство имён для использования констант, переменных, перечислений
namespace my_var_and_const {
    constexpr size_t max_size_stack{16};
    constexpr int32_t stack_empty{-1};
    constexpr int32_t el_not_found{-1};
    const std::string menu_str = "\nВыберите действие:\n"
            "1 - Создать магазин\n"
            "2 - Добавить отдел\n"
            "3 - Удалить отдел\n"
            "4 - Добавить менеджера\n"
            "5 - Удалить менеджера\n"
            "6 - Найти отдел\n"
            "7 - Найти менеджера\n"
            "8 - Показать все отделы и менеджера\n"
            "9 - Удалить магазин\n"
            "10 - Загрузить данные из файла\n"
            "11 - Сохранить данные в файле\n"
            "0 - Выход\n";

    // операции допустимые пользователю
    enum class Operation {
        Create_new_magazine,
        Add_dep,
        Del_dep,
        Add_pers,
        Del_pers,
        Find_dep,
        Find_pers,
        Print_all,
        Del_mag,
        Load_file,
        Save_file,
        Exit,
    };

    inline std::unordered_map<std::string, Operation> operationMap = {
        {"1", Operation::Create_new_magazine},
        {"2", Operation::Add_dep},
        {"3", Operation::Del_dep},
        {"4", Operation::Add_pers},
        {"5", Operation::Del_pers},
        {"6", Operation::Find_dep},
        {"7", Operation::Find_pers},
        {"8", Operation::Print_all},
        {"9", Operation::Del_mag},
        {"10", Operation::Load_file},
        {"11", Operation::Save_file},
        {"0", Operation::Exit}
    };
}

#endif //MY_CONST_H
