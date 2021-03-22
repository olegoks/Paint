#pragma once

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : protected std::exception {
private:

	std::string message_;

public:

	explicit Exception(const Exception& copy_exception)noexcept = delete;
	explicit Exception(Exception&& move_exception)noexcept = default;

	Exception& operator=(Exception&& move_exception)noexcept = default;
	Exception& operator=(const Exception& copy_exception)noexcept = delete;

	~Exception()noexcept = default;

	explicit Exception(std::string&& message)noexcept :
		message_{ message } { }

	explicit Exception(const std::string& message)noexcept :
		message_{ message } { }

	const std::string& What()const noexcept { return message_; }

};

#endif //EXCEPTION_HPP