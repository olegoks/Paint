#pragma once
#include <filesystem>
#include <windows.h>

#include <FormTypes.hpp>

using FileDialogException = ComponentException;

class EXPIMP FileDialog final{
private:

	OPENFILENAME init_struct_;
	std::filesystem::path file_path_ = L"";
	std::wstring file_name_ = L"";

public:

	explicit FileDialog()noexcept;
	void FindFile(const HWND parent_hWnd);
	std::filesystem::path GetPath()const noexcept;
	std::wstring GetName()const noexcept;

};