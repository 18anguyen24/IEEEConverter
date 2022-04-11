using namespace std;
#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

int main()
{
	cout << "dec2ieee" << endl;
	string input = "";
	double num = 0;
	cout << "Enter number: ";
	getline(cin, input);
	cout << endl;
	int checker = 0;
	int sign = 0;

	//parsing string input
	//division
	if (input.find('/') != string::npos)
	{
		double num1 = stod(input.substr(0, input.find('/')));
		double num2 = stod(input.substr(input.find('/') + 1));
		num = num1 / num2;
	}
	//if input is already in decimal
	else if (input.find('^') == string::npos)
	{
		num = stod(input);
	}
	//scientific notation
	else
	{
		double num1 = 0;
		int xposition = input.find("x");
		int carrot = input.find("^");
		int paren1 = input.find("(");
		int paren2 = input.find(")");

		if (xposition == -1)
		{
			num1 = 1.0;
		}
		else
		{
			num1 = stod(input.substr(0, xposition));
		}

		double num2 = stod(input.substr(xposition + 1, carrot));
		double num3 = stod(input.substr(paren1 + 1, paren2));

		num = num1 * pow(num2, num3);
	}

	//sign bit
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}

	//exponent calculation using log
	int exponent = floor(log(num) / log(2));
	int exponentBias = exponent + 127;
	string binaryExp = bitset<8>(exponentBias).to_string();

	double mantissa = abs((num / pow(2, exponent)) - 1);

	//creating mantissa in binary, we go up to 24 in case of infinite result
	string binMantissa = "";
	while (fmod(mantissa, 1) != 0 && checker != 24)
	{
		mantissa *= 2;
		if (mantissa >= 1)
		{
			binMantissa.push_back('1');
			mantissa -= 1;
		}
		else
		{
			binMantissa.push_back('0');
		}
		++checker;
	}

	//this is to add 1 to the mantissa if we have 24 bits.
	bool carry = true;
	int i = 0;
	if (binMantissa.length() > 0)
	{
		i = binMantissa.length() - 1;
	}
	if (binMantissa[i] == '1' && checker == 24)
	{
		while(i > 0 && carry == true)
		{
			if (binMantissa[i] == '1')
			{
				binMantissa[i] = '0';
				carry = true;
			}
			else
			{
				binMantissa[i] = '1';
				carry = false;
			}
			--i;
		}
	}

	//remove last bit if it's infinite
	if (checker == 24)
	{
		binMantissa.pop_back();
	}
	else if (checker < 23)
	{
		int numZero = 23 - binMantissa.length();
		binMantissa.insert(binMantissa.end(), numZero, '0');
	}


	cout << "IEE 754: " << sign << " " << binaryExp << " " << binMantissa << endl;
	cout << endl;


	system("pause");
	return 0;

}