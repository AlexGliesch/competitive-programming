#include <string>
#include <iostream>
#include <sstream>
#include <ciso646>
#include <cstring>
#include <map>

using namespace std;

/*
 * ad-hoc, the idea is: if a program is called with the same input on the same
 * call stack, it will never terminate. note: it has to be on the same call 
 * stack! if it calls with the same input, one after the other, then there's
 * no problem.
 * 
 * lots of important details:
 * 
 * - watch out for overflow (>=1000) and underflow (<0)
 * - you must dp the return of a call with a given input, otherwise you'll 
 * get TLE.
 * - watch out for nested if's
 * - watch out for division or mod by 0
 **/

int called_values[1010], dp[1010];
string opcode[110], op1[110], op2[110], s;
int L, N, error;

int get_val(const string& op, map<string, int>& regs) {
	istringstream ss(op);
	int val;
	ss >> val;
	if (not ss.fail() and ss.eof()) 
		return val;		
	else return regs[op];
}

void go_to_end_if(int& i) {
	int new_ifs = 1;
	while ((++i < L)) {
		if (opcode[i][0] == 'I' and opcode[i][1] == 'F') ++new_ifs;
		else if (opcode[i] == "ENDIF") --new_ifs;		
		if (new_ifs == 0) break;
	}
}

void correct_overflow(int& val) {
	if (val >= 1000) val -= 1000;
	if (val < 0) val += 1000;
}

int run(int startval) {
	int retval = -1;
	if (called_values[startval]) {
		error = true;
		return -1;
	}

	if (dp[startval] != -1) return dp[startval];
	called_values[startval] = true;

	map<string, int> regs;
	regs["R0"] = startval;	

	for (int i = 0; i < L and not error; ++i) {
		if (opcode[i] == "MOV") {
			regs[op1[i]] = get_val(op2[i], regs);
			correct_overflow(regs[op1[i]]);
		} else if (opcode[i] == "ADD") {
			regs[op1[i]] += get_val(op2[i], regs);
			correct_overflow(regs[op1[i]]);
		} else if (opcode[i] == "SUB") {
			regs[op1[i]] -= get_val(op2[i], regs);
			correct_overflow(regs[op1[i]]);
		} else if (opcode[i] == "MUL") {
			regs[op1[i]] *= get_val(op2[i], regs);
			correct_overflow(regs[op1[i]]);
		} else if (opcode[i] == "DIV") {
			if (get_val(op2[i], regs) == 0 or get_val(op1[i], regs) == 0)
				regs[op1[i]] = 0;
			else regs[op1[i]] /= get_val(op2[i], regs);
			correct_overflow(regs[op1[i]]);
		} else if (opcode[i] == "MOD") {
			if (get_val(op2[i], regs) == 0 or get_val(op1[i], regs) == 0)
				regs[op1[i]] = 0;
			else regs[op1[i]] %= get_val(op2[i], regs);
			correct_overflow(regs[op1[i]]);
		} else if (opcode[i] == "ENDIF") {
			continue;
		} else if (opcode[i] == "IFEQ") {
			if (not(get_val(op1[i], regs) == get_val(op2[i], regs)))
				go_to_end_if(i);
		} else if (opcode[i] == "IFNEQ") {
			if (not(get_val(op1[i], regs) != get_val(op2[i], regs)))
				go_to_end_if(i);
		} else if (opcode[i] == "IFG") {
			if (not(get_val(op1[i], regs) > get_val(op2[i], regs)))
				go_to_end_if(i);
		} else if (opcode[i] == "IFL") {
			if (not(get_val(op1[i], regs) < get_val(op2[i], regs)))
				go_to_end_if(i);
		} else if (opcode[i] == "IFGE") {
			if (not(get_val(op1[i], regs) >= get_val(op2[i], regs)))
				go_to_end_if(i);
		} else if (opcode[i] == "IFLE") {
			if (not(get_val(op1[i], regs) <= get_val(op2[i], regs)))
				go_to_end_if(i);
		} else if (opcode[i] == "RET") {
			retval = get_val(op1[i], regs);
			break;
		} else if (opcode[i] == "CALL") {
			regs["R9"] = run(get_val(op1[i], regs));
		}
	}
	called_values[startval] = false;	
	dp[startval] = retval;
	return retval;
}

int main(){
	ios_base::sync_with_stdio(false);
	while (cin >> L >> N, not(L == 0 and N == 0)) {
		for (int i = 0; i < L; ++i) {
			cin >> opcode[i];
			if (opcode[i] == "ENDIF") {
				continue;
			} 
			cin >> s;
			istringstream ss(s);
			if (opcode[i] == "CALL" or opcode[i] == "RET") {
				getline(ss, op1[i], ',');
			} else {
				getline(ss, op1[i], ',');
				getline(ss, op2[i], ',');
			}
		}
		error = false;
		memset(called_values, false, sizeof(called_values));
		memset(dp, -1, sizeof(dp));

		int retval = run(N);
		if (error or retval == -1) cout << "*" << endl;
		else cout << retval << endl;
	}
}