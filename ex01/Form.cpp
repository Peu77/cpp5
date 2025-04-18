//
// Created by Emil Ebert on 18.04.25.
//

#include "Form.h"
#include "Bureaucrat.h"

#include <iostream>


Form::Form(const std::string &name, int signGrade, int executeGrade)
    : name(name), is_signed(false), signGrade(signGrade), executeGrade(executeGrade) {
    if (signGrade < 1 || executeGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || executeGrade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form &other)
    : name(other.name), is_signed(other.is_signed), signGrade(other.signGrade), executeGrade(other.executeGrade) {}

Form &Form::operator=(const Form &other) {
    if (this != &other) {
        is_signed = other.is_signed;
    }
    return *this;
}

Form::~Form() {}

const std::string &Form::getName() const {
    return name;
}

bool Form::isSigned() const {
    return is_signed;
}

int Form::getSignGrade() const {
    return signGrade;
}

int Form::getExecuteGrade() const {
    return executeGrade;
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > signGrade)
        throw GradeTooLowException();
    if (is_signed)
        throw AlreadySignedException();
    is_signed = true;
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
    os << "Form: " << form.getName() << ", Signed: " << (form.isSigned() ? "Yes" : "No")
       << ", Sign Grade: " << form.getSignGrade() << ", Execute Grade: " << form.getExecuteGrade();
    return os;
}

const char *Form::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char *Form::GradeTooLowException::what() const throw() {
    return "Grade is too low!";
}

const char *Form::AlreadySignedException::what() const throw() {
    return "Form is already signed!";
}