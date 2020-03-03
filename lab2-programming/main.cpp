#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

vector<string> get_files(string);
void input(string, vector<string>, string*, int**, string*, int);
int kilkist(vector<string>, string);
vector<string> names_of_budg(string*, string*, int);
int** ball(int**, string*, int, int);
double* calculate_sr_ball(int, int**);
void sort_sr_ball(double*, vector<string>&, int);
void output_file(string, int, vector<string>, double*);
int forty_percent(int n_budg);
double calculate_min_ball(int n_forty, double* sr_ball_sorted);
void output_min(double min_ball);


int main() {

	setlocale(LC_ALL, "rus");

	string dir = "examples_2";

	vector<string> files = get_files(dir);

	for (int i = 0; i < files.size(); i++) {
		cout << files[i] << endl;
	}

	int all_st = kilkist(files, dir);

	string* all_names = new string[all_st];
	int** all_ball = new int* [all_st];
	for (int i = 0; i < all_st; i++)
	{
		all_ball[i] = new int[5];
	}
	string* if_budg = new string[all_st];

	input(dir, files, all_names, all_ball, if_budg, all_st);

	vector<string> budg = names_of_budg(all_names, if_budg, all_st);
	int n_budg = budg.size();
	int** b_ball = ball(all_ball, if_budg, all_st, n_budg);
	double* sr_ball = calculate_sr_ball(n_budg, b_ball);

	sort_sr_ball(sr_ball, budg, n_budg);

	int f = forty_percent(n_budg);
	double min = calculate_min_ball(f, sr_ball);

	output_file(dir, f, budg, sr_ball);
	output_min(min);

}

vector<string> get_files(string name) {
	vector<string> files;
	name += "\\*.csv";
	wstring wname(name.length(), L' ');
	copy(name.begin(), name.end(), wname.begin());
	wstring path = L"D:\\Кпи\\Прога\\git-projects\\git-lab2\\lab2\\lab2-programming\\";
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

int kilkist(vector<string> files, string dir) {
	int k = 0;
	int n = files.size();
	ifstream fin;
	string str;
	string path = dir + "\\";
	for (int i = 0; i < n; i++)
	{
		path += files[i];
		fin.open(path);
		fin >> str;
		stringstream st;
		st << str;
		int a;
		st >> a;
		k += a;
		fin.close();
	}
	return k;
}

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

vector<string> names_of_budg(string* all_names, string* if_budg, int n) {
	vector<string> names;
	for (int i = 0; i < n; i++) {
		if (if_budg[i] == "TRUE") {
			names.push_back(all_names[i]);
		}
	}
	return names;
}

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
double* calculate_sr_ball(int n_budg, int** ball) {
	double* sr_ball = new double[n_budg] {};
	double sum = 0;
	for (int i = 0; i < n_budg; i++) {
		for (int j = 0; j < 5; j++) {
			sum += ball[i][j];
		}
		sr_ball[i] = round(sum / 5 * 1000) / 1000;
		sum = 0;
	}
	return sr_ball;
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
double calculate_min_ball(int n_forty, double* sr_ball_sorted) {
	double min_ball = sr_ball_sorted[n_forty - 1];
	return min_ball;
}
//вывод минимального балла
void output_min(double min_ball) {
	cout << "min ball: " << min_ball;
}
void output_file(string dir, int n_forty, vector<string> names_of_budg_sorted, double* sr_ball_sorted)
{
	string path = dir + "\\rating.csv";
	ofstream fout;
	fout.open(path);

	for (int i = 0; i < n_forty; i++)
	{
		fout << names_of_budg_sorted[i] << "," << sr_ball_sorted[i] << "\n";
	}
	fout.close();
}

