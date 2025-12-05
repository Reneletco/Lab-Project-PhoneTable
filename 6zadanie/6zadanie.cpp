#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <filesystem>
#include <algorithm>
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
struct record{
	mobile phone;
	string name;
	string phoneNumber;
	models test;
};
void getTable(record x[], int n, int c) {
	if (c == 0) {
		cout << "  --------------------------------------------------------------------------------------------\n"
		"  |    |                                |                |        Мобильный телефон          |\n"
		"  |  N |            ФИО                 |   Номер тел.   |-----------------------------------|\n"
		"  |    |                                |                |  Произв.   |  Процессор   |  ОЗУ  |\n"
			"  --------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			cout << "  | " << setw(2) << i + 1 << " | " << setw(30) << x[i].name << " | " << setw(14) << x[i].phoneNumber << " | " << setw(10) << x[i].phone.phoneProducer << " | " << setw(12) << x[i].phone.proccessorProducer << " | " << setw(5) << x[i].phone.ram << " |" << endl;
		}
		cout << "  --------------------------------------------------------------------------------------------\n";
	}
	else {
		cout << "  -----------------------------\n"
			"  |    |            |         |\n"
			"  |  N |  Произв.   |  Штук   |\n"
			"  |    |            |         |\n"
			"  -----------------------------\n";
		for(int i = 0; i<n; i++){
			cout << "  | " << setw(2) << (i + 1) << " | " << setw(10) << x[i].test.model << " | " << setw(7) << x[i].test.count << " |\n";
		}
		cout << "  -----------------------------\n";
	}
}
void loadFromFile(record x[], int &n) {  // 1 пункт
	string filename;
	n=0;
	cout<<"Введите название файла (example.txt): "; cin >> filename;
	ifstream file(filename);
	if (!file.is_open()) {
		cout<<"Файл не найден";
		Sleep(500);
	}
	else {
		string line;
		string init;
		record t;
		while (getline(file, line)) {
			if (n == N) {
				cout << "Таблица полна" << endl;
				return;
			}
			stringstream ss(line);
			ss >> t.name >> init >> t.phoneNumber >> t.phone.phoneProducer >> t.phone.proccessorProducer >> t.phone.ram;
			t.name = t.name+" "+init; 
			x[n]=t;
			n++;
		}
		cout << "Успешно"<<endl;
		file.close();
		_getch();
	}
}
void saveToFile(record x[], int& n) { // 2 пункт
	string filename;
	cout<<"Введите название файла: "; cin>>filename;
	ofstream out(filename);
	if(tableType==0){
		out << "  --------------------------------------------------------------------------------------------\n"
		"  |    |                                |                |        Мобильный телефон          |\n"
		"  |  N |            ФИО                 |   Номер тел.   |-----------------------------------|\n"
		"  |    |                                |                |  Произв.   |  Процессор   |  ОЗУ  |\n"
		"  --------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			out << "  | " << setw(2) << i + 1 << " | " << setw(30) << x[i].name << " | " << setw(14) << x[i].phoneNumber << " | " << setw(10) << x[i].phone.phoneProducer << " | " << setw(12) << x[i].phone.proccessorProducer << " | " << setw(5) << x[i].phone.ram << " |\n";
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
			out << "  | " << setw(2) << (i + 1) << " | " << setw(10) << x[i].test.model << " | " << setw(7) << x[i].test.count << " |\n";
		}
		out << "  -----------------------------\n";
	}
	cout<<"Успешно сохранил файл в "<<filesystem::absolute(filename)<<endl;
	out.close();
	_getch();
}
void addRecord(record x[], int &n){ // 3 пункт
	record t;
	string init;
	if (n == N) {
		cout<<"Таблица полна"<<endl;
		return;
	}

	

	cout<<"Введите ФИО: "; cin>>t.name>>init;
	t.name = t.name + " " + init;
	cout << "Введите номер телефона: "; cin >> t.phoneNumber;
	cout << "Введите производителя телефона: "; cin >> t.phone.phoneProducer;
	cout << "Введите название процессора: "; cin >> t.phone.proccessorProducer;
	cout << "Введите ОЗУ (в МБ): "; cin >> t.phone.ram;
	cout << "Успешно!" << endl;
	x[n] = t;
	n++;
	Sleep(500);
	
}
void deleteRecord(record x[], int &n) { // 4 пункт
	int i;
	tableType=0;
	getTable(x,n,tableType);
	cout<<"Введите номер строчки которую вы хотите удалить: ";
	cin >> i;
	i = i-1;
	cout<<setw(2) << i+1 << " | " << setw(30) << x[i].name << " | " << setw(14) << x[i].phoneNumber << " | " << setw(10) << x[i].phone.phoneProducer << " | " << setw(12) << x[i].phone.proccessorProducer << " | " << setw(5) << x[i].phone.ram<<endl;
	cout<<"Вы уверены что хотите удалить эту запись? Y - да | N - нет"<<endl;
	char input;
	cin >> input;
	if (input == 'Y') {
		if (i == n) {
			n--;
		}
		else {
			for (int ix = i - 1; ix < n - 1; ix++) {
				x[ix] = x[ix + 1];
			}
			n--;
			cout<<"Успешно удалено";
			Sleep(500);
		}
	}
}
void printTable(record x[], int n,int c){ // 5 пункт
	getTable(x,n,c);
	cout<<"\n Нажмите кнопку чтобы продолжить"<<endl;
	_getch();
}
void sortByNumber(record x[], int n, record y[], int &k) { // 8 пункт
	tableType=0;
	k = n;
	for (int i = 0; i < n; i++) {
		y[i]=x[i];
	}
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1; j++) {
			if (y[j].phone.ram > y[j + 1].phone.ram) {
				record temp = y[j];
				y[j]=y[j+1];
				y[j+1]=temp;
			}
		}
	}
	cout<<"Успешно"<<endl;
	cout<<"Нажмите кнопку чтобы продолжить"<<endl;
	_getch();
}
void sortByAlphabet(record x[], int n, record y[], int &k) { // 7 пункт
	tableType = 0;
	k = n;
	for (int i = 0; i < n; i++) {
		y[i] = x[i];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (y[j].phone.phoneProducer == y[j + 1].phone.phoneProducer) {
				if (y[j].phone.proccessorProducer > y[j + 1].phone.proccessorProducer) {
					record temp = y[j];
					y[j]=y[j+1];
					y[j+1]=temp;
				}
			}
			else if (y[j].phone.phoneProducer > y[j + 1].phone.phoneProducer) {
				record temp = y[j];
				y[j] = y[j + 1];
				y[j + 1] = temp;
			}
		}
	}
	cout << "Успешно" << endl;
	cout << "Нажмите кнопку чтобы продолжить" << endl;
	_getch();
}
void sortByAlphabetB(record x[], int n, record y[], int& k) { // 6 пункт
	tableType = 0;
	k = n;
	for (int i = 0; i < n; i++) {
		y[i] = x[i];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (y[j].name > y[j + 1].name) {
				record temp = y[j];
				y[j] = y[j + 1];
				y[j + 1] = temp;
			}
		}
	}
	cout << "Успешно" << endl;
	cout << "Нажмите кнопку чтобы продолжить" << endl;
	_getch();
}
void getProducers(record x[], int n, record y[], int &k) { // 9 пункт
	tableType=1;
	map<string,int>  Models;
	k=0;
	models t;
	for (int i = 0; i < n; i++) {
		Models[x[i].phone.phoneProducer]++;
	}
	for (auto& i : Models) {
		t.model = i.first;
		t.count = i.second;
		y[k].test=t;
		k++;
	}
	getTable(y,k,tableType);
	cout << "Нажмите кнопку чтобы продолжить" << endl;
	_getch();
}
void findByName(record x[], int n, record y[], int &k) { // 10 пункт
	tableType=0;
	record phone0;
	string init;
	k=0;
	cout<<"Введите ФИО владельца телефона: "; cin >> phone0.name >> init;
	phone0.name = phone0.name + " "+init;
	for (int i = 0; i < n; i++) {
		if (x[i].name == phone0.name) {
			y[k]=x[i];
			k++;
		}
	}
	for (int i = 0; i < k - 1; i++) {
		for (int j = 0; j < k - 1; j++) {
			if (y[j].phoneNumber > y[j + 1].phoneNumber) {
				record temp = y[j];
				y[j] = y[j + 1];
				y[j + 1] = temp;
			}
		}
	}
}
int main() {
	setlocale(LC_ALL, "");
	record a[N], b[N];
	int ma=0,mb=0,choose;
	while (true) {
		system("cls");
		choose=-1;
		cout<< "1. Загрузить из файла"<<endl;
		cout<< "2. Сохранить в файл"<<endl;
		cout<< "3. Ввести значение"<<endl;
		cout<< "4. Удалить данные"<<endl;
		cout<< "5. Вывести таблицу" << endl;
		cout<< "6. Сортировать по ФИО"<<endl;
		cout<< "7. Сортировать по производителю"<<endl;
		cout<< "8. Сортировать по ОЗУ"<<endl;
		cout<< "9. Список производителей"<<endl;
		cout<< "10. Найти по ФИО"<<endl;
		cout<< "11. Вывести найденные данные"<<endl;
		cout<<"12. Сохранить найденные данные"<<endl;
		cout<< "0. Выйти"<<endl;
		cin>>choose;
		switch (choose) {
			case 1: loadFromFile(a, ma);
				break;
			case 2: saveToFile(a, ma);
				break;
			case 3: addRecord(a, ma);
				break;
			case 4: deleteRecord(a, ma);
				break;
			case 5: printTable(a, ma,0);
				break;
			case 6: sortByAlphabetB(a,ma,b,mb);
				break;
			case 7: sortByAlphabet(a,ma,b,mb);
				break;
			case 8: sortByNumber(a, ma,b,mb);
				break;
			case 9: getProducers(a, ma, b, mb);
				break;
			case 10: findByName(a, ma, b, mb);
				break;
			case 11:
				if(mb!=0){
					printTable(b,mb,tableType);
				} else {
					cout<<"Не найдено записей"<<endl;
					_getch();
				}
				break;
			case 12:
				if (mb != 0) {
					saveToFile(b, mb);
				}
				else {
					cout << "Не найдено записей" << endl;
					_getch();
				}
				break;
			case 0:
				return 0;
			default:
				cout<<"Нет такого пункта";
				_getch();
		}
	}
}