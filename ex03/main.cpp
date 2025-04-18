#include <iostream>
#include "Bureaucrat.h"
#include "AForm.h"
#include "colors.h"
#include "Intern.h"
#include "ShrubberyCreationForm.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"

int main() {
    try {
        std::cout << BOLD << CYAN << "\n=== Creating Bureaucrats ===" << RESET << std::endl;
        Bureaucrat intern("Intern", 150);
        Bureaucrat clerk("Clerk", 140);
        Bureaucrat manager("Manager", 70);
        Bureaucrat executive("Executive", 20);
        Bureaucrat president("President", 1);

        std::cout << YELLOW << intern << RESET << std::endl;
        std::cout << YELLOW << clerk << RESET << std::endl;
        std::cout << YELLOW << manager << RESET << std::endl;
        std::cout << YELLOW << executive << RESET << std::endl;
        std::cout << YELLOW << president << RESET << std::endl;

        // Test ShrubberyCreationForm (sign: 145, exec: 137)
        std::cout << BOLD << CYAN << "\n=== Testing ShrubberyCreationForm ===" << RESET << std::endl;
        ShrubberyCreationForm shrub("garden", 10, 3);
        std::cout << MAGENTA << shrub << RESET << std::endl;

        intern.signForm(shrub);      // Should fail (grade 150 > 145)
        clerk.signForm(shrub);       // Should succeed (grade 140 < 145)

        intern.executeForm(shrub);   // Should fail (grade 150 > 137)
        clerk.executeForm(shrub);    // Should succeed (grade 140 < 137)

        // Test RobotomyRequestForm (sign: 72, exec: 45)
        std::cout << BOLD << CYAN << "\n=== Testing RobotomyRequestForm ===" << RESET << std::endl;
        RobotomyRequestForm robotomy("Marvin");
        std::cout << MAGENTA << robotomy << RESET << std::endl;

        clerk.signForm(robotomy);    // Should fail (grade 140 > 72)
        manager.signForm(robotomy);  // Should succeed (grade 70 < 72)

        manager.executeForm(robotomy); // Should fail (grade 70 > 45)
        executive.executeForm(robotomy); // Should succeed (grade 20 < 45)

        // Test multiple robotomies to show 50% success rate
                std::cout << BOLD << ORANGE << "\n=== Multiple Robotomy Attempts ===" << RESET << std::endl;
        for (int i = 0; i < 5; i++) {
            RobotomyRequestForm robotomy("Subject-" + std::to_string(i+1));
            executive.signForm(robotomy);
            executive.executeForm(robotomy);
        }

        // Test PresidentialPardonForm (sign: 25, exec: 5)
        std::cout << BOLD << CYAN << "\n=== Testing PresidentialPardonForm ===" << RESET << std::endl;
        PresidentialPardonForm pardon("Arthur Dent");
        std::cout << MAGENTA << pardon << RESET << std::endl;

        manager.signForm(pardon);     // Should fail (grade 70 > 25)
        executive.signForm(pardon);   // Should succeed (grade 20 < 25)

        executive.executeForm(pardon); // Should fail (grade 20 > 5)
        president.executeForm(pardon); // Should succeed (grade 1 < 5)

        // Test re-execution
        std::cout << BOLD << CYAN << "\n=== Testing Re-Execution ===" << RESET << std::endl;
        president.executeForm(pardon); // Should fail (already executed)

        // Test when form is not signed
        std::cout << BOLD << CYAN << "\n=== Testing Unsigned Form ===" << RESET << std::endl;
        PresidentialPardonForm unsignedPardon("Zaphod");
        president.executeForm(unsignedPardon); // Should fail (not signed)

        // Test Intern class
        std::cout << BOLD << CYAN << "\n=== Testing Intern Class ===" << RESET << std::endl;
        Intern someRandomIntern;

        // Test creating each form type
        std::cout << BOLD << ORANGE << "\n--- Creating Valid Forms ---" << RESET << std::endl;
        AForm* shrubForm = someRandomIntern.makeForm("shrubbery creation", "Backyard");
        AForm* robotForm = someRandomIntern.makeForm("robotomy request", "Bender");
        AForm* pardonForm = someRandomIntern.makeForm("presidential pardon", "Ford Prefect");

        if (shrubForm && robotForm && pardonForm) {
            // Print form info
            std::cout << MAGENTA << *shrubForm << RESET << std::endl;
            std::cout << MAGENTA << *robotForm << RESET << std::endl;
            std::cout << MAGENTA << *pardonForm << RESET << std::endl;

            // Test that forms can be signed and executed
            std::cout << BOLD << ORANGE << "\n--- Using Intern-Created Forms ---" << RESET << std::endl;
            clerk.signForm(*shrubForm);
            clerk.executeForm(*shrubForm);

            executive.signForm(*robotForm);
            executive.executeForm(*robotForm);

            president.signForm(*pardonForm);
            president.executeForm(*pardonForm);

            // Cleanup
            delete shrubForm;
            delete robotForm;
            delete pardonForm;
        }

        // Test creating an unknown form
        std::cout << BOLD << ORANGE << "\n--- Creating Invalid Form ---" << RESET << std::endl;
        AForm* unknownForm = someRandomIntern.makeForm("vacation request", "Employee");
        if (!unknownForm) {
            std::cout << YELLOW << "Successfully detected unknown form type" << RESET << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    return 0;
}