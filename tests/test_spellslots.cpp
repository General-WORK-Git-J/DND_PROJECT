#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include "H_SpellSlots.h"

TEST(SpellSlotsTest, UseSlotReturnsFalseWithNoSlotsSet) {
    SpellSlots ss;
    EXPECT_FALSE(ss.useSlot(1));
}

TEST(SpellSlotsTest, UseSlotReturnsTrueWhenSlotAvailable) {
    SpellSlots ss;
    ss.setSlots(1, 3);
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_EQ(ss.getCurrentSlots(1), 2);
    EXPECT_EQ(ss.getMaxSlots(1), 3);
}

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
    EXPECT_FALSE(ss.useSlot(1));
}

TEST(SpellSlotsTest, SlotsAtDifferentLevelsAreIndependent) {
    SpellSlots ss;
    ss.setSlots(1, 1);
    ss.setSlots(2, 2);

    ss.useSlot(1);
    EXPECT_FALSE(ss.useSlot(1));

    EXPECT_TRUE(ss.useSlot(2));
    EXPECT_TRUE(ss.useSlot(2));
    EXPECT_FALSE(ss.useSlot(2));
}

TEST(SpellSlotsTest, ResetRestoresCurrentSlotsToMax) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.useSlot(1);
    ss.useSlot(1);
    EXPECT_FALSE(ss.useSlot(1));

    ss.resetSlots();
    EXPECT_TRUE(ss.useSlot(1));
}

TEST(SpellSlotsTest, ResetRestoresMultipleLevels) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.setSlots(2, 1);
    ss.useSlot(1);
    ss.useSlot(1);
    ss.useSlot(2);

    ss.resetSlots();

    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(2));
}

TEST(SpellSlotsTest, SetSlotsOverwritesPreviousMax) {
    SpellSlots ss;
    ss.setSlots(1, 2);
    ss.setSlots(1, 4);
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_TRUE(ss.useSlot(1));
    EXPECT_FALSE(ss.useSlot(1));
}

TEST(SpellSlotsTest, CurrentSlotsCanBeEditedAndAreClampedToMax) {
    SpellSlots ss;
    ss.setSlots(3, 2);

    ss.setCurrentSlots(3, 1);
    EXPECT_EQ(ss.getCurrentSlots(3), 1);

    ss.setCurrentSlots(3, 5);
    EXPECT_EQ(ss.getCurrentSlots(3), 2);
}

TEST(SpellSlotsTest, SaveLoadRoundTripPreservesCurrentAndMaxSlots) {
    const char* path = "dnd_test_spellslots.tmp";
    std::remove(path);

    {
        SpellSlots ss;
        ss.setSlots(1, 4);
        ss.setCurrentSlots(1, 2);
        ss.setSlots(3, 2);
        ss.setCurrentSlots(3, 1);

        std::ofstream out(path);
        ASSERT_TRUE(out.is_open());
        ss.save(out);
    }

    {
        SpellSlots ss;
        std::ifstream in(path);
        ASSERT_TRUE(in.is_open());
        ss.load(in);

        EXPECT_EQ(ss.getMaxSlots(1), 4);
        EXPECT_EQ(ss.getCurrentSlots(1), 2);
        EXPECT_EQ(ss.getMaxSlots(3), 2);
        EXPECT_EQ(ss.getCurrentSlots(3), 1);
    }

    std::remove(path);
}
