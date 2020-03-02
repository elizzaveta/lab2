#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main() {

	
}

vector<string> get_files(string name) {
	vector<string> files;
	name += "\\*.csv";
	wstring wname(name.length(), L' ');
	copy(name.begin(), name.end(), wname.begin());
	wstring path = L"D:\\Êïè\\Ïðîãà\\lab-code\\lab2-code\\lab2-code\\";
	path += wname;
	WIN32_FIND_DATA names;
	HANDLE hf = FindFirstFileW(path.c_str(), &names);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			wstring ws(&names.cFileName[0]);
			string s(ws.begin(), ws.end());
			files.push_back(s);
		} while (FindNextFile(hf, &names) != 0);
	}

	return files;
}

//ñäåëàòü ìàññèâ èìåí áþäæåòíèêîâ
vector<string> names_of_budg(string* all_names, string* if_budg, int n) {
	vector<string> names;
	for (int i = 0; i < n; i++) {
		if (if_budg[i] == "TRUE") {
			names.push_back(all_names[i]);
		}
	}
	return names;
}


int* sr_ball(int n_budg, int** ball){
	int* sr_ball = new int[n_budg] {};
	int sum = 0;
	for (int i = 0; i < n_budg; i++){
		for (int j = 0; j < 5; j++){
			sum += ball[i][j];
		}
		sr_ball[i] = sum / 5;
		sum = 0;
	}
	return sr_ball;
}

//çàïèñàòü âñå áàëëû áþäæåòíèêîâ â ìàññèâ
int** ball(int** all_ball, string* if_budg, int n, int n_budg) {
	int** ball = new int* [n_budg];
	for (int i = 0; i < n_budg; i++) {
		ball[i] = new int[5];
	}
	int b_pointer = 0;
	for (int f = 0; f < n; f++) {
		if (if_budg[f] == "TRUE") {
			for (int j = 0; j < 5; j++) {
				ball[b_pointer][j] = all_ball[f][j];
			}
			b_pointer++;
		}
	}
	return ball;
}

//сортировка имен бджетников и их среднего балла по спаданию среднего балла
void sort_sr_ball(double* sr_ball, vector<string>& names, int n_budg) {
	for (int f = 1; f < n_budg; f++) {
		int j = f - 1;
		double key = sr_ball[f];
		string key_name = names[f];
		while ((j >= 0) && (sr_ball[j] < key)) {
			sr_ball[j + 1] = sr_ball[j];
			names[j + 1] = names[j];
			j--;
		}
		sr_ball[j + 1] = key;
		names[j + 1] = key_name;
	}
}
