#include <iostream>
#include "Bureaucrat.h"
#include "Form.h"
#include "colors.h"

int main() {
    // Test Form creation and exceptions
    try {
        Form invalidForm1("Invalid", 0, 50);  // Should throw GradeTooHighException
    } catch (const std::exception& e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    try {
        Form invalidForm2("Invalid", 50, 151);  // Should throw GradeTooLowException
    } catch (const std::exception& e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    // Test valid Form creation and signing
    try {
        Bureaucrat highRank("Director", 1);
        Bureaucrat lowRank("Intern", 150);
        Form topSecret("Top Secret", 5, 3);

        std::cout << YELLOW << "Initial form state:" << RESET << std::endl;
        std::cout << topSecret << std::endl;

        // Test signing with low-rank bureaucrat
        std::cout << "\nTesting low-rank bureaucrat signing:" << std::endl;
        lowRank.signForm(topSecret);

        // Test signing with high-rank bureaucrat
        std::cout << "\nTesting high-rank bureaucrat signing:" << std::endl;
        highRank.signForm(topSecret);

        std::cout << YELLOW << "\nFinal form state:" << RESET << std::endl;
        std::cout << topSecret << std::endl;

        // Test copy constructor and assignment operator
        Form copyForm(topSecret);
        std::cout << YELLOW << "\nCopied form state:" << RESET << std::endl;
        std::cout << copyForm << std::endl;

        Form assignedForm("Empty", 10, 10);
        assignedForm = topSecret;
        std::cout << YELLOW << "\nAssigned form state:" << RESET << std::endl;
        std::cout << assignedForm << std::endl;

    } catch (const std::exception& e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    return 0;
}