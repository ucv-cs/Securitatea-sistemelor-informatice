#include <algorithm>  // sort()
#include <iostream>	  // cout, cin
#include <iterator>	  // istream_iterator
#include <sstream>	  // istringstream
#include <string>	  // to_string()
#include <vector>	  // vector<>

using namespace std;

unsigned seed;	// valoarea (starea) initiala

/**
 * Returneaza reprezentarea unui bit, data fiind o valoare initiala (seed) si
 * gradele termenilor (monoamelor) unui polinom de feedback (polynomial).
 * @param polynomial polinomul de feedback
 * @return output bit dupa o iteratie (ceas)
 */
unsigned lfsr(vector<unsigned> polynomial) {
	// XOR intre bitii tap
	unsigned feedback = seed >> (polynomial[0] - 1);
	for (auto i = 1; i < polynomial.size(); i++) {
		feedback ^= seed >> (polynomial[i] - 1);
	}

	// extrage outputul XOR-ului
	feedback &= 1;

	// seteaza primul bit ca rezultat al operatiei anterioare
	seed = (seed >> 1) | (feedback << (polynomial[0] - 1));

	// extrage ultimul bit din noua valoare a seed-ului
	return seed & 1;
}

/**
 * Pregateste cin pentru un nou input.
 */
void clear_cin() {
	cin.clear();			 // reseteaza starea bufferului cin
	cin.ignore(1000, '\n');	 // "goleste" bufferul cin
}

/**
 * Citeste o lista de numere naturale (separate prin spatii) pe care le adauga
 * in vectorul pentru polinom, sortat ulterior. Gradul maxim al polinomului este
 * 32 (numarul de biti din unsigned).
 * @param polynomial vectorul pentru polinom
 */
bool read_polynomial(vector<unsigned> &polynomial) {
	// citeste si valideaza inputul
	string input_numbers;
	getline(cin, input_numbers);

	istringstream buffer(input_numbers);
	istream_iterator<unsigned> start(buffer), end;
	polynomial = vector<unsigned>(start, end);

	// elimina valorile neacceptate
	polynomial.erase(
		remove_if(polynomial.begin(), polynomial.end(),
				  [](unsigned &e) { return (e <= 0) || (e > 32); }),
		polynomial.end());

	// daca nu mai exista nicio valoare valida, returneaza fals pentru repetare
	if (polynomial.size() == 0) {
		return false;
	}

	// sorteaza valorile descrescator
	sort(polynomial.begin(), polynomial.end(), greater<unsigned>());

	return true;
}

/**
 * Citeste un numar natural, pe care il adauga in variabila din input.
 * @param number variabila in care se citeste numarul
 */
void read_number(unsigned &number) {
	while (!(cin >> number)) {
		cout << "[!] Trebuie scris un numar natural!\nReincearca -> ";
		clear_cin();
	}
}

/**
 * Afiseaza descrierea LFSR-ului.
 * @param polynomial polinomul LFSR-ului
 * @param seed starea initiala
 */
void print_lfsr_description(vector<unsigned> polynomial, unsigned seed) {
	// pregateste un string pentru afisarea polinomului
	string poly = "";
	for (auto e : polynomial) {
		poly += "X^" + to_string(e) + " + ";
	}
	poly += "1";

	// calculeaza perioada maxima: 2^n - 1
	unsigned max_period = (1 << polynomial[0]) - 1;

	cout << "[*] Configuratia LFSR-ului\n----------------------\n"
			"Polinom generator: "
		 << poly << "\nGrad: " << polynomial[0] << "\nSeed: " << seed
		 << "\nTaps: " << polynomial.size()
		 << "\nPerioada maxima: " << max_period
		 << "\n----------------------\n\n";
}

/**
 * Executia programului.
 */
int main() {
	// polinomul LFSR-ului
	vector<unsigned> polynomial;

	// loop de input
	bool flag = true;
	while (flag) {
		// obtine o lista de numere: polynomial; ex. 7 1 => x^7 + x^1 + 1
		do {
			cout << "[*] Scrie puterile termenilor din polinomul generator "
					"(numere "
					"naturale nenule <= 32 separate prin spatiu; fara termenul "
					"constant):\n -> ";
		} while (!read_polynomial(polynomial));

		// obtine numarul de iteratii: limit
		unsigned limit;
		cout << "[*] Scrie lungimea sirului care trebuie generat:\n -> ";
		read_number(limit);

		// obtine starea initiala: seed
		cout << "[*] Scrie valoarea initiala (seed):\n -> ";
		read_number(seed);

		// afiseaza descrierea LFSR-ului
		print_lfsr_description(polynomial, seed);

		// afiseaza sirul de biti
		cout << "[*] Sirul generat este:\n";
		for (auto i = 0; i < limit; i++) {
			cout << lfsr(polynomial);
		}

		// controlul repetarii
		cout << "\n\n[?] Continuam? (d / n): ";
		char answer;
		cin >> answer;
		clear_cin();
		flag = (answer == 'd') ? true : false;
		cout << "------------------------\n";
	}
}