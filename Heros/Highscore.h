/**
 * Highscore.h
 * Declares the Highscore class.
 */
#pragma once

// Manages the highscore
class Highscore {
public:
    // Reads the highscore from the file
    static void read();

    // Writes the highscore to the file
    static void write();

    // Sets the highscore
    static void score(int score) {
        score_ = score;
    }

    // Gets the highscore
    static int score() {
        return score_;
    }
private:
    static int score_;
};