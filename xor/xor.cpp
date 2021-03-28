/**
 * T1: Implementati un sistem criptografic bazat pe functia XOR.
 * https://github.com/ucv-cs/Securitatea-sistemelor-informatice
 */

#include <iostream>	 // cout, cin, endl
#include <string>	 // getline()

using namespace std;

bool hex_output = false;

// string int_as_hex(string text) {

// }

// string hex_as_int(string text) {
// }

/**
 * Cripteaza/decripteaza un text cu o cheie, folosind operatia xor.
 *
 * @param text
 * @param key
 * @return textul criptat/decriptat
 */
string xor_string(string text, string key) {
	for (int i = 0; i < text.length(); i++) {
		// pentru fiecare caracter din input realizeaza xor cu fiecare caracter
		// din cheie, repetand, daca e cazul tot continutul cheii
		text[i] = text[i] ^ key[i % key.length()];
	}

	return text;
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
		cipher_text = xor_string(plain_text, key);
		cout << "\n[*] Text criptat:   " << cipher_text << endl;
		cout << "[*] Text decriptat: " << xor_string(cipher_text, key) << endl;

		// controlul repetarii
		cout << "\n[?] Continuam? (d / n): ";
		char answer;
		cin >> answer;
		clear_cin();
		flag = (answer == 'd') ? true : false;
		cout << separator;
	}
}