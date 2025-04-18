//
// Created by Emil Ebert on 18.04.25.
//

#include "AForm.h"
#include "Bureaucrat.h"

#include <iostream>


AForm::AForm(const std::string &name, int signGrade, int executeGrade)
    : name(name), hasSigned(false), signGrade(signGrade), executeGrade(executeGrade), hasExecuted(false) {
    if (signGrade < 1 || executeGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || executeGrade > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
    : name(other.name), hasSigned(other.hasSigned), signGrade(other.signGrade), executeGrade(other.executeGrade), hasExecuted(false) {}

AForm &AForm::operator=(const AForm &other) {
    if (this != &other) {
        hasSigned = other.hasSigned;
    }
    return *this;
}

AForm::~AForm() {}

const std::string &AForm::getName() const {
    return name;
}

bool AForm::isSigned() const {
    return hasSigned;
}

int AForm::getSignGrade() const {
    return signGrade;
}

int AForm::getExecuteGrade() const {
    return executeGrade;
}

void AForm::executionGuard(const Bureaucrat &bureaucrat) const {
    if (bureaucrat.getGrade() > executeGrade)
        throw GradeTooLowException();
    if (!hasSigned)
        throw NotSignedException();
    if (hasExecuted)
        throw AlreadyExecutedException();
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > signGrade)
        throw GradeTooLowException();
    if (hasSigned)
        throw AlreadySignedException();
    hasSigned = true;
}

std::ostream &operator<<(std::ostream &os, const AForm &form) {
    os << "Form: " << form.getName() << ", Signed: " << (form.isSigned() ? "Yes" : "No")
       << ", Sign Grade: " << form.getSignGrade() << ", Execute Grade: " << form.getExecuteGrade();
    return os;
}

const char *AForm::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char *AForm::GradeTooLowException::what() const throw() {
    return "Grade is too low!";
}

const char *AForm::AlreadySignedException::what() const throw() {
    return "Form is already signed!";
}

const char *AForm::NotSignedException::what() const throw() {
    return "Form is not signed!";
}

const char *AForm::AlreadyExecutedException::what() const throw() {
    return "Form was already executed!";
}
