#pragma once
#ifndef WINDOW_TYPES_HPP
#define WINDOW_TYPES_HPP

#include <windows.h>
#include <Windowsx.h>
#include <functional>
#include <exception>

#define CALLBACK __stdcall

#define COMPILING_DLL

#ifdef COMPILING_DLL
#define EXPIMP __declspec(dllexport)
#else
#define EXPIMP __declspec(dllimport)
#endif

#include <ComponentException.hpp>
#include <Message.hpp>

#endif //WINDOW_TYPES_HPP