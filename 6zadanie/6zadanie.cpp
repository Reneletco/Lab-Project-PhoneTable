#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <filesystem>
#include <map>
using namespace std;
const int N = 100;
int tableType = 0; // 0 - стандартная матрица | 1 - перечень
struct mobile {
	string phoneProducer;
	string proccessorProducer;
	int ram;
};
struct models {
	string model;
	int count;
};
struct record {
	mobile phone;
	string name;
	string phoneNumber;
	models test;
};
void printTable(record x[], int n, int c) {
	if (c == 0) {
		cout << "  --------------------------------------------------------------------------------------------\n"
			"  |    |                                |                |        Мобильный телефон          |\n"
			"  |  N |            ФИО                 |   Номер тел.   |-----------------------------------|\n"
			"  |    |                                |                |  Произв.   |  Процессор   |  ОЗУ  |\n"
			"  --------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			cout << "  | " << left << setw(2) << i + 1 << left << " | " << setw(30) << x[i].name << left << " | " << setw(14) << x[i].phoneNumber << left << " | " << setw(10) << x[i].phone.phoneProducer << left << " | " << setw(12) << x[i].phone.proccessorProducer << left << " | " << setw(5) << x[i].phone.ram << left << " |" << endl;
		}
		cout << "  --------------------------------------------------------------------------------------------\n";
	}
	else {
		cout << "  -----------------------------\n"
			"  |    |            |         |\n"
			"  |  N |  Произв.   |  Штук   |\n"
			"  |    |            |         |\n"
			"  -----------------------------\n";
		for (int i = 0; i < n; i++) {
			cout << "  | " << left << setw(2) << (i + 1) << left << " | " << setw(10) << x[i].test.model << left << " | " << setw(7) << x[i].test.count << left << " |\n";
		}
		cout << "  -----------------------------\n";
	}
}
void loadFromFile(record x[], int& n) {  // 1 пункт
	string filename;
	cout << "Введите название файла (example.txt): "; cin >> filename;
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Файл не найден" << endl;
	}
	else {
		string line;
		string init;
		record t;
		n = 0;
		while (getline(file, line)) {
			if (n == N) {
				cout << "Таблица полна" << endl;
				return;
			}
			stringstream ss(line);
			ss >> t.name >> init >> t.phoneNumber >> t.phone.phoneProducer >> t.phone.proccessorProducer >> t.phone.ram;
			t.name = t.name + " " + init;
			x[n] = t;
			n++;
		}
		cout << "Успешно" << endl;
		file.close();
	}
}
void saveToFile(record x[], int& n) { // 2 пункт
	string filename;
	cout << "Введите название файла: "; cin >> filename;
	ofstream out(filename);
	if (tableType == 0) {
		out << "  --------------------------------------------------------------------------------------------\n"
			"  |    |                                |                |        Мобильный телефон          |\n"
			"  |  N |            ФИО                 |   Номер тел.   |-----------------------------------|\n"
			"  |    |                                |                |  Произв.   |  Процессор   |  ОЗУ  |\n"
			"  --------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			out << "  | " << left << setw(2) << i + 1 << left << " | " << setw(30) << x[i].name << left << " | " << setw(14) << x[i].phoneNumber << left << " | " << setw(10) << x[i].phone.phoneProducer << left << " | " << setw(12) << x[i].phone.proccessorProducer << left << " | " << setw(5) << x[i].phone.ram << left << " |\n";
		}
		out << "  --------------------------------------------------------------------------------------------\n";
		tableType = 1;
	}
	else {
		out << "  -----------------------------\n"
			"  |    |            |         |\n"
			"  |  N |  Произв.   |  Штук   |\n"
			"  |    |            |         |\n"
			"  -----------------------------\n";
		for (int i = 0; i < n; i++) {
			out << "  | " << left << setw(2) << (i + 1) << left << " | " << setw(10) << x[i].test.model << left << " | " << setw(7) << x[i].test.count << left << " |\n";
		}
		out << "  -----------------------------\n";
	}
	cout << "Успешно сохранил файл в " << filesystem::absolute(filename) << endl;
	out.close();
}
void addRecord(record x[], int& n) { // 3 пункт
	record t;
	string init;
	if (n == N) {
		cout << "Таблица полна" << endl;
		return;
	}



	cout << "Введите ФИО: "; cin >> t.name >> init;
	t.name = t.name + " " + init;
	cout << "Введите номер телефона: "; cin >> t.phoneNumber;
	cout << "Введите производителя телефона: "; cin >> t.phone.phoneProducer;
	cout << "Введите название процессора: "; cin >> t.phone.proccessorProducer;
	cout << "Введите ОЗУ (в МБ): "; cin >> t.phone.ram;
	cout << "Успешно!" << endl;
	x[n] = t;
	n++;

}
void getData(record x[], int i) {
	cout << setw(2) << i + 1 << " | " << setw(30) << x[i].name << " | " << setw(14) << x[i].phoneNumber << " | " << setw(10) << x[i].phone.phoneProducer << " | " << setw(12) << x[i].phone.proccessorProducer << " | " << setw(5) << x[i].phone.ram << endl;
}
void deleteRecord(record x[], int& n) { // 4 пункт
	int i;
	tableType = 0;
	printTable(x, n, tableType);
	cout << "Введите номер строчки которую вы хотите удалить: ";
	cin >> i;
	i = i - 1;
	getData(x, i);
	cout << "Вы уверены что хотите удалить эту запись? Y - да | N - нет" << endl;
	char input;
	cin >> input;
	i = i + 1;
	if (input == 'Y') {
		if (i == n) {
			n--;
		}
		else {
			for (int ix = i - 1; ix < n - 1; ix++) {
				x[ix] = x[ix + 1];
			}
			n--;
			cout << "Успешно удалено";
		}
	}
}
void redactData(record x[], int n) {
	printTable(x, n, 0);
	int choose, decision;
	int ram;
	cout << "Выберите какую строку вы хотите изменить: "; cin >> choose;
	choose -= 1;
	getData(x, choose);
	cout << "1. Изменить ФИО\n2. Изменить номер телефона\n3. Изменить производителя телефона\n4. Изменить процессор телефона \n5. Изменить объем памяти\n0. Выход";
	cin >> decision;
	string input, init;
	switch (decision) {
	case 1:
		cout << "Введите новое ФИО: "; cin >> input >> init; x[choose].name = input + " " + init;
		break;
	case 2:
		cout << "Введите новый номер телефона: "; cin >> input; x[choose].phoneNumber = input;
		break;
	case 3:
		cout << "Введите название телефона: "; cin >> input; x[choose].phone.phoneProducer = input;
		break;
	case 4:
		cout << "Введите название процессора: "; cin >> input; x[choose].phone.proccessorProducer = input;
		break;
	case 5:
		cout << "Введите ОЗУ: "; cin >> ram; x[choose].phone.ram = ram;
		break;
	case 0:
		break;
	default:
		cout << "Не найдено" << endl;
		break;
	}
}
string getStructData(record x[], int k, int choose) {
	switch (choose) {
	case 1:
		return x[k].name;
		break;
	case 2:
		return x[k].phoneNumber;
		break;
	case 3:
		return x[k].phone.phoneProducer;
	case 4:
		return x[k].phone.proccessorProducer;
	case 5:
		return to_string(x[k].phone.ram);
	}
}
void sortByNumber(record y[], int n, int choose, int choose2) {
	tableType = 0;
	int type1, type2;
	string ts1, ts2;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			type1 = atoi(getStructData(y, j, choose).c_str());
			type2 = atoi(getStructData(y, j + 1, choose).c_str());
			if (type1 == type2) {
				ts1 = getStructData(y, j, choose2);
				ts2 = getStructData(y, j + 1, choose2);
				if (ts1 > ts2) {
					record temp = y[j];
					y[j] = y[j + 1];
					y[j + 1] = temp;
				}
			}
			else if (type1 > type2) {
				record temp = y[j];
				y[j] = y[j + 1];
				y[j + 1] = temp;
			}
		}
	}
}
void sortByAlphabet(record y[], int n, int choose, int choose2) {
	tableType = 0;
	string type1, type2;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			type1 = getStructData(y, j, choose);
			type2 = getStructData(y, j + 1, choose);
			if (type1 == type2) {
				type1 = getStructData(y, j, choose2);
				type2 = getStructData(y, j + 1, choose2);
				if (type1 > type2) {
					record temp = y[j];
					y[j] = y[j + 1];
					y[j + 1] = temp;
				}
			}
			else if (type1 > type2) {
				record temp = y[j];
				y[j] = y[j + 1];
				y[j + 1] = temp;
			}
		}
	}
}
void getProducers(record x[], int n, record y[], int& k) { // 9 пункт
	tableType = 1;
	map<string, int>  Models;
	k = 0;
	models t;
	for (int i = 0; i < n; i++) {
		Models[x[i].phone.phoneProducer]++;
	}
	for (auto& i : Models) {
		t.model = i.first;
		t.count = i.second;
		y[k].test = t;
		k++;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (y[j].phone.phoneProducer > y[j + 1].phone.phoneProducer) {
				record temp = y[j];
				y[j] = y[j + 1];
				y[j + 1] = temp;
			}
		}
	}
	printTable(y, k, tableType);
}
void getParam(string& param1, string& param2, int& find1, int& find2, int choose) {
	if (param1.empty()) {
		cin >> param1;
		find1 = choose;
	}
	else if (!param1.empty() && param2.empty()) {
		cin >> param2;
		find2 = choose;
	}
	else {
		cout << "Вы уже выбрали максимальное кол-во параметров";
	}
}
void find(record x[], int n, record y[], int& k) { // 10 пункт
	tableType = 0;
	record phone0;
	string init;
	int choose;
	string search1 = "", search2 = "";
	int param1 = 0, param2 = 0;
	k = 0;
	bool start = true;
	while (start) {
		system("cls");
		if (!search1.empty() || !search2.empty()) {
			cout << "Вы ищете по параметрам: " << search1 << " " << search2 << endl;
		}
		cout << "1. По ФИО\n2. По номеру телефона\n3. По названию производителя телефона\n4. По названию процессора телефона\n5. По объему памяти\n6. Начать поиск\n7. Очистить критерии поиска\n0. Выйти из поиска\n";
		cout << "Введите параметры по которым необходимо вести поиск: ";
		cin >> choose;
		switch (choose) {
		case 1:
			cout << "Введите ФИО: ";
			if (search1.empty()) {
				cin >> search1 >> init;
				search1 = search1 + " " + init;
				param1 = choose;
			}
			else if (!search1.empty() && search2.empty()) {
				cin >> search2 >> init;
				search2 = search2 + " " + init;
				param2 = choose;
			}
			else {
				cout << "Вы уже выбрали максимальное кол-во параметров";
			}
			break;
		case 2:
			cout << "Введите номер телефона: ";
			getParam(search1, search2, param1, param2, choose);
			break;
		case 3:
			cout << "Введите производителя телефона: ";
			getParam(search1, search2, param1, param2, choose);
			break;
		case 4:
			cout << "Введите процессор телефона: ";
			getParam(search1, search2, param1, param2, choose);
			break;
		case 5:
			cout << "Введите объём памяти: ";
			getParam(search1, search2, param1, param2, choose);
			break;
		case 6:
			start = false;
			break;
		case 7:
			search1 = ""; search2 = ""; param1 = 0; param2 = 0;
			break;
		case 0:
			return;
			break;
		}
	}
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (!search1.empty() && !search2.empty()) {
			if (search1 == getStructData(x, i, param1) && search2 == getStructData(x, i, param2)) {
				y[k] = x[i];
				k++;
			}
		}
		else if (!search1.empty() && search2.empty()) {
			if (search1 == getStructData(x, i, param1)) {
				y[k] = x[i];
				k++;
			}
		}
		else {
			flag = 1;
		}
	}
	if (flag == 0 && k > 0) {
		printTable(y, k, 0);
	}
	else if (flag == 1) {
		cout << "Не указаны параметры поиска" << endl;
	}
	else if (flag == 0 && k == 0) {
		cout << "Не было найдено запсией удовлетворяющим вашим запросам" << endl;
	}
}
int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	record a[N], b[N];
	int ma = 0, mb = 0, choose;
	while (true) {
		system("cls");
		choose = -1;
		cout << "1. Загрузить из файла" << endl;
		cout << "2. Сохранить в файл" << endl;
		cout << "3. Ввести значение" << endl;
		cout << "4. Удалить данные" << endl;
		cout << "5. Редактировать данные" << endl;
		cout << "6. Вывести таблицу" << endl;
		cout << "7. Сортировать по ФИО" << endl;
		cout << "8. Сортировать по производителю" << endl;
		cout << "9. Сортировать по ОЗУ" << endl;
		cout << "10. Список производителей" << endl;
		cout << "11. Поиск" << endl;
		cout << "12. Вывести найденные данные" << endl;
		cout << "12. Сохранить найденные данные" << endl;
		cout << "0. Выйти" << endl;
		cin >> choose;
		switch (choose) {
		case 1: loadFromFile(a, ma);
			break;
		case 2: saveToFile(a, ma);
			break;
		case 3: addRecord(a, ma);
			break;
		case 4: deleteRecord(a, ma);
			break;
		case 5: redactData(a, ma);
			break;
		case 6: printTable(a, ma, 0);
			break;
		case 7: sortByAlphabet(a, ma, 1, 2);
			break;
		case 8: sortByAlphabet(a, ma, 3, 4);
			break;
		case 9: sortByNumber(a, ma, 5, 1);
			break;
		case 10: getProducers(a, ma, b, mb);
			break;
		case 11: find(a, ma, b, mb);
			break;
		case 12:
			if (mb != 0) {
				printTable(b, mb, tableType);
			}
			else {
				cout << "Не найдено записей" << endl;
			}
			break;
		case 13:
			if (mb != 0) {
				saveToFile(b, mb);
			}
			else {
				cout << "Не найдено записей" << endl;
			}
			break;
		case 0:
			return 0;
		default:
			cout << "Нет такого пункта" << endl;
		}
		cout << "Нажмите клавишу чтобы продолжить" << endl;
		_getch();
	}
}