//
// Created by Emil Ebert on 18.04.25.
//

#include "Intern.h"

#include "PresidentialPardonForm.h"
#include "RobotomyRequestForm.h"
#include "ShrubberyCreationForm.h"

#include <iostream>
#include "colors.h"

std::array<std::pair<std::string, AForm *(*)(const std::string &)>, 3> Intern::formTypes = {
    std::make_pair("shrubbery creation", &Intern::createShrubberyCreationForm),
    std::make_pair("robotomy request", &Intern::createRobotomyRequestForm),
    std::make_pair("presidential pardon", &Intern::createPresidentialPardonForm)
};

Intern::Intern() {
}

Intern::Intern(const Intern &other) {
    *this = other;
}

Intern &Intern::operator=(const Intern &other) {
    if (this != &other) {
    }
    return *this;
}

Intern::~Intern() {
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target) const {
    for (const auto &formType: formTypes) {
        if (formType.first == formName)
            return formType.second(target);
    }
std::cerr << RED << "Intern: Form type '" << formName << "' not recognized." << RESET << std::endl;    return nullptr;
}

AForm *Intern::createShrubberyCreationForm(const std::string &target) {
    return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobotomyRequestForm(const std::string &target) {
    return new RobotomyRequestForm(target);
}

AForm *Intern::createPresidentialPardonForm(const std::string &target) {
    return new PresidentialPardonForm(target);
}
