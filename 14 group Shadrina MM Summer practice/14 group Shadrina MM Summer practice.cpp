#define _USE_MATH_DEFINES
#include <iostream>;
#include <string>;
#include <fstream>;
#include <cmath>;

using namespace std;

double Function(double x, double t)
{
	return (1 / (pow(1 + pow(M_E, t * x), 0.5)));
}

double IntegralSum(double x, double n, double h)
{
	double sum = 0;
	for (int i = 1; i < n; ++i)
		sum += (Function(x, h * i)) * h;
	return sum;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double x, y, h, a, b, c, d, N[4], discrepancy[4] = { 0, 0, 0, 0 };

	cout << "Введите нижнюю границу интегрирования (a): " << endl;
	cin >> a;
	cout << "Введите верхнюю границу интегрирования (b): " << endl;
	cin >> b;
	cout << "Введите нижнюю границу для х (c): " << endl;
	cin >> c;
	cout << "Введите верхнюю границу для х (d): " << endl;
	cin >> d;
	cout << "Введите четыре числа разбиений(N) : " << endl;
	cin >> N[0] >> N[1] >> N[2] >> N[3];

	string s = "";
	for (int i = 0; i <= 20; i++)
	{
		x = c + i * (d - c) / 20;
		if (x == 0)
		{
			y = pow(2, 0.5) / 2;
			s += to_string(x) + '\t' + to_string(y) + '\t';
		}
		else
		{
			y = ((log((pow(pow(M_E, x) + 1, 0.5) - 1) / (pow(pow(M_E, x) + 1, 0.5) + 1)) + log((pow(2, 0.5) + 1) / (pow(2, 0.5) - 1))) / x);
			s += to_string(x) + '\t' + to_string(y) + '\t';
		}
		for (int j = 0; j < 4; j++)
		{
			h = (b - a) / N[j];
			s += to_string(IntegralSum(x, N[j], h)) + '\t';
			if (abs(y - IntegralSum(x, N[j], h)) > discrepancy[j])
				discrepancy[j] = abs(y - IntegralSum(x, N[j], h));
		}
		s += '\n';
	}
	for (int i = 0; i < s.length(); i++)
		if (s[i] == '.')
			s[i] = ',';

	ofstream file("table.txt");
	file << s;
	file << "Максимальная невязка для различных значений разбиений: \n ";
	cout << endl << "Максимальная невязка для различных значений разбиений:" << endl;
	for (int i = 0; i < 4; i++)
	{
		file << N[i] << ": " << discrepancy[i] << "\n";
		cout << N[i] << ": " << discrepancy[i] << "\n";
	}
	cout << endl << "x \t\t" << " Analitical" << "\t" << N[0] << "\t\t" << N[1] << "\t\t" << N[2] << "\t\t" << N[3] << "\t\t" << '\n' << s;
	file.close();
	return 0;
}

