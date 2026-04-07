#ifndef H_WALLET_H
#define H_WALLET_H

#include <fstream>

class Wallet {
private:
    int copper;
    int silver;
    int electrum;
    int gold;
    int platinum;

public:
    Wallet();

    // Getters
    int getCopper() const;
    int getSilver() const;
    int getElectrum() const;
    int getGold() const;
    int getPlatinum() const;

    // Add/subtract currency (negative values reduce)
    void adjustCopper(int amount);
    void adjustSilver(int amount);
    void adjustElectrum(int amount);
    void adjustGold(int amount);
    void adjustPlatinum(int amount);

    void display() const;
    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif
