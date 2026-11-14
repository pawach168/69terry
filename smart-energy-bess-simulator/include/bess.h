#pragma once

#include <string>

namespace energy {

class BESS {
public:
    BESS(double capacityKWh,
         double stateOfChargePercent,
         double minimumSocPercent,
         double dischargeEfficiencyPercent);

    double usableEnergyKWh() const;
    double estimatedRuntimeHours(double loadKW) const;
    std::string status() const;

    double capacityKWh() const;
    double stateOfChargePercent() const;
    double minimumSocPercent() const;
    double dischargeEfficiencyPercent() const;

private:
    double capacityKWh_;
    double stateOfChargePercent_;
    double minimumSocPercent_;
    double dischargeEfficiencyPercent_;

    static void validatePercent(double value, const std::string& fieldName);
};

} // namespace energy
