#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>
#include <string>
#include <random>

using namespace std;

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:

    wxTextCtrl* textCtrl1; // Поле для сообщения
    wxTextCtrl* textCtrl2; // Поле для ключа
    wxTextCtrl* textCtrl3; // Поле для процесса шифрования
    wxTextCtrl* textCtrl4; // Поле для результата
    wxTextCtrl* textCtrl5; //
    wxTextCtrl* textCtrl6;
    wxTextCtrl* textCtrl7;
    wxTextCtrl* textCtrl8;
    wxTextCtrl* textCtrl9;
    wxTextCtrl* textCtrl10;

    int main(int button);
    void Button1Clicked(wxCommandEvent& event);
    void Button2Clicked(wxCommandEvent& event);
    void OnClearButtonClicked(wxCommandEvent& event); // Новый обработчик кнопки 

    // Функция для получения ASCII - символов;
    string asciiUTF();

    // Функция для чтения содержимого из файла;
    string read_file(const string& filename);

    // Функция для записи (записи) содержимого в файл;
    void record_file(const string& filename, const string& content);

    // Функция для генерации случайного ключа заданной длины с использованием ASCII символов;
    string randomKey(int length, const string& ascii, mt19937& gen);

    // Функция Зашифрования Vigenere;
    string vigenereEncrypted(const string& text, const string& key, const string& ascii, const string& ascii2);

    // Функция расшифровки Vigenere;
    string vigenereDecrypted(const string& text, const string& key, const string& ascii, const string& ascii2);

    // Функция для сдвига символов в строке на заданное количество позиций;
    string shiftString(const string& str, int shift);

    // Генерации случайное число от -94 до 94;
    int randomNumber(mt19937& gen);

    //
    vector<int> extractShiftNumbers(const string& text);

};

#endif