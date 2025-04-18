//
// Created by Emil Ebert on 18.04.25.
//

#include "Bureaucrat.h"
#include "colors.h"

#include <iostream>

Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name), grade(grade) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : name(other.name), grade(other.grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
    if (this != &other) {
        this->grade = other.grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {}

void Bureaucrat::signForm(AForm &form) const {
    try {
        form.beSigned(*this);
        std::cout << GREEN << name << " signed " << form.getName() << RESET << std::endl;
    } catch (const std::exception &e) {
        std::cerr << RED << name << " couldn't sign " << form.getName() << " because " << e.what() << RESET << std::endl;
    }
}

void  Bureaucrat::executeForm(AForm const & form) const {
    try {
        form.execute(*this);
        std::cout << GREEN << name << " executed " << form.getName() << RESET << std::endl;
    } catch (const std::exception&e) {
        std::cerr << RED << name << " couldn't execute " << form.getName() << " because " << e.what() << RESET << std::endl;
    }
}

const std::string& Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

void Bureaucrat::incrementGrade() {
    if (grade <= 1)
        throw GradeTooHighException();
    grade--;
}

void Bureaucrat::decrementGrade() {
    if (grade >= 150)
        throw GradeTooLowException();
    grade++;
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat) {
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
    return os;
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade too high!";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade too low!";
}
