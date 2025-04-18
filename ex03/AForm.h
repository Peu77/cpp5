//
// Created by Emil Ebert on 18.04.25.
//

#ifndef FORM_H
#define FORM_H

#include <string>

class Bureaucrat;

class AForm {
private:
    const std::string name;
    bool hasSigned;
    const int signGrade;
    const int executeGrade;

protected:
    mutable bool hasExecuted;

public:
    AForm(const std::string &name, int signGrade, int executeGrade);

    AForm(const AForm &other);

    AForm &operator=(const AForm &other);

    virtual ~AForm();

    void executionGuard(const Bureaucrat &bureaucrat) const;

    virtual void execute(const Bureaucrat &executor) const = 0;

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

    class NotSignedException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

    class AlreadyExecutedException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, AForm const &form);

#endif //FORM_H
