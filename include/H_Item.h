#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>
#include <memory>

class Item {
protected:
    std::string name;
    std::string description;
    float weight;
    int quantity;
    int value; // in gp
    std::string rarity;
    bool requiresAttunement;

public:
    Item(std::string name = "", std::string description = "", float weight = 0.0f,
         int quantity = 1, int value = 0, std::string rarity = "Common", bool requiresAttunement = false);
    virtual ~Item() = default;

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    float getWeight() const;
    int getQuantity() const;
    int getValue() const;
    std::string getRarity() const;
    bool getRequiresAttunement() const;

    // Setters
    void setQuantity(int qty);

    // Polymorphic interface
    virtual std::string getItemTag() const = 0;
    virtual void display() const;
    virtual void saveData(std::ofstream& file) const;
    virtual void loadData(std::ifstream& file);

    // Top-level save writes tag then calls saveData
    void save(std::ofstream& file) const;

    // Factory: reads tag, constructs correct subclass, calls loadData
    static std::unique_ptr<Item> loadFromFile(std::ifstream& file);

protected:
    void displayCommon() const;
    void saveCommon(std::ofstream& file) const;
    void loadCommon(std::ifstream& file);
};

#endif
