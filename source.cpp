#include<iostream>
#include"des.h"

Data s_box[8][4][16] =
{
	{
		{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
	},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
	}
};

Data pow2(Data num, Data exp) {
	return exp > 0 ? pow2(num * 2, exp - 1) : num;
}
void Print(Data *arr, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
Data Bit_Checker(Data States, Data bit_offset, Data table_bit_offset) {
	Data pownum = pow2(1, 7 - bit_offset);
	Data check_num = States & pownum;
	if (check_num == 0) {
		return 0;
	}
	else {
		return pow2(1, 7- table_bit_offset);
	}

}
void DES::Split(Data *split_arr, Data *Left, Data *Right) {
	for (int i = 0; i < 8; i++) {
		if (i < 4)
			Left[i] = split_arr[i];
		else
			Right[i - 4] = split_arr[i];
	}
}
void DES::Permutation(Data *return_arr, Data *States, Data *table, int length_bit) {
	for (int i = 0; i < length_bit; i++) {
		Data block_offset = (table[i] - 1) / 8;
		Data bit_offset = (table[i] - 1) % 8;
		return_arr[i / 8] += Bit_Checker(States[block_offset], bit_offset,i%8);
	}
}
void Combine(Data *combine, Data *left, Data*right) {
	for (int i = 0; i < 8; i++) {
		if (i < 4)
			combine[i] = left[i];
		else
			combine[i] = right[i % 4];
	}
}
void CopyLR(Data *temp, Data *arr) {
	for (int i = 0; i < 4; i++)
		temp[i] = arr[i];
}
void SetLR(Data *arr, Data *temp) {
	for (int i = 0; i < 4; i++) {
		arr[i] = temp[i];
	}
}
void CopySubKey(Data *return_arr, Data *SubKey) {
	for (int i = 0; i <= 7; i++) {
		return_arr[i] = SubKey[i];
	}
}
void DES::function_f(Data *Left, Data *Right, Data round) {
	Data expansion[6] = { 0 };
	Data Permute_Sbox[4] = { 0 };
	Data Permute_P[4] = { 0 };
	Permutation(expansion, Right, Expansion, 48);	
	for (int i = 0; i < 6; i++) {
		expansion[i] ^= round_key[round][i];
	}
	//S_box 치환
	Sbox(expansion,Permute_Sbox);
	Permutation(Permute_P, Permute_Sbox, P, 32);
		for (int i = 0; i < 4; i++) 
			Right[i] = Left[i] ^ Permute_P[i];	
	
}
void DES::SubkeyGenerator(Data *key) {
	Data SubKey[7] = { 0 };
	Data receive_SubKey[7] = { 0 };
	Permutation(SubKey, key, PC_1, 56);
	for (int i = 0; i < 16; i++) {
		Permutation(round_key[i], SubKey, PC_2, 48);
	}
}
void DES::Shift(Data *SubKey,Data round) {
	Data Shift_time = rotation[round];
	for (int k = 0; k < Shift_time; k++) {
		Data left_first = (SubKey[0] & 128) / 8;
		Data right_first = (SubKey[3] & 8) / 8;
		Data Subkey4_first = (SubKey[4] & 128) / 128;
		Data Subkey3_left = ((SubKey[3] & 240) << 1) + left_first;
		Data Subkey3_right = ((SubKey[3] << 1) & 15) + Subkey4_first;
		for (int i = 0; i < 6; i++) {
			if ((SubKey[i + 1] & 128) > 0) {
				SubKey[i] <<= 1;
				SubKey[i] += 1;
			}
			else {
				SubKey[i] <<= 1;
			}
		}

		SubKey[3] = 0;
		SubKey[3] = Subkey3_left + Subkey3_right;
		SubKey[6] <<= 1;
		SubKey[6] += right_first;
	}
}
void DES::Sbox(Data *key, Data *PermuteSbox) {
	Data col = 0;
	Data row = 0;
	Data block_flag = 0;
	Data sbox_block_flag = 0;
	for (int i = 0; i < 8; i++) {
		if (i == 0 || i == 4){
			col = key[block_flag] & 128;
			col >>= 6;
			col += ((key[block_flag] & 4)>>2);
			row = key[block_flag] & 120;
			row >>= 3;
		}
		else if (i == 3 || i == 7) {
			col = key[block_flag] & 32;
			col >>= 4;
			col += (key[block_flag] & 1);
			row = key[block_flag] & 30;
			row >>= 1;
			block_flag++;
			
		}
		else if (i == 1 || i == 5) {
			col = key[block_flag] & 2;
			row = key[block_flag] & 1;
			row <<= 3;
			block_flag++;
			col += (key[block_flag] & 16) >> 4;
			row += (key[block_flag] & 224) >> 5;
		}
		else if (i == 2 || i == 6) {
			col = key[block_flag] & 8;
			row = key[block_flag] & 7;
			col >>= 2;
			row <<= 1;
			block_flag++;
			col += (key[block_flag] & 64) >> 6;
			row += (key[block_flag] & 128) >> 7;
		}
		if (i % 2 == 1) {
			PermuteSbox[sbox_block_flag] += (s_box[i][col][row]);
			sbox_block_flag++;
		}
		else 
			PermuteSbox[sbox_block_flag] += (s_box[i][col][row]) * 16;
		col = 0;
		row = 0;
	}

}
void DES::encryption(Data *Cipher) {
	Data right_temp[4] = { 0 }; 
	Data InitPermute[8] = { 0 };
	Data cipher[8] = { 0 };
	Data combine[8] = { 0 };
	Permutation(InitPermute, states, IP, 64); // 초기 치환
	Split(InitPermute, left, right); // 초기 치환 32비트씩 좌우 분리
	for (int round = 0; round < 16; round++) {
		CopyLR(right_temp, right);
		function_f(left, right, round);
		SetLR(left, right_temp);
	}
	Combine(combine, right,left);
	Print(combine, 8);
	Permutation(Cipher, combine, IP_Inverse, 64);
	cout << "Cipher : ";
	Print(Cipher, 8);
}
void DES::decryption(Data *PlainText,Data *Cipher) {
	Data right_temp[4] = { 0 }; // Round에서 오른쪽 연산전 왼쪽에 저장
	Data InitPermute[8] = { 0 };
	Data combine[8] = { 0 };
	Permutation(InitPermute, Cipher, IP, 64); // 초기 치환
	Split(InitPermute, left, right); // 초기 치환 32비트씩 좌우 분리
	for (int round = 15; round >=0; round--) {
		CopyLR(right_temp, right);
		function_f(left, right, round);
		SetLR(left, right_temp);
	}
	Combine(combine, right, left);
	Permutation(PlainText, combine, IP_Inverse, 64);
}

int main(int argc, char *argv[]) {
	
	Data PlainText[8] = "asdsaad";
	Data key[8] = {12,34,5,7,8,9,0,1 };
	Data return_arr[8] = { 0 };
	DES des(PlainText, key);
	Data Cipher[8] = { 0 };
	Print(PlainText, 8);
	des.SubkeyGenerator(key);
	des.encryption(Cipher);	
	des.decryption(return_arr,Cipher);
	for (int i = 0; i < 8; i++) {
		printf("%c", Cipher[i],Cipher[i]);
	}
	cout << endl;
	for (int i = 0; i < 8; i++) {
		printf("%c ", return_arr[i]);
	}

	
	return 0;
}
