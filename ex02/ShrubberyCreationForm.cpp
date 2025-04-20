//
// Created by Emil Ebert on 18.04.25.
//

#include "ShrubberyCreationForm.h"
#include <fstream>
#include <iostream>
#include "colors.h"
#include <random>
#include <filesystem>


ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137),
                                                                  target(std::move(target)), height(10),
                                                                  trunkHeight(3) {
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target, int height,
                                             int trunkHeight): AForm("ShrubberyCreationForm", 145, 137),
                                                               target(std::move(target)),
                                                               height(height),
                                                               trunkHeight(trunkHeight) {
    if (height < 3 || trunkHeight < 1) {
        throw TreeToSmall();
    }
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other): AForm(other) {
    *this = other;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
    if (this != &other) {
        AForm::operator=(other);
        target = other.target;
        height = other.height;
        trunkHeight = other.trunkHeight;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const {
    executionGuard(executor);
    const std::string fileName = target + "_shrubbery";

    if (std::filesystem::exists(fileName)) {
        std::cout << ORANGE << "File already exists, overwriting..." << RESET << std::endl;

        if (!std::filesystem::is_regular_file(fileName)) {
            throw std::ios_base::failure("There is already an directory with the same name");
        }
    }

    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file");
    }

    if (!file.good()) {
        throw std::ios_base::failure("Failed to write to file");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> decoDist(1, 10);
    std::uniform_int_distribution<> decoTypeDist(0, 3);

    const char decorations[4] = {'O', '@', 'o', '+'};

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height - i - 1; j++) {
            file << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            if (i == 0)
                file << "^";
            else if (j == 0)
                file << "/";
            else if (j == 2 * i)
                file << "\\";
            else if (decoDist(gen) == 1)
                file << decorations[decoTypeDist(gen)];
            else
                file << "*";
        }
        file << "\n";
    }

    for (int i = 0; i < trunkHeight; i++) {
        for (int j = 0; j < height - 2; j++) {
            file << " ";
        }
        file << "|||";
        file << "\n";
    }

    for (int i = 0; i < 2 * height - 1; i++) {
        file << "\"";
    }
    file << "\n";

    file.close();
    std::cout << GREEN << "Shrubbery created in file " << fileName << RESET << std::endl;
    hasExecuted = true;
}

const char *ShrubberyCreationForm::TreeToSmall::what() const throw() {
    return "The dimensions of the tree are too small, the height must be at least 3 and the trunk height must be at least 1.";
}
