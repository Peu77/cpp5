//
// Created by Emil Ebert on 18.04.25.
//

#ifndef ROBOTOMYREQUESTFORM_H
#define ROBOTOMYREQUESTFORM_H

#include "AForm.h"

class RobotomyRequestForm: public AForm {
private:
    std::string target;

public:
    RobotomyRequestForm(std::string target);
    RobotomyRequestForm(const RobotomyRequestForm &other);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
    ~RobotomyRequestForm();

    void execute(const Bureaucrat &executor) const override;
};



#endif //SHRUBBERYCREATIONFORM_H
