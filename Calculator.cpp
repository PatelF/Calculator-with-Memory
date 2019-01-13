#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// #include <sstream>
// #include <string>
#include <bits/stdc++.h>

using namespace std;

float history[100];
int historyCount = 0;
bool foundOper(char expression[], int loc){

	if (expression[loc] == '+' || expression[loc] == '-' 
		|| expression[loc] == '*' || expression[loc] == '/')
		return true;

	return false;
}

float firstNum(char expression[], int loc, float finalAns){

	char num1[loc];

	for(int i = 0; i < loc; i++){
		num1[i] = expression[i];
	}

	string str(num1,loc);

	if(str == "ans"){
		return history[historyCount - 1];
	}

	float num = strtof (num1, NULL);

	return num;
}

float secNum(char expression[], int loc, int length){

	char num2[length - loc];

	int j = 0;
	for(int i = loc; i < length; i++){
		num2[j] = expression[i+1];
		j++;	
	}

	float num = strtof(num2, NULL);
	return num;
}

float evaluate(char expression[], int length){

	float num1 = 0;
	float num2 = 0;
	float finalAns = 0;

	for(int i = 0; i < length; i++){
		if (foundOper(expression,i) == 1){

			num1 = firstNum(expression, i, finalAns);
			num2 = secNum(expression, i, length);

			if(expression[i] == '*'){
				finalAns = num1*num2;
				history[historyCount] = finalAns;
			}

			else if (expression[i] == '/'){

				if(num2 == 0){
					return NAN;
				}

				finalAns = num1/num2;
				history[historyCount] = finalAns;		
			}

			else if (expression[i] == '+'){
				finalAns = num1 + num2;
				history[historyCount] = finalAns;
			}

			else{
				finalAns = num1 - num2;
				history[historyCount] = finalAns;
			}

			historyCount++;
		}
	}

	return finalAns;
}

int main(){
	cout << "Enter an expression with one operation, no spaces, and press enter" << endl;

	while(true){
		string input = "";

		cin >> input;

		if (input == "Done"){
			cout << "\nHistory of Answers" << endl;
			cout << endl;
			cout << "[";

			for(int i = 0; i < historyCount; i++){	
				cout << history[i];

				if(i + 1 != historyCount){
					cout << " , ";
				}
			}

			cout << "]" << endl;

			return 0;
		}

		int n = input.length();

		char expression[n+1];

		strcpy(expression, input.c_str());

		float ans = evaluate(expression,n);

		cout << endl;

		cout << input << " = " << ans << endl;

		cout << "\n\nStart with ans to use your previous answer -> Example: 'ans/2.05'" << endl;
		cout << "Otherwise enter a new expression Or type 'Done' when finished" << endl;
	}
}
