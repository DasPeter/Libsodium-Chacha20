// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "sodium.h"

int main()
{
	if (sodium_init() < 0) {
		/* panic! the library couldn't be initialized, it is not safe to use */
		return -1;
	}

	// Open file and print original text
	std::ifstream input("input.txt");
	unsigned char* plainText = new unsigned char[300];
	input.getline((char*)plainText, 300, '\0');
	std::cout << "Original text:\n";
	std::cout << plainText << std::endl<< std::endl;

	int plainTextLen = strlen((char *)plainText);

	unsigned char* cipherText = new unsigned char[plainTextLen];
	unsigned char* decipherText = new unsigned char[plainTextLen];

	unsigned char key[crypto_stream_chacha20_KEYBYTES];
	unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];

	crypto_secretbox_keygen(key); // Generate new key
	randombytes_buf(nonce, sizeof nonce); // Generate new nonce

	// Execute encryption
	int toCipher = crypto_stream_chacha20_xor(cipherText, plainText, plainTextLen, nonce, key);

	// Print ciphered result
	std::cout << "Ciphered text:\n";
	for (int i = 0; i < plainTextLen; i++)
	{
		std::cout << std::setfill('0') << std::setw(2) << std::hex << int(cipherText[i]);
	}
	std::cout << std::endl << std::endl;


	// Do decipher
	int toDecipher = crypto_stream_chacha20_xor(decipherText, cipherText, plainTextLen, nonce, key);
	std::cout << "Deciphered text:\n";
	for (int i = 0; i < plainTextLen; i++)
	{
		std::cout << decipherText[i];
	}
	std::cout << std::endl;

	

	return 1;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
