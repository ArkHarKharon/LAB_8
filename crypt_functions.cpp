#include "crypt_functions.hpp"

// ������� ��� �������� ������ � ������������
template<size_t N, size_t M> std::bitset<M> permute(const std::bitset<N>& value, const std::vector<int>& table)
{
    /*
        N --> M ( �� 10 ������� ����� ������ 8 ������ ������� )
        N - ���-�� ����� � ��������, � ������� �� ����� �������� ( � ������� 10-������ ���� )
        M - ���-�� ����� ��������� �������� ( � ������� �������, � �������� 8 ��� )
    */

    std::bitset<M> result;

    // ������������ ������� ������� � ������������ �������� ������������ :)
    /*
        !!! C���� ������ ���(������� ���) ����� ������ 0,
        � ����� ����� ���(������� ���) ����� ������ N - 1 ��� std::std::bitset<N>

        ������� ���������� �������� ������� �������� (������ ������)
    */

    for (int i = 0; i < table.size(); i++)
    {
        result[M - 1 - i] = value[N - 1 - table[i]];
    }

    return result;
}

template<size_t N> std::bitset<N> �yclic_shift_left(std::bitset<N>& key, const int& shift)
{
    const int bytes = N / 2;

    // �������� ����� �������� (������ 5 ���) � ��������� ����������� ����� ����� �� ���� �������
    std::bitset<bytes> key_left_half(key.to_string().substr(0, bytes));

    std::cout << "\n����� �������� �����:   " << key_left_half << std::endl;

    key_left_half = key_left_half << shift | key_left_half >> (bytes - shift);

    // �������� ����� �������� (��������� 5 ���) � ��������� ����������� ����� ����� �� ���� �������
    std::bitset<bytes> key_right_half(key.to_string().substr(bytes, bytes));

    std::cout << "������ �������� �����:  " << key_right_half << std::endl;

    key_right_half = key_right_half << shift | key_right_half >> (bytes - shift);

    // ���������� ��� ��������� � ���� ����
    key = (key_left_half.to_ulong() << bytes) | key_right_half.to_ulong();

    return key;
}

// ������� ��� ��������� ������
std::vector<bit_8_t> generate_keys()
{
    std::vector<bit_8_t> keys(2);    // ��� �������� �� 8 ��� ������

    std::cout << "\n�������� ����:\t  " << KEY << std::endl;


    bit_10_t key = permute<10, 10>(KEY, P10);
    std::cout << "������������ P10: " << key << std::endl;


    std::cout << "\n\t *** ����������� ����� ����� �� ���� ������� (������ �������� �����) ***\n";

    key = �yclic_shift_left<10>(key, 1);
    std::cout << "������������ ����: \t" << key << std::endl;


    std::cout << "\n\t *** ��������� ����� �1 ***\n\n";

    keys.at(0) = permute<10, 8>(key, P8);
    std::cout << "������������ P8: " << keys.at(0) << std::endl;

    std::cout << "\n���� �1 = " << keys.at(0) << std::endl;


    std::cout << "\n\t *** ��������� ����� �2 ***\n";


    std::cout << "\n\t *** ����������� ����� ����� �� ��� ������� (������ �������� �����) ***\n";

    key = �yclic_shift_left<10>(key, 2);
    std::cout << "������������ ����: \t" << key << std::endl;


    keys.at(1) = permute<10, 8>(key, P8);
    std::cout << "������������ P8: \t" << keys.at(1) << std::endl;

    std::cout << "\n���� �2 = " << keys.at(1) << std::endl;


    return keys;
}

int sbox(bit_4_t value, const int S[4][4])
{
    // �������� �������� ������ (������ ��� + ��������� ���)
    bit_2_t row_2(value.to_string().substr(0, 1) + value.to_string().substr(3, 1));
    std::cout << "�������� ������: " << row_2 << std::endl;

    // �������� �������� ������� (2 ���� ��-��������)
    bit_2_t col_2(value.to_string().substr(1, 2));
    std::cout << "�������� �������: " << col_2 << std::endl;

    int row = row_2.to_ulong();
    int col = col_2.to_ulong();

    return S[row][col];
}

