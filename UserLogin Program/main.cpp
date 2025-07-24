#include <iostream>
#include <string>
#include "PassStrChecker.h" // Header for password strength checker
#include "LoginSystem.h" // header for registration/login system

int main() {
	LoginSystem system; // Creates an instance of the login system
	std::string username, password; // Stores user input for future logins
	int choice = 0; // Menu Selection Variable
	std::string input; // Raw input string for validation

	do {
		// Displays Menu
		std::cout << "- - - CIS25 Login System - - -\n\n";
		std::cout << "1. Register New User\n\n";
		std::cout << "2. Login Existing User\n\n";
		std::cout << "3. Exit\n\n";
		std::cout << "Please Select an Option\n\n";

		std::getline(std::cin, input); // Gets full user input (e.g., "1", "a", etc.) 
		choice = -1; // Resets choice before validation

		// Validates input to allow digits only
		if (input.find_first_not_of("0123456789") == std::string::npos && !input.empty()) {
			choice = std::stoi(input);  // Convert to number if valid
		}
		else {
			std::cout << "\nInvalid input. Please Enter a Number Between 1-3.\n\n";
			continue;  // Skips the rest of loop and re-displays the menu
		}

		switch (choice) {
		case 1: { // Registers a new user
			std::string errorMsg;

			// Loops until a unique username is entered
			do {
				std::cout << "\nEnter a Username: ";
				std::getline(std::cin, username);

				// Checks if username already exists
				if (system.usernameExists(username)) {
					std::cout << "\nUsername Taken. Try Again.\n";
				}
				else {
					break; // Username is available
				}
			} while (true);

			// Loops until password is strong and contains valid characters
			do {
				std::cout << "\nEnter a Password: ";
				std::getline(std::cin, password);

				errorMsg = system.registerUser(username, password); // Attempts registration and returns error message if any
				if (!errorMsg.empty()) {
					std::cout << "\n" << errorMsg << "\nTry again.\n"; // Displays reason for failure (e.g., weak password)
				}
			} while (!errorMsg.empty());

			std::cout << "\nRegistration Successful!";
			break;
		}

		case 2: // Login for existing users
			std::cout << "\nEnter Your Username: ";
			std::getline(std::cin, username);
			std::cout << "\nEnter Your Password: ";
			std::getline(std::cin, password);

			// Attempts to log in using given info
			if (system.loginUser(username, password)) {
				std::cout << "\nLogin Successful. Demo Complete!\n\n";

			}
			else {
				std::cout << "\nLogin Failed. Username or Password is Incorrect\n\n";
			}
			break;

		case 3: // Exit option
			std::cout << "\nExiting System..\n";
			break;

		default: // Catches numbers outside of the given option range
			std::cout << "\nInvalid Option Selected. Try Again.\n\n";
		}

	} while (choice != 3); // Repeats menu display until user chooses to exit 

	return 0;
}