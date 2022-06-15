#include <fstream>

#include "sha.h"
#include "osrng.h"
#include "hex.h"
#include "files.h"

int main() {
	// for comparision of how many zero 
	CryptoPP::byte zero[CryptoPP::SHA256::DIGESTSIZE];
	memset(zero, 0, CryptoPP::SHA256::DIGESTSIZE);

	CryptoPP::SHA256 hash;
	CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
	CryptoPP::AutoSeededRandomPool prng;
	CryptoPP::byte nonce[4];
	CryptoPP::byte preimage[CryptoPP::SHA256::DIGESTSIZE + 4];

	CryptoPP::HexEncoder hex_encoder;
	std::fstream file;
	file.open("out.txt", std::fstream::out | std::fstream::trunc);
	hex_encoder.Attach(new CryptoPP::FileSink(file));
	
	std::string msg = "0716234";
	hash.Update((const CryptoPP::byte*)msg.data(), msg.length());
	hash.Final(digest);
	
	unsigned int count = 0;
	for (uint8_t num = 0; num < 9; ++num) {
		file << +num << "\n";
		hex_encoder.PutMessageEnd(digest, CryptoPP::SHA256::DIGESTSIZE);
		file << "\n";

		memcpy(preimage, digest, CryptoPP::SHA256::DIGESTSIZE);
		do {
			prng.GenerateBlock(nonce, 4);
			memcpy(preimage + CryptoPP::SHA256::DIGESTSIZE, nonce, 4);

			hash.Update(preimage, CryptoPP::SHA256::DIGESTSIZE + 4);
			hash.Final(digest);

			if (count++ == 4294967294) break;
		} while (memcmp(digest, zero, num >> 1) != 0 || ((num % 2) && ((digest[(num >> 1)] >> 4) ^ zero[num >> 1]) != 0));

		hex_encoder.PutMessageEnd(nonce, 4);
		file << "\n";
		hex_encoder.PutMessageEnd(digest, CryptoPP::SHA256::DIGESTSIZE);
		file << "\n";
	}

	file.close();
	return 0;
}