/**
 * Highscore.h
 * Defines the Highscore class.
 */
#include "Highscore.h"
#include "fileutil.h"
#include <fstream>

using namespace std;

int Highscore::score_ = 0;

void Highscore::read() {
    if (file_exists("score.dat")) {
        ifstream istream = ifstream("score.dat", std::ios::in | std::ios::binary);

        istream >> score_;
        istream.close();
    }
}

void Highscore::write() {

    ofstream istream = ofstream("score.dat", std::ios::out | std::ios::binary);

    istream << score_;
    istream.close();
}