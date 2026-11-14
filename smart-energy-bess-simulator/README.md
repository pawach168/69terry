# Smart Energy & BESS Simulator

A C++17 console application that models a simplified data-center energy system and estimates battery backup runtime.

## Features
- Data-center load calculation from IT load and facility overhead (PUE)
- BESS usable energy calculation using capacity, state of charge, depth of discharge, and efficiency
- Estimated backup runtime at the current facility load
- Simple grid-outage simulation
- Generator comparison using configurable fuel consumption and fuel availability
- Input validation and readable engineering-oriented output

> This is an educational planning simulator, not an electrical design, protection, or safety tool. Real projects require validated equipment data, load profiles, transient studies, redundancy design, and qualified engineering review.

## Requirements
- C++17 compiler (GCC 8+, Clang 7+, or modern MSVC)
- CMake 3.16+

## Build

### Windows (Visual Studio Build Tools / Developer PowerShell)
```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\energy_simulator.exe
```

### Linux
```bash
cmake -S . -B build
cmake --build build -j
./build/energy_simulator
```

### macOS
```bash
cmake -S . -B build
cmake --build build -j
./build/energy_simulator
```

## Example assumptions
The default scenario uses:
- IT load: 500 kW
- PUE: 1.40
- BESS nameplate capacity: 2,000 kWh
- State of charge: 95%
- Minimum allowed state of charge: 10%
- Discharge efficiency: 92%

The program estimates runtime from usable AC energy divided by facility load. Actual runtime will vary with battery power limits, temperature, aging, auxiliary loads, inverter limits, and the load profile.

## Project layout
```text
include/   Public class declarations
src/       Implementations and main application
docs/      Model assumptions and architecture notes
```

## Suggested next improvements
- Add CSV load-profile input
- Add time-step simulation and battery degradation
- Add inverter power limit and N+1 redundancy
- Export results to CSV/JSON
- Add unit tests with CTest
