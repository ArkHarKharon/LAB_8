#include "menu_functions.hpp"


void main_menu()
{
    setlocale(0, "");

    int choice;

    do
    {
        std::cout 
            << "\n\tГлавное меню:\n"
            << "\t1. Работа с символом\n"
            << "\t2. Работа со строкой\n"
            << "\t3. Выход\n"
            << "\tВыберите действие: ";
       std::cin >> choice;

        switch (choice)
        {
        case ((int)MainMenu::SYMBOL_MENU): 
            symbol_crypt_menu(); 
            break;

        case ((int)MainMenu::STRING_MENU):
            string_crypt_menu();
            break;

        case ((int)MainMenu::EXIT): 
            std::cout << "\nВсего доброго!";
            break;

        default:  
            std::cout << "\nНеверный индекс!";
            break;
        }

    } while (choice != (int)MainMenu::EXIT);
}


void symbol_crypt_menu()
{
    char symbol;
    int choice;
    char symbol_encrypted = '\0';


    std::cout << "\nВведите символ для шифрования (первая буква фамилии на английском): ";
    std::cin >> symbol;

    do
    {
        std::cout << "\n\tМеню шифрования и расшифрования символа:\n";
        std::cout << "\t1. Зашифровать символ\n";
        std::cout << "\t2. Зашифровать символ (с выводом промежуточных значений)\n";
        std::cout << "\t3. Расшифровать символ\n";
        std::cout << "\t4. Расшифровать символ (с выводом промежуточных значений)\n";
        std::cout << "\t5. Выход\n";
        std::cout << "\tВыберите действие: ";
        std::cin >> choice;

        switch (choice)
        {
        case ((int)SymbolMenu::ENCRYPT):
        {
            bit_8_t ciphertext = encrypt_char(bit_8_t(symbol));
            symbol_encrypted = static_cast<int>(ciphertext.to_ulong());
            std::cout << "\nЗашифрованный символ: " << symbol_encrypted << std::endl;
            break;
        }
        case ((int)SymbolMenu::ENCRYPT_BY_VALUES):
        {
            // Реализация с выводом промежуточных значений для шифрования символа
            bit_8_t plaintext_8(symbol);
            bit_8_t ciphertext = encrypt_char(plaintext_8);
            std::cout << "\nЗашифрованный символ: " << static_cast<char>(ciphertext.to_ulong()) << std::endl;
            break;
        }
        case ((int)SymbolMenu::DECRYPT):
        {
            bit_8_t plaintext = decrypt_char(bit_8_t(symbol_encrypted));
            std::cout << "\nРасшифрованный символ: " << static_cast<char>(plaintext.to_ulong()) << std::endl;
            break;
        }
        case ((int)SymbolMenu::DECRYPT_BY_VALUES):
        {
            // Реализация с выводом промежуточных значений для расшифрования символа
            bit_8_t ciphertext(symbol);
            bit_8_t plaintext = decrypt_char(ciphertext);
            std::cout << "\nРасшифрованный символ: " << static_cast<char>(plaintext.to_ulong()) << std::endl;
            break;
        }
        case ((int)SymbolMenu::EXIT):
            std::cout << "\nМеню шифрования и расшифрования символа --> Главное меню." << std::endl;
            break;
        default:
            std::cout << "\nНеверный выбор. Попробуйте снова." << std::endl;
        }
    } while (choice != (int)SymbolMenu::EXIT);

}


void string_crypt_menu()
{
    std::string str = "";
    std::string str_encrypted = "";
    int choice;

   std::cout << "\nВведите строку для шифрования: ";
    std::cin.clear();
    std::cin.ignore(); // Игнорируем символ новой строки из предыдущего ввода
    getline(std::cin, str); // Считываем всю строку, включая пробелы

    do
    {
       std::cout << "\n\tМеню для шифрования и расшифрования строки:\n";
       std::cout << "\t1. Зашифровать строку\n";
       std::cout << "\t2. Зашифровать строку (с выводом промежуточных значений)\n";
       std::cout << "\t3. Расшифровать строку\n";
       std::cout << "\t4. Расшифровать строку (с выводом промежуточных значений)\n";
       std::cout << "\t5. Выход\n";
       std::cout << "\tВыберите действие: ";
        std::cin >> choice;

        switch (choice)
        {
        case ((int)StringMenu::ENCRYPT):
        {
            str_encrypted = encrypt_string(str);
            std::cout << "\nЗашифрованная строка: " << str_encrypted << std::endl;
            break;
        }
        case ((int)StringMenu::ENCRYPT_BY_VALUES):
        {
            std::string ciphertext = "";std::cout << std::endl;
            for (bit_8_t c : str)
            {
                bit_8_t cipherchar = encrypt_char(bit_8_t(c));
               std::cout << "Промежуточное значение для символа '" << c << "': " << static_cast<char>(cipherchar.to_ulong()) << std::endl;
                ciphertext += static_cast<char>(cipherchar.to_ulong());
            }
            std::cout << "\nЗашифрованная строка: " << ciphertext << std::endl;
            break;
        }
        case ((int)StringMenu::DECRYPT):
        {
            str = decrypt_string(str_encrypted);
            std::cout << "\nРасшифрованная строка: " << str << std::endl;
            break;
        }
        case ((int)StringMenu::DECRYPT_BY_VALUES):
        {
            std::string plaintext = "";std::cout << std::endl;
            for (char c : str) {
                bit_8_t plainchar = decrypt_char(bit_8_t(c));
               std::cout << "Промежуточное значение для символа '" << c << "': " << static_cast<char>(plainchar.to_ulong()) << std::endl;
                plaintext += static_cast<char>(plainchar.to_ulong());
            }
            std::cout << "\nРасшифрованная строка: " << plaintext << std::endl;
            break;
        }
        case ((int)StringMenu::EXIT):
        {
            std::cout << "\nМеню для шифрования и расшифрования строки --> Главное меню." << std::endl;
            break;
        }
        default:
        {
            std::cout << "\nНеверный выбор. Попробуйте снова." << std::endl;
            break;
        }
        }
    } while (choice != (int)StringMenu::EXIT);
}