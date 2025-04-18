#include <iostream>
#include "Bureaucrat.h"
#include "colors.h"

int main() {
    try {
        Bureaucrat b1("Alice", 1);
        std::cout << b1 << std::endl;

        b1.incrementGrade(); // Should throw GradeTooHighException
    } catch (const std::exception &e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    try {
        Bureaucrat b2("Bob", 150);
        std::cout << b2 << std::endl;

        b2.decrementGrade(); // Should throw GradeTooLowException
    } catch (const std::exception &e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    try {
        Bureaucrat b3("Charlie", 75);
        std::cout << b3 << std::endl;

        b3.incrementGrade();
        std::cout << GREEN << "After increment: " << b3 << RESET << std::endl;

        b3.decrementGrade();
        std::cout << GREEN << "After decrement: " << b3 << RESET << std::endl;
    } catch (const std::exception &e) {
        std::cerr << RED << "Exception: " << e.what() << RESET << std::endl;
    }

    return 0;
}