//
// Created by joseph on 10/12/18.
//

#include "BaseCircuitComponent.h"

BaseCircuitComponent::BaseCircuitComponent() {
    // field_8
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
    // TODO: impl
}

bool BaseCircuitComponent::removeSource(const BlockPos *pos, const BaseCircuitComponent *component) {
    // TODO: impl
    // Remove the source from the CircuitComponentList (field_8)
}

bool BaseCircuitComponent::hasSource(BaseCircuitComponent *component) {
    // TODO: impl
    // Search for the source from the CircuitComponentList (field_8)
}
