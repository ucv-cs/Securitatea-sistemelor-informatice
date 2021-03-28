"""
T1: Implementati un sistem criptografic bazat pe functia XOR.
https://github.com/ucv-cs/Securitatea-sistemelor-informatice
"""
import sys

# setarea implicită de afișare
hex_output = True


def encrypt(text, key):
	"""
	Criptează un text cu o cheie, folosind operația xor.
	@param text
	@param key
	@returns textul criptat
	"""
	result = ""
	if hex_output:
		for i in range(len(text)):
			result += hex(ord(text[i]) ^ ord(key[i % len(key)]))[2:].zfill(2)
	else:
		for i in range(len(text)):
			result += chr(ord(text[i]) ^ ord(key[i % len(key)]))

	return result


def decrypt(text, key):
	"""
	Decriptează un text cu o cheie, folosind operația xor.
	@param text
	@param key
	@returns textul decriptat
	"""
	result = ""
	temp = ""
	if hex_output:
		# dacă outputul este în format hexazecimal, trebuie citite grupuri
		# de câte 2 caractere, apoi transformate în int
		for i in range(len(text)):
			if (i + 1) % 2 == 0:
				s = "0x" + text[i - 1] + text[i]
				temp += chr(int(eval(s)))
		text = temp

	for i in range(len(text)):
		result += chr(ord(text[i]) ^ ord(key[i % len(key)]))

	return result


def main():
	"""
	Execuția programului.
	"""
	# switch pentru afișarea textului criptat în format ASCII sau
	# hexazecimal (implicit)
	# utilizare: py -i affine.py -a
	if "-a" in str(sys.argv):
		global hex_output
		hex_output = False

	separator = "\n----------------------"

	# input de la utilizator
	flag = True
	while flag:
		plain_text = input("[*] Scrie textul de criptat: ")
		while True:
			key = input("[*] Scrie cheia: ")
			if key == "":
				continue
			else:
				break

		# output
		cipher_text = encrypt(plain_text, key)
		print(f"\n[*] Text criptat:   {cipher_text}")
		print(f"[*] Text decriptat: {decrypt(cipher_text, key)}")

		flag = True if input(
		    "\n[?] Continuăm? (d / n): ").lower() == "d" else False
		print(separator)


if __name__ == "__main__":
	main()