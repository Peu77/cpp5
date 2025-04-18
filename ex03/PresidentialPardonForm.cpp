//
// Created by Emil Ebert on 18.04.25.
//

#include "PresidentialPardonForm.h"
#include <iostream>
#include "colors.h"

PresidentialPardonForm::PresidentialPardonForm(std::string target): AForm("PresidentialPardonForm", 25, 5),
                                                                    target(std::move(target)) {
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other): AForm(other) {
    *this = other;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
    if (this != &other) {
        AForm::operator=(other);
        target = other.target;
    }
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
}

void PresidentialPardonForm::execute(const Bureaucrat &executor) const {
    executionGuard(executor);
    std::cout << GREEN << target << " has been pardoned by Zaphod Beeblebrox." << RESET << std::endl;
    hasExecuted = true;
}
