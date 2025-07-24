#pragma once

#include <string>

// Class for checking password strength and character composition
class PasswordChecker {
private:
	std::string password; // The password string to analyze

public:
	// Constructor to initialize the password to be checked
	PasswordChecker(const std::string& pwd);

	// Analyzes the overall strength of the password
	// Returns: "Very Weak", "Weak", "Moderate", "Strong", or "Very Strong"
	std::string checkStrength() const;

	// Checks if the password contains at least one lowercase letter
	bool hasLower() const;

	// Checks if the password contains at least one uppercase letter
	bool hasUpper() const;

	// Checks if the password contains at least one digit
	bool hasDigit() const;

	// Checks if the password contains at least one special character
	// (i.e., non-alphanumeric and printable)
	bool hasSpecial() const;

	// Checks for disallowed characters such as whitespace (e.g., space, tab, newline)
	// Returns true if any invalid characters are found
	bool hasInvalidCharacters() const;
};
