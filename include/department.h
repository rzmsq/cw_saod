#pragma once
#include <utility>

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

class Department {
    std::string name;

public:
    Department() : name("Unknown") {}

    explicit Department(std::string name) : name(std::move(name)) {}



};

#endif //DEPARTMENT_H