// ������� ��� ���������� �������
bit_8_t encrypt_char(bit_8_t plaintext_8)
{
    std::vector<bit_8_t> keys = generate_keys();

    std::cout << "-----------------";
    std::cout << "\n����������� ��� �������: " << plaintext_8 << std::endl;

    plaintext_8 = permute<8, 8>(plaintext_8, IP);
    std::cout << "������������ IP: " << plaintext_8 << std::endl;

    std::cout << "\n\t**** ���������� ���������� f ����� �1 ****\n";

    /*
                                                ������!
        .to_string(): ����������� ������� ������ � ������ ��������, �������������� �������� ��������.
        .substr(0, 4): ����� ��������� �� �������� ������, ������� � ������� 0 � ������ 4 �������.
        .to_ulong(): ����������� �������� �������� ������ � unsigned long int
    */

    // �������� ����� �������� (��������� 4 ���)
    bit_4_t plaintext_left_IP(plaintext_8.to_string().substr(0, 4));
    // �������� ������ �������� (��������� 4 ���)
    bit_4_t plaintext_right_IP(plaintext_8.to_string().substr(4, 4));
    plaintext_8 = permute<4, 8>(plaintext_right_IP, EP);
    std::cout << "\n������������ E/P(R): " << plaintext_8 << '\n' << '\n';


    plaintext_8 = (plaintext_8 ^ keys[0]);
    std::cout << "�������� XOR(E/P(R), k1): " << plaintext_8 << '\n' << '\n';


    // �������� ����� �������� (��������� 4 ���)
    bit_4_t plaintext_left(plaintext_8.to_string().substr(0, 4));
    // �������� ������ �������� (��������� 4 ���)
    bit_4_t plaintext_right = static_cast<bit_4_t>(plaintext_8.to_string().substr(4, 4));
    std::cout << "����� �����: " << plaintext_left << '\n';
    std::cout << "������ �����: " << plaintext_right << '\n' << '\n';


    bit_2_t plaintext_left_2 = sbox(plaintext_left, S0);
    bit_2_t plaintext_right_2 = sbox(plaintext_right, S1);
    bit_4_t plaintext_4 = (plaintext_left_2.to_ulong() << 2) | plaintext_right_2.to_ulong();
    std::cout << "\n��������� ������ S-������: " << plaintext_4 << '\n' << '\n';


    plaintext_4 = permute<4, 4>(plaintext_4, P4);
    std::cout << "������������ P4: " << plaintext_4 << '\n' << '\n';


    plaintext_4 = plaintext_left_IP ^ plaintext_4;
    std::cout << "�������� XOR(L, P4): " << plaintext_4 << '\n' << '\n';

    plaintext_8 = (plaintext_right_IP.to_ulong() << 4) | plaintext_4.to_ulong();
    std::cout << "������������ SW: " << plaintext_8 << '\n' << '\n';



    std::cout << "\n\t**** ���������� ���������� f ����� �2 ****\n";

    bit_4_t plaintext_left_main = static_cast<bit_4_t>(plaintext_8.to_string().substr(0, 4));
    bit_4_t plaintext_right_main = static_cast<bit_4_t>(plaintext_8.to_string().substr(4, 4));

    plaintext_8 = permute<4, 8>(plaintext_right_main, EP);
    std::cout << "\n������������ E/P(R): " << plaintext_8 << '\n' << '\n';

    plaintext_8 = (plaintext_8 ^ keys[1]);
    std::cout << "�������� XOR(E/P(R), k2): " << plaintext_8 << '\n' << '\n';


    plaintext_left = static_cast<bit_4_t>(plaintext_8.to_string().substr(0, 4));
    plaintext_right = static_cast<bit_4_t>(plaintext_8.to_string().substr(4, 4));
    std::cout << "����� �����: " << plaintext_left << '\n' << '\n';
    std::cout << "������ �����: " << plaintext_right << '\n' << '\n';


    plaintext_left_2 = sbox(plaintext_left, S0);
    plaintext_right_2 = sbox(plaintext_right, S1);
    plaintext_4 = (plaintext_left_2.to_ulong() << 2) | plaintext_right_2.to_ulong();
    std::cout << "\n��������� ������ S-������: " << plaintext_4 << '\n' << '\n';


    plaintext_4 = permute<4, 4>(plaintext_4, P4);
    std::cout << "������������ P4: " << plaintext_4 << '\n' << '\n';


    plaintext_4 = plaintext_left_main ^ plaintext_4;
    std::cout << "�������� XOR(L, P4): " << plaintext_4 << '\n' << '\n';


    plaintext_8 = (plaintext_4.to_ulong() << 4) | plaintext_right_main.to_ulong();
    std::cout << "������������ SW(XOR(L, P4), R): " << plaintext_8 << '\n' << '\n';


    plaintext_8 = permute<8, 8>(plaintext_8, IP_1);
    std::cout << "������������ IP^-1: " << plaintext_8 << '\n' << '\n';

    return plaintext_8;
}

