#include "LoginSystem.h"
#include "PassStrChecker.h"
#include "sha256Hash.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string LoginSystem::registerUser(const std::string& username, const std::string& password) {
    // Opens users.txt to check if username is taken
    std::ifstream infile("users.txt");
    if (!infile) {
        return "Failed to open users.txt for reading.";
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string storedUser, storedHash;
        if (iss >> storedUser >> storedHash) {
            if (storedUser == username) {
                return "Username is already taken.";
            }
        }
    }
    infile.close();

    // Class for password strength check
    PasswordChecker checker(password);

    // Checks if the password meets minimum length requirement
    if (password.length() < 8) {
        return "Password must be at least 8 characters long.";
    }

    // Checks if the password contains any invalid characters (e.g., whitespace, tabs, non-printables)
    if (checker.hasInvalidCharacters()) {
        return "Password contains invalid characters (spaces, tabs, or non-printable characters).";
    }

    // Explicitly checks for required character classes
    if (!checker.hasLower()) {
        return "Password must contain at least one lowercase letter.";
    }
    if (!checker.hasUpper()) {
        return "Password must contain at least one uppercase letter.";
    }
    if (!checker.hasDigit()) {
        return "Password must contain at least one digit.";
    }
    if (!checker.hasSpecial()) {
        return "Password must contain at least one special character.";
    }

    // Evaluates overall password strength
    std::string strength = checker.checkStrength();

    // Rejects passwords that are too weak or only meet minimal conditions
    if (strength == "Weak" || strength == "Moderate") {
        return "Password is too weak: " + strength;
    }

    // Hashes the password
    std::string hashed = sha256(password);

    // Appends new user to users.txt
    std::ofstream outfile("users.txt", std::ios::app);
    if (!outfile) {
        return "Failed to open users.txt for writing.";
    }
    outfile << username << " " << hashed << "\n";
    outfile.close();

    // Returns empty string to indicate success
    return "";
}

// Attempts to log in an existing user, returns true on success
bool LoginSystem::loginUser(const std::string& username, const std::string& password) {
    std::ifstream infile("users.txt");
    if (!infile) {
        std::cerr << "Error opening users.txt for reading.\n";
        return false;
    }

    std::string hashed = sha256(password);
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string storedUser, storedHash;
        if (iss >> storedUser >> storedHash) {
            if (storedUser == username && storedHash == hashed) {
                return true; // Found matching user and password
            }
        }
    }
    return false; // No match found
}

// Checks if a username already exists in the file
bool LoginSystem::usernameExists(const std::string& username) const {
    std::ifstream infile("users.txt");
    if (!infile) {
        return false; // If file doesn't open, assume username doesn't exist
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string storedUser, storedHash;
        if (iss >> storedUser >> storedHash) {
            if (storedUser == username) {
                return true; // Username match found
            }
        }
    }
    return false; // No match found
}