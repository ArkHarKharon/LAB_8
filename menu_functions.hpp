#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

#include "crypt_functions.hpp"


enum class SymbolMenu
{
	ENCRYPT = 1,
	ENCRYPT_BY_VALUES,
	DECRYPT,
	DECRYPT_BY_VALUES,
	EXIT
};

enum class StringMenu
{
	ENCRYPT = 1,
	ENCRYPT_BY_VALUES,
	DECRYPT,
	DECRYPT_BY_VALUES,
	EXIT
};

enum class MainMenu
{
	SYMBOL_MENU = 1,
	STRING_MENU,
	EXIT
};


void main_menu();
void symbol_crypt_menu();
void string_crypt_menu();
