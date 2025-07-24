#pragma once

#include <string>

// The LoginSystem class handles user registration and login functionality.
// It performs tasks such as checking username availability and validating password
// strength using PassStrChecker, then securely hashes passwords with SHA-256.
class LoginSystem {
public:
	// Registers a new user with a given username and password.
	// Performs validation for username uniqueness and password strength,
	// then stores the username and a hashed password in users.txt.
	std::string registerUser(const std::string& username, const std::string& password);

	// Logs in an existing user by checking the given username and password.
	// Returns true if the username exists and the hashed password matches
	// what's stored in users.txt; false otherwise.
	bool loginUser(const std::string& username, const std::string& password);

	bool usernameExists(const std::string& username) const;
};