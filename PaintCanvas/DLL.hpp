#pragma once

#ifndef DLL_HPP
#define DLL_HPP

#include <string>
#include <windows.h>

#include <exception>
using std::exception;

#include <cstdint>
using std::uint64_t;

#include <functional>

class DLLException final : private exception {
public:

	enum class Code : uint64_t {

		SUCCESS = 0,
		LOADLIBRARYERROR,
		GETFUNCTIONERROR,
		DLLNAMESETYET,
		NOSETNAME

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

	explicit DLL(std::string&& dll_name)noexcept :
		hModule_{ NULL },
		name_{ dll_name } { }

	explicit DLL()noexcept :
		DLL{ std::string{ } } {}

	DLL(DLL&& move_dll)noexcept :
		DLL{ std::string{} } {

		std::swap(name_, move_dll.name_);
		std::swap(hModule_, move_dll.hModule_);

	}

	explicit DLL(const DLL& copy_dll)noexcept = delete;
	DLL& operator=(const DLL& copy_dll)noexcept = delete;

	DLL& operator=(DLL&& move_dll)noexcept {

		if (&move_dll == this)return *this;

		std::swap(name_, move_dll.name_);
		std::swap(hModule_, move_dll.hModule_);

		return *this;

	}

	void Load() {

		if (name_.empty())
			throw DLLException{ DLLException::Code::NOSETNAME };

		hModule_ = LoadLibraryA(name_.c_str());

		if (!hModule_)throw
			DLLException{ DLLException::Code::LOADLIBRARYERROR };

	}

	void Load(std::string&& dll_name) {

		if (!name_.empty())
			throw DLLException{ DLLException::Code::DLLNAMESETYET };

		name_ = std::move(dll_name);

		Load();

	}

	bool Loaded()const noexcept { return hModule_; }

	FARPROC GetFunction(const std::string& function_name) {

		if (!hModule_)
			throw DLLException{ DLLException::Code::GETFUNCTIONERROR };

		const FARPROC address = GetProcAddress(hModule_, function_name.c_str());

		if (!address)
			throw DLLException{ DLLException::Code::GETFUNCTIONERROR };

		return address;

	}

	void Unload()noexcept {

		//Dll was loaded
		if(hModule_)
			FreeLibrary(hModule_);

	}

};

//Цекада 3301 для хакера

#endif //DLL_HPP