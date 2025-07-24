#include "PassStrChecker.h"
#include <cctype> // Necessary for character checking functions like islower, isupper, etc.

// Constructor initializes the password string
PasswordChecker::PasswordChecker(const std::string& pwd) : password(pwd) {}

// Checks if the password contains at least one lowercase letter
bool PasswordChecker::hasLower() const {
	for (char ch : password)
		if (std::islower(ch)) return true;
	return false;
}

// Checks if the password contains at least one uppercase letter
bool PasswordChecker::hasUpper() const {
	for (char ch : password)
		if (std::isupper(ch)) return true;
	return false;

}

// Checks if the password contains at least one digit letter
bool PasswordChecker::hasDigit() const {
	for (char ch : password)
		if (std::isdigit(ch)) return true;
	return false;
}

// Checks if the password contains non-alphanumerics characters except for unlisted characters.
// (e.g. spaces ' ', tab '\t', and '\n', emojis, etc.
bool PasswordChecker::hasSpecial() const {
	std::string specialChars = "!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?`~";
	for (char ch : password)
		if (specialChars.find(ch) != std::string::npos) 
			return true;
	return false;
}

// Checks if the password contains any invalid characters like whitespace
bool PasswordChecker::hasInvalidCharacters() const {
	for (char ch : password) {
		// std::isspace() returns true for space, tab, newline, etc.
		if (std::isspace(static_cast<unsigned char>(ch))) {
			return true;
		}
		// Optionally blocks non-printable or extended characters
		if (!std::isprint(static_cast<unsigned char>(ch))) {
			return true;
		}
	}
	return false;
}

// Evaluates the overall strength of the password based on content and length
std::string PasswordChecker::checkStrength() const {
	int score = hasLower() + hasUpper() + hasDigit() + hasSpecial(); // Total number of conditions met

	if (password.length() < 8) {
		return "Very Weak (Password is too short)";

	} else if (score == 1) {
		return "Weak";

	} else if (score == 2) {
		return "Moderate";

	} else if (score == 3) {
		return "Strong";

	} else {
		return "Very Strong";
	}
}