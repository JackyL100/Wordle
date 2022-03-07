#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <time.h>
#include <vector>
#include <string.h>
const int rows = 6;
const int col = 5;
bool win = false;

std::vector<std::string> words;
std::vector<char> correctPos;

bool search(std::vector<std::string> list, std::string target) {
    int first = 0;
    int last = list.size();
    int middle;
    if (target.length() != 5) {
        return false;
    }
    while (first < last - 1) {
        middle = (first + last) / 2;
        if (list[middle].compare(target) < 0) {
            first = middle;
        } else if (list[middle].compare(target) > 0) {
            last = middle;
        } else {
            return true;
        }
    }
    return false;
}

void printArr(std::string arr[rows]) {
    std::cout << "\n";
    for (int i = 0; i < rows; i++) {
        std::cout << arr[i] << "\n";
    }
}

void printList(std::vector<char> v) {
    if (v.size() != 0) {
        std::cout << "The letters in the correct position are: ";
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << " ";
        }
        std::cout << "\n";
    }
}

bool in(char letter, std::string word) {
    for (int i = 0; i < 5; i++) {
        if (letter == word[i]) {
            return true;
        }
    }
    return false;
}

bool in(char letter, std::vector<char> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == letter) {
            return true;
        }
    }
    return false;
}

std::string getWord() {
    std::string word;
    do {
        std::cin >> word;
        if (search(words, word)) {
            break;
        } else {
            std::cout << "word not in list\n";
        }
    }
    while (true);
    return word;
}

void guess(std::string wordArr[rows], int row, std::string word) {
    std::string g = getWord();
    if (g == word) {
        win = true;
    }
    for (int i = 0; i < 5; i++) {
        if (g[i] == word[i] && !in(g[i], correctPos)) {
            correctPos.push_back(g[i]);
        }
        if (in(g[i], word)) {
            g[i] = toupper(g[i]);
        }
    }
    wordArr[row] = g;
}

int main() {
    std::string wordArray[rows];
    std::string chosenWord;
    for (int i = 0; i < rows; i++) {
        wordArray[i] = "-----";
    }
    printArr(wordArray);
    std::string fileName = "word.txt";
    std::fstream wordFile(fileName, wordFile.in | wordFile.out);
    if (!wordFile.is_open()) {
        std::cout << " ah shit ya fucked up\n";
    } else {
        srand(time(0));
        int lineNum = 0;
        int random = rand() % 200;
        std::string word;
        while (std::getline(wordFile, word)) {
            words.push_back(word);
            if (lineNum == random) {
                chosenWord = word;
            }
            lineNum++;
        }
    }
    int rowCount = 0;
    while (rowCount < rows) {
        std::cout << "\n";
        guess(wordArray, rowCount, chosenWord);
        printArr(wordArray);
        printList(correctPos);
        if (win) {
            std::cout << "yay you win\n";
            rowCount = rows;
        }
        rowCount++;
    }
    if (!win) {
        std::cout << "The word was: " << chosenWord << "\n";
    }
    wordFile.close();
}