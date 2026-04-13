#include <gtest/gtest.h>
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"

// ── Weapon helpers ────────────────────────────────────────────────────────────

static Weapon makeLongsword() {
    return Weapon(
        "Longsword", "A versatile blade", 3.0f,
        /*quantity*/ 1, /*value*/ 15, "Common", /*attunement*/ false,
        "1d8", "Slashing", "Martial", "Melee", "Versatile", "5 ft"
    );
}

// ── WeaponTest ────────────────────────────────────────────────────────────────

TEST(WeaponTest, TagIsWeapon) {
    EXPECT_EQ(makeLongsword().getItemTag(), "WEAPON");
}

TEST(WeaponTest, ConstructorSetsBaseItemFields) {
    Weapon w = makeLongsword();
    EXPECT_EQ(w.getName(),        "Longsword");
    EXPECT_EQ(w.getDescription(), "A versatile blade");
    EXPECT_FLOAT_EQ(w.getWeight(), 3.0f);
    EXPECT_EQ(w.getQuantity(), 1);
    EXPECT_EQ(w.getValue(),    15);
    EXPECT_EQ(w.getRarity(),   "Common");
    EXPECT_FALSE(w.getRequiresAttunement());
}

TEST(WeaponTest, ConstructorSetsWeaponSpecificFields) {
    Weapon w = makeLongsword();
    EXPECT_EQ(w.getDamageDice(),     "1d8");
    EXPECT_EQ(w.getDamageType(),     "Slashing");
    EXPECT_EQ(w.getWeaponCategory(), "Martial");
    EXPECT_EQ(w.getWeaponType(),     "Melee");
    EXPECT_EQ(w.getProperties(),     "Versatile");
    EXPECT_EQ(w.getRange(),          "5 ft");
}

TEST(WeaponTest, DefaultConstructorHasSensibleDefaults) {
    Weapon w;
    EXPECT_EQ(w.getName(),           "");
    EXPECT_EQ(w.getDamageDice(),     "");
    EXPECT_EQ(w.getWeaponCategory(), "Simple");
    EXPECT_EQ(w.getWeaponType(),     "Melee");
    EXPECT_EQ(w.getProperties(),     "None");
    EXPECT_EQ(w.getRange(),          "5 ft");
}

TEST(WeaponTest, RangedWeaponFieldsStoredCorrectly) {
    Weapon w("Shortbow", "A light bow", 2.0f, 1, 25, "Common", false,
             "1d6", "Piercing", "Simple", "Ranged", "None", "80/320 ft");
    EXPECT_EQ(w.getWeaponType(), "Ranged");
    EXPECT_EQ(w.getRange(),      "80/320 ft");
}

TEST(WeaponTest, AttunementAndRarityStoredCorrectly) {
    Weapon w("Flame Tongue", "A magical sword", 3.0f, 1, 500, "Rare", /*attunement*/ true,
             "2d6", "Fire", "Martial", "Melee", "None", "5 ft");
    EXPECT_TRUE(w.getRequiresAttunement());
    EXPECT_EQ(w.getRarity(), "Rare");
}

TEST(WeaponTest, SetQuantityUpdatesQuantity) {
    Weapon w = makeLongsword();
    w.setQuantity(3);
    EXPECT_EQ(w.getQuantity(), 3);
}

// ── ArmorTest ─────────────────────────────────────────────────────────────────

static Armor makeLeatherArmor() {
    return Armor(
        "Leather Armor", "Light armor made from cured leather", 10.0f,
        /*quantity*/ 1, /*value*/ 10, "Common", /*attunement*/ false,
        "Light", /*baseAC*/ 11, /*maxDexBonus*/ -1, /*strReq*/ 0, /*stealthDisadv*/ false
    );
}

static Armor makePlateArmor() {
    return Armor(
        "Plate Armor", "Full heavy-plate armor", 65.0f,
        /*quantity*/ 1, /*value*/ 1500, "Common", false,
        "Heavy", /*baseAC*/ 18, /*maxDexBonus*/ 0, /*strReq*/ 15, /*stealthDisadv*/ true
    );
}

