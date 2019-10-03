#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <bitset>

#include "../Headers/Hash.h"

using namespace std::chrono;

string kurkEilute(size_t ilgis){
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_shuffle(str.begin(), str.end());
    return str.substr(0, ilgis);
}

string kurkOCEilute(string pirma){
    pirma[0] = pirma[1];
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
    std::ifstream in("../konstitucija.txt");
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

void eilutes(int iterations){

    srand(time(0));

    int sutapimai = 0;
    for (int i = 0; i < iterations; i++){
        string s1 = kurkEilute(1000);
        string s2 = kurkEilute(1000);
        if (s1 != s2) {
            string h1 = racerHash(s1);
            string h2 = racerHash(s2);
            if (h1 == h2) {
                sutapimai++;
            }
        }
    }
    std::cout << "During the generation of " << iterations << " of not equal random pairs of strings we found "
              << sutapimai << " pairs that have the same hash." << std::endl;
}

void raides(int iterations){
    int max = -100;
    string max1;
    string max2;

    int min = 150;
    string min1;
    string min2;

    int bitcount;
    int sum = 0;

    for (int i = 0; i < iterations; i++){
        int t = 0;
        string s1 = kurkEilute(1000);
        string s2 = kurkEilute(1000);
        string h1 = racerHash(s1);
        string h2 = racerHash(s2);
        string b1 = "";
        string b2 = "";
        for (char c : h1){
            b1 += std::bitset<8>(c).to_string();
        }
        for (char c : h2){
            b2 += std::bitset<8>(c).to_string();
        }
        bitcount = b1.length();

        for (int j = 0; j < b1.length(); j++){
            if (b1[j] != b2[j]) {
                t++;
            }
        }
        if (t > max) {
            max = t;
            max1 = s1;
            max2 = s2;
        }
        if (t < min) {
            min = t;
            min1 = s1;
            min2 = s2;
        }
        sum += t;
    }
    std::cout << "During the generation of " << iterations << " of not equal random pairs of strings that differ by one character we found that:" << std::endl;
    std::cout << "The maximum bitwise difference is " << max * 100 / bitcount << "%." << std::endl;
    std::cout << "The minimum bitwise difference is " << min * 100 / bitcount << "%." << std::endl;
    std::cout << "The average bitwise diffference is " << (sum * 100 / bitcount) / iterations << "%." << std::endl;
}

int main() {

    if (!patikrinkIlgi(1)){
        return -1;
    }
    if (!patikrinkIlgi(100000)){
        return -1;
    }

    konstitututita();
    eilutes(1000000);
    raides(100000);

    return 0;
}