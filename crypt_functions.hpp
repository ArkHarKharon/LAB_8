#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <bitset>


using bit_10_t = std::bitset<10>;
using bit_8_t = std::bitset<8>;
using bit_5_t = std::bitset<5>;
using bit_4_t = std::bitset<4>;
using bit_2_t = std::bitset<2>;


// Таблицы для операций замены и перестановки	
const std::vector<int> IP = { 1, 5, 2, 0, 3, 7, 4, 6 };			// Таблица начальной перестановки (IP)
const std::vector<int> IP_1 = { 3, 0, 2, 4, 6, 1, 7, 5 };		// Таблица обратной начальной перестановки (IP_1)
const std::vector<int> P10 = { 2, 4, 1, 6, 3, 9, 0, 8, 7, 5 };  // Таблица перестановки 10 бит ключа (P10)
const std::vector<int> P8 = { 5, 2, 6, 3, 7, 4, 9, 8 };			// Таблица перестановки 8 бит подключа (P8)
const std::vector<int> P4 = { 1, 3, 2, 0 };						// таблица перестановки, применяемая к 4-битному выходу S-блоков (P4)
const std::vector<int> EP = { 3, 0, 1, 2, 1, 2, 3, 0 };			// Таблица перестановки 4 бит в расширенном перестановочном блоке (EP)
const int S0[4][4] = { {1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2} }; // Таблица замен S0
const int S1[4][4] = { {0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3} }; // Таблица замен S1

// Статический ключ
const bit_10_t KEY("0000010101");

std::vector<bit_8_t> generate_keys();
template <size_t N, size_t M> std::bitset<M> permute(const std::bitset<N>& value, const std::vector<int>& table);
template<size_t N> std::bitset<N> сyclic_shift_left(std::bitset<N>& key, const int& shift);
int sbox(bit_4_t value, const int S[4][4]);
bit_8_t encrypt_char(bit_8_t plaintext);
bit_8_t decrypt_char(bit_8_t ciphertext_8);
std::string encrypt_string(std::string plaintext);
std::string decrypt_string(std::string ciphertext);