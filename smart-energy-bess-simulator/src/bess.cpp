#include "bess.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace energy {

void BESS::validatePercent(double value, const std::string& fieldName) {
    if (value < 0.0 || value > 100.0) {
        throw std::invalid_argument(fieldName + " must be between 0 and 100.");
    }
}

BESS::BESS(double capacityKWh,
           double stateOfChargePercent,
           double minimumSocPercent,
           double dischargeEfficiencyPercent)
    : capacityKWh_(capacityKWh),
      stateOfChargePercent_(stateOfChargePercent),
      minimumSocPercent_(minimumSocPercent),
      dischargeEfficiencyPercent_(dischargeEfficiencyPercent) {
    if (capacityKWh_ <= 0.0) {
        throw std::invalid_argument("BESS capacity must be greater than zero.");
    }
    validatePercent(stateOfChargePercent_, "State of charge");
    validatePercent(minimumSocPercent_, "Minimum state of charge");
    validatePercent(dischargeEfficiencyPercent_, "Discharge efficiency");

    if (minimumSocPercent_ > stateOfChargePercent_) {
        throw std::invalid_argument("Minimum SOC cannot exceed current SOC.");
    }
    if (dischargeEfficiencyPercent_ == 0.0) {
        throw std::invalid_argument("Discharge efficiency must be greater than zero.");
    }
}

double BESS::usableEnergyKWh() const {
    const double availableFraction =
        (stateOfChargePercent_ - minimumSocPercent_) / 100.0;
    const double efficiency = dischargeEfficiencyPercent_ / 100.0;
    return capacityKWh_ * availableFraction * efficiency;
}

double BESS::estimatedRuntimeHours(double loadKW) const {
    if (loadKW <= 0.0) {
        throw std::invalid_argument("Load must be greater than zero.");
    }
    return usableEnergyKWh() / loadKW;
}

std::string BESS::status() const {
    std::ostringstream output;
    output << std::fixed << std::setprecision(1)
           << "SOC " << stateOfChargePercent_ << "% (minimum "
           << minimumSocPercent_ << "%)";
    return output.str();
}

double BESS::capacityKWh() const { return capacityKWh_; }
double BESS::stateOfChargePercent() const { return stateOfChargePercent_; }
double BESS::minimumSocPercent() const { return minimumSocPercent_; }
double BESS::dischargeEfficiencyPercent() const { return dischargeEfficiencyPercent_; }

} // namespace energy
