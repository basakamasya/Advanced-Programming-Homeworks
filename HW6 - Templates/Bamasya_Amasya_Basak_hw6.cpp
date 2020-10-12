//Basak Amasya
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
class Encrypter {
private:
	const T key;
	const int nShifts;

public:
	vector<int> listFlips;
	Encrypter(T, int, vector<int>);
	T encrypt(const T decrypted);
	T decrypt(const T encrypted);
};

template <typename T> 
Encrypter<typename T>::Encrypter(T key, int nShifts, vector<int> listFlips): key(key), nShifts(nShifts), listFlips(listFlips) //using initializer list
{
}

template <typename T>
T Encrypter<typename T>::encrypt(const T decrypted)
{
	vector<int> newlistflips;
	T result;
	int newnShifts, size;
	unsigned int MSB;
	long long int mask = 1;
	size = sizeof(decrypted) * 8; //getting the size of the T in terms of bit
	result = decrypted ^ key; //XOR operation
	cout << "Xor result:" << result << endl;
	if (nShifts >= size ) 	//circular shifting
	{
		newnShifts = nShifts % size; //getting the modulus if nshifts is bigger or equal to size
	}
	else
	{
		newnShifts = nShifts;
	}
	for (int x = 0; x < newnShifts; x ++) //shifting the result one by one, newnShifts times
	{
		MSB = result & (mask << (size - 1));
		result = result << mask;
		result = result | (MSB >> (size - 1));
	}
	cout << "Shift result: " << result << endl;
	for (int i = 0; i < listFlips.size(); i++) //flipping the bits
	{
		if (listFlips[i] < size)
		{
			newlistflips.push_back(listFlips[i]);
			if (result & ( mask << listFlips[i])) //mask is equal to 1
			{
				result = result & (~(mask << listFlips[i]));
			}
			else
			{
				result = result | (mask << listFlips[i]);
			}
		}
	}
	listFlips = newlistflips; //updating the listFlips
	return result;	
}

template <typename T>
T Encrypter<typename T>::decrypt(const T encrypted)
{
	T result = encrypted;
	unsigned int newnShifts, size, LSB;
	size = sizeof(encrypted) * 8;
	long long int mask = 1;
	for (int i = 0; i < listFlips.size(); i++) //flipping bits, same way done in the encrypter
	{
		if (listFlips[i] < size)
		{
			if (result & (mask << listFlips[i]))
			{
				result = result & (~(mask << listFlips[i])); //mask is equal to 1
			}
			else
			{
				result = result | (mask << listFlips[i]);
			}
		}
	}
	if (nShifts >= size ) //circular shifting
	{
		newnShifts = nShifts % size;
	}
	else
	{
		newnShifts = nShifts;
	}
	for (int x = 0; x < newnShifts; x ++) //shifting the bits back one by one, newnShifts times
	{
		LSB = result & 1;
		result = result >> 1;
		result = result | (LSB << (size - 1));
	}
	result = result ^ key; 	//XOR operation
	return result;
}


int main() {

	int nShifts = 12;
	vector<int> listFlips; //added by me
	listFlips.push_back(1);
	listFlips.push_back(2);
	listFlips.push_back(3);
	listFlips.push_back(4);
	listFlips.push_back(9);
	listFlips.push_back(15);
	listFlips.push_back(30);
	listFlips.push_back(35);
	listFlips.push_back(0);
	//vector<int> listFlips = { 0,1,2,3,4,9,15,30,35 }; //does not work in VS 2012

	unsigned char key1 = 101;
	unsigned char chClear = 'b';
	Encrypter<unsigned char> encrypterChar(key1, nShifts, listFlips);

	cout << "Char to encrypt: " << chClear << endl;
	unsigned char encryptedCh = encrypterChar.encrypt(chClear);
	unsigned char decryptedCh = encrypterChar.decrypt(encryptedCh);

	cout << "Char encrypted: " << encryptedCh << endl;
	cout << "Char decrypted: " << decryptedCh << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterChar.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;

	unsigned short int key2 = 101;
	unsigned short int intShortClear = 500;
	Encrypter<unsigned short int> encrypterShortInt(key2, nShifts, listFlips);

	cout << "Short Int to encrypt: " << intShortClear << endl;
	unsigned short int encryptedShortInt = encrypterShortInt.encrypt(intShortClear);
	unsigned short int decryptedShortInt = encrypterShortInt.decrypt(encryptedShortInt);

	cout << "Short Int encrypted: " << encryptedShortInt << endl;
	cout << "Short Int decrypted: " << decryptedShortInt << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterShortInt.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;

	unsigned int key3 = 101;
	unsigned int intClear = 32800;
	Encrypter<unsigned int> encrypterInt(key3, nShifts, listFlips);

	cout << "Int to encrypt: " << intClear << endl;
	unsigned int encryptedInt = encrypterInt.encrypt(intClear);
	unsigned int decryptedInt = encrypterInt.decrypt(encryptedInt);

	cout << "Int encrypted: " << encryptedInt << endl;
	cout << "Int decrypted: " << decryptedInt << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterInt.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;

	unsigned long long int key4 = 101;
	unsigned long long int intLLClear = 34359738368;
	Encrypter<unsigned long long int> encrypterLLInt(key4, nShifts, listFlips);

	cout << "Long Long Int to encrypt: " << intLLClear << endl;
	unsigned long long int encryptedLLInt = encrypterLLInt.encrypt(intLLClear);
	unsigned long long int decryptedLLInt = encrypterLLInt.decrypt(encryptedLLInt);

	cout << "Long Long Int encrypted: " << encryptedLLInt << endl;
	cout << "Long Long Int decrypted: " << decryptedLLInt << endl;
	cout << "List of flipped bits: ";
	for (int i : encrypterLLInt.listFlips) {
		cout << i << " ";
	}
	cout << endl << endl;


	system("pause");
	return 0;
}