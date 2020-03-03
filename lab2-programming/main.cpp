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
void output_file(string dir, int n_forty, vector<string> names_of_budg_sorted, double* sr_ball_sorted){
	string path = dir + "\\rating.csv";
	ofstream fout;
	fout.open(path);

	for (int i = 0; i < n_forty; i++){
		fout << names_of_budg_sorted[i] << "," << sr_ball_sorted[i] << "\n";
	}
	fout.close();
}
int kilkist(vector<string> files)//кількість студентів{
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
void input(vector<string> files, string* all_names, int** all_ball, string* if_budg, int k){
	int n = files.size();
	ifstream fin;
	string str;
	int m = 0;
	for (int i = 0; i < n; i++){
		string path = files[i];
		fin.open(path);
		if (fin.is_open()){
			while (getline(fin, str)){
				if (m == 0)
					continue;
				int pos1 = 0;
				int pos2 = str.find(",", pos1);
				all_names[m] = str.substr(pos1, pos2 - pos1);
				for (int l = 0; l < 5; l++){
					pos1 = pos2;
					pos2 = str.find(",", pos1 + 1);
					all_ball[m][l] = stoi(str.substr(pos1, pos2 - pos1));
				}
				pos1 = pos2;
				pos2 = str.length();
				if_budg[m] = str.substr(pos1, pos2 - pos1);
				m++;
			}
		}
		fin.close();
	}
}
