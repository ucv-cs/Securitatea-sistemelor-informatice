/**
 * Algoritmul Vigenere.
 * - varianta pe baza de matrice...
 * https://github.com/ucv-cs/Securitatea-sistemelor-informatice
 */

#include <iostream>	 // cin, cout, endl
#include <string>	 // getline(), toupper()
using namespace std;

// limitele alfabetului utilizat, prin raportare la valorile ASCII
int low_char = 65;	// = A
int up_char = 90;	// = Z
#define m 26		// lungimea alfabetului; m = 1 + up_char - low_char

// tabula recta cu alfabetul standard
// https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
char tabula[m][m];

/**
 * Completeaza o matrice de tip tabula recta, pentru cifrul Vigenere.
 *
 * @param matrix tabula deja alocata
 */
void fill_tabula(char matrix[m][m]) {
	char k;
	for (int i = 0; i < m; i++) {
		k = i;
		for (int j = 0; j < m; j++) {
			matrix[i][j] = k + low_char;
			k++;
			if (k == m) {
				k = 0;
			}
		}
	}
}

/**
 * Realizeaza criptarea pentru fiecare caracter folosind tabula recta.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul criptat
 */
string encrypt(string text, string key) {
	for (int i = 0; i < text.length(); i++) {
		// cf. pasilor de aici, pentru criptare:
		// https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#Description
		// linia = litera curenta din input (pentru index 0-based, trebuie
		// scazuta limita inferioara a alfabetului)
		// coloana = litera curenta din cheia repetata (daca e necesar)
		text[i] = tabula[text[i] - low_char][key[i % key.length()] - low_char];
	}

	return text;
}

/**
 * Realizeaza decriptarea pentru fiecare caracter folosind tabula recta.
 *
 * @param text inputul
 * @param key cheia
 * @return stringul decriptat
 */
string decrypt(string text, string key) {
	for (int i = 0; i < text.length(); i++) {
		for (int j = 0; j < m; j++) {
			// cf. pasilor de aici, pentru decriptare:
			// https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#Description
			// linia = litera curenta din cheia repetata (daca e necesar)
			// coloana  =
			// 1. gaseste pe linie celula in care se afla litera curenta din
			// input;
			// 2. gaseste coloana in care se afla celula, folosind prima linie,
			// ce corespunde alfabetului simplu
			if (tabula[key[i % key.length()] - low_char][j] == text[i]) {
				text[i] = tabula[0][j];
				break;
			}
		}
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
	for (int i = 0; i < text.length(); i++) {
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
	for (int i = 0; i < text.length(); i++) {
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

	// completeaza in memorie tabula recta
	fill_tabula(tabula);

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