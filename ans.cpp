#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool isCompoundWord(const string& word, const unordered_set<string>& wordSet) {
    if (wordSet.empty()) return false; 

    vector<bool> dp(word.size() + 1, false);
    dp[0] = true;

    for (int i = 1; i <= word.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && wordSet.find(word.substr(j, i - j)) != wordSet.end()) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp.back();
}

int main() {
    auto start = high_resolution_clock::now();

    ifstream inputFile("Input_01.txt");
    vector<string> words;
    string word;
    while (inputFile >> word) {
        words.push_back(word);
    }

    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });

    unordered_set<string> wordSet;
    string longestCompound;
    string secondLongestCompound;

    for (const string& word : words) {
        if (isCompoundWord(word, wordSet)) {
            if (word.size() > longestCompound.size()) {
                secondLongestCompound = longestCompound;
                longestCompound = word;
            } else if (word.size() > secondLongestCompound.size()) {
                secondLongestCompound = word;
            }
        }
        wordSet.insert(word);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Longest Compound Word: " << longestCompound << endl;
    cout << "Second Longest Compound Word: " << secondLongestCompound << endl;
    cout << "Time taken to process file Input_01.txt: " << duration.count() << " milliseconds" << endl;

    return 0;
}
