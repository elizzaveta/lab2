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
//подсчет среднего балла
double* calculate_sr_ball(int n_budg, int** ball){
	double* sr_ball = new double[n_budg] {};
	double sum = 0;
	for (int i = 0; i < n_budg; i++){
		for (int j = 0; j < 5; j++){
			sum += ball[i][j];
		}
		sr_ball[i] = round(sum / 5 * 1000) / 1000;
		sum = 0;
	}
	return sr_ball;
}
//вывод данных
void output_file(string dir, int n_forty, vector<string> names_of_budg_sorted, double* sr_ball_sorted){
	string path = dir + "\\rating.csv";
	ofstream fout;
	fout.open(path);

	for (int i = 0; i < n_forty; i++){
		fout << names_of_budg_sorted[i] << "," << sr_ball_sorted[i] << "\n";
	}
	fout.close();
}
//количество студентов
int kilkist(vector<string> files){
	int k = 0;
	int n = files.size();
	ifstream fin;
	string str;
	for (int i = 0; i < n; i++){
		string path = files[i];
		fin.open(path);
		fin >> str;
		k += stoi(str);
		fin.close();
	}
	return k;
}
//ввод данных
void input(string dir, vector<string> files, string* all_names, int** all_ball, string* if_budg, int k) {
	int n = files.size();
	ifstream fin;
	string str;
	int g = 0;
	int m = -1;
	for (int i = 0; i < n; i++) {
		string path = dir + "\\";
		path += files[i];
		fin.open(path);
		if (fin.is_open()) {
			while (getline(fin, str)) {
				if (m == -1) {
					m = g;
					g += stoi(str);
				}
				else {
					int pos1 = 0;
					int pos2 = str.find(",", pos1);
					all_names[m] = str.substr(pos1, pos2 - pos1);
					for (int l = 0; l < 5; l++) {
						pos1 = pos2 + 1;
						pos2 = str.find(",", pos1 + 1);
						all_ball[m][l] = stoi(str.substr(pos1, pos2 - pos1));
					}
					pos1 = pos2 + 1;
					pos2 = str.length();
					if_budg[m] = str.substr(pos1, pos2 - pos1);
					m++;
				}
			}
			m = -1;
		}
		fin.close();
	}
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
//вычисление 40 процентов от бюджетников
int forty_percent(int n_budg)
{
	int n_forty = n_budg * 0.4;
	return n_forty;
}
//вычисление минимального балла для стипендии
double calculate_min_ball(int n_forty, double* sr_ball_sorted){
	double min_ball = sr_ball_sorted[n_forty - 1];
	return min_ball;
}

