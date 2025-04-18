//
// Created by Emil Ebert on 18.04.25.
//

#ifndef SHRUBBERYCREATIONFORM_H
#define SHRUBBERYCREATIONFORM_H

#include "AForm.h"

class ShrubberyCreationForm: public AForm {
private:
    std::string target;
    int height;
    int trunkHeight;

public:
    ShrubberyCreationForm(std::string target);
    ShrubberyCreationForm(std::string target, int height, int trunkHeight);
    ShrubberyCreationForm(const ShrubberyCreationForm &other);
    ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
    ~ShrubberyCreationForm();

    void execute(const Bureaucrat &executor) const override;

    class TreeToSmall: public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};



#endif //SHRUBBERYCREATIONFORM_H
