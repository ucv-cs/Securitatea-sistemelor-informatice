/**
 * Algoritmul Vigenere.
 * - lungimea alfabetului: m (= 26)
 * - cheia: k
 * - functia de criptare: E(x) = (xi + ki) mod m
 * - functia de decriptare: D(x) = (xi - ki + m) mod m
 * https://github.com/ucv-cs/Securitatea-sistemelor-informatice
 */

#include <iostream>	 // cin, cout, endl
#include <string>	 // getline(), toupper()
using namespace std;

// limitele alfabetului utilizat, prin raportare la valorile ASCII
unsigned low_char = 65;				  // = A
unsigned up_char = 90;				  // = Z
unsigned m = 1 + up_char - low_char;  // lungimea alfabetului

/**
 * Realizeaza criptarea pentru fiecare caracter dupa formula: (xi + ki) mod m.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul criptat
 */
string encrypt(string text, string key) {
	for (unsigned i = 0; i < text.length(); i++) {
		text[i] = (text[i] + key[i % key.length()]) % m + low_char;
	}

	return text;
}

/**
 * Realizeaza decriptarea pentru fiecare caracter dupa formula: (xi - ki + m)
 * mod m.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul decriptat
 */
string decrypt(string text, string key) {
	for (unsigned i = 0; i < text.length(); i++) {
		text[i] = (text[i] - key[i % key.length()] + m) % m + low_char;
	}

	return text;
}

/**
 * Returneaza un text in care toate caracterele inputului sunt uppercase.
 *
 * @param text
 * @return text uppercase
 */
string upper(string text) {
	for (unsigned i = 0; i < text.length(); i++) {
		text[i] = toupper(text[i]);
	}

	return text;
}

/**
 * Returneaza textul din input fara caracterele din afara alfabetului.
 *
 * @param text
 * @return text modificat
 */
string clear_unknown_chars(string text) {
	string result;
	for (unsigned i = 0; i < text.length(); i++) {
		if (text[i] >= low_char && text[i] <= up_char) {
			result += text[i];
		}
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
int main() {
	string plain_text;
	string cipher_text;
	string separator = "\n------------------------\n";
	string key;

	// afiseaza configuratia
	cout << "Configuratie\nAlfabet:\n";
	for (unsigned i = 0; i < m; i++) {
		cout << char(i + low_char) << " ";
		if ((i + 1) % 12 == 0) {
			cout << endl;
		}
	}
	cout << "\nLungime: m = " << m << separator;

	bool flag = true;
	while (flag) {
		// obtine de la utilizator textul in clar
		cout << "[*] Scrie textul care trebuie criptat (ASCII): ";
		getline(cin, plain_text);

		// obtine cheia
		cout << "[*] Scrie cheia (litere ale alfabetului acceptat): ";
		getline(cin, key);

		// proceseaza inputul (textul in clar si cheia)
		// 1. converteste literele in uppercase
		plain_text = upper(plain_text);
		key = upper(key);
		// 2. elimina caracterele necunoscute din string
		plain_text = clear_unknown_chars(plain_text);
		key = clear_unknown_chars(key);

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