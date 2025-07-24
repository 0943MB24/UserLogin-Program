#include "sha256Hash.h"
#include <string>
#include <functional>
#include <sstream>

// This function simulates hashing a string using std::hash,
// and returns the result as a hexadecimal string.
// Because it is only a simulation of hashing and not a real SHA-256 Implementation,
// it's unsuitable for real usage as it lacks security.

std::string sha256(const std::string& input) {
	// std::hash generates a size_t hash value for the given string
	std::hash<std::string> hasher;
	size_t hashValue = hasher(input);

	// Convert the numerical hash value to a hexadecimal string
	std::ostringstream oss;
	oss << std::hex << hashValue;

	// Return the hex string as the "hashed" result
	return oss.str();
}