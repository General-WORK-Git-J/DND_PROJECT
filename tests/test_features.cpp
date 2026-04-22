#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "H_CharacterFeatures.h"

TEST(CharacterFeaturesTest, StartsWithNoFeatsOrTraits) {
    CharacterFeatures features;
    EXPECT_TRUE(features.getFeats().empty());
    EXPECT_TRUE(features.getRacialTraits().empty());
}

TEST(CharacterFeaturesTest, CanAddAndRemoveFeat) {
    CharacterFeatures features;
    features.addFeat("Sharpshooter");

    ASSERT_EQ(features.getFeats().size(), 1u);
    EXPECT_EQ(features.getFeats()[0], "Sharpshooter");
    EXPECT_TRUE(features.removeFeat(1));
    EXPECT_TRUE(features.getFeats().empty());
}

TEST(CharacterFeaturesTest, CanAddAndRemoveRacialTrait) {
    CharacterFeatures features;
    features.addRacialTrait("Darkvision");

    ASSERT_EQ(features.getRacialTraits().size(), 1u);
    EXPECT_EQ(features.getRacialTraits()[0], "Darkvision");
    EXPECT_TRUE(features.removeRacialTrait(1));
    EXPECT_TRUE(features.getRacialTraits().empty());
}

TEST(CharacterFeaturesTest, SkillModifiersUseAbilityAndProficiency) {
    CharacterFeatures features;
    features.setSkillRank("Stealth", SkillRank::Proficient);
    features.setSkillRank("Perception", SkillRank::Expertise);

    EXPECT_EQ(features.getSkillModifier("Stealth",
                                        10, 16, 10, 10, 12, 10,
                                        3), 6);
    EXPECT_EQ(features.getSkillModifier("Perception",
                                        10, 16, 10, 10, 12, 10,
                                        3), 7);
}

TEST(CharacterFeaturesTest, SaveLoadPreservesFeatsTraitsAndSkills) {
    const char* path = "dnd_test_features.tmp";
    std::remove(path);

    {
        CharacterFeatures features;
        features.addFeat("War Caster");
        features.addRacialTrait("Fey Ancestry");
        features.setSkillRank("Arcana", SkillRank::Proficient);
        features.setSkillRank("Perception", SkillRank::Expertise);

        std::ofstream out(path);
        ASSERT_TRUE(out.is_open());
        features.save(out);
    }

    {
        CharacterFeatures features;
        std::ifstream in(path);
        ASSERT_TRUE(in.is_open());
        features.load(in);

        ASSERT_EQ(features.getFeats().size(), 1u);
        ASSERT_EQ(features.getRacialTraits().size(), 1u);
        EXPECT_EQ(features.getFeats()[0], "War Caster");
        EXPECT_EQ(features.getRacialTraits()[0], "Fey Ancestry");
        EXPECT_EQ(features.getSkillRank("Arcana"), SkillRank::Proficient);
        EXPECT_EQ(features.getSkillRank("Perception"), SkillRank::Expertise);
    }

    std::remove(path);
}
