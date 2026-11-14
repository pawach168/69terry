#pragma once

namespace energy {

class DataCenter {
public:
    DataCenter(double itLoadKW, double pue);

    double facilityLoadKW() const;
    double itLoadKW() const;
    double pue() const;

private:
    double itLoadKW_;
    double pue_;
};

} // namespace energy
