#ifndef __DES_H__
#define __DES_H__
typedef unsigned char Data;
using namespace std;

class DES {
public:
	Data * states;
	Data *key;
	Data round_key[16][6];
	Data right[4];
	Data left[4];

public:
	DES(Data *PlainText, Data *Key) {
		states = PlainText;
		key = Key;
	}
	void Permutation(Data *return_arr, Data *States, Data *table, int length_bit);
	void Split(Data *split_arr, Data *Left, Data *Right);
	void encryption(Data *Cipher);
	void decryption(Data *PlainText, Data *Cipher);
	void SubkeyGenerator(Data *key);
	void Shift(Data*Subkey, Data round);
	void Sbox(Data *key, Data *Sbox);
	void function_f(Data *left, Data *right, Data round);
};
Data IP[];
Data IP_Inverse[];
Data Expansion[];
Data PC_1[];
Data PC_2[];
Data rotation[];
Data P[];
#endif
