#include <gtest/gtest.h>
#include "H_Spells.h"
#include "H_SpellBook.h"

// ── Spell helpers ─────────────────────────────────────────────────────────────

static Spell makeFireball() {
    return Spell(
        "Fireball", "Evocation", "Damage",
        /*level*/ 3, "1 action", "150 ft", "V, S, M",
        "Instantaneous", "Dexterity", "A ball of fire explodes at a point."
    );
}

static Spell makeMagicMissile() {
    return Spell(
        "Magic Missile", "Evocation", "Damage",
        /*level*/ 1, "1 action", "120 ft", "V, S",
        "Instantaneous", "None", "Unerring bolts of force strike the target."
    );
}

static Spell makeMageHand() {
    return Spell(
        "Mage Hand", "Conjuration", "Utility",
        /*level*/ 0, "1 action", "30 ft", "V, S",
        "1 minute", "None", "A spectral floating hand appears."
    );
}

// ── Spell: default constructor ─────────────────────────────────────────────────

TEST(SpellTest, DefaultConstructorEmptyStrings) {
    Spell s;
    EXPECT_EQ(s.getSpellName(),        "");
    EXPECT_EQ(s.getSpellType(),        "");
    EXPECT_EQ(s.getSpellEffect(),      "");
    EXPECT_EQ(s.getSpellTime(),        "");
    EXPECT_EQ(s.getSpellRange(),       "");
    EXPECT_EQ(s.getSpellComponents(),  "");
    EXPECT_EQ(s.getSpellDuration(),    "");
    EXPECT_EQ(s.getSpellSavingThrow(), "");
    EXPECT_EQ(s.getSpellDescription(), "");
}

TEST(SpellTest, DefaultConstructorLevelIsZero) {
    Spell s;
    EXPECT_EQ(s.getSpellLevel(), 0);
}

// ── Spell: parametrized constructor ───────────────────────────────────────────

TEST(SpellTest, ParametrizedConstructorSetsAllStringFields) {
    Spell s = makeFireball();
    EXPECT_EQ(s.getSpellName(),        "Fireball");
    EXPECT_EQ(s.getSpellType(),        "Evocation");
    EXPECT_EQ(s.getSpellEffect(),      "Damage");
    EXPECT_EQ(s.getSpellTime(),        "1 action");
    EXPECT_EQ(s.getSpellRange(),       "150 ft");
    EXPECT_EQ(s.getSpellComponents(),  "V, S, M");
    EXPECT_EQ(s.getSpellDuration(),    "Instantaneous");
    EXPECT_EQ(s.getSpellSavingThrow(), "Dexterity");
    EXPECT_EQ(s.getSpellDescription(), "A ball of fire explodes at a point.");
}

TEST(SpellTest, ParametrizedConstructorSetsLevel) {
    EXPECT_EQ(makeFireball().getSpellLevel(),      3);
    EXPECT_EQ(makeMagicMissile().getSpellLevel(),  1);
}

TEST(SpellTest, CantripLevelIsZero) {
    EXPECT_EQ(makeMageHand().getSpellLevel(), 0);
}

// ── Spell: setters ────────────────────────────────────────────────────────────

TEST(SpellTest, SetSpellNameUpdatesName) {
    Spell s;
    s.setSpellName("Cure Wounds");
    EXPECT_EQ(s.getSpellName(), "Cure Wounds");
}

TEST(SpellTest, SetSpellLevelUpdatesLevel) {
    Spell s;
    s.setSpellLevel(9);
    EXPECT_EQ(s.getSpellLevel(), 9);
}

TEST(SpellTest, SetAllFieldsViaSetters) {
    Spell s;
    s.setSpellName("Shield");
    s.setSpellType("Abjuration");
    s.setSpellEffect("Defense");
    s.setSpellLevel(1);
    s.setSpellTime("1 reaction");
    s.setSpellRange("Self");
    s.setSpellComponents("V, S");
    s.setSpellDuration("1 round");
    s.setSpellSavingThrow("None");
    s.setSpellDescription("An invisible barrier of force appears.");

    EXPECT_EQ(s.getSpellName(),        "Shield");
    EXPECT_EQ(s.getSpellType(),        "Abjuration");
    EXPECT_EQ(s.getSpellEffect(),      "Defense");
    EXPECT_EQ(s.getSpellLevel(),       1);
    EXPECT_EQ(s.getSpellTime(),        "1 reaction");
    EXPECT_EQ(s.getSpellRange(),       "Self");
    EXPECT_EQ(s.getSpellComponents(),  "V, S");
    EXPECT_EQ(s.getSpellDuration(),    "1 round");
    EXPECT_EQ(s.getSpellSavingThrow(), "None");
    EXPECT_EQ(s.getSpellDescription(), "An invisible barrier of force appears.");
}

