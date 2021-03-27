#include <ComponentException.hpp>

ComponentException::ComponentException(std::string&& message)noexcept:
	std::exception{ },
	message_{ std::move(message) } {



}

ComponentException::ComponentException(const std::string& message)noexcept:
	std::exception{},
	message_{ message }{


}

const std::string& ComponentException::What()const noexcept(true) { return message_; };