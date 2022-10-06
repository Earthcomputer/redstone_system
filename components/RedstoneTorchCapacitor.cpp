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
        if (item.mComponent) {
            ComponentType baseType = item.mComponent->getBaseType();
            if (baseType == TYPE_POWERED_BLOCK || baseType == TYPE_CONSUMER) {
                CircuitComponentList *childList = item.mComponent->mDependencies;
                for (auto &childItem : *childList) {
                    if (childItem.field_19) {
                        BaseCircuitComponent *child = childItem.mComponent;
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
        BaseCircuitComponent *v37 = item.mComponent;
        if (v37) {
            BlockPos posAbove = item.mPos + Facing::DIRECTION[Facing::UP];
            BaseCircuitComponent *v34 = graph->getComponent(&posAbove, TYPE_TRANSPORTER);
            if (v34) {
                ComponentType baseType = v37->getBaseType();
                if (baseType == TYPE_POWERED_BLOCK || baseType == TYPE_CONSUMER) {
                    BlockPos v32 = item.mPos;
                    CircuitComponentList *componentList1 = v37->mDependencies;
                    for (auto &v27 : *componentList1) {
                        if (v27.field_19) {
                            BaseCircuitComponent *v26 = v27.mComponent;
                            BlockPos v25 = v27.mPos + Facing::DIRECTION[v26->getDirection()];
                            if (v26 && v25 == v32 && v26->getInstanceType() == TYPE_REDSTONE_TORCH) {
                                BlockPos v24 = v27.mPos + Facing::DIRECTION[Facing::UP];
                                BaseCircuitComponent *v22 = graph->getComponent(&v24, TYPE_POWERED_BLOCK);
                                BaseCircuitComponent *v21 = graph->getComponent(&v24, TYPE_CONSUMER);
                                if (v22 || v21) {
                                    if (v26->getDirection() != Facing::DOWN) {
                                        posToTorchMap.insert(std::make_pair(v27.mPos, dynamic_cast<RedstoneTorchCapacitor *>(v26)));
                                    }
                                }
                            }
                        }
                    }
                    if (posToTorchMap.size() > 1) {
                        std::queue<RedstoneTorchCapacitor *> torchQueue;
                        PushCircularReference(posToTorchMap, item.mPos + Facing::DIRECTION[Facing::NORTH], torchQueue);
                        PushCircularReference(posToTorchMap, item.mPos + Facing::DIRECTION[Facing::WEST], torchQueue);
                        PushCircularReference(posToTorchMap, item.mPos + Facing::DIRECTION[Facing::SOUTH], torchQueue);
                        PushCircularReference(posToTorchMap, item.mPos + Facing::DIRECTION[Facing::EAST], torchQueue);
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
    ComponentType componentType = trackingInfo->entry2.mComponentType;
    if (componentType != TYPE_POWERED_BLOCK && componentType != TYPE_TRANSPORTER && componentType != TYPE_CONSUMER) {
        if (trackingInfo->entry0.mDirection == Facing::OPPOSITE_FACING[trackingInfo->entry0.mComponent->getDirection()]) {
            trackPowerSource(trackingInfo, *a4, *a5, false);
        }
    }
    return false;
}

bool RedstoneTorchCapacitor::allowConnection(CircuitSceneGraph *graph, const CircuitTrackingInfo *trackingInfo,
                                             bool *a4) {
    bool providesPower = trackingInfo->entry0.mComponentType == TYPE_POWERED_BLOCK || trackingInfo->entry0.mComponentType == TYPE_PRODUCER;
    bool flag2 = providesPower && trackingInfo->entry0.mDirection == trackingInfo->entry2.mDirection;
    bool flag3 = trackingInfo->entry0.mComponentType == TYPE_CONSUMER && getDirection() == trackingInfo->entry0.mDirection;
    if (flag2 || flag3) {
        const CircuitTrackingInfo trackingInfo1(*trackingInfo);
        trackPowerSource(&trackingInfo1, trackingInfo->field_80, trackingInfo->field_84, false);
        if (trackingInfo->entry0.mComponentType == TYPE_POWERED_BLOCK) {
            return false;
        }
    }

    return mDirection != Facing::DOWN || trackingInfo->entry0.mDirection != Facing::DOWN;
}

void RedstoneTorchCapacitor::cacheValues(CircuitSystem *system, const BlockPos *pos) {
    if (mNextInQueue) {
        if (sub_1F62CA0(mDependencies)) {
            field_58 = false;
            field_57 = true;
            field_59 = !field_54;
            mSelfPowerCount = -1;
        } else if (mSelfPowerCount != 0) {
            field_58 = false;
            field_57 = false;
            field_59 = field_54;
        } else {
            field_58 = false;
            field_57 = true;
            field_59 = !field_54;
            if (mNextInQueue) {
                mNextInQueue->mSelfPowerCount = -1;
                RedstoneTorchCapacitor *torch = mNextInQueue->mNextInQueue;
                for (int i = 0; i < 4 && torch && torch != this; i++) {
                    torch->mSelfPowerCount = 1;
                    torch = torch->mNextInQueue;
                }
            }
        }
    } else {
        bool v11 = false;
        int strongestStrength = FindStrongestStrength(pos, system, &v11);
        bool v9, v8;
        if (v11) {
            if (_canIncrementSelfPower())
                mSelfPowerCount++;
            if (mSelfPowerCount >= 16) {
                if (mSelfPowerCount == 16) {
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
            mSelfPowerCount = 0;
            field_5A = false;
            v9 = strongestStrength <= 0;
            v8 = false;
        }
        field_58 = v8;
        field_57 = v9;
        field_59 = v9 != field_54;
        if (mSelfPowerCount > 32) {
            field_5A = true;
        }
    }
}

void RedstoneTorchCapacitor::updateDependencies(CircuitSceneGraph *graph, const BlockPos *pos) {
    if (!sub_1F63000(mDependencies, graph)) {
        mNextInQueue = nullptr;
    }
}

int RedstoneTorchCapacitor::FindStrongestStrength(const BlockPos *pos, CircuitSystem *system, bool *a4) {
    if (mDependencies->size() <= 0)
        return 0;

    int v27 = 0;
    CircuitComponentList::Item *v26 = nullptr, *v25 = nullptr, *v24 = nullptr;

    for (auto v22 = mDependencies->begin(); v22 != mDependencies->end(); ++v22) {
        CircuitComponentList::Item *v20 = v22._Unwrapped();
        BaseCircuitComponent *component = v20->mComponent;
        if (component) {
            ComponentType v18 = component->getBaseType();
            if (v18 != TYPE_PRODUCER && (v18 != TYPE_CAPACITOR || component->mDependencies->size() != 0)) {
                int v16 = 0;
                int v15 = 0;
                CircuitComponentList *v14 = component->mDependencies;
                for (auto v13 = v14->begin(), v12 = v14->end(); v13 != v12; ++v13) {
                    if (v13->field_19) {
                        BaseCircuitComponent *v10 = v13->mComponent;
                        if (v10) {
                            v16 = v10->getStrength() - v13->field_8;
                            v16 = std::max(v16, 0);
                            if (v16 >= v27 && v16 != 0) {
                                v27 = v16;
                                v26 = v13._Unwrapped();;
                                if (*pos != v13->mPos) {
                                    v24 = v13._Unwrapped();
                                }
                            }
                            if (*pos == v13->mPos) {
                                v25 = v13._Unwrapped();
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

