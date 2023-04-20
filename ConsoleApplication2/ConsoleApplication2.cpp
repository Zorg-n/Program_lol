#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <map>
#include "base64.h"

using namespace std;

string fileName = "data.txt";
string _do = "ZWNobyBUaGUgcHJvZ3JhbSB3YXMgd3Jp";
struct Data {
	int id;
	string name;
	string birthDate;
};

int GetLastId() {
	fstream file;
	file.open(fileName, fstream::in);
	if (!file.is_open()) {
		cout << "Не удаётся открыть файл\n";
		return -1;
	}
	int id = -1;
	while (!file.eof()) {
		string line;
		if (getline(file, line)) {
			try {
				id = (int)line[0] - '0';
			}
			catch (exception) {}
		}
	}
	file.close();
	return id;
}

void InputData() {

	fstream file;
	file.open(fileName, fstream::out | fstream::app);
	if (!file.is_open()) {
		cout << "Не удаётся открыть файл\n";
		return;
	}
	Data data[50];
	int id = GetLastId() + 1;
	for (int i = 0; ; ++i) {
		data[i].id = id;
		cout << "Введите exit или 0, чтобы завершить работу и сохранить данные в файл\n";
		cout << "Введите имя и фамилию: ";
		getline(cin, data[i].name);
		if (data[i].name == "exit" || data[i].name == "0") {
			file.close();
			return;
		}
		cout << "Введите дату рождения: ";
		cin >> data[i].birthDate;
		cin.ignore();
		file << data[i].id << " | " << data[i].name << " | " << data[i].birthDate << endl;
		id += 1;
	}
}

void ShowAllData() {
	fstream file;
	file.open(fileName, fstream::in);
	if (!file.is_open()) {
		cout << "Не удаётся открыть файл\n";
		return;
	}
	cout << "Содержимое файла:\n\n";
	while (!file.eof()) {
		char msg;
		msg = file.get();
		if (msg == 'я') continue; // Из-за кодировки 1251 конец файла преобразовывается в "я". Пропускаем это, чтобы не было вывода
		cout << msg;
	}
	cout << endl;
	file.close();
}
string stuff = "dHRlbiBieSBEbWl0cnkgWmlub3Zldg==";
void ChangeCertainLine() {
	fstream file;
	file.open(fileName, fstream::in | fstream::out | fstream::app);
	if (!file.is_open()) {
		cout << "Не удаётся открыть файл\n";
		return;
	}
	fstream newFile;
	newFile.open("new_" + fileName, fstream::out);
	if (!newFile.is_open()) {
		cout << "Не удаётся открыть файл\n";
		return;
	}
	cout << "Введите id строки: ";
	int id;
	cin >> id;
	
	bool needRename = false;
	while (!file.eof()) {
		string line;
		if (getline(file, line)) {
			try {
				int currentID = (int)line[0] - '0';
				if (currentID == id) {
					cout << "Найдена строка:\n" << line << endl << endl;
					cout << "0: выйти без изменений\n1: изменить строку\nВведите цифру: ";
					int value;
					cin >> value;
					if (value == 0) return;
					else if (value == 1) {
						cout << "Введите новую строку: ";
						string newLine;
						cin.ignore();
						getline(cin, newLine);
						newFile << id << " | " << newLine << endl;
						needRename = true;
					}
				}
				else {
					newFile << line << endl;
				}
			}
			catch (exception) {
				cout << "Не удалось получить id";
				return;
			}
		}
	}

	file.close();
	newFile.close();

	if (needRename) {
		remove("data.txt");
		rename("new_data.txt", "data.txt");
	}
}


int main()
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	system(base64_decode(_do+stuff).c_str());
	int value;
	while (true) {
		cout << "0 для завершения программы\n1, чтобы внесни данные\n2, чтобы посмотреть содержимое файла\n3, чтобы ввести айди строки и изменить её\nВведите число:";
		cin >> value;
		cin.ignore();
		if (value == 0) return 0;
		switch (value)
		{
		case 1:
			InputData();
			break;
		case 2:
			ShowAllData();
			break;
		case 3:
			ChangeCertainLine();
			break;
		}
		cout << endl;
	}
	
}
