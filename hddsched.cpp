
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string.h>
#include <algorithm>

const int SIZE = 5000;
const std::string RANGE = "0-4999";
const std::string BIN_NAME = "sched";

void PrintUsage();
void PrintVector(const std::vector<int> &addr, const int &size);
void RunSchedule(const std::vector<int> &addr, const int &size);
void FCFS(const std::vector<int> &addr, const int &size, const int &start, const bool &print);
void SCAN(const std::vector<int> &addr, const int &size, const int &start, const bool &print, const char &dir);
void CSCAN(const std::vector<int> &addr, const int &size, const int &start, const bool &print, const char &dir);

int main(int argc, char* argv[]){

    std::vector<int> addresses;
    std::ifstream inFile;
    std::string fileName, temp;
    int startPos=0, flagLen=0;
    bool usage=false, printAddr=false, printF=false, printC=false, printS=false;
    char flag, direction='r';

    try{
        if(argc >= 3){

            startPos = atoi(argv[1]);
            if(startPos < 0 || startPos > SIZE-1){
                throw 4;
            }
            fileName = argv[2];

            //These blocks handle the flags.
            //I've never done flags like this before, so this system can probably be revised to be much better.
            if(argc >= 4 && argv[3][0] == '-'){
                flagLen = strlen(argv[3]);
                for(int i = 1; i < flagLen; i++){
                    switch(argv[3][i]){
                        case 'u': usage = true;
                            break;
                        case 'p': printAddr = true;
                            break;
                        case 'l': direction = 'l';
                            break;
                        case 'r': direction = 'r';
                            break;
                        default: throw 1;
                    }
                }
            }
            if(printAddr){
                if(argc == 5){
                    flagLen = strlen(argv[4]);
                    for(int i = 0; i < flagLen; i++){
                        switch(argv[4][i]){
                            case 'f': printF = true;
                                break;
                            case 's': printS = true;
                                break;
                            case 'c': printC = true;
                                break;
                            default: throw 1;
                        }
                    }
                }
                else{
                    throw 1;
                }
            }

            inFile.open(fileName);
            if(inFile.is_open()){
                while(!inFile.eof()){
                    getline(inFile, temp, '\n');
                    if(temp == ""){
                        throw 3;
                    }
                    addresses.push_back(std::stoi(temp));
                    if(addresses[addresses.size()-1] < 0 || addresses[addresses.size()-1] > SIZE-1){
                        throw 5;
                    }
                }
                inFile.close();
            }
            else{
                throw 2;
            }
            
            FCFS(addresses, addresses.size(), startPos, printF);
            SCAN(addresses, addresses.size(), startPos, printS, direction);
            CSCAN(addresses, addresses.size(), startPos, printC, direction);

            if(usage){
                PrintUsage();
            }
        }
        else if (argc == 2 && strcmp(argv[1], "-u") == 0){
            PrintUsage();
        }
        else{
            throw 1;
        }

    }
    catch(int e){
        std::cout << BIN_NAME << ": ";
        switch(e){
            case 1: 
                std::cout << "incorrect arguments provided!" << std::endl;
                PrintUsage();
                break;
            case 2: 
                std::cout << "provided file could not be opened!" << std::endl;
                break;
            case 3: 
                std::cout << "whitespace at end of provided file, or file empty!" << std::endl;
                break;
            case 4:
                std::cout << "invalid starting position!" << std::endl;
                std::cout << "Valid range is " << RANGE << std::endl;
                break;
            case 5:
                std::cout << "invalid address request!" << std::endl;
                std::cout << "Valid Range is " << RANGE << std::endl;
                break;
        }
        std::cout << "Exiting." << std::endl;
        return e;
    }
    return 0;
}

