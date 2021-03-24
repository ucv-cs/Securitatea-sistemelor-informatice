"""
Implementare a algoritmului de criptare Affine.
"""
import sys


def alphabet_generator(low_char=65, up_char=90):
	"""
	Creează o listă de caractere ASCII, între limitele specificate.
	Limitele implicite sunt: 65=A, 90=Z.
	@param low_char valoarea ASCII pentru limita inferioară
	@param up_char valoarea ASCII pentru limita superioară
	@returns lista
	"""
	result = ""
	for i in [chr(i) for i in range(low_char, up_char + 1)]:
		result += i
	return result


def encrypt(text, key):
	"""
	Criptează un text, folosind cheia dată.
	@param text
	@param key
	@returns text criptat
	"""
	result = ""
	a = key[0]
	b = key[1]

	for i in text:
		l = alphabet.find(i)
		result += alphabet[(a * l + b) % m]
	return result


def decrypt(text, key):
	"""
	Decriptează un text, folosind cheia dată.
	@param text
	@param key
	@returns text decriptat
	"""
	result = ""
	a = key[0]
	b = key[1]
	a_inv = invert(a, m)
	s = 0

	for i in text:
		l = alphabet.find(i)
		result += alphabet[(a_inv * (l - b)) % m]
	return result


def invert(a, m):
	"""
	Calculează inversul (simetricul) unui număr a în mulțimea Zm.
	@param a numărul de inversat în Zm
	@param m dimensiunea mulțimii Z
	@returns inversul lui a în Zm
	"""
	s = 0
	for i in range(1, m):
		if (((a % m) * (s % m)) % m == 1):
			return s
		s += 1


def gcd(a, b):
	"""
	Calculează CMMDC a două numere.
	@param a
	@param b
	@returns CMMDC(a, b)
	"""
	a = abs(a)
	b = abs(b)

	while a != b:
		if a > b:
			a -= b
		else:
			b -= a

	return a


#aliasuri pentru scriere rapidă
e = encrypt
d = decrypt
gen = alphabet_generator
i = invert

#switch între setul ASCII extins și cel de 26 de caractere;
# TODO: ar trebui făcută verificarea inputului în funcție de setul ales...
# utilizare: py -i affine.py -e
if "-e" in str(sys.argv):
	low_char = 32
	up_char = 126
	print("Alfabetul selectat este: 32 <space>... 126 ~")
else:
	low_char = 65
	up_char = 90
	print("Alfabetul selectat este: 65 A... 90 Z")

#alfabetul ASCII extins la caracterele printabile
alphabet = alphabet_generator(low_char, up_char)  # hardcodat pentru teste
m = len(alphabet)
print(f"Lungimea alfabetului: m = {m}")

#input de la utilizator
flag = True
while flag:
	plain_text = t = input("[*] Scrie textul care trebuie criptat (ASCII): ")
	print("[*] Scrie cheia:")
	a = b = 1
	while True:
		try:
			a = int(input("[*] a = "))
			# verificarea condiției: gcd(a, m) = 1
			if gcd(a, m) != 1:
				a = int(
				    input(
				        f"[!] a și m = {m} trebuie să fie coprime.\n[!] Scrie o altă valoare pentru "
				        "a: "))
			b = int(input("[*] b = "))
			break
		except:
			print("[!] Trebuie scrise numere întregi!")

	key = k = (a, b)

	#output
	cipher_text = c = encrypt(plain_text, key)
	print(f"[*] Text criptat:   {cipher_text}")
	print(f"[*] Text decriptat: {decrypt(cipher_text, key)}")

	flag = True if input(
	    "\n[?] Continuăm? (d / n): ").lower() == "d" else False
