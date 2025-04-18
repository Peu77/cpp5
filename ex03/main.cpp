#include <iostream>
#include "Bureaucrat.h"
#include "AForm.h"
#include "colors.h"
#include "ShrubberyCreationForm.h"

int main() {

    ShrubberyCreationForm form("home", 10, 3);
    Bureaucrat bureaucrat("John", 130);

    bureaucrat.signForm(form);
    bureaucrat.executeForm(form);

    return 0;
}
