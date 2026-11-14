#pragma once

#include "bess.h"
#include "datacenter.h"

namespace energy {

class EnergySimulator {
public:
    EnergySimulator(const DataCenter& dataCenter, const BESS& bess);

    void printReport() const;
    void simulateGridOutage(double outageHours,
                            double generatorFuelLitres,
                            double generatorConsumptionLitresPerHour) const;

private:
    DataCenter dataCenter_;
    BESS bess_;
};

} // namespace energy
