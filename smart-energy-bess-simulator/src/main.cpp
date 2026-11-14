#include "bess.h"
#include "datacenter.h"
#include "simulator.h"

#include <exception>
#include <iostream>

int main() {
    try {
        // Editable example scenario. Change these values to test other facilities.
        constexpr double itLoadKW = 500.0;
        constexpr double pue = 1.40;

        constexpr double bessCapacityKWh = 2000.0;
        constexpr double currentSocPercent = 95.0;
        constexpr double minimumSocPercent = 10.0;
        constexpr double dischargeEfficiencyPercent = 92.0;

        constexpr double outageHours = 6.0;
        constexpr double generatorFuelLitres = 1200.0;
        constexpr double generatorConsumptionLitresPerHour = 150.0;

        const energy::DataCenter dataCenter(itLoadKW, pue);
        const energy::BESS bess(
            bessCapacityKWh,
            currentSocPercent,
            minimumSocPercent,
            dischargeEfficiencyPercent);

        const energy::EnergySimulator simulator(dataCenter, bess);
        simulator.printReport();
        simulator.simulateGridOutage(
            outageHours,
            generatorFuelLitres,
            generatorConsumptionLitresPerHour);

        std::cout << "\nSimulation completed successfully.\n";
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
