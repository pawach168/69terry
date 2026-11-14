# System Architecture & Model Assumptions

## Component overview

- `DataCenter`: converts IT load to estimated facility load using PUE.
- `BESS`: estimates usable AC energy and runtime from nameplate capacity, SOC window, and discharge efficiency.
- `EnergySimulator`: prints the report and evaluates a simplified outage scenario.
- `main.cpp`: defines the example scenario and connects the components.

## Core formulas

Facility load:

`Facility Load (kW) = IT Load (kW) × PUE`

Estimated usable AC energy:

`Usable Energy (kWh) = Nameplate Capacity × (Current SOC − Minimum SOC) × Discharge Efficiency`

SOC values and efficiency are expressed as fractions in the calculation.

Estimated runtime:

`Runtime (hours) = Usable Energy (kWh) ÷ Facility Load (kW)`

## Simplifications and limitations

1. Constant facility load throughout the outage.
2. No battery inverter power limit or overload capability model.
3. No temperature, aging, degradation, or auxiliary-load correction.
4. No transient response, UPS ride-through, generator start-up, synchronization, or transfer-time model.
5. Generator consumption is constant and independent of loading.
6. The outage scenario assumes BESS is used first, then generator fuel is used.

Do not use these estimates as the basis for procurement, protection coordination, or life-safety decisions. Validate with vendor datasheets and a qualified electrical engineer.
