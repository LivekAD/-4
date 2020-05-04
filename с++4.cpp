#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>

using namespace std;

class CBank
{
public:
	string name;
	string line;
	double dep=0.1, kred=0.2;
	int vkred = 0, vdep=0, o = 1;
	long double bmoney, zkred, zdep;
	
	void schboney()
	{
		ofstream ifile("bmoney.txt");

		if (!ifile)
		{
			cout << "Файл не відкритий.\n";
		}

		ifile << bmoney << " " << zkred << " " << zdep << " " << name << endl;
		ifile.close();
	}

	void boney()
	{
		std::ifstream ifile("bmoney.txt"); // окрываем файл для чтения
		if (ifile.is_open())
		{
			while (!ifile.eof())
			{
				line = "";
				ifile >> line;
				if (o == 1) { cout << "bmoney - " << line; }
				if (o == 2) { cout << "\nzkred - " << line; }
				if (o == 3) { cout << "\nzdep - " << line; }
				//if (o == 4) { cout << ", приблизительное количество дней работы - " << line; }
				o++;
				if (o == 4) { cout << endl; o = 1; }
			}
		}
		ifile.close();
	}
	void load()
	{
		std::ifstream ifile("bmoney.txt"); // окрываем файл для чтения
		if (ifile.is_open())
		{
			while (!ifile.eof())
			{
				line = "";
				ifile >> line;
				if (o == 1) {
					istringstream iss(line, istringstream::in);
					iss >> bmoney;
				}
				if (o == 2) {
					istringstream is(line, istringstream::in);
					is >> zkred;
				}
				if (o == 3) {
					istringstream isss(line, istringstream::in);
					isss >> zdep;
				}
				if (o == 4) {
					istringstream isas(line, istringstream::in);
					isas >> name;
				}
				o++;
				if (o == 5) { cout << endl; o = 1; }
			}
		}
		ifile.close();
	}
};

int main() {
	int z, pass;
	long int sumkred, sumdep;
	setlocale(LC_ALL, "Rus");
	CBank test;

	test.load();
	cout << "\t\tДобро пожаловать в " << test.name << "\n1.Kредит" << "\n2.Депозит" << "\n3.Посмотреть статистику банка" << "\n4.Настройки банка\n";
	cin >> z;
	switch (z)
	{
	case 1:
		int zx;
		cout << "1.Оформить кредить" << "\n2.Погасить кредит" << endl;
		cin >> zx;
		switch (zx) {
		case 1:
			cout << "Сколько Вы хотите взять - "; cin >> sumkred; cout << "Вы будете должны в конце месяца - " << (sumkred * test.kred) + sumkred << endl;
			test.zkred = test.zkred + ((sumkred * test.kred) + sumkred);
			test.bmoney = test.bmoney - sumkred;
			test.vkred++;
			break;
		case 2:
			int zxc = 0;
			cout << "Сколько Вы брали - "; cin >> sumkred; cout << ". Вы должны банку - " << (sumkred * test.kred) + sumkred << endl;
			cout << "Внесите деньги(введите ту суму которая была на экране) - " << endl;
			cin >> zxc;
			if (zxc == (sumkred * test.kred) + sumkred) 
			{
				test.zkred = test.zkred - ((sumkred * test.kred) + sumkred);
				test.bmoney = test.bmoney + test.zkred;
				test.vkred--;
			}
			break;
		}
		break;
	case 2:
		int depo;
		cout << "1.Положить на депозит" << "\n2.Забрать депозит" << endl;
		cin >> depo;
		switch (depo)
		{
		case 1:
			cout << "Сколько Вы хотите положить - "; cin >> sumdep; cout << "Вы получите в конце месяца - " << (sumdep * test.dep) + sumdep << endl;
			test.zdep = test.zdep + ((sumdep * test.dep) + sumdep);
			test.vdep++;
			break;
		case 2:
			cout << "Сколько Вы положили - "; cin >> sumdep; cout << "Вы забираете - " << (sumdep * test.dep) + sumdep << endl;
			test.zdep = test.zdep - ((sumdep * test.dep) + sumdep);
			test.vdep++;
			break;
		}
	case 3: 
		test.boney();
		break;
	case 4:
		int x = 0;
		cout << "Введите пароль - ";
		cin >> pass;
		if (pass == 4375) {
			cout << "1.Изменить имя банка" << endl << "2.Изменить процент депозита"<< endl << "3.Изменить процент кредита" << endl;
			cin >> x;
	switch (x) { case 1: cin >> test.name; break; case 2: cin >> test.dep; break; case 3: cin >> test.kred; break;}
		}
		break;
	}
	test.schboney();
}

