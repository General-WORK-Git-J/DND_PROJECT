#include <gtest/gtest.h>
#include <memory>
#include "H_Inventory.h"
#include "H_Weapon.h"
#include "H_Armor.h"
#include "H_Gear.h"

// Helpers to create concrete items (Item is abstract — must use a subclass)
static std::unique_ptr<Weapon> makeSword() {
    return std::make_unique<Weapon>(
        "Longsword", "A standard longsword", 3.0f,
        /*quantity*/ 1, /*value*/ 15, "Common", false,
        "1d8", "Slashing", "Martial", "Melee", "Versatile", "5 ft"
    );
}

static std::unique_ptr<Armor> makeLeatherArmor() {
    return std::make_unique<Armor>(
        "Leather Armor", "Light armor", 10.0f,
        /*quantity*/ 1, /*value*/ 10, "Common", false,
        /*armorType*/ "Light", /*baseAC*/ 11,
        /*maxDexBonus*/ -1, /*strRequirement*/ 0, /*stealthDisadvantage*/ false
    );
}

static std::unique_ptr<Gear> makeRope() {
    return std::make_unique<Gear>(
        "Rope", "50 ft of hempen rope", 10.0f,
        /*quantity*/ 1, /*value*/ 1, "Common", false
    );
}

// ── Initial state ─────────────────────────────────────────────────────────────

TEST(InventoryTest, StartsEmpty) {
    Inventory inv;
    EXPECT_EQ(inv.size(), 0);
}

// ── addItem ───────────────────────────────────────────────────────────────────

TEST(InventoryTest, AddItemIncreasesSize) {
    Inventory inv;
    inv.addItem(makeSword());
    EXPECT_EQ(inv.size(), 1);
}

TEST(InventoryTest, AddMultipleItemsAccumulates) {
    Inventory inv;
    inv.addItem(makeSword());
    inv.addItem(makeLeatherArmor());
    inv.addItem(makeRope());
    EXPECT_EQ(inv.size(), 3);
}

TEST(InventoryTest, AddedItemNameIsPreserved) {
    Inventory inv;
    inv.addItem(makeSword());
    EXPECT_EQ(inv.getItem(0).getName(), "Longsword");
}

// ── getItem ───────────────────────────────────────────────────────────────────

TEST(InventoryTest, GetItemReturnsCorrectItemByIndex) {
    Inventory inv;
    inv.addItem(makeSword());
    inv.addItem(makeLeatherArmor());
    EXPECT_EQ(inv.getItem(0).getName(), "Longsword");
    EXPECT_EQ(inv.getItem(1).getName(), "Leather Armor");
}

// ── removeItem ────────────────────────────────────────────────────────────────

TEST(InventoryTest, RemoveItemDecreasesSize) {
    Inventory inv;
    inv.addItem(makeSword());
    inv.addItem(makeRope());
    inv.removeItem(0);
    EXPECT_EQ(inv.size(), 1);
}

TEST(InventoryTest, RemoveFirstItemShiftsRemaining) {
    Inventory inv;
    inv.addItem(makeSword());
    inv.addItem(makeRope());
    inv.removeItem(0); // remove Longsword
    EXPECT_EQ(inv.getItem(0).getName(), "Rope");
}

TEST(InventoryTest, RemoveLastItemLeavesInventoryEmpty) {
    Inventory inv;
    inv.addItem(makeSword());
    inv.removeItem(0);
    EXPECT_EQ(inv.size(), 0);
}

// ── polymorphic item tags ─────────────────────────────────────────────────────

TEST(InventoryTest, WeaponHasCorrectItemTag) {
    Inventory inv;
    inv.addItem(makeSword());
    EXPECT_EQ(inv.getItem(0).getItemTag(), "WEAPON");
}

TEST(InventoryTest, ArmorHasCorrectItemTag) {
    Inventory inv;
    inv.addItem(makeLeatherArmor());
    EXPECT_EQ(inv.getItem(0).getItemTag(), "ARMOR");
}

TEST(InventoryTest, GearHasCorrectItemTag) {
    Inventory inv;
    inv.addItem(makeRope());
    EXPECT_EQ(inv.getItem(0).getItemTag(), "GEAR");
}
