#include<iostream>
#include<set>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int no_of_transactions, friends;
	cin >> no_of_transactions >> friends;

	int x, y, amount;

	// Make a 1-D array to store the net amount that each person will have to take at the end
	int net[100000] = {0};

	while (no_of_transactions--) {
		cin >> x >> y >> amount;
		net[x] -= amount;
		net[y] += amount;
	}

	multiset<int> m;
	// Init a list & sort it => multiset
	for (int i = 0; i < friends; i++) {
		if (net[i] != 0) {
			m.insert(net[i]);
		}
	}

	// Pop out two person (left & right) and try to settle them
	int cnt = 0;
	while (!m.empty()) {
		auto low = m.begin();
		auto high = prev(m.end());

		int debit = *low;
		int credit = *high;

		// Erase
		m.erase(low);
		m.erase(high);

		// Settlement
		int settlement_amount = min(-debit, credit);

		cnt++;

		// Settlement_amount from donor to acceptor
		debit += settlement_amount;
		credit -= settlement_amount;

		// one of them will be zero
		if (debit != 0) {
			m.insert(debit);
		}
		if (credit != 0) {
			m.insert(credit);
		}
	}

	cout << cnt << endl;

	return 0;
}