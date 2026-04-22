#ifndef CHARACTER_FEATURES_H
#define CHARACTER_FEATURES_H

#include <fstream>
#include <string>
#include <vector>

enum class SkillRank {
    None = 0,
    Proficient = 1,
    Expertise = 2
};

struct SkillEntry {
    // Stores the skill's linked ability plus its current training level.
    std::string name;
    std::string ability;
    SkillRank rank;
};

struct SaveEntry {
    std::string ability; // "STR", "DEX", "CON", "INT", "WIS", "CHA"
    bool proficient;
};

class CharacterFeatures {
private:
    std::vector<std::string> feats;
    std::vector<std::string> racialTraits;
    // Fixed 5e skill list with editable proficiency/expertise state per skill.
    std::vector<SkillEntry> skills;

    std::vector<SaveEntry> savingThrows;
    SaveEntry* findSave(const std::string& ability);
    const SaveEntry* findSave(const std::string& ability) const;

    SkillEntry* findSkill(const std::string& skillName);
    const SkillEntry* findSkill(const std::string& skillName) const;

public:
    CharacterFeatures();

    void addFeat(const std::string& feat);
    bool removeFeat(int index);
    const std::vector<std::string>& getFeats() const;

    void addRacialTrait(const std::string& trait);
    bool removeRacialTrait(int index);
    const std::vector<std::string>& getRacialTraits() const;

    bool setSkillRank(const std::string& skillName, SkillRank rank);
    SkillRank getSkillRank(const std::string& skillName) const;
    const std::vector<SkillEntry>& getSkills() const;
    int getSkillModifier(const std::string& skillName,
                         int strength, int dexterity, int constitution,
                         int intelligence, int wisdom, int charisma,
                         int proficiencyBonus) const;

    bool setSaveProficiency(const std::string& ability, bool proficient);
    bool getSaveProficiency(const std::string& ability) const;
    int getSaveModifier(const std::string& ability,
                        int strength, int dexterity, int constitution,
                        int intelligence, int wisdom, int charisma,
                        int proficiencyBonus) const;

    const std::vector<SaveEntry>& getSavingThrows() const;
    void displaySaves(int strength, int dexterity, int constitution,
                      int intelligence, int wisdom, int charisma,
                      int proficiencyBonus) const;

    void displayFeats() const;
    void displayRacialTraits() const;
    void displaySkills(int strength, int dexterity, int constitution,
                       int intelligence, int wisdom, int charisma,
                       int proficiencyBonus) const;

    void save(std::ofstream& file) const;
    void load(std::ifstream& file);
};

#endif
