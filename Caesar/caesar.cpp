/**
 * Cifrul Caesar.
 * - lungimea alfabetului: m (ex. 26)
 * - cheia: k
 * - functia de criptare: E(x) = (x + k) mod m
 * - functia de decriptare: D(x) = (x - k) mod m
 *
 * Specificatii suplimentare:
 * - alfabetul trebuie sa fie mai flexibil (ex. sa poata include setul ASCII
 * printabil: de la 32 = spatiu la 126 = ~); alfabetul are maparea (ASCII ->
 * index): 32 -> 0; 33 -> 1 ...; 126 -> 94
 * N.B.: programul poate prezenta si urme de validare a inputului :)
 */

#include <iostream>	 // cin, cout, endl
#include <string>	 // getline()
using namespace std;

// limitele alfabetului utilizat, prin raportare la valorile ASCII
// implicit: A-Z, dar poate deveni <space>-~, daca programul ruleaza cu -e
int low_char = 65;	// = A
int up_char = 90;	// = Z
int m;				// lungimea alfabetului

/**
 * Reimplementare a operatiei modulo, pentru rezultate ca in Python.
 * @source https://stackoverflow.com/a/1907585
 *
 * @param a
 * @param b
 * @return modulo implementat ca in Python
 */
int mod(int a, int b) {
	return ((a % b) + b) % b;
}

/**
 * Realizeaza criptarea pentru fiecare caracter dupa formula: (x + k) mod m.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul criptat
 */
string encrypt(string text, int key) {
	string result;
	for (int i = 0; i < text.length(); i++) {
		result += char(mod(text[i] - low_char + key, m) + low_char);
	}

	return result;
}

/**
 * Realizeaza decriptarea pentru fiecare caracter dupa formula: (x - k) mod m.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul decriptat
 */
string decrypt(string text, int key) {
	string result;
	for (int i = 0; i < text.length(); i++) {
		result += char(mod(text[i] - low_char - key, m) + low_char);
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
		if (string(argv[i]) == "-e") {
			// limitele setului ASCII printabil
			// (implicit sunt A-Z)
			low_char = 32;	// = spatiu
			up_char = 126;	// = ~
		}
	}

	// lungimea alfabetului
	m = 1 + up_char - low_char;

	string plain_text;
	string cipher_text;
	string separator = "\n------------------------\n";
	int key;

	// afiseaza configuratia
	cout << "Configuratie\nAlfabet:\n";
	for (int i = 0; i < m; i++) {
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

		// obtine cheia si verifica indeplinirea conditiei: a si m coprime
		//  <=> (gcd(a, m) = 1); repeta solicitarea pana cand conditia se
		//  indeplineste
		cout << "[*] Scrie cheia (numar intreg): ";
		while (!(cin >> key)) {
			cout << "[!] Trebuie scris un numar intreg: ";
			clear_cin();
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