#include <iostream>
#include <string>

using namespace std;

int main() {
	string str;
	int a_num = 0, b_num = 0, c_num = 0, d_num = 0, e_num = 0, error_addr_num = 0, private_ip_num = 0;
	while (cin >> str) {
		string ip_addr;
		string mask_addr;
		bool formmer_or_latteer = false;
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '~') formmer_or_latteer = true;
			if (formmer_or_latteer) {
				ip_addr = str.substr(0, i);
				mask_addr = str.substr(i+1);
				break;
			}
		}
		int index = 0;
		int type_ip = 0;
		int private_ip_statu = 0;
		switch (index)
		{
		case 0:
			{
				int dot_position = ip_addr.find_first_of('.');
				if (dot_position == 0 || ip_addr.find_first_of('.') == string::npos) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
				}
				int ip_first_value = stoi(ip_addr.substr(0, dot_position));

				if (ip_first_value < 128 && ip_first_value > 0) {
					type_ip = 1;
					if (ip_first_value == 10) private_ip_statu = 11;
				}
				else if (ip_first_value < 192) {
					type_ip = 2;
					if (ip_first_value == 172) private_ip_statu = 20;
				}
				else if (ip_first_value < 224) {
					type_ip = 3;
					if (ip_first_value == 192) private_ip_statu = 30;
				}
				else if (ip_first_value < 240) {
					type_ip = 4;
				}
				else if (ip_first_value < 256) {
					type_ip = 5;
				}
				else if (ip_first_value > 255 || ip_first_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				index = 1;
				ip_addr = ip_addr.substr(dot_position + 1);
			}
		case 1:
			{
				int dot_position = ip_addr.find_first_of('.');
				if (dot_position == 0 || ip_addr.find_first_of('.') == string::npos) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
					index = 4;
				}
				int ip_second_value = stoi(ip_addr.substr(0, dot_position));

				if (ip_second_value == 16 && private_ip_statu == 20) private_ip_statu = 21;
				if (ip_second_value == 168 && private_ip_statu == 30) private_ip_statu = 31;
				if (ip_second_value > 255 || ip_second_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				index = 2;
				ip_addr = ip_addr.substr(dot_position + 1);
			}
		case 2:
			{
				int dot_position = ip_addr.find_first_of('.');
				if (dot_position == 0 || ip_addr.find_first_of('.') == string::npos) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
					index = 4;
				}
				int ip_third_value = stoi(ip_addr.substr(0, dot_position));

				if (ip_third_value > 255 || ip_third_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				index = 3;
				ip_addr = ip_addr.substr(dot_position + 1);
			}
		case 3:
			{

				if (ip_addr.size() == 0) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
					index = 4;
				}
				int forth_value = stoi(ip_addr);

				if (forth_value > 255 || forth_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}


				if (private_ip_statu == 11 || private_ip_statu == 21 || private_ip_statu == 31)
					++private_ip_num;

				
			}
		case 4:
			break;
		default:
			break;
		}  

		index = 0;
		int mask_statu = 0;
		switch (index)
		{
			case 0:
			{
				int dot_position = mask_addr.find_first_of('.');
				if (dot_position == 0 || mask_addr.find_first_of('.') == string::npos) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
				}
				int mask_first_value = stoi(mask_addr.substr(0, dot_position));

				if (mask_first_value > 255 || mask_first_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				if (mask_first_value < 128) {
					++error_addr_num;
					break;
				}
				else {
					mask_statu = 1;
				}
				for (int i = 0; i < 8; ++i) {
					if ((mask_first_value >> (7 - i) & 1) == 1 && mask_statu == 1) {
						mask_statu = 1;
					}
					else if ((mask_first_value >> (7 - i) & 1) == 0 && mask_statu == 1) {
						mask_statu = 10;
					}
					else if ((mask_first_value >> (7 - i) & 1) == 1 && mask_statu == 10) {
						mask_statu = 101;
						++error_addr_num;
						break;
						index = 4;
					}
					else if ((mask_first_value >> (7 - i) & 1) == 0 && mask_statu == 10) {
						mask_statu = 10;
					}
				}
				index = 1;
				mask_addr = mask_addr.substr(dot_position + 1);
			}
			case 1:
			{
				int dot_position = mask_addr.find_first_of('.');
				if (dot_position == 0 || mask_addr.find_first_of('.') == string::npos) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
				}
				int mask_second_value = stoi(mask_addr.substr(0, dot_position));

				if (mask_second_value > 255 || mask_second_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				for (int i = 0; i < 8; ++i) {
					if ((mask_second_value >> (7 - i) & 1) == 1 && mask_statu == 1) {
						mask_statu = 1;
					}
					else if ((mask_second_value >> (7 - i) & 1) == 0 && mask_statu == 1) {
						mask_statu = 10;
					}
					else if ((mask_second_value >> (7 - i) & 1) == 1 && mask_statu == 10) {
						mask_statu = 101;
						++error_addr_num;
						break;
						index = 4;
					}
					else if ((mask_second_value >> (7 - i) & 1) == 0 && mask_statu == 10) {
						mask_statu = 10;
					}
				}
				index = 2;
				mask_addr = mask_addr.substr(dot_position + 1);

			}
			case 2:
			{
				int dot_position = mask_addr.find_first_of('.');
				if (dot_position == 0 || mask_addr.find_first_of('.') == string::npos) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
				}
				int mask_third_value = stoi(mask_addr.substr(0, dot_position));

				if (mask_third_value > 255 || mask_third_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				for (int i = 0; i < 8; ++i) {
					if ((mask_third_value >> (7 - i) & 1) == 1 && mask_statu == 1) {
						mask_statu = 1;
					}
					else if ((mask_third_value >> (7 - i) & 1) == 0 && mask_statu == 1) {
						mask_statu = 10;
					}
					else if ((mask_third_value >> (7 - i) & 1) == 1 && mask_statu == 10) {
						mask_statu = 101;
						++error_addr_num;
						break;
						index = 4;
					}
					else if ((mask_third_value >> (7 - i) & 1) == 0 && mask_statu == 10) {
						mask_statu = 10;
					}
				}
				index = 3;
				mask_addr = mask_addr.substr(dot_position + 1);

			}
			case 3:
			{
				if (!mask_addr.size()) {
					error_addr_num++; //错误ip地址
					break; //ip地址第一段没有内容
				}
				int mask_forth_value = stoi(mask_addr);

				if (mask_forth_value > 255 || mask_forth_value < 0) {
					error_addr_num++; //错误ip地址
					break;
				}
				for (int i = 0; i < 8; ++i) {
					if ((mask_forth_value >> (7 - i) & 1) == 1 && mask_statu == 1) {
						mask_statu = 1;
					}
					else if ((mask_forth_value >> (7 - i) & 1) == 0 && mask_statu == 1) {
						mask_statu = 10;
					}
					else if ((mask_forth_value >> (7 - i) & 1) == 1 && mask_statu == 10) {
						mask_statu = 101;
						++error_addr_num;
						break;
						index = 4;
					}
					else if ((mask_forth_value >> (7 - i) & 1) == 0 && mask_statu == 10) {
						mask_statu = 10;
					}
				}
				if (type_ip == 1)
					++a_num;
				else if (type_ip == 2)
					++b_num;
				else if (type_ip == 3)
					++c_num;
				else if (type_ip == 4)
					++d_num;
				else if (type_ip == 5)
					++e_num;
				index = 0;
			}
			case 4:
				break;
			default:
				break;
		}

	}
	return 0;
}