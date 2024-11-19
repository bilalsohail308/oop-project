#include "FileDialog.h"
#include <windows.h>
#include <commdlg.h>

// Utility function: Convert wide string to narrow string
std::string wideToNarrow(const std::wstring& wideString) {
    return std::string(wideString.begin(), wideString.end());
}

// Function to open a file dialog and get the file path
std::string openFileDialog() {
    wchar_t fileName[MAX_PATH] = L""; // Wide-character array for file name
    OPENFILENAMEW ofn;               // Use the wide-character version of OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));   // Initialize all members to zero

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // No owner window
    ofn.lpstrFilter = L"Image Files\0*.bmp;*.jpg;*.jpeg;*.png;*.tga\0All Files\0*.*\0"; // Wide-character filter
    ofn.lpstrFile = fileName; // File path buffer
    ofn.nMaxFile = MAX_PATH; // Maximum path length
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // Ensure valid file path

    // Open the file dialog
    if (GetOpenFileNameW(&ofn)) { // Use wide version of GetOpenFileName
        return wideToNarrow(std::wstring(fileName)); // Convert wide string to narrow and return it
    }

    return ""; // Return an empty string if the user cancels
}
