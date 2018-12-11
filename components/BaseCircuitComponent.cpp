//
// Created by Earthcomputer on 10/12/18.
//

#include "BaseCircuitComponent.h"

BaseCircuitComponent::BaseCircuitComponent() {
    field_8 = new CircuitComponentList;
    field_20 = false;
    field_21 = true;
    field_22 = false;
    // field_24
    field_30 = true;
    field_34 = 0;
    field_38 = 6;
    field_39 = false;
    field_3A = true;
}

BaseCircuitComponent::~BaseCircuitComponent() {
    delete field_8;
}

bool BaseCircuitComponent::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    bool removedAny = false;
    for (auto it = field_8->begin(); it != field_8->end();) {
        if (it->field_C == *pos) {
            it = field_8->erase(it);
            removedAny = true;
        } else {
            ++it;
        }
    }
    return removedAny;
}

bool BaseCircuitComponent::hasSource(BaseCircuitComponent *component) {
    if (field_8->size() <= 0)
        return false;

    for (auto it = field_8->begin(), e = field_8->end(); it != e; ++it) {
        BaseCircuitComponent *comp = it->field_0;
        if (comp) {
            if (comp == component) {
                return true;
            }
            if (comp->hasChildrenSource()) {
                //e = component; FIXME
                if (comp->hasSource(component)) {
                    return true;
                }
            }
        }
    }

    return false;
}
