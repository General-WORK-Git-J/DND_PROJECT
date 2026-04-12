#include <gtest/gtest.h>
#include "H_Wallet.h"

// ── Initial state ─────────────────────────────────────────────────────────────

TEST(WalletTest, DefaultConstructorZerosAllCurrencies) {
    Wallet w;
    EXPECT_EQ(w.getCopper(),   0);
    EXPECT_EQ(w.getSilver(),   0);
    EXPECT_EQ(w.getElectrum(), 0);
    EXPECT_EQ(w.getGold(),     0);
    EXPECT_EQ(w.getPlatinum(), 0);
}

// ── Positive adjustments ──────────────────────────────────────────────────────

TEST(WalletTest, AdjustCopperPositive) {
    Wallet w;
    w.adjustCopper(50);
    EXPECT_EQ(w.getCopper(), 50);
}

TEST(WalletTest, AdjustSilverPositive) {
    Wallet w;
    w.adjustSilver(20);
    EXPECT_EQ(w.getSilver(), 20);
}

TEST(WalletTest, AdjustElectrumPositive) {
    Wallet w;
    w.adjustElectrum(10);
    EXPECT_EQ(w.getElectrum(), 10);
}

TEST(WalletTest, AdjustGoldPositive) {
    Wallet w;
    w.adjustGold(100);
    EXPECT_EQ(w.getGold(), 100);
}

TEST(WalletTest, AdjustPlatinumPositive) {
    Wallet w;
    w.adjustPlatinum(5);
    EXPECT_EQ(w.getPlatinum(), 5);
}

// ── Negative adjustments (spending currency) ──────────────────────────────────

TEST(WalletTest, AdjustGoldNegativeReducesBalance) {
    Wallet w;
    w.adjustGold(50);
    w.adjustGold(-30);
    EXPECT_EQ(w.getGold(), 20);
}

TEST(WalletTest, AdjustCopperNegativeReducesBalance) {
    Wallet w;
    w.adjustCopper(100);
    w.adjustCopper(-40);
    EXPECT_EQ(w.getCopper(), 60);
}

// ── Multiple adjustments accumulate ──────────────────────────────────────────

TEST(WalletTest, MultipleAdjustmentsAccumulate) {
    Wallet w;
    w.adjustGold(10);
    w.adjustGold(5);
    w.adjustGold(3);
    EXPECT_EQ(w.getGold(), 18);
}

// ── Currencies are independent ────────────────────────────────────────────────

TEST(WalletTest, AdjustingOneTypeDoesNotAffectOthers) {
    Wallet w;
    w.adjustGold(100);
    EXPECT_EQ(w.getCopper(),   0);
    EXPECT_EQ(w.getSilver(),   0);
    EXPECT_EQ(w.getElectrum(), 0);
    EXPECT_EQ(w.getPlatinum(), 0);
}
