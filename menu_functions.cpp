#include "menu_functions.hpp"


void main_menu()
{
    setlocale(0, "");

    int choice;

    do
    {
        std::cout 
            << "\n\t������� ����:\n"
            << "\t1. ������ � ��������\n"
            << "\t2. ������ �� �������\n"
            << "\t3. �����\n"
            << "\t�������� ��������: ";
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
            std::cout << "\n����� �������!";
            break;

        default:  
            std::cout << "\n�������� ������!";
            break;
        }

    } while (choice != (int)MainMenu::EXIT);
}


void symbol_crypt_menu()
{
    char symbol;
    int choice;
    char symbol_encrypted = '\0';


    std::cout << "\n������� ������ ��� ���������� (������ ����� ������� �� ����������): ";
    std::cin >> symbol;

    do
    {
        std::cout << "\n\t���� ���������� � ������������� �������:\n";
        std::cout << "\t1. ����������� ������\n";
        std::cout << "\t2. ����������� ������ (� ������� ������������� ��������)\n";
        std::cout << "\t3. ������������ ������\n";
        std::cout << "\t4. ������������ ������ (� ������� ������������� ��������)\n";
        std::cout << "\t5. �����\n";
        std::cout << "\t�������� ��������: ";
        std::cin >> choice;

        switch (choice)
        {
        case ((int)SymbolMenu::ENCRYPT):
        {
            bit_8_t ciphertext = encrypt_char(bit_8_t(symbol));
            symbol_encrypted = static_cast<int>(ciphertext.to_ulong());
            std::cout << "\n������������� ������: " << symbol_encrypted << std::endl;
            break;
        }
        case ((int)SymbolMenu::ENCRYPT_BY_VALUES):
        {
            // ���������� � ������� ������������� �������� ��� ���������� �������
            bit_8_t plaintext_8(symbol);
            bit_8_t ciphertext = encrypt_char(plaintext_8);
            std::cout << "\n������������� ������: " << static_cast<char>(ciphertext.to_ulong()) << std::endl;
            break;
        }
        case ((int)SymbolMenu::DECRYPT):
        {
            bit_8_t plaintext = decrypt_char(bit_8_t(symbol_encrypted));
            std::cout << "\n�������������� ������: " << static_cast<char>(plaintext.to_ulong()) << std::endl;
            break;
        }
        case ((int)SymbolMenu::DECRYPT_BY_VALUES):
        {
            // ���������� � ������� ������������� �������� ��� ������������� �������
            bit_8_t ciphertext(symbol);
            bit_8_t plaintext = decrypt_char(ciphertext);
            std::cout << "\n�������������� ������: " << static_cast<char>(plaintext.to_ulong()) << std::endl;
            break;
        }
        case ((int)SymbolMenu::EXIT):
            std::cout << "\n���� ���������� � ������������� ������� --> ������� ����." << std::endl;
            break;
        default:
            std::cout << "\n�������� �����. ���������� �����." << std::endl;
        }
    } while (choice != (int)SymbolMenu::EXIT);

}


void string_crypt_menu()
{
    std::string str = "";
    std::string str_encrypted = "";
    int choice;

   std::cout << "\n������� ������ ��� ����������: ";
    std::cin.clear();
    std::cin.ignore(); // ���������� ������ ����� ������ �� ����������� �����
    getline(std::cin, str); // ��������� ��� ������, ������� �������

    do
    {
       std::cout << "\n\t���� ��� ���������� � ������������� ������:\n";
       std::cout << "\t1. ����������� ������\n";
       std::cout << "\t2. ����������� ������ (� ������� ������������� ��������)\n";
       std::cout << "\t3. ������������ ������\n";
       std::cout << "\t4. ������������ ������ (� ������� ������������� ��������)\n";
       std::cout << "\t5. �����\n";
       std::cout << "\t�������� ��������: ";
        std::cin >> choice;

        switch (choice)
        {
        case ((int)StringMenu::ENCRYPT):
        {
            str_encrypted = encrypt_string(str);
            std::cout << "\n������������� ������: " << str_encrypted << std::endl;
            break;
        }
        case ((int)StringMenu::ENCRYPT_BY_VALUES):
        {
            std::string ciphertext = "";std::cout << std::endl;
            for (bit_8_t c : str)
            {
                bit_8_t cipherchar = encrypt_char(bit_8_t(c));
               std::cout << "������������� �������� ��� ������� '" << c << "': " << static_cast<char>(cipherchar.to_ulong()) << std::endl;
                ciphertext += static_cast<char>(cipherchar.to_ulong());
            }
            std::cout << "\n������������� ������: " << ciphertext << std::endl;
            break;
        }
        case ((int)StringMenu::DECRYPT):
        {
            str = decrypt_string(str_encrypted);
            std::cout << "\n�������������� ������: " << str << std::endl;
            break;
        }
        case ((int)StringMenu::DECRYPT_BY_VALUES):
        {
            std::string plaintext = "";std::cout << std::endl;
            for (char c : str) {
                bit_8_t plainchar = decrypt_char(bit_8_t(c));
               std::cout << "������������� �������� ��� ������� '" << c << "': " << static_cast<char>(plainchar.to_ulong()) << std::endl;
                plaintext += static_cast<char>(plainchar.to_ulong());
            }
            std::cout << "\n�������������� ������: " << plaintext << std::endl;
            break;
        }
        case ((int)StringMenu::EXIT):
        {
            std::cout << "\n���� ��� ���������� � ������������� ������ --> ������� ����." << std::endl;
            break;
        }
        default:
        {
            std::cout << "\n�������� �����. ���������� �����." << std::endl;
            break;
        }
        }
    } while (choice != (int)StringMenu::EXIT);
}