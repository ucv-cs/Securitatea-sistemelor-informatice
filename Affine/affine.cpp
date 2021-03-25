/**
 * Cifrul afin.
 * - lungimea alfabetului: m (ex. 26)
 * - cheia: K = (a, b)
 * - conditie: a si m coprime (gcd(a, m) = 1)
 * - functia de criptare: E(x) = (ax + b) mod m
 * - functia de decriptare: D(x) = a_inv (x - b) mod m, unde a_inv este
 * simetricul lui a in Zm
 *
 * Specificatii suplimentare:
 * - alfabetul trebuie sa fie mai flexibil (ex. sa poata include setul ASCII
 * printabil: de la 32 = spatiu la 126 = ~); alfabetul are maparea (ASCII ->
 * index): 32 -> 0; 33 -> 1 ...; 126 -> 94
 * N.B.: programul poate prezenta si urme de validare a inputului :)
 * https://github.com/ucv-cs/Securitatea-sistemelor-informatice
 */

#include <iostream>	 // cin, cout, endl
#include <string>	 // getline()
using namespace std;

// limitele alfabetului utilizat, prin raportare la valorile ASCII
// implicit: A-Z, dar poate deveni <space>-~, daca programul ruleaza cu -e
int low_char = 65;	// = A
int up_char = 90;	// = Z
int m;				// lungimea alfabetului

// cheia K = (a, b)
struct K {
	int a;
	int b;
};

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
 * Calculeaza CMMDC a doua numere (necesar pentru a testa daca doua
 * numere sunt coprime = prime intre ele: au CMMDC = 1).
 *
 * @param a primul numar
 * @param b al doilea numar
 * @return CMMDC(a, b)
 */
int gcd(int a, int b) {
	// normalizeaza numerele, intrucat: GCD(a, b) = GCD(|a|, |b|)
	a = abs(a);
	b = abs(b);

	while (a != b) {
		if (a > b) {
			a -= b;
		} else {
			b -= a;
		}
	}

	return a;
}

/**
 * Calculeaza inversul (simetricul) unui numar a in multimea Zm.
 *
 * @param a numarul de inversat in Zm
 * @param m dimensiunea multimii Z
 * @return inversul lui a in Zm
 */
int invert(int a, int m) {
	for (int s = 1; s < m; s++) {
		if (mod((mod(a, m) * mod(s, m)), m) == 1) {
			return s;
		}
	}

	return 0;
}

/**
 * Realizeaza criptarea pentru fiecare caracter dupa formula: E(x) = (ax + b)
 * mod m.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul criptat
 */
string encrypt(string text, struct K key) {
	string result;
	for (int i = 0; i < text.length(); i++) {
		result += char(mod(key.a * (text[i] - low_char) + key.b, m) + low_char);
	}

	return result;
}

/**
 * Realizeaza decriptarea pentru fiecare caracter dupa formula: D(x) = a_inv (x
 * - b) mod m.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul decriptat
 */
string decrypt(string text, struct K key) {
	string result;
	int a_inv = invert(key.a, m);
	for (int i = 0; i < text.length(); i++) {
		result += char(mod(a_inv * (text[i] - low_char - key.b), m) + low_char);
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
	struct K key;

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
		cout << "[*] Scrie cheia (numerele a si b separate prin spatiu): ";
		while (!(cin >> key.a >> key.b) || key.a == 0) {
			cout << "[!] Trebuie scrise doua numere intregi nenule: ";
			clear_cin();
		}

		while (gcd(key.a, m) != 1) {
			cout << "[!] a si m = " << m
				 << " trebuie sa fie coprime.\n[!] Scrie o alta valoare pentru "
					"a: ";
			while (!(cin >> key.a) || key.a == 0) {
				clear_cin();
				cout << "[!] Trebuie scris un numar intreg nenul: ";
			}
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