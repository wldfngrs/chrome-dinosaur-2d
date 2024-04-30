#pragma once

#include <exception>
#include <sstream>
#include <string>

class Exception : public std::exception {
public:
	Exception() noexcept {}
	
	Exception(const std::string& errorMessage) noexcept {
		this->message = errorMessage;
	}
	
	~Exception() noexcept {}

	template <typename T>
	Exception& operator << (T value) noexcept {
		std::stringstream stream;
		stream << this->message << value;
		this->message = stream.str();
		return *this;
	}

	const char* what() const noexcept {
		return this->message.c_str();
	}

private:
	std::string message;
};