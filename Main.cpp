#define _CRT_SECURE_NO_WARNINGS
#include <algorithm> // Для перемешивания
#include <vector>    // Для работы с массивами
#include <fstream>   // Для чтения и записи файла
#include <string.h>  // Для работы со строками
#include <random>    // Для генератора случайных чисел
#include <regex>     // Для поиска, замены и анализа строк с использованием шаблонов регулярных выражений


using namespace std; 
#include "Main.h" // Заголовка файла  


int MainFrame::main(int button) {

    random_device rd;  // Источник случайных чисел
    mt19937 gen(rd()); // Генератор случайных чисел на основе rd
    string encrypted = "Encrypted.bin";
    string decrypted; // Для зашифрованного и расшифрованного текста
    string ascii_1 = textCtrl3->GetValue().ToStdString(); 
    string ascii_2 = textCtrl4->GetValue().ToStdString();
    string random_key = textCtrl5->GetValue().ToStdString(); // Хранит случайный ключ
    string msg; //
    string file_extension; // Расширение файла
    string button_format = textCtrl1->GetValue().ToStdString();  // Формат файла, введенный пользователем
    string shift_1, shift_2, shift_key;
    char pos; // Позиция для извлечения расширения файла
    vector<int> shiftNumbers; //
    const char key_length = 95;
     
    // Извлекаем расширение файла
    pos = button_format.find("."); // Из файла находем "."
    file_extension = (pos != string::npos) ? button_format.substr(pos) : ""; // Извлечение расширения файла
    decrypted = "Decrypted" + file_extension; // Decrypted даем расширение

    msg.clear(); // Функция для очищения строки, так что длина строки становится равной нулю.

    // Зашифрование текст с использованием шифра Виженера
    if (button == 1) {
        // Перемешиваем массив случайным образом 1
        ascii_1 = asciiUTF();
        shuffle(ascii_1.begin(), ascii_1.end(), gen); // Перемешиваем таблицу 
        // Перемешиваем массив случайным образом 2 
        ascii_2 = asciiUTF();
        shuffle(ascii_2.begin(), ascii_2.end(), gen); // Перемешиваем таблицу
        // Генерация случайного ключа
        random_key = randomKey(key_length, ascii_1, gen); // Генерируем случайный ключ

        // Зашифрование текст
        msg = read_file(button_format); // Читаем файл button_format
        if (msg.empty()) {  // Проверка на пустой файл
            wxMessageBox("File is empty!", "Error", wxOK | wxICON_ERROR);
            return 0;
        }

        // Записываем сдвиги заранее в msg
        shift_1 = "shift_1:" + to_string(randomNumber(gen));
        shift_2 = "shift_2:" + to_string(randomNumber(gen));
        shift_key = "shift_3:" + to_string(randomNumber(gen));
        msg = shift_1 + shift_2 + shift_key + msg; // Добавить в конец текста

        msg = vigenereEncrypted(msg, random_key, ascii_1, ascii_2);
        record_file(encrypted, msg); // Запис файла encrypted c помощью record_file

        textCtrl3->SetValue(ascii_1);
        textCtrl4->SetValue(ascii_2);
        textCtrl5->SetValue(random_key);
    }

    // расшифрование текст с использованием того же ключа
    if (button == 2) {

        msg = read_file(encrypted); // Читаем файл button_format
        if (msg.empty()) { // Проверка на пустой файл
            wxMessageBox("File is empty!", "Error", wxOK | wxICON_ERROR);
            return 0;
        }

        msg = vigenereDecrypted(msg, random_key, ascii_1, ascii_2); // Decryted text
        
        // Извлечение сдвигов из сообщения
        shiftNumbers = extractShiftNumbers(msg);

        // Проверка, что найдено как минимум 3 числа
        if (shiftNumbers.size() >= 3) {
            // Применение сдвигов для каждой строки
            ascii_1 = shiftString(ascii_1, shiftNumbers[0]);  // Сдвиг для ascii_1 на shiftNumbers[0]
            ascii_2 = shiftString(ascii_2, shiftNumbers[1]);  // Сдвиг для ascii_2 на shiftNumbers[1]
            random_key = shiftString(random_key, shiftNumbers[2]);  // Сдвиг для random_key на shiftNumbers[2]
        }

        // Регулярное выражение для поиска текста в скобках
        regex re("shift_\\w+:\\s*(-?\\d+)");
        // Заменяем все вхождения на пустую строку
        msg = regex_replace(msg, re, "");

        textCtrl7->SetValue(ascii_1);
        textCtrl8->SetValue(ascii_2);
        textCtrl9->SetValue(random_key);

        record_file(decrypted, msg); // Запис файла encrypted c помощью record_file
    }
    return 0;
}

void MainFrame::Button1Clicked(wxCommandEvent& event) {
    main(1);
}

void MainFrame::Button2Clicked(wxCommandEvent& event) {
    main(2);
}

// для поиска чисел
vector<int> MainFrame::extractShiftNumbers(const string& text) {
    regex re("shift_\\w+:\\s*(-?\\d+)");  // Регулярное выражение для поиска чисел
    smatch match;
    vector<int> numbers;
    auto it = text.cbegin();
    while (regex_search(it, text.cend(), match, re)) {
        numbers.push_back(stoi(match[1].str()));  // Преобразуем найденное число в целое и сохраняем в вектор
        it = match[0].second;  // Двигаем итератор к следующей позиции
    }

    return numbers;
}

