//
// Created by Emil Ebert on 18.04.25.
//

#ifndef INTERN_H
#define INTERN_H
#include <array>
#include "AForm.h"


class Intern {
private:
    static std::array<std::pair<std::string, AForm *(*)(const std::string &)>, 3> formTypes;

public:
    Intern();

    Intern(const Intern &other);

    Intern &operator=(const Intern &other);

    ~Intern();

    AForm *makeForm(const std::string &formName, const std::string &target) const;

private:
    static AForm *createShrubberyCreationForm(const std::string &target);
    static AForm *createRobotomyRequestForm(const std::string &target);
    static AForm *createPresidentialPardonForm(const std::string &target);
};


#endif //INTERN_H
