/**
 * Highscore.h
 * Declares the Highscore class.
 */
#pragma once

class Highscore {
public:
    static void read();
    static void write();

    static void score(int score) {
        score_ = score;
    }
    static int score() {
        return score_;
    }
private:
    static int score_;
};