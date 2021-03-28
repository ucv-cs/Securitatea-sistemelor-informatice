/**
 * T1: Implementati un sistem criptografic bazat pe functia XOR.
 * https://github.com/ucv-cs/Securitatea-sistemelor-informatice
 * Nota: era suficienta o singura functie xor pentru criptare/decriptare, insa
 * pentru ca aplicatia are optiunea (implicita) de afisare a outputului ca
 * numere hexazecimale, a fost necesara separarea functiilor de
 * criptare/decriptare.
 */

#include <cstdio>	 // sscanf()
#include <iomanip>	 // hex, setfill
#include <iostream>	 // cout, cin, endl
#include <sstream>	 // stringstream
#include <string>	 // getline(), stoi()

using namespace std;

// setarea implicita de afisare
bool hex_output = true;

/**
 * Cripteaza un text cu o cheie, folosind operatia xor.
 *
 * @param text
 * @param key
 * @return textul criptat
 */
string encrypt(string text, string key) {
	string result;
	stringstream temp;

	if (hex_output) {
		for (int i = 0; i < text.length(); i++) {
			// pentru fiecare caracter din input realizeaza xor cu fiecare
			// caracter din cheie, repetand, daca e cazul tot continutul cheii
			// + converteste fiecare int in format hexazecimal (2 caractere)
			temp << setfill('0') << setw(2) << hex
				 << int(text[i] ^ key[i % key.length()]);
		}
		result = temp.str();
	} else {
		for (int i = 0; i < text.length(); i++) {
			// pentru fiecare caracter din input realizeaza xor cu fiecare
			// caracter din cheie, repetand, daca e cazul tot continutul cheii
			text[i] = text[i] ^ key[i % key.length()];
		}
		result = text;
	}

	return result;
}

/**
 * Decripteaza un text cu o cheie, folosind operatia xor.
 *
 * @param text
 * @param key
 * @return textul decriptat
 */
string decrypt(string text, string key) {
	string result;
	string temp;

	if (hex_output) {
		// dacă outputul este in format hexazecimal, trebuie citite grupuri
		// de cate 2 caractere, apoi transformate in int
		for (int i = 0; i < text.length(); i++) {
			if ((i + 1) % 2 == 0) {
				int j;
				sscanf(text.substr(i - 1, 2).c_str(), "%x", &j);
				temp += char(j);
			}
		}
		text = temp;
	}

	for (int i = 0; i < text.length(); i++) {
		result += text[i] ^ key[i % key.length()];
	}

	return result;
}

/**
 * Pregateste cin pentru un nou input.
 */
void clear_cin() {
	cin.clear();			 // reseteaza starea bufferului cin
	cin.ignore(1000, '\n');	 // "goleste" bufferul cin
}

/**
 * Executia programului.
 */
int main(int argc, const char* argv[]) {
	// citeste argumentele programului
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-h") {
			// output reprezentat hexazecimal
			// implicit, reprezentarea este in ASCII
			hex_output = true;
		}
	}

	string plain_text;
	string cipher_text;
	string key;
	string separator = "\n----------------------\n";

	bool flag = true;
	while (flag) {
		// obtine de la utilizator textul in clar si cheia
		cout << "[*] Scrie textul de criptat: ";
		getline(cin, plain_text);
		cout << "[*] Scrie cheia: ";
		while (true) {
			getline(cin, key);
			if (key == "") {
				cout << "[!] Cheia nu poate fi goala: ";
				continue;
			}
			break;
		}

		// afiseaza textul criptat si pe cel decriptat (ca verificare)
		cipher_text = encrypt(plain_text, key);
		cout << "\n[*] Text criptat:   " << cipher_text << endl;
		cout << "[*] Text decriptat: " << decrypt(cipher_text, key) << endl;

		// controlul repetarii
		cout << "\n[?] Continuam? (d / n): ";
		char answer;
		cin >> answer;
		clear_cin();
		flag = (answer == 'd') ? true : false;
		cout << separator;
	}
}