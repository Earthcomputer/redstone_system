//
// Created by Earthcomputer on 10/12/18.
//

#ifndef REDSTONE_SYSTEM_CIRCUITCOMPONENTLIST_H
#define REDSTONE_SYSTEM_CIRCUITCOMPONENTLIST_H

#include <vector>
#include "BlockPos.h"
#include "Facing.h"

class BaseCircuitComponent;

class CircuitComponentList {
public:
    class Item {
    public:
        BaseCircuitComponent *mComponent; // off = 0x0
        int field_8;
        BlockPos mPos; // off = 0xC
        Facing::Facing mDirection; // off = 0x18
        bool field_19;
        int field_1C;

        Item() :
            mComponent(nullptr),
            field_8(0),
            mPos(),
            mDirection(Facing::NONE),
            field_19(false),
            field_1C(0) {
        }
        Item(BaseCircuitComponent *component, int i, BlockPos *pos) :
            mComponent(component),
            field_8(i),
            mPos(pos),
            mDirection(Facing::NONE),
            field_19(false),
            field_1C(0) {
        }
        explicit Item(Item* other) :
            mComponent(other->mComponent),
            field_8(other->field_8),
            mPos(other->mPos),
            mDirection(other->mDirection),
            field_19(other->field_19),
            field_1C(other->field_1C) {
        }
    };

    typedef std::vector<Item>::iterator iterator;

private:
    std::vector<Item> items;

public:
    void add(BaseCircuitComponent *component, int i, BlockPos *pos) {
        items.push_back(Item(component, i, pos));
    }

    iterator begin() {
        return items.begin();
    }

    iterator end() {
        return items.end();
    }

    iterator erase(iterator item) {
        return items.erase(item);
    }

    auto push_back(Item *item) {
        return items.push_back(Item(item));
    }

    auto at(size_t index) {
        return items.at(index);
    }

    bool removeSource(const BlockPos *a2, const BaseCircuitComponent *a3) {
        bool erasedAny = false;
        for (auto it = items.begin(); it != items.end();) {
            if (it->mPos == *a2) {
                it = items.erase(it);
                erasedAny = true;
            } else {
                ++it;
            }
        }
        return erasedAny;
    }

    auto size() {
        return items.size();
    }
};

#endif //REDSTONE_SYSTEM_CIRCUITCOMPONENTLIST_H
