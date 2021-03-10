#pragma once

#ifndef DLL_HPP
#define DLL_HPP

#include <string>
#include <winbase.h>

#include <exception>
using std::exception;

#include <cstdint>
using std::uint64_t;

#include <functional>

class DLLException final : private exception{
public:

	enum class Code : uint64_t {

		SUCCESS = 0,
		LOADLIBRARYERROR,
		GETFUNCTIONERROR,
		DLLNAMESETYET

	};

private:

	Code code_;

public:

	

	explicit DLLException(Code code)noexcept :
		exception::exception{},
		code_{ code } {};

	explicit DLLException()noexcept = delete;
	explicit DLLException(DLLException&& dll_exception) = delete;
	explicit DLLException(const DLLException& dll_exception) = default;

	DLLException& operator=(DLLException&& dll_exception) = delete;
	DLLException& operator=(const DLLException& dll_exception) = default;

	inline Code Code()noexcept { return code_; }

	~DLLException()noexcept = default;

};

class DLL final {
private:

	HMODULE  hModule_;
	std::string name_;

public:

	static const inline std::string extension{ u8".dll" };

	explicit DLL(std::string&& dll_name)noexcept:
		hModule_{ NULL },
		name_{ dll_name } { }

	explicit DLL()noexcept:
		DLL{ std::string{ } }{}

	void Load(std::string&& dll_name = std::string{ }) {

		if (!dll_name.empty() && !name_.empty())
			throw DLLException{ DLLException::Code::DLLNAMESETYET };

		name_ = std::move(dll_name);

		hModule_ = LoadLibraryA(name_.c_str());

		if (!hModule_)throw 
			DLLException{ DLLException::Code::LOADLIBRARYERROR };

	}

	FARPROC GetFunction(const std::string& function_name) {
		
		if (!hModule_)
			throw DLLException{ DLLException::Code::GETFUNCTIONERROR };

		const FARPROC address = GetProcAddress(hModule_, function_name.c_str());

		if (!address)
			throw DLLException{ DLLException::Code::GETFUNCTIONERROR };
		
		return address;

	}

	void Unload()noexcept {

		FreeLibrary(hModule_);

	}

};

//Цекада 3301 для хакера

#endif //DLL_HPP