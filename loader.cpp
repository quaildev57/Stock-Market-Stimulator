#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool parseCSV(const string& line, int& price) {
    stringstream ss(line);
    string date, priceStr;
    if (!getline(ss, date, ',')) return false;
    if (!getline(ss, priceStr, ',')) return false;

    stringstream ps(priceStr);
    ps >> price;
    return true;
}

bool loadData(const string& filename, vector<int>& prices) {
    prices.clear();
    ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        cout << "Could not open file!" << filename << endl;
        return false;
    }

    string line;
    bool firstLine = true;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        if (firstLine) {
            firstLine = false;
            if (line.find("Date") != string::npos) continue;
        }

        int p = 0;
        if (parseCSV(line, p)) prices.push_back(p);
    }

    fin.close();
    if (prices.empty()) {
        cout << "No valid data found in the file!" << endl;
        return false;
    }

    cout << "Loaded " << prices.size() - 1 << " days of data!" << endl;
    return true;
}

pair<int, int> getMinMax(const vector<int>& prices) {
    int mini = *min_element(prices.begin(), prices.end());
    int maxi = *max_element(prices.begin(), prices.end());

    return {mini, maxi};
}

void showSummary(const vector<int>& prices) {
    if (prices.empty()) cout << "Error in loading data!" << endl;

    pair<int, int> p = getMinMax(prices);
    cout << "Total days: " << prices.size() << endl;
    cout << "Maximum price: " << p.first << endl;
    cout << "Minimum price: " << p.second << endl;
}