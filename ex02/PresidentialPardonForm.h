//
// Created by Emil Ebert on 18.04.25.
//

#ifndef PRESIDENTIALPARDONFORM_H
#define PRESIDENTIALPARDONFORM_H

#include "AForm.h"

class PresidentialPardonForm: public AForm {
  private:
    std::string target;

  public:
    PresidentialPardonForm(std::string target);
    PresidentialPardonForm(const PresidentialPardonForm &other);
    PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
    ~PresidentialPardonForm();

    void execute(const Bureaucrat &executor) const override;
};



#endif //PRESIDENTIALPARDONFORM_H
