#include "FileDialog.hpp"

FileDialog::FileDialog() noexcept{

	ZeroMemory(&init_struct_, sizeof(OPENFILENAME));

	init_struct_.lStructSize = sizeof(OPENFILENAME);
	init_struct_.hwndOwner = NULL;
	init_struct_.lpstrFilter = NULL;
	init_struct_.nFilterIndex = 1;
	init_struct_.lpstrInitialDir = NULL;
	init_struct_.Flags = OFN_EXPLORER;

}

void FileDialog::FindFile(const HWND parent_hWnd){

	wchar_t file_name[260];
	wchar_t direct[260];

	init_struct_.hwndOwner = parent_hWnd;
	init_struct_.lpstrFileTitle = file_name;
	*(init_struct_.lpstrFileTitle) = 0;
	init_struct_.lpstrFile = direct;
	*(init_struct_.lpstrFile) = 0;
	init_struct_.nMaxFile = sizeof(direct);
	init_struct_.nMaxFileTitle = sizeof(file_name);
	
	GetOpenFileName(&init_struct_);
	
	if (*(init_struct_.lpstrFile) == 0)
		throw ComponentException{ u8"GetOpenFileName" };

	file_path_ = direct;
	file_name_ = file_name;

}

EXPIMP std::filesystem::path FileDialog::GetPath() const noexcept{

	return file_path_;
}

EXPIMP std::wstring FileDialog::GetName() const noexcept
{
	return file_name_;
}