TEST(ArmorTest, TagIsArmor) {
    EXPECT_EQ(makeLeatherArmor().getItemTag(), "ARMOR");
}

TEST(ArmorTest, ConstructorSetsBaseItemFields) {
    Armor a = makeLeatherArmor();
    EXPECT_EQ(a.getName(),        "Leather Armor");
    EXPECT_EQ(a.getDescription(), "Light armor made from cured leather");
    EXPECT_FLOAT_EQ(a.getWeight(), 10.0f);
    EXPECT_EQ(a.getQuantity(), 1);
    EXPECT_EQ(a.getValue(),   10);
    EXPECT_EQ(a.getRarity(),  "Common");
    EXPECT_FALSE(a.getRequiresAttunement());
}

TEST(ArmorTest, ConstructorSetsArmorSpecificFields) {
    Armor a = makeLeatherArmor();
    EXPECT_EQ(a.getArmorType(),          "Light");
    EXPECT_EQ(a.getBaseAC(),             11);
    EXPECT_EQ(a.getMaxDexBonus(),        -1);   // -1 = no cap
    EXPECT_EQ(a.getStrRequirement(),      0);
    EXPECT_FALSE(a.getStealthDisadvantage());
}

TEST(ArmorTest, HeavyArmorFieldsStoredCorrectly) {
    Armor a = makePlateArmor();
    EXPECT_EQ(a.getArmorType(),     "Heavy");
    EXPECT_EQ(a.getBaseAC(),        18);
    EXPECT_EQ(a.getMaxDexBonus(),   0);
    EXPECT_EQ(a.getStrRequirement(), 15);
    EXPECT_TRUE(a.getStealthDisadvantage());
}

TEST(ArmorTest, DefaultConstructorHasSensibleDefaults) {
    Armor a;
    EXPECT_EQ(a.getName(),          "");
    EXPECT_EQ(a.getArmorType(),     "Light");
    EXPECT_EQ(a.getBaseAC(),        10);
    EXPECT_EQ(a.getMaxDexBonus(),   -1);
    EXPECT_EQ(a.getStrRequirement(), 0);
    EXPECT_FALSE(a.getStealthDisadvantage());
}

TEST(ArmorTest, ShieldArmorType) {
    Armor a("Shield", "A wooden shield", 6.0f, 1, 10, "Common", false,
            "Shield", /*baseAC*/ 2, /*maxDexBonus*/ -1, /*strReq*/ 0, false);
    EXPECT_EQ(a.getArmorType(), "Shield");
    EXPECT_EQ(a.getBaseAC(),    2);
}

// ── GearTest ──────────────────────────────────────────────────────────────────

TEST(GearTest, TagIsGear) {
    Gear g("Rope", "50 ft of hempen rope", 10.0f, 1, 1, "Common", false);
    EXPECT_EQ(g.getItemTag(), "GEAR");
}

TEST(GearTest, ConstructorSetsBaseItemFields) {
    Gear g("Rope", "50 ft of hempen rope", 10.0f, 2, 1, "Common", false);
    EXPECT_EQ(g.getName(),        "Rope");
    EXPECT_EQ(g.getDescription(), "50 ft of hempen rope");
    EXPECT_FLOAT_EQ(g.getWeight(), 10.0f);
    EXPECT_EQ(g.getQuantity(), 2);
    EXPECT_EQ(g.getValue(),    1);
    EXPECT_EQ(g.getRarity(),   "Common");
    EXPECT_FALSE(g.getRequiresAttunement());
}

TEST(GearTest, SetQuantityUpdatesQuantity) {
    Gear g("Torch", "A simple torch", 1.0f, 1, 0, "Common", false);
    g.setQuantity(5);
    EXPECT_EQ(g.getQuantity(), 5);
}

TEST(GearTest, UncommonGearRarityStoredCorrectly) {
    Gear g("Sending Stones", "A pair of linked stones", 0.5f, 1, 100, "Uncommon", true);
    EXPECT_EQ(g.getRarity(), "Uncommon");
    EXPECT_TRUE(g.getRequiresAttunement());
}