// ── Spellbook: empty state ─────────────────────────────────────────────────────

TEST(SpellbookTest, StartsEmpty) {
    Spellbook sb;
    EXPECT_TRUE(sb.getAllSpells().empty());
}

TEST(SpellbookTest, GetSpellsByLevelOnEmptyBookReturnsEmpty) {
    Spellbook sb;
    EXPECT_TRUE(sb.getSpellsByLevel(1).empty());
}

// ── Spellbook: addSpell ────────────────────────────────────────────────────────

TEST(SpellbookTest, AddSpellIncreasesCount) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    EXPECT_EQ(sb.getAllSpells().size(), 1u);
}

TEST(SpellbookTest, AddMultipleSpellsAccumulates) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    sb.addSpell(makeMagicMissile());
    sb.addSpell(makeMageHand());
    EXPECT_EQ(sb.getAllSpells().size(), 3u);
}

TEST(SpellbookTest, AddedSpellNameIsPreserved) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    EXPECT_EQ(sb.getAllSpells()[0].getSpellName(), "Fireball");
}

// ── Spellbook: removeSpell ─────────────────────────────────────────────────────

TEST(SpellbookTest, RemoveSpellDecreasesCount) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    sb.addSpell(makeMagicMissile());
    sb.removeSpell("Fireball");
    EXPECT_EQ(sb.getAllSpells().size(), 1u);
}

TEST(SpellbookTest, RemoveSpellRemovesCorrectSpell) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    sb.addSpell(makeMagicMissile());
    sb.removeSpell("Fireball");
    EXPECT_EQ(sb.getAllSpells()[0].getSpellName(), "Magic Missile");
}

TEST(SpellbookTest, RemoveOnlyRemainingSpellLeavesBookEmpty) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    sb.removeSpell("Fireball");
    EXPECT_TRUE(sb.getAllSpells().empty());
}

TEST(SpellbookTest, RemoveNonExistentSpellDoesNotCrash) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    EXPECT_NO_FATAL_FAILURE(sb.removeSpell("Nonexistent Spell"));
    EXPECT_EQ(sb.getAllSpells().size(), 1u);  // unchanged
}

// ── Spellbook: getSpellsByLevel ────────────────────────────────────────────────

TEST(SpellbookTest, GetSpellsByLevelFiltersToCorrectLevel) {
    Spellbook sb;
    sb.addSpell(makeMageHand());      // level 0
    sb.addSpell(makeMagicMissile());  // level 1
    sb.addSpell(makeFireball());      // level 3

    auto level1 = sb.getSpellsByLevel(1);
    ASSERT_EQ(level1.size(), 1u);
    EXPECT_EQ(level1[0].getSpellName(), "Magic Missile");
}

TEST(SpellbookTest, GetSpellsByLevelReturnsCantrips) {
    Spellbook sb;
    sb.addSpell(makeMageHand());
    sb.addSpell(makeFireball());

    auto cantrips = sb.getSpellsByLevel(0);
    ASSERT_EQ(cantrips.size(), 1u);
    EXPECT_EQ(cantrips[0].getSpellName(), "Mage Hand");
}

TEST(SpellbookTest, GetSpellsByLevelWithNoMatchReturnsEmpty) {
    Spellbook sb;
    sb.addSpell(makeFireball());   // level 3
    EXPECT_TRUE(sb.getSpellsByLevel(9).empty());
}

TEST(SpellbookTest, GetSpellsByLevelReturnsMultipleMatchingSpells) {
    Spellbook sb;
    sb.addSpell(makeMagicMissile());  // level 1
    Spell shield("Shield", "Abjuration", "Defense", 1,
                 "1 reaction", "Self", "V, S", "1 round", "None", "Barrier of force.");
    sb.addSpell(shield);

    auto level1 = sb.getSpellsByLevel(1);
    EXPECT_EQ(level1.size(), 2u);
}

TEST(SpellbookTest, GetAllSpellsReturnsEveryAddedSpell) {
    Spellbook sb;
    sb.addSpell(makeFireball());
    sb.addSpell(makeMagicMissile());

    auto all = sb.getAllSpells();
    ASSERT_EQ(all.size(), 2u);
    EXPECT_EQ(all[0].getSpellName(), "Fireball");
    EXPECT_EQ(all[1].getSpellName(), "Magic Missile");
}