// Функция циклического сдвига строки
string MainFrame::shiftString(const string& str, int shift) {
    int n = str.length(); // Получаем длину строки
    // Нормализация сдвига
    shift = shift % n;
    if (shift < 0) {
        shift += n; // Если сдвиг отрицательный, приводим его в положительный диапазон
    }
    return str.substr(shift) + str.substr(0, shift); // Возвращаем строку после сдвига
}

// Генерации случайное число от -94 до 94;
int MainFrame::randomNumber(mt19937& gen) {
    // Устанавливаем диапазон значений от -94 до 94;
    uniform_int_distribution<> dis(-94, 94);
    // Генерируем и возвращаем случайное число;
    return dis(gen);
}

// ASCII Функчия 32-126 значет 94 символы
string MainFrame::asciiUTF() {
    string ascii;
    char c;
    for (c = 32; c <= 126; ++c) {
        ascii += c;  // Добавляем все печатные символы
    }
    return ascii;
}

// Функция для генерации случайного ключа
string MainFrame::randomKey(int length, const string& ascii, mt19937& gen) {
    string key = ""; // Переменная для результата ключа
    int i;
    uniform_int_distribution<> dist(0, ascii.length() - 1); // Диапазон индексов ASCII символов
    for (i = 0; i < length; ++i) {
        key += ascii[dist(gen)]; // Выбираем случайный символ из набора
    }
    return key;
}

// Функчия чтения файла 
string MainFrame::read_file(const string& filename) { // const не позволяет модифицировать оригинал, & ссылка
    ifstream read; // Для чтения
    string list, content;
    read.open(filename, ios_base::in | ios_base::binary); // Открываем файл для чтения в бинарном режиме
    if (!read.is_open()) { // Проверяем успешность открытия файла
        wxMessageBox("Error: Unable to open file \"" + filename + "\" for reading.", "Error", wxOK | wxICON_ERROR);
        return ""; // Возвращаем пустую строку (""), что чтение файла не удалось.
    }
    while (getline(read, list)) { // Читаем файл построчно
        content += list + "\n"; // Добавляем каждую строку к результату
    }
    read.close(); // Закрываем файл после чтения
    return content;
}

// Функчия record_file запись файла 
void MainFrame::record_file(const string& filename, const string& content) {
    ofstream record; // Для запись
    record.open(filename, ios_base::out | ios_base::binary); // Открываем файл для записи в бинарном режиме
    if (!record.is_open()) {
        wxMessageBox("Error: Unable to open file \"" + filename + "\" for reading.", "Error", wxOK | wxICON_ERROR);
        return; // Завершаем выполнение функции в случае ошибки
    }
    record << content; // Записываем содержимое в файл
    record.close();
}

// Функция для зашифрования текста с использованием шифра Виженера
string MainFrame::vigenereEncrypted(const string& text, const string& key, const string& ascii, const string& ascii2) {
    string result = "";
    int keyIndex = 0;
    int pos, shift, msg;
    for (char c : text) { // Цикл автоматически перебирает каждый элемент строки
        if (ascii.find(c) != string::npos) { // Неподлежащие в ascii, 94 символов проста пропускает. 
            pos = ascii.find(c); // Находим индекс символа в ascii
            msg = ascii2.find(ascii[pos]); //
            // Сдвигаем символ в зависимости от ключа
            shift = ascii2.find(key[keyIndex % key.length()]); // Индекс символа ключа в ascii2
            result += ascii2[(msg + shift) % ascii2.length()]; // Добавляем зашифрованный символ
            keyIndex++; // Переход к следующему символу ключа
        }
        else {
            result += c; // Не изменяем неалфавитные символы
        }
    }
    return result;
}

// Функция для расшифрования текста с использованием шифра Виженера
string MainFrame::vigenereDecrypted(const string& text, const string& key, const string& ascii, const string& ascii2) {
    string result = "";
    int keyIndex = 0;
    int pos, shift, msg;
    for (char c : text) { // Цикл автоматически перебирает каждый элемент строки
        if (ascii2.find(c) != string::npos) { // Только символы из ascii расшифруем
            pos = ascii2.find(c); // Находим индекс символа в ascii
            shift = ascii2.find(key[keyIndex % key.length()]); // Находим сдвиг по ключу
            msg = (pos - shift + ascii2.length()) % ascii2.length(); // Вычисляем индекс оригинального символа
            result += ascii[ascii.find(ascii2[msg])]; // Получаем оригинальный символ из ascii2
            keyIndex++; // Переход к следующему символу ключа
        }
        else {
            result += c;  // Не изменяем неалфавитные символы
        }
    }
    return result;
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& event) {
    // Очищаем все текстовые поля
    textCtrl1->Clear();
    textCtrl3->Clear();
    textCtrl4->Clear();
    textCtrl5->Clear();
    textCtrl7->Clear();
    textCtrl8->Clear();
    textCtrl9->Clear();

}