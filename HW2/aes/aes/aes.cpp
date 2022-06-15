#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "modes.h"
#include "aes.h"
#include "filters.h"
#include "hex.h"

std::string AES_CFB_Encrypt(std::string plainText, std::string key_string, std::string iv_string) {
	std::string cipherText;
	std::stringstream ss;

	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	memcpy(key, key_string.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memcpy(iv, iv_string.c_str(), CryptoPP::AES::BLOCKSIZE);

	CryptoPP::AES::Encryption AES_E(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CFB_Mode_ExternalCipher::Encryption AES_CFB(AES_E, iv, 4); // block size = 4 bytes
	CryptoPP::StreamTransformationFilter AES_CFB_Encryptor(AES_CFB, new CryptoPP::StringSink(cipherText)); // no padding

	AES_CFB_Encryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
	AES_CFB_Encryptor.MessageEnd();

	for (int i = 0; i < cipherText.size(); i++) {
		ss << std::setw(2) << std::setfill('0') << std::hex << (0xFF & static_cast<CryptoPP::byte>(cipherText[i])) << " ";
	}

	return ss.str();
}

std::string AES_CBC_Encrypt(std::string plainText, std::string key_string, std::string iv_string,
	CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme padding_mode) {

	std::string cipherText;
	std::stringstream ss;

	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	memcpy(key, key_string.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memcpy(iv, iv_string.c_str(), CryptoPP::AES::BLOCKSIZE);

	CryptoPP::AES::Encryption AES_E(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption AES_CBC(AES_E, iv); 
	CryptoPP::StreamTransformationFilter AES_CBC_Encryptor(AES_CBC, new CryptoPP::StringSink(cipherText), padding_mode); 

	AES_CBC_Encryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
	AES_CBC_Encryptor.MessageEnd();

	for (int i = 0; i < cipherText.size(); i++) {
		ss << std::setw(2) << std::setfill('0') << std::hex << (0xFF & static_cast<CryptoPP::byte>(cipherText[i])) << " ";
	}

	return ss.str();
}

std::string AES_ECB_Encrypt(std::string plainText, std::string key_string,
	CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme padding_mode) {

	std::string cipherText;
	std::stringstream ss;

	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];

	memcpy(key, key_string.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

	CryptoPP::AES::Encryption AES_E(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode_ExternalCipher::Encryption AES_EBC(AES_E);
	CryptoPP::StreamTransformationFilter AES_EBC_Encryptor(AES_EBC, new CryptoPP::StringSink(cipherText), padding_mode);

	AES_EBC_Encryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
	AES_EBC_Encryptor.MessageEnd();

	for (int i = 0; i < cipherText.size(); i++) {
		ss << std::setw(2) << std::setfill('0') << std::hex << (0xFF & static_cast<CryptoPP::byte>(cipherText[i])) << " ";
	}

	return ss.str();
}

int main() {
	std::fstream out;
	out.open("aes-out.txt", std::fstream::out | std::fstream::trunc);

	std::string plainText = "AES is the US block cipher standard.";
	std::string key_string = "keyis84932731830";
	std::string iv_string;
	CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme padding_mode;

	iv_string = "0000000000000000";
	out << AES_CFB_Encrypt(plainText, key_string, iv_string)<<'\n';

	iv_string = "0000000000000000";
	padding_mode = CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING;
	out << AES_CBC_Encrypt(plainText, key_string, iv_string, padding_mode)<<'\n';

	iv_string = "9999999999999999";
	padding_mode = CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING;
	out << AES_CBC_Encrypt(plainText, key_string, iv_string, padding_mode) << '\n';

	padding_mode = CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING;
	out << AES_ECB_Encrypt(plainText, key_string, padding_mode) << '\n';

	/*std::string cipherText = "ac45d78068c2bd87c3f50dec9f898260";
	std::string ciphertextDecode;
	CryptoPP::StringSource ss(cipherText, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(ciphertextDecode)));
	std::string key_string = "1200000000000000";
	std::string iv_string = "0000000000000000";

	std::string decryptedtext;
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	memcpy(key, key_string.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memcpy(iv, iv_string.c_str(), CryptoPP::AES::BLOCKSIZE);

	CryptoPP::AES::Decryption AES_Decryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption AES_CBC_D(AES_Decryption, iv);
	CryptoPP::StreamTransformationFilter AES_CBC_Decryptor
	(AES_CBC_D, new CryptoPP::StringSink(decryptedtext), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING);
	AES_CBC_Decryptor.Put(reinterpret_cast<const unsigned char*>(ciphertextDecode.c_str()), ciphertextDecode.size());
	AES_CBC_Decryptor.MessageEnd();
	std::cout << "Decrypted Text: " << std::endl;
	std::cout << decryptedtext;
	std::cout << std::endl;*/
}