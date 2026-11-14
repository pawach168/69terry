#include "datacenter.h"

#include <stdexcept>

namespace energy {

DataCenter::DataCenter(double itLoadKW, double pue)
    : itLoadKW_(itLoadKW), pue_(pue) {
    if (itLoadKW_ <= 0.0) {
        throw std::invalid_argument("IT load must be greater than zero.");
    }
    if (pue_ < 1.0) {
        throw std::invalid_argument("PUE must be 1.0 or greater.");
    }
}

double DataCenter::facilityLoadKW() const {
    return itLoadKW_ * pue_;
}

double DataCenter::itLoadKW() const { return itLoadKW_; }
double DataCenter::pue() const { return pue_; }

} // namespace energy
