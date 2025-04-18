//
// Created by Emil Ebert on 18.04.25.
//

#ifndef FORM_H
#define FORM_H

#include <string>

class Bureaucrat;

class Form {
private:
    const std::string name;
    bool is_signed;
    const int signGrade;
    const int executeGrade;

public:
    Form(const std::string &name, int signGrade, int executeGrade);

    Form(const Form &other);

    Form &operator=(const Form &other);

    ~Form();

    const std::string &getName() const;

    bool isSigned() const;

    int getSignGrade() const;

    int getExecuteGrade() const;

    void beSigned(const Bureaucrat &bureaucrat);

    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

    class AlreadySignedException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, Form const &form);

#endif //FORM_H
