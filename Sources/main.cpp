#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

#include "../Headers/Hash.h"

using namespace std::chrono;

string kurkEilute(size_t ilgis){
    auto randchar = []() -> char
    {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(ilgis,0);
    std::generate_n( str.begin(), ilgis, randchar );
    return str;
}

string kurkOCEilute(string pirma){
    string s = kurkEilute(1);
    pirma[0] = s[0];
    return pirma;
}

bool patikrinkIlgi(size_t ilgis){
    string s1 = kurkEilute(ilgis);
    string s2 = kurkEilute(ilgis);
    string h1 = racerHash(s1);
    string h2 = racerHash(s2);
    if (s1.length() == s2.length()){
        std::cout << "When hashing messages with the length of " << ilgis << " the length of hashes match." << std::endl;
        return true;
    } else {
        std::cout << "When hashing messages with the length of " << ilgis << " the length of hashes does not match. Not running further tests."
                  << std::endl;
        return false;
    }
}

void konstitututita() {
    long pilnasLaikas = 0;
    std::ifstream in("konstitucija.txt");
    std::string str;
    std::vector<string> kons{};

    int a = 0;
    while (std::getline(in, str)) {
        kons.push_back(str);
    }

    for (int i = 0; i < 1000; i++) {
        auto start = high_resolution_clock::now();
        for (string s : kons) {
            racerHash(str);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        pilnasLaikas += duration.count();
    }

    double time =  pilnasLaikas * 1.0 / 1000000000.0;
    std::cout << "The average time to hash Kontitucija: " << time  << " s" << std::endl;
}





int main() {

    srand(time(0));

    if (!patikrinkIlgi(1)){
        return -1;
    }
    if (!patikrinkIlgi(100000)){
        return -1;
    }

    konstitututita();

    return 0;
}