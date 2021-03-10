#pragma once

#ifndef COMPONENTEXCEPTION_HPP
#define COMPONENTEXCEPTION_HPP

#include <FormTypes.hpp>
#include <exception>
#include <string>

#pragma warning( disable: 4251 )
class EXPIMP std::exception;

class EXPIMP ComponentException final : protected std::exception {
private:

	std::string message_;

public:

	explicit ComponentException(const ComponentException& copy_exception)noexcept = delete;
	explicit ComponentException(ComponentException&& move_exception)noexcept = default;

	ComponentException& operator=(ComponentException && move_exception)noexcept = default;
	ComponentException& operator=(const ComponentException & copy_exception)noexcept = delete;

	~ComponentException()noexcept = default;

	explicit ComponentException(std::string&& message)noexcept;
	explicit ComponentException(const std::string& message)noexcept;
	const std::string& What()const noexcept;

};

#endif //COMPONENTEXCEPTION_HPP