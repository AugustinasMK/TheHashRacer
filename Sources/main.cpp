#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <bitset>
#include <array>
#include <memory>
#include <cstdio>
#include <stdexcept>

using namespace std::chrono;
using std::string;

std::string exec(const string& cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

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
    pirma[0] = pirma[1];
    return pirma;
}

bool patikrinkIlgi(size_t ilgis, const string& path){
    string s1 = kurkEilute(ilgis);
    string s2 = kurkEilute(ilgis);
    string h1 = exec(path + " " + s1);
    string h2 = exec(path + " " + s2);;
    if (s1.length() == s2.length()){
        std::cout << "When hashing messages with the length of " << ilgis << " the length of hashes match." << std::endl;
        return true;
    } else {
        std::cout << "When hashing messages with the length of " << ilgis << " the length of hashes does not match. Not running further tests."
                  << std::endl;
        return false;
    }
}

void konstitututita(const string& path) {
    long pilnasLaikas = 0;
    std::ifstream in("../konstitucija.txt");
    std::string str;
    std::vector<string> kons{};

    while (std::getline(in, str)) {
        string p = path + " \"" + str + "\"";
        kons.push_back(p);
    }

    std::cout << "Running konstitucija test:" << std::endl;
    for (int i = 0; i < 1; i++) {
        auto start = high_resolution_clock::now();
        for (const string& s : kons) {
            std::shared_ptr<FILE> pipe(popen(s.c_str(), "r"), pclose);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        pilnasLaikas += duration.count();
    }

    double time =  pilnasLaikas * 1.0 / 1000000.0;
    std::cout << "The average time to hash Kontitucija: " << time  << " s" << std::endl;
}

void eilutes(int iterations, const string& path){
    std::cout << "Starting words test." << std::endl;
    int sutapimai = 0;
    for (int i = 0; i < iterations; i++){
        string s1 = kurkEilute(1000);
        string s2 = kurkEilute(1000);
        string p1 = path + " \"" + s1 + "\"";
        string p2 = path + " \"" + s2 + "\"";
        if (s1 != s2) {
            string h1 = exec(p1);
            string h2 = exec(p2);
            if (h1 == h2) {
                sutapimai++;
            }
        }
        if (i % (iterations / 10) == 0) {
            std::cout << i * 100 / iterations << "% ";
        }
    }
    std::cout << std::endl;
    std::cout << "During the generation of " << iterations << " of not equal random pairs of strings we found "
              << sutapimai << " pairs that have the same hash." << std::endl;
}

void raides(int iterations, const string& path){
    std::cout << "Starting bitwise test." << std::endl;
    int max = -100;
    string max1;
    string max2;

    int min = 150;
    string min1;
    string min2;

    int bitcount = 0;
    int sum = 0;

    for (size_t i = 0; i < iterations; i++){
        int t = 0;
        string s1 = kurkEilute(1000);
        string s2 = kurkOCEilute(s1);
        string p1 = path + " \"" + s1 + "\"";
        string p2 = path + " \"" + s2 + "\"";
        string h1 = exec(p1);
        string h2 = exec(p2);
        string b1;
        string b2;
        for (char c : h1){
            b1 += std::bitset<8>(c).to_string();
        }
        for (char c : h2){
            b2 += std::bitset<8>(c).to_string();
        }
        bitcount = b1.length();

        for (size_t j = 0; j < b1.length(); j++){
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
        if (i % (iterations / 10) == 0) {
            std::cout << i * 100 / iterations << "% ";
        }
    }
    std::cout << std::endl;
    std::cout << "During the generation of " << iterations << " of not equal random pairs of strings that differ by one character we found that:" << std::endl;
    std::cout << "The maximum bitwise difference is " << max * 100 / bitcount << "%." << std::endl;
    std::cout << "The minimum bitwise difference is " << min * 100 / bitcount << "%." << std::endl;
    std::cout << "The average bitwise difference is " << (sum * 100 / bitcount) / iterations << "%." << std::endl;
}

int main(int argc,char* argv[]) {

    if (argc == 1) {
        std::cout << "Please input the path to you hasher executable.";
        return -1;
    }

    string path = argv[1];

    srand(time(0));

    if (!patikrinkIlgi(1, path)){
        return -1;
    }
    if (!patikrinkIlgi(1000, path)){
        return -1;
    }

    konstitututita(path);
    eilutes(10000, path);
    raides(10000, path);

    return 0;
}