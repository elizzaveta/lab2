#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main() {


}

//сделать массив имен бюджетников
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