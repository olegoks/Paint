#pragma once
#include <filesystem>
#include <windows.h>

#include <FormTypes.hpp>

using FileDialogException = ComponentException;

class EXPIMP std::filesystem::path;

class EXPIMP FileDialog final{
private:

	OPENFILENAME init_struct_;
	std::filesystem::path file_path_ = L"";
	std::wstring file_name_ = L"";

public:

	explicit FileDialog()noexcept;
	explicit FileDialog(const FileDialog& copy_dialog)noexcept = delete;
	explicit FileDialog(FileDialog&& move_dialog)noexcept = default;

	FileDialog& operator=(const FileDialog& copy_dialog)noexcept = delete;
	FileDialog& operator=(FileDialog&& move_dialog)noexcept = default;

	~FileDialog()noexcept = default;

	void FindFile(const HWND parent_hWnd);
	std::filesystem::path GetPath()const noexcept;
	std::wstring GetName()const noexcept;

};