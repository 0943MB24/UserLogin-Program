#pragma once

#include <string>

// Function prototype for a simple hashing function
// Simulates SHA-256 behavior (not cryptographically secure)
// Takes a string input and returns a hexadecimal string as the "hashed" output
std::string sha256(const std::string& input);