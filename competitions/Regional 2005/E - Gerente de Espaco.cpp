#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <ciso646>
#include <limits>

using namespace std;

/*
 * 100% ad-hoc, not much to say. some tips:
 * 
 * - take care of overflows, use long long.
 * 
 * - in the sample output, it shows [#] [#] [#] [#] [#] [#] [-] [ ], but,
 * in truth, the output should be [#][#][#][#][#][#][-][ ] (without spaces)
 * 
 * - when inserting, take the SMALLEST free block, not the first free block. 
 * if two blocks are the smallest, then take the first one.
 * 
 * - store a vector of files, each having start, end, size and name. don't
 * manage the memory as an array, because you'll get memory limit.
 **/

struct file {
	file(int size, int start, const string& name)
		: size(size), start(start), end(start + size), name(name) {
	}
	int size, start, end;
	string name;
};

vector<file> files;
bool error = false;
int N, disk_size = 0;

int get_size(const string& sz) {
	string measure;
	int num;
	istringstream ss(sz);
	ss >> num >> measure;
	if (measure == "Mb") return num * 1024;
	else if (measure == "Gb") return num * 1024 * 1024;
	else return num;
}

void organize() {
	if (error) return;
	for (int i = 0; i < (int)files.size(); ++i) {
		int bef = (i == 0 ? 0 : files[i - 1].end);
		if (bef != files[i].start) {
			files[i].start = bef;
			files[i].end = files[i].start + files[i].size;
		}
	}
}

void insert(int size, const string& name) {
	if (error) return;
	if (size > disk_size) {	error = true; return; }
	if (files.empty()) {
		files.push_back(file(size, 0, name));
		return;
	}

	int where = -1; // put before 'where'
	int smallest_size = numeric_limits<int>::max();
	for (int i = 0; i < (int)files.size(); ++i) {
		int bef = (i == 0 ? 0 : files[i - 1].end);
		int sz = files[i].start - bef;
		if (sz >= size and smallest_size > sz) {
			smallest_size = sz;
			where = i;
		}
	}
	int last_sz = disk_size - files.back().end;
	if (last_sz >= size and smallest_size > last_sz) {
		where = files.size();
	}

	if (where == -1) {
		organize();
		if (disk_size - files.back().end >= size) {
			files.push_back(file(size, files.back().end, name));
			return;
		}			
		// already organized and didn't find any free place		
		error = true;
		return;
	}

	// put before 'where'
	int bef = (where == 0 ? 0 : files[where - 1].end);
	files.insert(files.begin() + where, file(size, bef, name));
	return;
}

void remove(const string& name) {
	if (error) return;
	for (int i = 0; i < (int)files.size(); ++i) {
		if (files[i].name == name) {
			files.erase(files.begin() + i);
			break;
		}
	}
}

void print() {
	if (error) {
		cout << "ERRO: disco cheio" << endl;
	} else {
		vector<int> blocks(8, 0);
		int block_size = disk_size / 8;
		for (int i = 0; i < (int)files.size(); ++i) {
			int bs = files[i].start / block_size;
			int be = files[i].end / block_size;
			if (bs == be) { blocks[bs] += files[i].size; } else {
				blocks[bs] += (bs + 1) *  block_size - files[i].start;
				blocks[be] += files[i].end - be * block_size;
				for (int j = bs + 1; j < be; ++j)
					blocks[j] = block_size;
			}
		}
		for (int i = 0; i < 8; ++i) {
			double pc = 100.0 * ((block_size - blocks[i]) / (double)block_size);
			cout << "[";
			if (pc > 75.0 and pc <= 100.0) cout << " ";
			else if (pc > 25.0 and pc <= 75.0) cout << "-";
			else if (pc >= 0.0 and pc <= 25.0) cout << "#";
			else cout << "x";
			cout << "]";
		}
		cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N, N != 0) {
		error = false;
		files.clear();

		string ds; cin >> ds;
		disk_size = get_size(ds);
		
		for (int c = 0; c < N; ++c) {
			string cmd, name, size;
			cin >> cmd;			
			if (cmd == "insere") {
				cin >> name >> size;
				insert(get_size(size), name);	
			} else if (cmd == "remove") {
				cin >> name;
				remove(name);
			} else if (cmd == "otimiza") {
				organize();
			}
		}
		print();
	}
}