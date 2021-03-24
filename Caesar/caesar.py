"""
Implementare a algoritmului de criptare Caesar.
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

	for i in text:
		l = alphabet.find(i)
		result += alphabet[(l + key) % m]
	return result


def decrypt(text, key):
	"""
	Decriptează un text, folosind cheia dată.
	@param text
	@param key
	@returns text decriptat
	"""
	result = ""

	for i in text:
		l = alphabet.find(i)
		result += alphabet[(l - key) % m]
	return result


#aliasuri pentru scriere rapidă
e = encrypt
d = decrypt
gen = alphabet_generator

#switch între setul ASCII extins și cel de 26 de caractere;
# TODO: ar trebui făcută verificarea inputului în funcție de setul ales...
# utilizare: py -i caesar.py -e
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
	plain_text = t = input("Scrie textul clar: ")
	while True:
		try:
			key = int(input("[*] Scrie cheia (număr întreg): "))
			break
		except:
			print("[!] Trebuie scris un număr întreg!")

	k = key

	#output
	cipher_text = c = encrypt(plain_text, key)
	print(f"[*] Text criptat:   {cipher_text}")
	print(f"[*] Text decriptat: {decrypt(cipher_text, key)}")

	flag = True if input(
	    "\n[?] Continuăm? (d / n): ").lower() == "d" else False
