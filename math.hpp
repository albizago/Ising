#ifndef MATH_HPP
#define MATH_HPP

#include "spins.hpp"

namespace math
{
    double node_energy(phys::Spin const &, phys::Board const &, double const &);
    double energy_calc(phys::Board const &, double const &);
    bool probability_calc(double const &);
    void evolution(phys::Board &, double const &, double const &, int const &a, int const &b);
}

#endif