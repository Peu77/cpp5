//
// Created by Emil Ebert on 18.04.25.
//

#ifndef BUREAUCRAT_H
#define BUREAUCRAT_H

#include <string>
#include <exception>

#include "Form.h"

class Bureaucrat {
  private:
    const std::string name;
    int grade;

  public:
    Bureaucrat(const std::string &name, int grade);
    Bureaucrat(const Bureaucrat &other);
    Bureaucrat &operator=(const Bureaucrat &other);
    ~Bureaucrat();

    void signForm(Form &form) const;

    const std::string &getName() const;
    int getGrade() const;
    void incrementGrade();
    void decrementGrade();

  class GradeTooHighException : public std::exception
  {
  public:
    virtual const char *what() const throw();
  };

  class GradeTooLowException : public std::exception
  {
  public:
    virtual const char *what() const throw();
  };
};

std::ostream &operator<<(std::ostream & os, Bureaucrat const &bureaucrat);




#endif //BUREAUCRAT_H
