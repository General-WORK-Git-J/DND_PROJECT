#include <gtest/gtest.h>
#include "H_SpellSlots.h"

// ── setSlots / initial state ──────────────────────────────────────────────────

TEST(SpellSlotsTest, UseSlotReturnsFalseWithNoSlotsSet) {
    SpellSlots ss;
    // Level 1 was never configured — usedSlots[1] and maxSlots[1] both default
    // to 0 via map's default-insert, so useSlot should return false
    EXPECT_FALSE(ss.useSlot(1));
}

TEST(SpellSlotsTest, UseSlotReturnsTrueWhenSlotAvailable) {
    SpellSlots ss;
    ss.setSlots(1, 3);
    EXPECT_TRUE(ss.useSlot(1));
}

// ── using slots ───────────────────────────────────────────────────────────────

TEST(SpellSlotsTest, CanUseAllAvailableSlots) {
    SpellSlots ss;
    ss.setSlots(1, 3);
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
}

TEST(SpellSlotsTest, CannotUseSlotWhenExhausted) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.useSlot(1);
    ss.useSlot(1);
    EXPECT_FALSE(ss.useSlot(1)); // all slots spent
}

TEST(SpellSlotsTest, SlotsAtDifferentLevelsAreIndependent) {
    SpellSlots ss;
    ss.setSlots(1, 1);
    ss.setSlots(2, 2);

    // Exhaust level 1
    ss.useSlot(1);
    EXPECT_FALSE(ss.useSlot(1));

    // Level 2 should still be available
    EXPECT_TRUE(ss.useSlot(2));
    EXPECT_TRUE(ss.useSlot(2));
    EXPECT_FALSE(ss.useSlot(2));
}

// ── resetSlots ────────────────────────────────────────────────────────────────

TEST(SpellSlotsTest, ResetRestoresUsedSlotsToZero) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.useSlot(1);
    ss.useSlot(1);
    EXPECT_FALSE(ss.useSlot(1)); // exhausted

    ss.resetSlots();
    EXPECT_TRUE(ss.useSlot(1)); // available again after long rest
}

TEST(SpellSlotsTest, ResetRestoresMultipleLevels) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.setSlots(2, 1);
    ss.useSlot(1); ss.useSlot(1);
    ss.useSlot(2);

    ss.resetSlots();

    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(2));
}

// ── setSlots overwrites previous value ───────────────────────────────────────

TEST(SpellSlotsTest, SetSlotsOverwritesPreviousMax) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.setSlots(1, 4); // level up — more slots now
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_FALSE(ss.useSlot(1));
}
