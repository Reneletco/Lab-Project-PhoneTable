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
int tableType = 0; // 0 - полный вывод, 1 - вывод моделей и их количество
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
void getTable(record x[], int n) {
	if (tableType == 0) {
		cout << "  --------------------------------------------------------------------------------------------\n"
		 "  |    |                                |                |              Mobile Phone         |\n"
		 "  |  N |            Name                |  Phone Number  |-----------------------------------|\n"
		 "  |    |                                |                |  Producer  |  Proccessor  |  RAM  |\n"
		 "  --------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < n; i++) {
			cout << "  | " << setw(2) << i + 1 << " | " << setw(30) << x[i].name << " | " << setw(14) << x[i].phoneNumber << " | " << setw(10) << x[i].phone.phoneProducer << " | " << setw(12) << x[i].phone.proccessorProducer << " | " << setw(5) << x[i].phone.ram << " |" << endl;
		}
		cout << "  --------------------------------------------------------------------------------------------\n";
		tableType=1;
	}
	else {
		cout << "  -----------------------------\n";
		cout << "  |    |            |         |\n";
		cout << "  |  N |  Producer  |  Count  |\n";
		cout << "  |    |            |         |\n";
		cout << "  -----------------------------\n";
		for(int i = 0; i<n; i++){
			cout << "  | " << setw(2) << (i + 1) << " | " << setw(10) << x[i].test.model << " | " << setw(7) << x[i].test.count << " |\n";
		}
		cout << "  -----------------------------\n";
	}
}
void loadFromFile(record x[], int &n) {  // 1 пункт
	string filename;
	n=0;
	cout<<"Enter filename: "; cin >> filename;
	ifstream file(filename);
	if (!file.is_open()) {
		cout<<"File not found";
	}
	else {
		string line;
		string init;
		record t;
		while (getline(file, line)) {
			if (n == N) {
				cout << "Table is full" << endl;
				return;
			}
			stringstream ss(line);
			ss >> t.name >> init >> t.phoneNumber >> t.phone.phoneProducer >> t.phone.proccessorProducer >> t.phone.ram;
			t.name = t.name+" "+init;
			cout<<t.name<<endl;
			x[n]=t;
			n++;
		}
		cout << "Successfully loaded from file"<<endl;
		file.close();
		_getch();
	}
}
void saveToFile(record x[], int& n) { // 2 пункт
	string filename;
	cout<<"Enter filename: "; cin>>filename;
	ofstream out(filename);
	out << "  --------------------------------------------------------------------------------------------\n";
	out << "  |    |                                |                |              Mobile Phone         |\n";
	out << "  |  N |            Name                |  Phone Number  |-----------------------------------|\n";
	out << "  |    |                                |                |  Producer  |  Proccessor  |  RAM  |\n";
	out << "  --------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < n; i++) {
		out << "  | " << setw(2) << i + 1 << " | " << setw(30) << x[i].name << " | " << setw(14) << x[i].phoneNumber << " | " << setw(10) << x[i].phone.phoneProducer << " | " << setw(12) << x[i].phone.proccessorProducer << " | " << setw(5) << x[i].phone.ram << " |\n";
	}
	out << "  --------------------------------------------------------------------------------------------\n";	
	cout<<"Successfully saved the file in "<<filesystem::absolute(filename)<<endl;
	_getch();
}
void addRecord(record x[], int &n){ // 3 пункт
	record t;
	string init;
	if (n == N) {
		cout<<"Table is full"<<endl;
		return;
	}
	cout<<"Enter surname and initials: "; cin>>t.name>>init;
	t.name = t.name + " " + init;
	cout << "Enter phone number: "; cin >> t.phoneNumber;
	cout << "Enter phone producer: "; cin >> t.phone.phoneProducer;
	cout << "Enter processor producer: "; cin >> t.phone.proccessorProducer;
	cout << "Enter RAM size (in MB): "; cin >> t.phone.ram;
	cout << "Successfully added!" << endl;
	x[n] = t;
	n++;
	Sleep(3);
	
}
void deleteRecord(record x[], int &n) { // 4 пункт
	int number;
	tableType=0;
	getTable(x,n);
	cout<<"Enter number of which data you want to remove: ";
	cin >> number;
	if (number == n) {
		n--;
	}
	else {
		for (int i = number-1; i < n-1; i++) {
			x[i]=x[i+1];
		}
		n--;
	}
}
void printTable(record x[], int n){ // 5 пункт
	getTable(x,n);
	cout<<"\n Press Enter to continue"<<endl;
	_getch();
}
void sortByNumber(record x[], int n, record y[], int &k) {
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
	cout<<"Successfully sorted"<<endl;
	cout<<"Press Enter to continue"<<endl;
	_getch();
}
// void sortByAlphabet() // 6 пункт доделать
void getProducers(record x[], int n, record y[], int &k) { // пункт 8
	tableType=1;
	map<string,int> Models;
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
	getTable(y,k);
	cout << "Press Enter to continue" << endl;
	_getch();
}
void findByName(record x[], int n, record y[], int &k) { // 10 пункт
	tableType=0;
	record phone0;
	string init;
	k=0;
	cout<<"Enter phone owner's name: "; cin >> phone0.name >> init;
	phone0.name = phone0.name + " "+init;
	for (int i = 0; i < n; i++) {
		if (x[i].name == phone0.name) {
			y[k]=x[i];
			k++;
		}
	}
}
int main() {
	record a[N], b[N];
	int ma=0,mb=0,choose;
	while (true) {
		system("cls");
		choose=-1;
		cout<< "1. Load from file"<<endl;
		cout<< "2. Save in file"<<endl;
		cout<< "3. Enter data"<<endl;
		cout<< "4. Delete data"<<endl;
		cout<< "5. Print data" << endl;
		cout<< "6. Sort in alphabetical order"<<endl;
		cout<< "7. Sort by producers name"<<endl;
		cout<< "8. Sort by RAM"<<endl;
		cout<< "9. List of producers"<<endl;
		cout<< "10. Find by initials"<<endl;
		cout<< "11. Print found data"<<endl;
		cout<< "0. Exit"<<endl;
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
			case 5:
				tableType = 0;
				printTable(a, ma);
				break;
			case 8: sortByNumber(a, ma,b,mb);
				break;
			case 9: getProducers(a, ma, b, mb);
				break;
			case 10: findByName(a, ma, b, mb);
				break;
			case 11: 
				if(mb!=0){
					printTable(b,mb);
				} else {
					cout<<"No records found"<<endl;
					_getch();
				}
				break;
			case 0:
				return 0;
			default:
				cout<<"Not found";
				_getch();
		}
	}
}