#include "RobotomyRequestForm.h"
#include "Bureaucrat.h"
#include <random>
#include <iostream>

#include "colors.h"

RobotomyRequestForm::RobotomyRequestForm(std::string target): AForm("RobotomyRequestForm", 72, 45),
                                                              target(std::move(target)) {
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other): AForm(other) {
    *this = other;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
    if (this != &other) {
        AForm::operator=(other);
        target = other.target;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const {
    executionGuard(executor);

    std::cout << "* DRILLING NOISES * Brrr... Drrr... Zzzzzzt! *" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    if (dist(gen) == 1) {
        std::cout << GREEN << target << " has been robotomized successfully!" << RESET << std::endl;
    } else {
        std::cout << RED << "Robotomy failed on " << target << "." << RESET << std::endl;
    }

    hasExecuted = true;
}