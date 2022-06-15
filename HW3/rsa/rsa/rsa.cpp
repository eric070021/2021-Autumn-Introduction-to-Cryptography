#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

#include "rsa.h"
#include "hex.h"
#include "filters.h"

using std::cout;
using std::hex;

//int main() {
//	std::fstream out;
//	out.open("out.txt", std::fstream::out | std::fstream::trunc);
//
//	CryptoPP::Integer n, e, d, r;
//	CryptoPP::RSA::PublicKey pubKey;
//	std::string message, cipher, cipherDecode;
//
//	message = "ElGamal";
//	n = CryptoPP::Integer("0xc963f963d93559ff");
//	e = CryptoPP::Integer("0x11");
//	pubKey.Initialize(n, e);
//	cout << hex << pubKey.ApplyFunction(CryptoPP::Integer((const CryptoPP::byte*)message.c_str(), message.size()))
//		<< '\n';
//
//	message = "Hello World!";
//	n = CryptoPP::Integer("0x04823f9fe38141d93f1244be161b20f");
//	e = CryptoPP::Integer("0x11");
//	pubKey.Initialize(n, e);
//	out << hex << pubKey.ApplyFunction(CryptoPP::Integer((const CryptoPP::byte*)message.c_str(), message.size()))
//		<< '\n';
//
//	message = "RSA is public key.";
//	n = CryptoPP::Integer("0x9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9");
//	e = CryptoPP::Integer("0x10001");
//	pubKey.Initialize(n, e);
//	out << hex << pubKey.ApplyFunction(CryptoPP::Integer((const CryptoPP::byte*)message.c_str(), message.size()))
//		<< '\n';
//
//	cipher = "a4a59490b843eea0";
//	CryptoPP::StringSource ss1(cipher, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(cipherDecode)));
//	n = CryptoPP::Integer("0xc45350fa19fa8d93");
//	d = CryptoPP::Integer("0x454a950c5bcbaa41");
//	pubKey.Initialize(n, d);
//	r = pubKey.ApplyFunction(CryptoPP::Integer((const CryptoPP::byte*)cipherDecode.c_str(), cipherDecode.size()));
//	message.resize(r.MinEncodedSize());
//	r.Encode((CryptoPP::byte*)message.data(), message.size());
//	cout << message << '\n';
//
//	cipherDecode.clear();
//	cipher = "a02d51d0e87efe1defc19f3ee899c31d";
//	CryptoPP::StringSource ss2(cipher, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(cipherDecode)));
//	n = CryptoPP::Integer("0xc4b361851de35f080d3ca7352cbf372d");
//	std::string guess, know = "0x53a0a95b089cf23adb5cc73f07";
//	std::stringstream ss;
//	bool bad = false;
//	
//	for (int test = 1; test != 1048577; test += 2) {
//		ss << std::setw(5) << std::setfill('0') << hex << test;
//		guess = know + ss.str();
//		d = CryptoPP::Integer(guess.c_str());
//		pubKey.Initialize(n, d);
//		r = pubKey.ApplyFunction(CryptoPP::Integer((const CryptoPP::byte*)cipherDecode.c_str(), cipherDecode.size()));
//		message.resize(r.MinEncodedSize());
//		r.Encode((CryptoPP::byte*)message.data(), message.size());
//
//		// check if the message has unprintable character
//		for (int i = 0; i < message.length(); i++) {
//			if ((int)message[i] < 32 || (int)message[i] > 126) {
//					bad = true;
//					break;
//			}
//		}
//
//		if (bad) {
//			bad = false;
//		}
//		else {
//			if (message == "Q-system 1") out << d << '\n' << message;
//			cout << "Private key:" << guess << " " << "Message:" << message << '\n';
//		}
//
//		ss.str("");
//		ss.clear();
//	}
//
//	return 0;
//}

int main() {
	CryptoPP::Integer n, e, d, r, cipherInt;
	CryptoPP::RSA::PublicKey pubKey;
	std::string message, cipher, cipherDecode;

	std::string guess, know = "0x53a0a95b089cf23adb5cc73f07";
	//cipher = "31639169974475525248366103533531939340";
	cipher = "17CD7B84439C06A54D58BB3BBD2FC215";
	CryptoPP::StringSource ss1(cipher, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(cipherDecode)));
	n = CryptoPP::Integer("0xBF0F7EF00E7F4D8DCB14073EA8630D65");
	d = CryptoPP::Integer("0x202DAE31A4A36CAE5D242917953AC601");
	pubKey.Initialize(n, d);
	r = pubKey.ApplyFunction(CryptoPP::Integer((const CryptoPP::byte*)cipherDecode.c_str(), cipherDecode.size()));
	message.resize(r.MinEncodedSize());
	r.Encode((CryptoPP::byte*)message.data(), message.size());
	cout << message << '\n';
}