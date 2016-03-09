#include <iostream>
#include <thread>
#include <mutex>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <climits>
#include <stdlib.h>
#include <fstream>

using namespace std;

std::mutex g_lock;

bool append{false},
        prepend{false},
        capfirst{false},
        capall{false},
        caplast{false},
        capallbutfirst{false},
        capallbutlast{false},
        lowercase{false},
        capception{false},
        capnone{false};

int bufferLength{2000000},
        threadcount{4},
        minlength{1},
        maxlength{5};


string charset{"\01203495687.!-@*_$#/,+%&?;=~^)[\\]`(:<'>|\"€"};

void threading(int start, vector<string> wordlist) {


    //array buffer
    vector<string> finalguess(bufferLength);

    //array chars

    string chars{charset};

    int count{0};
    //wordlist.push_back("password");
    //wordlist.push_back("word");
    //wordlist.push_back("computer");
    unsigned long long size{chars.size()},
            wordcount{wordlist.size()};


    string guess{""};

    clog << "[+] Thread " << start + 1 << " created!" << endl;
    //j = pw-zeichen anzahl
    for (int j = minlength; j <= maxlength; ++j) {
        g_lock.lock();
        clog << "[*] Thread " << start + 1 << " now appends " << j << " chars" << endl;
        g_lock.unlock();

        //Guess:
        for (unsigned long long x = start; x < pow(size, j); x += threadcount) {

            //guess:
            guess = "";
            for (int h = 1; h < j; ++h) {
                guess += chars[(int) (x / pow(size, j - h)) % size];
            }
            guess += chars[x % size];

            for (int k = 0; k < wordcount; ++k) {

                //if buffer array is full:
                if (count >= bufferLength - 100) {
                    //lock stdout
                    g_lock.lock();
                    //print buffer array
                    for (int i = 0; i <= count; ++i) {
                        printf("%s\n", finalguess[i].c_str());
                    }
                    //unlock stdout
                    g_lock.unlock();
                    count = 0;
                }

                string tmp{""};
                //add guess to buffer array
                if (append) {
                    if (capnone || capception) {
                        finalguess[count] = wordlist[k] + guess;
                        count++;
                    }
                    if (capfirst || capception) {
                        try {
                            tmp = wordlist[k];
                            wordlist[k][0] = toupper(wordlist[k][0]);
                            finalguess[count] = wordlist[k] + guess;
                            count++;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (capall || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 0; i < wordlist[k].size(); i++) {
                                wordlist[k][i] = toupper(wordlist[k][i]);
                            }
                            finalguess[count] = wordlist[k] + guess;
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (lowercase || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 0; i < wordlist[k].size(); i++) {
                                wordlist[k][i] = tolower(wordlist[k][i]);
                            }
                            finalguess[count] = wordlist[k] + guess;
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (caplast || capception) {
                        try {
                            tmp = wordlist[k];
                            wordlist[k][wordlist[k].size() - 1] = toupper(wordlist[k][wordlist[k].size() - 1]);
                            finalguess[count] = wordlist[k] + guess;
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (capallbutfirst || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 1; i < wordlist[k].size(); i++) {
                                wordlist[k][i] = toupper(wordlist[k][i]);
                            }
                            finalguess[count] = wordlist[k] + guess;
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (capallbutlast || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 0; i < wordlist[k].size() - 1; i++) {
                                wordlist[k][i] = toupper(wordlist[k][i]);
                            }
                            finalguess[count] = wordlist[k] + guess;
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }
                }
                if (prepend) {
                    if (!append && (capnone || capception)) {
                        finalguess[count] = wordlist[k] + guess;
                        count++;
                    }
                    if (capfirst || capception) {
                        try {
                            tmp = wordlist[k];
                            wordlist[k][0] = toupper(wordlist[k][0]);
                            finalguess[count] = guess + wordlist[k];
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (capall || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 0; i < wordlist[k].size(); i++) {
                                wordlist[k][i] = toupper(wordlist[k][i]);
                            }
                            finalguess[count] = guess + wordlist[k];
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (lowercase || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 0; i < wordlist[k].size(); i++) {
                                wordlist[k][i] = tolower(wordlist[k][i]);
                            }
                            finalguess[count] = guess + wordlist[k];
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (caplast || capception) {
                        try {
                            tmp = wordlist[k];
                            wordlist[k][wordlist[k].size() - 1] = toupper(wordlist[k][wordlist[k].size() - 1]);
                            finalguess[count] = guess + wordlist[k];
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (capallbutfirst || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 1; i < wordlist[k].size(); i++) {
                                wordlist[k][i] = toupper(wordlist[k][i]);
                            }
                            finalguess[count] = guess + wordlist[k];
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }


                    if (capallbutlast || capception) {
                        try {
                            tmp = wordlist[k];
                            for (int i = 0; i < wordlist[k].size() - 1; i++) {
                                wordlist[k][i] = toupper(wordlist[k][i]);
                            }
                            finalguess[count] = guess + wordlist[k];
                            count++;
                            wordlist[k] = tmp;
                        }
                        catch (...) {
                            throw;
                        }
                    }
                }
            }
        }
    }
    //print buffer one more time
    //lock stdout
    g_lock.lock();
    //print buffer array
    for (int i = 0; i <= count; ++i) {
        printf("%s\n", finalguess[i].c_str());
    }
    //unlock stdout
    g_lock.unlock();
}

void caponly(vector<string> wordlist) {
    clog << "[*] Trying the words without appending anything" << endl;
    //array chars

    string tmp{""};

    for (int k = 0; k < wordlist.size(); ++k) {


        if (capnone || capception) {
            printf("%s\n", wordlist[k].c_str());
        }
        if (capfirst || capception) {
            try {
                tmp = wordlist[k];
                wordlist[k][0] = toupper(wordlist[k][0]);
                printf("%s\n", wordlist[k].c_str());
                wordlist[k] = tmp;
            }
            catch (...) {
                throw;
            }
        }


        if (capall || capception) {
            try {
                tmp = wordlist[k];
                for (int i = 0; i < wordlist[k].size(); i++) {
                    wordlist[k][i] = toupper(wordlist[k][i]);
                }
                printf("%s\n", wordlist[k].c_str());
                wordlist[k] = tmp;
            }
            catch (...) {
                throw;
            }
        }


        if (lowercase || capception) {
            try {
                tmp = wordlist[k];
                for (int i = 0; i < wordlist[k].size(); i++) {
                    wordlist[k][i] = tolower(wordlist[k][i]);
                }
                printf("%s\n", wordlist[k].c_str());
                wordlist[k] = tmp;
            }
            catch (...) {
                throw;
            }
        }


        if (caplast || capception) {
            try {
                tmp = wordlist[k];
                wordlist[k][wordlist[k].size() - 1] = toupper(wordlist[k][wordlist[k].size() - 1]);
                printf("%s\n", wordlist[k].c_str());
                wordlist[k] = tmp;
            }
            catch (...) {
                throw;
            }
        }


        if (capallbutfirst || capception) {
            try {
                tmp = wordlist[k];
                for (int i = 1; i < wordlist[k].size(); i++) {
                    wordlist[k][i] = toupper(wordlist[k][i]);
                }
                printf("%s\n", wordlist[k].c_str());
                wordlist[k] = tmp;
            }
            catch (...) {
                throw;
            }
        }


        if (capallbutlast || capception) {
            try {
                tmp = wordlist[k];
                for (int i = 0; i < wordlist[k].size() - 1; i++) {
                    wordlist[k][i] = toupper(wordlist[k][i]);
                }
                printf("%s\n", wordlist[k].c_str());
                wordlist[k] = tmp;
            }
            catch (...) {
                throw;
            }
        }

    }
}


void help() {
    cout << endl << "Pipeline v2" << endl;
    cout << "Written by Sebastian Hirnschall 2016" << endl;
    cout << "Contact - hirnschallsebi@aol.at" << endl;
    cout << endl << "Usage: ./pipeline <options>" << endl;
    cout << "Options:" << endl;
    cout << "\t-t <value\tNumber of threads to use" << endl;
    cerr << "\t-b <value>\tNumber of values stored in each thread (Buffer)" << endl;
    cout << "\t-w <value>\tUses the specified dictionarys (up to 10)" << endl;
    cout << "\t-append\t\tAppends the values to the end of the input word" << endl;
    cout << "\t-prepend\t\tInserts the values to the front of the input word" << endl;
    cout << "\t-charSet <value>\tUses a custom charset. Do not use 'A'!" << endl;
    cout << "\t-c <value>\tSpecifies how long the inserted string should be" << endl;
    cout << "\t-capFirst\t\tCapitalizes the input word" << endl;
    cout << "\t-capAll\t\tCapitalizes the entire word" << endl;
    cout << "\t-capLast\t\tCapitalizes the last letter of the input word" << endl;
    cout << "\t-capAllButFirst\t\tCapitalizes all the letters but the first one" << endl;
    cout << "\t-capAllButLast\t\tCapitalizes all the letters but the last one" << endl;
    cout << "\t-capCeption\t\tAll cap options one after another" << endl;
    cout << endl << "Examples:" << endl;
    cout <<
    "./pipeline -w rockyou.txt -w dictionary.txt -capFirst -append -c 3 | ./john -stdin -format=NT hashlist.txt" <<
    endl;
    cout << "\tTakes two input dictionarys, capitalizes the first letter, appends 3 chars" << endl;
}


int main(int argc, char *argv[]) {

    vector<string> wordlists;

    vector<string> wordlist{};

    string line;



    //commandline arguments
    //-- Menu --//
    if (argc < 2) {
        help();
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        string arg{argv[i]};
        if ((arg == "-t") || (arg == "-T")) {
            i++;
            threadcount = atoi(argv[i]);
        }
        else if ((arg == "-b") || (arg == "-B")) {
            i++;
            bufferLength = atoi(argv[i]);
        }
            /**  else if ((arg == "-d") || (arg == "-D")) {
            *    threadcount = 4;
            *    bufferLength = 2000000;
            *    minLength = 1;
            *    maxlength = 5;
            *    break;
            *}
            **/
        else if ((arg == "-w") || (arg == "-W")) {
            //cout << arg;
            i++;
            wordlists.push_back(argv[i]);
        }
        else if ((arg == "-append") || (arg == "-Append")) {
            append = true;
        }
        else if ((arg == "-prepend") || (arg == "-Prepend")) {
            prepend = true;
        }
        else if ((arg == "-c") || (arg == "-C")) {
            i++;
            if (atoi(argv[i]) <= 9) {
                maxlength = atoi(argv[i]);
            }
            else {
                cout << "You cant append/prepend more than 9 chars...";
                return 0;
            }
        }
        else if ((arg == "-capfirst") || (arg == "-capFirst")) {
            capfirst = true;
        }
        else if ((arg == "-capall") || (arg == "-capAll")) {
            capall = true;
        }
        else if ((arg == "-caplast") || (arg == "-capLast")) {
            caplast = true;
        }
        else if ((arg == "-capallbutfirst") || (arg == "-capAllButFirst")) {
            capallbutfirst = true;
        }
        else if ((arg == "-capallbutlast") || (arg == "-capAllButLast")) {
            capallbutlast = true;
        }
        else if ((arg == "-capception") || (arg == "-capCeption")) {
            capception = true;
        }
        else if ((arg == "-capnone") || (arg == "-capNone")) {
            capnone = true;
        }
        else if ((arg == "-lowercase") || (arg == "-lowerCase")) {
            lowercase = true;
        }
        else if ((arg == "-charset") || (arg == "-charSet")) {
            i++;
            charset = "\0";
            charset += argv[i];
        }
        else if ((arg == "-min") || (arg == "-Min")) {
            i++;
            minlength = atoi(argv[i]);
        }
        else if ((arg == "-max") || (arg == "-Max")) {
            i++;
            maxlength = atoi(argv[i]);
        }
        else if ((arg == "-h") || (arg == "-H")) {
            help();
            return 0;
        }

    }


    for (string wordfile : wordlists) {
        clog << "Parsing " << wordfile.c_str() << "...\n";
        //cout << wordlist;
        ifstream file{wordfile};
        string str;
        if (file.is_open()) {
            while (getline(file, str)) {
                if (str != "") {
                    wordlist.push_back(str);
                }
            }
        }
        else {
            clog << "Error: Can't open" << wordfile.c_str() << "!\n";
        }
    }
    clog << "Done parsing all wordlists!\tTotal: " << wordlist.size() << " words\n\n";

    if (wordlist.size() == 0) {
        cerr << "No words found!\n";
        return 0;
    }
    if (!append && !prepend && !capfirst && !capall && !caplast && !capallbutlast && !capallbutfirst && !lowercase &&
        !capception) {
        cerr << "Just use \"cat wordlist\" instead of Pipeline!\nFor help run pipeline -h ...\n";
        return 0;
    }

    caponly(wordlist);


    clog << "[*] Now starting " << threadcount << " threads to append/prepend!\n";
    //how many threads?
    std::thread t1(threading, 0, wordlist);
    if (threadcount >= 2) {
        std::thread t2(threading, 1, wordlist);
        if (threadcount >= 3) {
            std::thread t3(threading, 2, wordlist);
            if (threadcount >= 4) {
                std::thread t4(threading, 3, wordlist);
                if (threadcount >= 5) {
                    std::thread t5(threading, 4, wordlist);
                    if (threadcount >= 6) {
                        std::thread t6(threading, 5, wordlist);
                        if (threadcount >= 7) {
                            std::thread t7(threading, 6, wordlist);
                            if (threadcount >= 8) {
                                std::thread t8(threading, 7, wordlist);
                                if (threadcount >= 9) {
                                    std::thread t9(threading, 8, wordlist);
                                    if (threadcount >= 10) {
                                        std::thread t10(threading, 9, wordlist);
                                        if (threadcount >= 11) {
                                            std::thread t11(threading, 10, wordlist);
                                            if (threadcount >= 12) {
                                                std::thread t12(threading, 11, wordlist);
                                                if (threadcount >= 13) {
                                                    std::thread t13(threading, 12, wordlist);
                                                    if (threadcount >= 14) {
                                                        std::thread t14(threading, 13, wordlist);
                                                        if (threadcount >= 15) {
                                                            std::thread t15(threading, 14, wordlist);
                                                            if (threadcount >= 16) {
                                                                std::thread t16(threading, 15, wordlist);
                                                                if (threadcount >= 17) {
                                                                    std::thread t17(threading, 16, wordlist);
                                                                    if (threadcount >= 18) {
                                                                        std::thread t18(threading, 17, wordlist);
                                                                        if (threadcount >= 19) {
                                                                            std::thread t19(threading, 18, wordlist);
                                                                            if (threadcount >= 20) {
                                                                                std::thread t20(threading, 19,
                                                                                                wordlist);
                                                                                if (threadcount >= 21) {
                                                                                    std::thread t21(threading, 20,
                                                                                                    wordlist);
                                                                                    if (threadcount >= 22) {
                                                                                        std::thread t22(threading, 21,
                                                                                                        wordlist);
                                                                                        if (threadcount >= 23) {
                                                                                            std::thread t23(threading,
                                                                                                            22,
                                                                                                            wordlist);
                                                                                            if (threadcount >= 24) {
                                                                                                std::thread t24(
                                                                                                        threading,
                                                                                                        23, wordlist);
                                                                                                if (threadcount >= 25) {
                                                                                                    std::thread t25(
                                                                                                            threading,
                                                                                                            24,
                                                                                                            wordlist);
                                                                                                    if (threadcount >=
                                                                                                        26) {
                                                                                                        std::thread t26(
                                                                                                                threading,
                                                                                                                25,
                                                                                                                wordlist);
                                                                                                        if (threadcount >=
                                                                                                            27) {
                                                                                                            std::thread t27(
                                                                                                                    threading,
                                                                                                                    26,
                                                                                                                    wordlist);
                                                                                                            if (threadcount >=
                                                                                                                28) {
                                                                                                                std::thread t28(
                                                                                                                        threading,
                                                                                                                        27,
                                                                                                                        wordlist);
                                                                                                                if (threadcount >=
                                                                                                                    29) {
                                                                                                                    std::thread t29(
                                                                                                                            threading,
                                                                                                                            28,
                                                                                                                            wordlist);
                                                                                                                    if (threadcount >=
                                                                                                                        30) {
                                                                                                                        std::thread t30(
                                                                                                                                threading,
                                                                                                                                29,
                                                                                                                                wordlist);
                                                                                                                        if (threadcount >=
                                                                                                                            31) {
                                                                                                                            std::thread t31(
                                                                                                                                    threading,
                                                                                                                                    30,
                                                                                                                                    wordlist);
                                                                                                                            if (threadcount >=
                                                                                                                                32) {
                                                                                                                                std::thread t32(
                                                                                                                                        threading,
                                                                                                                                        31,
                                                                                                                                        wordlist);
                                                                                                                                t32.join();
                                                                                                                            }
                                                                                                                            t31.join();
                                                                                                                        }
                                                                                                                        t30.join();
                                                                                                                    }
                                                                                                                    t29.join();
                                                                                                                }
                                                                                                                t28.join();
                                                                                                            }
                                                                                                            t27.join();
                                                                                                        }
                                                                                                        t26.join();
                                                                                                    }
                                                                                                    t25.join();
                                                                                                }
                                                                                                t24.join();
                                                                                            }
                                                                                            t23.join();
                                                                                        }
                                                                                        t22.join();
                                                                                    }
                                                                                    t21.join();
                                                                                }
                                                                                t20.join();
                                                                            }
                                                                            t19.join();
                                                                        }
                                                                        t18.join();
                                                                    }
                                                                    t17.join();
                                                                }
                                                                t16.join();
                                                            }
                                                            t15.join();
                                                        }
                                                        t14.join();
                                                    }
                                                    t13.join();
                                                }
                                                t12.join();
                                            }
                                            t11.join();
                                        }
                                        t10.join();
                                    }
                                    t9.join();
                                }
                                t8.join();
                            }
                            t7.join();
                        }
                        t6.join();
                    }
                    t5.join();
                }
                t4.join();
            }
            t3.join();
        }
        t2.join();
    }
    t1.join();

    return 0;
}

