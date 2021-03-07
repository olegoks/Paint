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
		GETFUNCTIONERROR

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

	explicit DLL(std::string&& dll_name)noexcept:
		hModule_{ NULL },
		name_{ dll_name }
		{ }

	void Load() {

		hModule_ = LoadLibraryA(name_.c_str());
		DWORD error = GetLastError();
		if (!hModule_)throw 
			DLLException{ DLLException::Code::LOADLIBRARYERROR };

	}

	
	FARPROC GetFunction(const char* const function_name) {
		
		const FARPROC address = GetProcAddress(hModule_, function_name);
		DWORD error = GetLastError();

		if (!address)throw 
			DLLException{ DLLException::Code::GETFUNCTIONERROR };
		
		return address;

	}

	void Unload() {

		FreeLibrary(hModule_);

	}

};

//Цекада 3301 для хакера

#endif //DLL_HPP