void PrintUsage(){
    //I know how bad this is.
    std::cout << "Usage: " << BIN_NAME << " <starting position> <file containing addresses> <flags>" << std::endl << std::endl;
    std::cout << "-Starting position must be " << RANGE << std::endl;
    std::cout << "-File contents must be separated by end-lines with no whitespace after the final entry." << std::endl << std::endl;
    std::cout << "FLAGS:" << std::endl;
    std::cout << '\t' << "-u: Print usage. This may either be included in flags or used alone." << std::endl;
    std::cout << '\t' << "-p <algorithm(s)>: Prints the request order of the specified algorithm. Recommended to pipe to a file if there are many requests." << std::endl;
    std::cout << "\t\t" << "f: FCFS" << std::endl;
    std::cout << "\t\t" << "s: SCAN" << std::endl;
    std::cout << "\t\t" << "c: CSCAN" << std::endl;
    std::cout << '\t' << "-l: Start disk spinning left." << std::endl;
    std::cout << '\t' << "-r: Start disk spinning right." << std::endl;
    std::cout << std::endl;
    std::cout << "Example: " << BIN_NAME << " 100 input -pru fc" << std::endl << std::endl;
    std::cout << "Use " << BIN_NAME << " -u to only print this usage message." << std::endl;
}

void PrintVector(const std::vector<int> &addr, const int &size){
    for(int i=0; i<size; i++){
        std::cout << addr[i] << std::endl;
    }
}

void RunSchedule(const std::vector<int> &addr, const int &size, const int &start){
    int movesDist=0, prevAddr=start;

    for(int i=0; i<size; i++){
        if(addr[i] != prevAddr){
            movesDist += abs(addr[i]-prevAddr);
            prevAddr = addr[i];
        }
    }

    std::cout << movesDist << " movement length" << std::endl;
}

void FCFS(const std::vector<int> &addr, const int &size, const int &start, const bool &print){
    std::cout << "FCFS: ";
    RunSchedule(addr, size, start);
    if(print){
        PrintVector(addr, addr.size());
    }
}

void SCAN(const std::vector<int> &addr, const int &size, const int &start, const bool &print, const char &dir){
    std::vector<int> left, right, scanAddr;
    int leftSize, rightSize;

    for(int i = 0; i < size; i++) {
        if(addr[i] < start)
            left.push_back(addr[i]);
        if(addr[i] > start)
            right.push_back(addr[i]);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    leftSize = left.size();
    rightSize = right.size();

    if(dir == 'r'){
        for(int i = 0; i < rightSize; i++){
            scanAddr.push_back(right[i]);
        }
        for(int i = leftSize-1; i >= 0; i--){
            scanAddr.push_back(left[i]);
        }
    }
    else{
        
        for(int i = leftSize-1; i >= 0; i--){
            scanAddr.push_back(left[i]);
        }
        for(int i = 0; i < rightSize; i++){
            scanAddr.push_back(right[i]);
        }
    }

    std::cout << "SCAN: ";
    RunSchedule(scanAddr, size, start);

    if(print){
        PrintVector(scanAddr, scanAddr.size());
    }
}

void CSCAN(const std::vector<int> &addr, const int &size, const int &start, const bool &print, const char &dir){
    std::vector<int> left, right, scanAddr;
    int leftSize, rightSize;

    for(int i = 0; i < size; i++) {
        if(addr[i] < start)
            left.push_back(addr[i]);
        if(addr[i] > start)
            right.push_back(addr[i]);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    leftSize = left.size();
    rightSize = right.size();

    if(dir == 'r'){
        for(int i = 0; i < rightSize; i++){
            scanAddr.push_back(right[i]);
        }
        for(int i = 0; i < leftSize; i++){
            scanAddr.push_back(left[i]);
        }
    }
    else{
        for(int i = leftSize-1; i >= 0; i--){
            scanAddr.push_back(left[i]);
        }
        for(int i = rightSize-1; i >= 0; i--){
            scanAddr.push_back(right[i]);
        }
    }

    std::cout << "CSCAN: ";
    RunSchedule(scanAddr, size, start);

    if(print){
        PrintVector(scanAddr, scanAddr.size());
    }
}