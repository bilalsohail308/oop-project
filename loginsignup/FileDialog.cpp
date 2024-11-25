#include "FileDialog.h"
#include <windows.h>
#include <commdlg.h>

// Utility function: Convert wide string to narrow string
std::string wideToNarrow(const std::wstring& wideString) {
    return std::string(wideString.begin(), wideString.end());
}

// Function to open a file dialog and get the file path
std::string openFileDialog() {
    wchar_t fileName[MAX_PATH] = L"";
    OPENFILENAMEW ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Image Files\0*.bmp;*.jpg;*.jpeg;*.png;*.tga\0All Files\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn)) {
        return wideToNarrow(std::wstring(fileName));
    }
    return "";
}
