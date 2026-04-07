#include "H_Wallet.h"
#include <iostream>

Wallet::Wallet() : copper(0), silver(0), electrum(0), gold(0), platinum(0) {}

int Wallet::getCopper() const { return copper; }
int Wallet::getSilver() const { return silver; }
int Wallet::getElectrum() const { return electrum; }
int Wallet::getGold() const { return gold; }
int Wallet::getPlatinum() const { return platinum; }

void Wallet::adjustCopper(int amount)   { copper   += amount; }
void Wallet::adjustSilver(int amount)   { silver   += amount; }
void Wallet::adjustElectrum(int amount) { electrum += amount; }
void Wallet::adjustGold(int amount)     { gold     += amount; }
void Wallet::adjustPlatinum(int amount) { platinum += amount; }

void Wallet::display() const {
    std::cout << "  PP: " << platinum
              << "  GP: " << gold
              << "  EP: " << electrum
              << "  SP: " << silver
              << "  CP: " << copper << std::endl;
}

void Wallet::save(std::ofstream& file) const {
    file << copper << " " << silver << " " << electrum << " " << gold << " " << platinum << "\n";
}

void Wallet::load(std::ifstream& file) {
    file >> copper >> silver >> electrum >> gold >> platinum;
    file.ignore();
}
