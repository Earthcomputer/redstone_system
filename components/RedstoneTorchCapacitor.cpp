//
// Created by Earthcomputer on 10/12/18.
//

#include <unordered_map>
#include <queue>
#include "RedstoneTorchCapacitor.h"

void PushCircularReference(std::unordered_map<BlockPos, RedstoneTorchCapacitor *> &posToTorchMap, const BlockPos &pos, std::queue<RedstoneTorchCapacitor *> &torchQueue) {
    auto it = posToTorchMap.find(pos);
    if (it != posToTorchMap.end()) {
        torchQueue.push(it->second);
    }
}

bool sub_1F62CA0(CircuitComponentList *componentList) {
    if (componentList->size() <= 0)
        return false;

    for (auto &item : *componentList) {
        if (item.field_0) {
            ComponentType baseType = item.field_0->getBaseType();
            if (baseType == TYPE_POWERED_BLOCK || baseType == TYPE_CONSUMER) {
                CircuitComponentList *childList = item.field_0->field_8;
                for (auto &childItem : *childList) {
                    if (childItem.field_19) {
                        BaseCircuitComponent *child = childItem.field_0;
                        if (child && child->getInstanceType() != TYPE_REDSTONE_TORCH) {
                            int v6 = child->getStrength() - childItem.field_8;
                            v6 = std::max(v6, 0);
                            if (v6 != 0)
                                return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool sub_1F63000(CircuitComponentList *componentList, CircuitSceneGraph *graph) {
    bool v42 = false;
    std::unordered_map<BlockPos, RedstoneTorchCapacitor *> posToTorchMap;
    for (auto &item : *componentList) {
        BaseCircuitComponent *v37 = item.field_0;
        if (v37) {
            BlockPos posAbove = item.field_C + Facing::DIRECTION[Facing::UP];
            BaseCircuitComponent *v34 = graph->getComponent(&posAbove, TYPE_TRANSPORTER);
            if (v34) {
                ComponentType baseType = v37->getBaseType();
                if (baseType == TYPE_POWERED_BLOCK || baseType == TYPE_CONSUMER) {
                    BlockPos v32 = item.field_C;
                    CircuitComponentList *componentList1 = v37->field_8;
                    for (auto &v27 : *componentList1) {
                        if (v27.field_19) {
                            BaseCircuitComponent *v26 = v27.field_0;
                            BlockPos v25 = v27.field_C + Facing::DIRECTION[v26->getDirection()];
                            if (v26 && v25 == v32 && v26->getInstanceType() == TYPE_REDSTONE_TORCH) {
                                BlockPos v24 = v27.field_C + Facing::DIRECTION[Facing::UP];
                                BaseCircuitComponent *v22 = graph->getComponent(&v24, TYPE_POWERED_BLOCK);
                                BaseCircuitComponent *v21 = graph->getComponent(&v24, TYPE_CONSUMER);
                                if (v22 || v21) {
                                    if (v26->getDirection() != Facing::DOWN) {
                                        posToTorchMap.insert(std::make_pair(v27.field_C, dynamic_cast<RedstoneTorchCapacitor *>(v26)));
                                    }
                                }
                            }
                        }
                    }
                    if (posToTorchMap.size() > 1) {
                        std::queue<RedstoneTorchCapacitor *> torchQueue;
                        PushCircularReference(posToTorchMap, item.field_C + Facing::DIRECTION[Facing::NORTH], torchQueue);
                        PushCircularReference(posToTorchMap, item.field_C + Facing::DIRECTION[Facing::WEST], torchQueue);
                        PushCircularReference(posToTorchMap, item.field_C + Facing::DIRECTION[Facing::SOUTH], torchQueue);
                        PushCircularReference(posToTorchMap, item.field_C + Facing::DIRECTION[Facing::EAST], torchQueue);
                        if (!torchQueue.empty()) {
                            RedstoneTorchCapacitor *firstTorch = torchQueue.front();
                            firstTorch->setSelfPowerCount(0);
                            RedstoneTorchCapacitor *lastTorch = torchQueue.back();
                            lastTorch->setNextInQueue(firstTorch);
                            lastTorch->setSelfPowerCount(0);
                            while (torchQueue.size() > 1) {
                                RedstoneTorchCapacitor *torchA = torchQueue.front();
                                torchQueue.pop();
                                RedstoneTorchCapacitor *torchB = torchQueue.front();
                                torchA->setNextInQueue(torchB);
                                lastTorch->setSelfPowerCount(16);
                            }
                        }
                        v42 = true;
                    }
                }
            }
        }
    }
    return v42;
}

bool RedstoneTorchCapacitor::addSource(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo, int *a4,
                                       bool *a5) {
    ComponentType componentType = trackingInfo->field_40.field_18;
    if (componentType != TYPE_POWERED_BLOCK && componentType != TYPE_TRANSPORTER && componentType != TYPE_CONSUMER) {
        if (trackingInfo->field_0.field_14 == Facing::OPPOSITE_FACING[trackingInfo->field_0.field_0->getDirection()]) {
            trackPowerSource(trackingInfo, *a4, *a5, false);
        }
    }
    return false;
}

bool RedstoneTorchCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                             bool *a4) {
    bool providesPower = trackingInfo->field_0.field_18 == TYPE_POWERED_BLOCK || trackingInfo->field_0.field_18 == TYPE_PRODUCER;
    bool flag2 = providesPower && trackingInfo->field_0.field_14 == trackingInfo->field_40.field_14;
    bool flag3 = trackingInfo->field_0.field_18 == TYPE_CONSUMER && getDirection() == trackingInfo->field_0.field_14;
    if (flag2 || flag3) {
        const CircuitTrackingInfo trackingInfo1(*trackingInfo);
        trackPowerSource(&trackingInfo1, trackingInfo->field_80, trackingInfo->field_84, false);
        if (trackingInfo->field_0.field_18 == TYPE_POWERED_BLOCK) {
            return false;
        }
    }

    return field_38 != Facing::DOWN || trackingInfo->field_0.field_14 != Facing::DOWN;
}

void RedstoneTorchCapacitor::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    if (field_48) {
        if (sub_1F62CA0(field_8)) {
            field_58 = false;
            field_57 = true;
            field_59 = !field_54;
            field_50 = -1;
        } else if (field_50 != 0) {
            field_58 = false;
            field_57 = false;
            field_59 = field_54;
        } else {
            field_58 = false;
            field_57 = true;
            field_59 = !field_54;
            if (field_48) {
                field_48->field_50 = -1;
                RedstoneTorchCapacitor *torch = field_48->field_48;
                for (int i = 0; i < 4 && torch && torch != this; i++) {
                    torch->field_50 = 1;
                    torch = torch->field_48;
                }
            }
        }
    } else {
        bool v11 = false;
        int strongestStrength = FindStrongestStrength(pos, system, &v11);
        bool v9, v8;
        if (v11) {
            if (_canIncrementSelfPower())
                field_50++;
            if (field_50 >= 16) {
                if (field_50 == 16) {
                    v9 = false;
                    v8 = true;
                } else {
                    v9 = false;
                    v8 = false;
                }
            } else {
                v9 = !field_54;
                v8 = true;
            }
        } else {
            field_50 = 0;
            field_5A = false;
            v9 = strongestStrength <= 0;
            v8 = false;
        }
        field_58 = v8;
        field_57 = v9;
        field_59 = v9 != field_54;
        if (field_50 > 32) {
            field_5A = true;
        }
    }
}

void RedstoneTorchCapacitor::updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    if (!sub_1F63000(field_8, graph)) {
        field_48 = nullptr;
    }
}

int RedstoneTorchCapacitor::FindStrongestStrength(const BlockPos *pos, CircuitSystem *system, bool *a4) {
    if (field_8->size() <= 0)
        return 0;

    int v27 = 0;
    CircuitComponentList::Item *v26 = nullptr, *v25 = nullptr, *v24 = nullptr;

    for (auto v22 = field_8->begin(); v22 != field_8->end(); ++v22) {
        CircuitComponentList::Item *v20 = v22.base();
        BaseCircuitComponent *component = v20->field_0;
        if (component) {
            ComponentType v18 = component->getBaseType();
            if (v18 != TYPE_PRODUCER && (v18 != TYPE_CAPACITOR || component->field_8->size() != 0)) {
                int v16 = 0;
                int v15 = 0;
                CircuitComponentList *v14 = component->field_8;
                for (auto v13 = v14->begin(), v12 = v14->end(); v13 != v12; ++v13) {
                    if (v13->field_19) {
                        BaseCircuitComponent *v10 = v13->field_0;
                        if (v10) {
                            v16 = v10->getStrength() - v13->field_8;
                            v16 = std::max(v16, 0);
                            if (v16 >= v27 && v16 != 0) {
                                v27 = v16;
                                v26 = v13.base();
                                if (*pos != v13->field_C) {
                                    v24 = v13.base();
                                }
                            }
                            if (*pos == v13->field_C) {
                                v25 = v13.base();
                                v15 = v16;
                            }
                        }
                    }
                }
                if (v16 == v15 && v24) {
                    v26 = v24;
                    v25 = nullptr;
                }
                if (!v27 && v25) {
                    v26 = v25;
                }
                *a4 = v26 == v25 && v25;
            } else {
                int v17 = component->getStrength();
                if (v17 >= v27 && v17 != 0) {
                    v26 = v20;
                    v27 = v17;
                }
            }
        }
    }

    return v27;
}

