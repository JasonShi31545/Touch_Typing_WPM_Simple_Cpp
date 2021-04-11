#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char *argv[]) {
    
    string ext = ""; // the main text
    
    srand(time(0));
    const int file_no = rand() % 5 + 0; // random number for exerpt file selection

    string temp; // temp for getline extraction of file
    string t = "exerpt .txt"; // f name without random number
    char *fn = (char *)t.c_str(); // official name in char *
    fn[6] = file_no + '0'; // f name with random number

    ifstream f_c(fn); // file with filename fn
    while(getline(f_c, temp)) {
        ext += temp;
    } // initialize ext with the content of file.

    vector<string> words; // all the words (tokens) in the file
    string temp_word = ""; // temporary for word storage from characters

    int word_count = 0; // word count for calculating wpm
    for (auto c : ext) { // initialization of words
        if (c == ' ') {
            word_count++;
            words.push_back(temp_word);
            temp_word = "";
        } else {
            temp_word += c;
        }
    }
    word_count++;

    cout << "Please type the following passage: " << endl;
    cout << ext << endl;
    cout << endl;

    const int in_threashold = 7; // input padding for _input (which is a fixed sized char array
    char _input[ext.size() + in_threashold];

    // start timer
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    // GET CONTENT
    cin.getline(_input, ext.size() + in_threashold);
    
    //end timer
    end = chrono::system_clock::now();

    chrono::duration<double> es = end - start;

    string input(_input); // convert _input (fixed sized char array) to string in c++
    // es.count();

    vector<string> input_words; // analyze the input words (tokens)
    temp_word = "";
    for (auto ch : input) {
        if (ch == ' ') {
            input_words.push_back(temp_word);
            temp_word = "";
        } else {
            temp_word += ch;
        }
    }



    // check mistake
    int mistake = 0; // mistake counter in character mistakes
    const int threashold_cc = 10; // if there are max 100  words (tokens) less from the input to original exerpt, it is tolerated as completed.

    if (input_words.size() >= (words.size() - threashold_cc)) {
        for (int i = 0; i < words.size(); i++) {
            if (i >= input_words.size()) {
                break;
            }
            if (words[i] != input_words[i]) {
                mistake += words[i].size() / 2 - 1; // assume you have to delete to middle of the token to fix all the issues
            }
        }
    } else {
        cerr << "Unfinished text" << endl;
        return -1;
    }
   
    // calculate score.
    double sec_f_m = (1.3/4.5) * mistake;
    chrono::duration<double> mt(mistake);
    double tt = (es + mt).count();
    double wps = word_count / tt;
    double wpm = wps * 60;
    cout << "Your WPM: " << wpm << endl;

    return 0;
}
