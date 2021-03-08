#pragma once

#ifndef COMPONENTEXCEPTION_HPP
#define COMPONENTEXCEPTION_HPP

#include <exception>
#include <string>

class ComponentException final : protected std::exception {
private:

	std::string message_;

public:

	explicit ComponentException(std::string&& message)noexcept;

	explicit ComponentException(const std::string& message)noexcept;

	const std::string& What()const noexcept;

};

#endif //COMPONENTEXCEPTION_HPP