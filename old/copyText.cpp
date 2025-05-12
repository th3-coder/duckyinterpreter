#include <iostream>
#include <windows.h>

int main() {
    if (!OpenClipboard(NULL)) {
        std::cerr << "Error opening clipboard." << std::endl;
        return 1;
    }

    HANDLE hClipboardData = GetClipboardData(CF_TEXT);
    if (hClipboardData == NULL) {
        std::cerr << "Error getting clipboard data." << std::endl;
        CloseClipboard();
        return 1;
    }

    char* pszText = static_cast<char*>(GlobalLock(hClipboardData));
    if (pszText == NULL) {
       std::cerr << "Error locking global memory." << std::endl;
       CloseClipboard();
       return 1;
    }

    std::string text(pszText);

    GlobalUnlock(hClipboardData);
    CloseClipboard();

    std::cout << "Copied text: " << text << std::endl;

    return 0;
} 