// ������� ��� ������������� �������
bit_8_t decrypt_char(bit_8_t ciphertext_8)
{
    std::vector<bit_8_t> keys = generate_keys();

    std::cout << "����������� ��� �������������� �������: " << ciphertext_8 << '\n' << '\n';

    std::cout << "\n\t**** ���������� ������������� f ����� �2 ****\n\n";

    ciphertext_8 = permute<8, 8>(ciphertext_8, IP);
    std::cout << "������������ IP: " << ciphertext_8 << '\n' << '\n';

    // �������� ����� �������� (��������� 4 ���)
    bit_4_t ciphertext_left_IP(ciphertext_8.to_string().substr(0, 4));
    // �������� ������ �������� (��������� 4 ���)
    bit_4_t ciphertext_right_IP(ciphertext_8.to_string().substr(4, 4));

    std::cout << "����� �����: " << ciphertext_left_IP << '\n';
    std::cout << "������ �����: " << ciphertext_right_IP << '\n' << '\n';

    ciphertext_8 = permute<4, 8>(ciphertext_right_IP, EP);
    std::cout << "������������ E/P(R): " << ciphertext_8 << '\n' << '\n';

    ciphertext_8 = (ciphertext_8 ^ keys.at(1));
    std::cout << "�������� XOR(E/P(R), k2): " << ciphertext_8 << '\n' << '\n';

    // �������� ����� �������� (��������� 4 ���)
    bit_4_t ciphertext_left(ciphertext_8.to_string().substr(0, 4));
    // �������� ������ �������� (��������� 4 ���)
    bit_4_t ciphertext_right = static_cast<bit_4_t>(ciphertext_8.to_string().substr(4, 4));
    std::cout << "����� �����: " << ciphertext_left << '\n' << '\n';
    std::cout << "������ �����: " << ciphertext_right << '\n' << '\n';

    bit_2_t ciphertext_left_2 = sbox(ciphertext_left, S0);
    bit_2_t ciphertext_right_2 = sbox(ciphertext_right, S1);
    bit_4_t ciphertext_4 = (ciphertext_left_2.to_ulong() << 2) | ciphertext_right_2.to_ulong();
    std::cout << "\n��������� ������ S-������: " << ciphertext_4 << '\n' << '\n';

    ciphertext_4 = permute<4, 4>(ciphertext_4, P4);
    std::cout << "������������ P4: " << ciphertext_4 << '\n' << '\n';


    ciphertext_4 = ciphertext_left_IP ^ ciphertext_4;
    std::cout << "�������� XOR(L, P4): " << ciphertext_4 << '\n' << '\n';

    ciphertext_8 = (ciphertext_right_IP.to_ulong() << 4) | ciphertext_4.to_ulong();
    std::cout << "������������ SW: " << ciphertext_8 << '\n' << '\n';


    std::cout << "\n\t**** ���������� ������������ f ����� �1 ****\n\n";

    bit_4_t ciphertext_left_main = static_cast<bit_4_t>(ciphertext_8.to_string().substr(0, 4));
    bit_4_t ciphertext_right_main = static_cast<bit_4_t>(ciphertext_8.to_string().substr(4, 4));

    ciphertext_8 = permute<4, 8>(ciphertext_right_main, EP);
    std::cout << "������������ E/P(R): " << ciphertext_8 << '\n' << '\n';

    ciphertext_8 = (ciphertext_8 ^ keys.at(0));
    std::cout << "�������� XOR(E/P(R), k1): " << ciphertext_8 << '\n' << '\n';

    ciphertext_left = static_cast<bit_4_t>(ciphertext_8.to_string().substr(0, 4));
    ciphertext_right = static_cast<bit_4_t>(ciphertext_8.to_string().substr(4, 4));
    std::cout << "����� �����: " << ciphertext_left << '\n' << '\n';
    std::cout << "������ �����: " << ciphertext_right << '\n' << '\n';

    ciphertext_left_2 = sbox(ciphertext_left, S0);
    ciphertext_right_2 = sbox(ciphertext_right, S1);
    ciphertext_4 = (ciphertext_left_2.to_ulong() << 2) | ciphertext_right_2.to_ulong();
    std::cout << "��������� ������ S-������: " << ciphertext_4 << '\n' << '\n';

    ciphertext_4 = permute<4, 4>(ciphertext_4, P4);
    std::cout << "������������ P4: " << ciphertext_4 << '\n' << '\n';

    ciphertext_4 = ciphertext_left_main ^ ciphertext_4;
    std::cout << "�������� XOR(L, P4): " << ciphertext_4 << '\n' << '\n';

    // ����������� 8-������� ����� �� ���� 4-������
    ciphertext_8 = (ciphertext_4.to_ulong() << 4) | ciphertext_right_main.to_ulong();
    std::cout << "������������ SW(XOR(L, P4), R): " << ciphertext_8 << '\n' << '\n';

    ciphertext_8 = permute<8, 8>(ciphertext_8, IP_1);
    std::cout << "������������ IP^-1: " << ciphertext_8 << '\n' << '\n';

    return ciphertext_8;
}

// ������� ��� ���������� ������
std::string encrypt_string(std::string plaintext)
{
    std::string ciphertext = "";
    for (bit_8_t c : plaintext)
    {
        bit_8_t cipherchar = encrypt_char(c);
        ciphertext += static_cast<char>(cipherchar.to_ulong());
    }
    return ciphertext;
}

// ������� ��� ������������� ������
std::string decrypt_string(std::string ciphertext)
{
    std::string plaintext = "";
    for (char c : ciphertext)
    {
        bit_8_t plainchar = decrypt_char(c);
        plaintext += static_cast<char>(plainchar.to_ulong());
    }
    return plaintext;
}