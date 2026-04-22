#include "H_CharacterFeatures.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

namespace {
// Normalizes text for case-insensitive skill lookups.
std::string toLowerCopy(const std::string& value)
{
    std::string result = value;
    for (char& c : result)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

// Standard 5e ability modifier formula.
int abilityModifier(int score)
{
    return (score / 2) - 5;
}

// Maps a skill's linked ability code to the character's matching ability score.
int scoreForAbility(const std::string& ability,
                    int strength, int dexterity, int constitution,
                    int intelligence, int wisdom, int charisma)
{
    if (ability == "STR") return strength;
    if (ability == "DEX") return dexterity;
    if (ability == "CON") return constitution;
    if (ability == "INT") return intelligence;
    if (ability == "WIS") return wisdom;
    return charisma;
}
}

CharacterFeatures::CharacterFeatures()
    : skills({
        // Initialize the standard 5e skill list with no proficiencies selected yet.
        {"Acrobatics", "DEX", SkillRank::None},
        {"Animal Handling", "WIS", SkillRank::None},
        {"Arcana", "INT", SkillRank::None},
        {"Athletics", "STR", SkillRank::None},
        {"Deception", "CHA", SkillRank::None},
        {"History", "INT", SkillRank::None},
        {"Insight", "WIS", SkillRank::None},
        {"Intimidation", "CHA", SkillRank::None},
        {"Investigation", "INT", SkillRank::None},
        {"Medicine", "WIS", SkillRank::None},
        {"Nature", "INT", SkillRank::None},
        {"Perception", "WIS", SkillRank::None},
        {"Performance", "CHA", SkillRank::None},
        {"Persuasion", "CHA", SkillRank::None},
        {"Religion", "INT", SkillRank::None},
        {"Sleight of Hand", "DEX", SkillRank::None},
        {"Stealth", "DEX", SkillRank::None},
        {"Survival", "WIS", SkillRank::None}
    })
{
}

SkillEntry* CharacterFeatures::findSkill(const std::string& skillName)
{
    const std::string target = toLowerCopy(skillName);
    for (auto& skill : skills)
    {
        if (toLowerCopy(skill.name) == target)
        {
            return &skill;
        }
    }
    return nullptr;
}

const SkillEntry* CharacterFeatures::findSkill(const std::string& skillName) const
{
    const std::string target = toLowerCopy(skillName);
    for (const auto& skill : skills)
    {
        if (toLowerCopy(skill.name) == target)
        {
            return &skill;
        }
    }
    return nullptr;
}

void CharacterFeatures::addFeat(const std::string& feat)
{
    if (!feat.empty())
    {
        feats.push_back(feat);
    }
}

bool CharacterFeatures::removeFeat(int index)
{
    if (index < 1 || index > static_cast<int>(feats.size()))
    {
        return false;
    }

    feats.erase(feats.begin() + index - 1);
    return true;
}

const std::vector<std::string>& CharacterFeatures::getFeats() const
{
    return feats;
}

void CharacterFeatures::addRacialTrait(const std::string& trait)
{
    if (!trait.empty())
    {
        racialTraits.push_back(trait);
    }
}

bool CharacterFeatures::removeRacialTrait(int index)
{
    if (index < 1 || index > static_cast<int>(racialTraits.size()))
    {
        return false;
    }

    racialTraits.erase(racialTraits.begin() + index - 1);
    return true;
}

const std::vector<std::string>& CharacterFeatures::getRacialTraits() const
{
    return racialTraits;
}

bool CharacterFeatures::setSkillRank(const std::string& skillName, SkillRank rank)
{
    SkillEntry* skill = findSkill(skillName);
    if (skill == nullptr)
    {
        return false;
    }

    skill->rank = rank;
    return true;
}

SkillRank CharacterFeatures::getSkillRank(const std::string& skillName) const
{
    const SkillEntry* skill = findSkill(skillName);
    return (skill != nullptr) ? skill->rank : SkillRank::None;
}

const std::vector<SkillEntry>& CharacterFeatures::getSkills() const
{
    return skills;
}

int CharacterFeatures::getSkillModifier(const std::string& skillName,
                                        int strength, int dexterity, int constitution,
                                        int intelligence, int wisdom, int charisma,
                                        int proficiencyBonus) const
{
    const SkillEntry* skill = findSkill(skillName);
    if (skill == nullptr)
    {
        return 0;
    }

    // Skill bonus = linked ability modifier + proficiency or expertise bonus.
    int modifier = abilityModifier(scoreForAbility(skill->ability,
                                                   strength, dexterity, constitution,
                                                   intelligence, wisdom, charisma));

    if (skill->rank == SkillRank::Proficient)
    {
        modifier += proficiencyBonus;
    }
    else if (skill->rank == SkillRank::Expertise)
    {
        modifier += proficiencyBonus * 2;
    }

    return modifier;
}

void CharacterFeatures::displayFeats() const
{
    if (feats.empty())
    {
        std::cout << "No feats recorded.\n";
        return;
    }

    for (size_t i = 0; i < feats.size(); i++)
    {
        std::cout << i + 1 << ". " << feats[i] << "\n";
    }
}

void CharacterFeatures::displayRacialTraits() const
{
    if (racialTraits.empty())
    {
        std::cout << "No racial traits recorded.\n";
        return;
    }

    for (size_t i = 0; i < racialTraits.size(); i++)
    {
        std::cout << i + 1 << ". " << racialTraits[i] << "\n";
    }
}

void CharacterFeatures::displaySkills(int strength, int dexterity, int constitution,
                                      int intelligence, int wisdom, int charisma,
                                      int proficiencyBonus) const
{
    for (size_t i = 0; i < skills.size(); i++)
    {
        const SkillEntry& skill = skills[i];
        const int modifier = getSkillModifier(skill.name,
                                              strength, dexterity, constitution,
                                              intelligence, wisdom, charisma,
                                              proficiencyBonus);
        const std::string rankLabel =
            (skill.rank == SkillRank::Expertise) ? "Expertise" :
            (skill.rank == SkillRank::Proficient) ? "Proficient" : "None";

        std::cout << i + 1 << ". " << skill.name
                  << " [" << skill.ability << "] "
                  << (modifier >= 0 ? "+" : "") << modifier
                  << " - " << rankLabel << "\n";
    }
}

void CharacterFeatures::save(std::ofstream& file) const
{
    // Save the two free-text lists first, then each skill's current rank.
    file << feats.size() << "\n";
    for (const auto& feat : feats)
    {
        file << feat << "\n";
    }

    file << racialTraits.size() << "\n";
    for (const auto& trait : racialTraits)
    {
        file << trait << "\n";
    }

    file << skills.size() << "\n";
    for (const auto& skill : skills)
    {
        file << skill.name << "\n";
        file << skill.ability << "\n";
        file << static_cast<int>(skill.rank) << "\n";
    }
}

void CharacterFeatures::load(std::ifstream& file)
{
    feats.clear();
    racialTraits.clear();

    int count = 0;
    file >> count;
    file.ignore();
    for (int i = 0; i < count; i++)
    {
        std::string feat;
        std::getline(file, feat);
        addFeat(feat);
    }

    file >> count;
    file.ignore();
    for (int i = 0; i < count; i++)
    {
        std::string trait;
        std::getline(file, trait);
        addRacialTrait(trait);
    }

    int skillCount = 0;
    file >> skillCount;
    file.ignore();
    for (int i = 0; i < skillCount; i++)
    {
        std::string name;
        std::string ability;
        int rankValue = 0;

        std::getline(file, name);
        std::getline(file, ability);
        file >> rankValue;
        file.ignore();

        SkillEntry* skill = findSkill(name);
        if (skill != nullptr)
        {
            // Reapply the saved state onto the built-in 5e skill table.
            skill->ability = ability;
            skill->rank = static_cast<SkillRank>(rankValue);
        }
    }
}
