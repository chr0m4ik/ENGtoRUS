#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#include <codecvt>
#elif __linux__
#include <cstdlib>
#include <fstream>
#endif

void clearConsole() {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

#ifdef _WIN32
bool copyToClipboard(const std::wstring& text) {
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();
        size_t size = (text.length() + 1) * sizeof(wchar_t);
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, size);
        if (hMem) {
            wchar_t* pMem = static_cast<wchar_t*>(GlobalLock(hMem));
            wcscpy_s(pMem, text.length() + 1, text.c_str());
            GlobalUnlock(hMem);
            SetClipboardData(CF_UNICODETEXT, hMem);
            CloseClipboard();
            return true;
        }
        CloseClipboard();
    }
    return false;
}
#elif __linux__
bool copyToClipboard(const std::wstring& text) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8_text = converter.to_bytes(text);
    std::string cmd = "echo -n '" + utf8_text + "' | xclip -selection clipboard";
    int result = system(cmd.c_str());
    return (result == 0);
}
#else
bool copyToClipboard(const std::wstring& text) {
    std::wcout << L"Копирование в буфер обмена не поддерживается на этой платформе\n";
    return false;
}
#endif

void capslock(std::wstring en, std::wstring ru, std::wstring enU, std::wstring ruU) {
    std::wstring text;
    std::wcout << L"Введите текст: ";
    std::getline(std::wcin, text);

    for (int i = 0; i < text.length(); i++) {
        bool replaced = false;
        for (int j = 0; j < en.length(); j++) {
            if (text[i] == en[j]) {
                text[i] = enU[j];
                replaced = true;
                break;
            }
            if (text[i] == enU[j]) {
                text[i] = en[j];
                replaced = true;
                break;
            }
        }
        for (int j = 0; j < ru.length() && !replaced; j++) {
            if (text[i] == ru[j]) {
                text[i] = ruU[j];
                break;
            }
            if (text[i] == ruU[j]) {
                text[i] = ru[j];
                break;
            }
        }
    }

    std::wcout << L"Результат: " << text << L"\n";

    while (true) {
        int choice;
        std::wcout << L"\n1 - продолжить\n2 - скопировать результат\n0 - выход\nВаш выбор: ";
        std::wcin >> choice;
        std::wcin.ignore();

        if (choice == 1) {
            break;
        }
        else if (choice == 2) {
            if (copyToClipboard(text)) {
                std::wcout << L"Результат скопирован в буфер обмена!\n";
            }
            else {
                std::wcout << L"Ошибка копирования в буфер обмена!\n";
            }
        }
        else if (choice == 0) {
            exit(0);
        }
        else {
            std::wcout << L"Неверный выбор, попробуйте снова.\n";
        }
    }
}

void translate(std::wstring en, std::wstring ru, std::wstring enU, std::wstring ruU) {
    std::wstring text;
    std::wcout << L"Введите текст: ";
    std::getline(std::wcin, text);

    for (int i = 0; i < text.length(); i++) {
        bool replaced = false;
        for (int j = 0; j < en.length(); j++) {
            if (text[i] == en[j]) {
                text[i] = ru[j];
                replaced = true;
                break;
            }
            if (text[i] == ru[j]) {
                text[i] = en[j];
                replaced = true;
                break;
            }
        }
        for (int j = 0; j < enU.length() && !replaced; j++) {
            if (text[i] == enU[j]) {
                text[i] = ruU[j];
                break;
            }
            if (text[i] == ruU[j]) {
                text[i] = enU[j];
                break;
            }
        }
    }

    std::wcout << L"Результат: " << text << L"\n";

    while (true) {
        int choice;
        std::wcout << L"\n1 - продолжить\n2 - скопировать результат\n0 - выход\nВаш выбор: ";
        std::wcin >> choice;
        std::wcin.ignore();

        if (choice == 1) {
            break;
        }
        else if (choice == 2) {
            if (copyToClipboard(text)) {
                std::wcout << L"Результат скопирован в буфер обмена!\n";
            }
            else {
                std::wcout << L"Ошибка копирования в буфер обмена!\n";
            }
        }
        else if (choice == 0) {
            exit(0);
        }
        else {
            std::wcout << L"Неверный выбор, попробуйте снова.\n";
        }
    }
}

int main() {
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::locale::global(std::locale(""));

    std::wstring en = L"qwertyuiop[]asdfghjkl;'zxcvbnm,.";
    std::wstring ru = L"йцукенгшщзхъфывапролджэячсмитьбю";
    std::wstring enU = L"QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>";
    std::wstring ruU = L"ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";

    while (true) {
        int start;
        std::wcout << L"1 - смена раскладки, 2 - caps lock, 3 - очистить вывод, 0 - выход: ";
        std::wcin >> start;
        std::wcin.ignore();

        clearConsole();

        if (start == 0) {
            return 0;
        }
        else if (start == 1) {
            translate(en, ru, enU, ruU);
        }
        else if (start == 2) {
            capslock(en, ru, enU, ruU);
        }
        else if (start == 3) {
            clearConsole();
        }
        else {
            std::wcout << L"Error: unregistred input!\n";
            continue;
        }
    }
    return 0;
}
