#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>

using namespace std;

int main() {
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wstring en = L"qwertyuiop[]asdfghjkl;'zxcvbnm,.";
    wstring ru = L"йцукенгшщзхъфывапролджэячсмитьбю";

    wstring enU = L"QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>";
    wstring ruU = L"ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";

    while (true) {
        wstring text;
        wcout << L"Введите текст: ";
        getline(wcin, text);

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

        wcout << L"Результат: " << text << L"\n";

        int choice;
        wcout << L"\n1 - продолжить\n2 - выход\nВаш выбор: ";
        wcin >> choice;
        wcin.ignore();

        if (choice == 2)
            break;
    }

    return 0;
}
