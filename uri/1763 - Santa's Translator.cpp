#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

unordered_map<string, string> m = {
		{ "brasil", "Feliz Natal!" },
		{ "alemanha", "Frohliche Weihnachten!" },
		{ "austria", "Frohe Weihnacht!" },
		{ "coreia", "Chuk Sung Tan!"},
		{ "espanha", "Feliz Navidad!" },
		{ "grecia", "Kala Christougena!" },
		{ "inglaterra", "Merry Christmas!" },
		{ "australia", "Merry Christmas!" },
		{ "portugal", "Feliz Natal!" },
		{ "suecia", "God Jul!" },
		{ "turquia", "Mutlu Noeller" },
		{ "argentina", "Feliz Navidad!" },
		{ "chile", "Feliz Navidad!" },
		{ "mexico", "Feliz Navidad!" },
		{ "antardida", "Merry Christmas!" },
		{ "canada", "Merry Christmas!" },
		{ "irlanda", "Nollaig Shona Dhuit!"},
		{ "belgica", "Zalig Kerstfeest!" },
		{ "italia", "Buon Natale!" },
		{ "libia", "Buon Natale!" },
		{ "siria", "Milad Mubarak!" },
		{ "marrocos", "Milad Mubarak!" },
		{ "japao", "Merii Kurisumasu!" },
		{ "estados-unidos", "Merry Christmas!" }
};

int main() {
	string s;
	ios_base::sync_with_stdio(false);
	while (getline(cin, s)) {
		auto i = m.find(s);
		if (i == m.end()) cout << "--- NOT FOUND ---" << endl;
		else cout << i->second << endl;
	}
}