#include "simulator.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace energy {

EnergySimulator::EnergySimulator(const DataCenter& dataCenter, const BESS& bess)
    : dataCenter_(dataCenter), bess_(bess) {}

void EnergySimulator::printReport() const {
    const double facilityLoad = dataCenter_.facilityLoadKW();
    const double usableEnergy = bess_.usableEnergyKWh();
    const double runtimeHours = bess_.estimatedRuntimeHours(facilityLoad);

    std::cout << "\n============================================\n";
    std::cout << "       SMART ENERGY & BESS SIMULATOR\n";
    std::cout << "============================================\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "DATA CENTER\n";
    std::cout << "  IT load                 : " << dataCenter_.itLoadKW() << " kW\n";
    std::cout << "  PUE                     : " << dataCenter_.pue() << "\n";
    std::cout << "  Estimated facility load : " << facilityLoad << " kW\n";
    std::cout << "\nBATTERY ENERGY STORAGE SYSTEM\n";
    std::cout << "  Nameplate capacity      : " << bess_.capacityKWh() << " kWh\n";
    std::cout << "  Battery status          : " << bess_.status() << "\n";
    std::cout << "  Discharge efficiency    : "
              << bess_.dischargeEfficiencyPercent() << "%\n";
    std::cout << "  Estimated usable energy : " << usableEnergy << " kWh\n";
    std::cout << "  Estimated runtime       : " << runtimeHours
              << " hours (" << runtimeHours * 60.0 << " minutes)\n";
    std::cout << "============================================\n";
}

void EnergySimulator::simulateGridOutage(
    double outageHours,
    double generatorFuelLitres,
    double generatorConsumptionLitresPerHour) const {

    if (outageHours <= 0.0) {
        throw std::invalid_argument("Outage duration must be greater than zero.");
    }
    if (generatorFuelLitres < 0.0 || generatorConsumptionLitresPerHour < 0.0) {
        throw std::invalid_argument("Generator fuel values cannot be negative.");
    }

    const double loadKW = dataCenter_.facilityLoadKW();
    const double bessRuntime = bess_.estimatedRuntimeHours(loadKW);
    const double generatorRuntime =
        generatorConsumptionLitresPerHour > 0.0
            ? generatorFuelLitres / generatorConsumptionLitresPerHour
            : 0.0;

    const double bessSuppliedHours = std::min(outageHours, bessRuntime);
    const double remainingOutage = std::max(0.0, outageHours - bessSuppliedHours);
    const double generatorSuppliedHours = std::min(remainingOutage, generatorRuntime);
    const double unmetHours = std::max(0.0, remainingOutage - generatorSuppliedHours);

    std::cout << "\nGRID OUTAGE SCENARIO\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Outage duration         : " << outageHours << " hours\n";
    std::cout << "  BESS can support        : " << bessSuppliedHours << " hours\n";
    std::cout << "  Generator fuel available: " << generatorFuelLitres << " litres\n";
    std::cout << "  Generator runtime       : " << generatorRuntime << " hours\n";
    std::cout << "  Generator support used  : " << generatorSuppliedHours << " hours\n";

    if (unmetHours <= 0.000001) {
        std::cout << "  Result                  : Backup covers the modeled outage.\n";
    } else {
        std::cout << "  Result                  : Estimated unsupported time = "
                  << unmetHours << " hours.\n";
    }
    std::cout << "\nNote: This simplified model assumes sequential BESS then generator use.\n";
}

} // namespace energy
