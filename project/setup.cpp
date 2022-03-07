#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// make sure you have word.txt and temp.txt with word.txt having words and temp.txt being empty
std::vector<std::string> words;

void sortFile(std::fstream &file, std::fstream &temp) {
    std::string currentWord;
    while (std::getline(file, currentWord)) {
        words.push_back(currentWord);
    }
    sort(words.begin(), words.end());
    int line;
    for (int i = 0; i < words.size(); i++) {
        temp << words[i] << std::endl;
    }
}

int main() {
    std::string fileName = "word.txt";
    std::fstream wordFile(fileName, wordFile.in | wordFile.out);
    std::fstream temp;
    temp.open("temp.txt");
    if (wordFile.is_open() && temp.is_open()) {
        sortFile(wordFile, temp);
    }
    wordFile.close();
    temp.close();
    remove("word.txt");
    rename("temp.txt", "word.txt");
}