#include "math.hpp"
#include "spins.hpp"
#include <numeric>
#include <cmath>
#include <random>
#include <chrono>

double math::node_energy(phys::Spin const &spin, phys::Board const &board, double const &field)
{
    /*int loc{0};
    for (int b : {-1, 1})
    {
        auto x = spin.get_x() + b;
        auto y = spin.get_y() + b;
        loc += spin.get_state() * (board.get_spin_const(x, spin.get_y())).get_state();
        loc += spin.get_state() * (board.get_spin_const(spin.get_x(), y)).get_state();
    }*/
    // return -loc / 2 - field * spin.get_state();
    // return -spin.get_state() * (board.get_neighbour(spin, 't').get_state() + board.get_neighbour(spin, 'b').get_state() + board.get_neighbour(spin, 'l').get_state() + board.get_neighbour(spin, 'r').get_state()) / 2 - field * spin.get_state();
    int sum{0};
    if (spin.get_y() < 2)
    {
        sum += board.get_spin_const(spin.get_x(), 500).get_state();
    }
    else
    {
        sum += board.get_spin_const(spin.get_x(), spin.get_y() - 1).get_state();
    }
    if (spin.get_y() > 499)
    {
        sum += board.get_spin_const(spin.get_x(), 1).get_state();
    }
    else
    {
        sum += board.get_spin_const(spin.get_x(), spin.get_y() + 1).get_state();
    }

    if (spin.get_x() < 2)
    {
        sum += board.get_spin_const(500, spin.get_y()).get_state();
    }
    else
    {
        sum += board.get_spin_const(spin.get_x() - 1, spin.get_y()).get_state();
    }

    if (spin.get_x() > 499)
    {
        sum += board.get_spin_const(1, spin.get_y()).get_state();
    }
    else
    {
        sum += board.get_spin_const(spin.get_x() + 1, spin.get_y()).get_state();
    }
    return -spin.get_state() * (sum) / 2 - field * spin.get_state();
}

double math::energy_calc(phys::Board const &board, double const &field)
{
    int spin_cum{0};
    auto spin_sum = [&](double n, phys::Spin const spin2) -> double
    {
        spin_cum += spin2.get_state();
        return n + math::node_energy(spin2, board, field);
    };
    double sum = std::accumulate((board.spins_const()).begin(), (board.spins_const()).end(), 0, spin_sum);
    return -sum - field * spin_cum;
}

bool math::probability_calc(double const &en)
{
    std::random_device ran;
    std::uniform_real_distribution<double> ar(0, 1);
    double pk = std::exp(-(en));
    if (ar(ran) <= pk)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void math::evolution(phys::Board &board, double const &field, double const &temp, int const &a, int const &b)
{
    /*for (phys::Spin &spin : board.spins())
    {*/
    std::random_device ran;
    std::mt19937_64 eng(ran());
    std::uniform_int_distribution<> dist(a, b);
    auto init = std::chrono::steady_clock::now();
    // for (int counter = 1; counter <= 5000; ++counter)
    while (std::chrono::steady_clock::now() - init < std::chrono::milliseconds(20))
    {
        auto spin = board.spins().begin() + dist(eng);
        double dE = -2 * math::node_energy(*spin, board, field);
        spin->flip_state();
        if (dE <= 0)
        {
        }
        else
        {
            if (math::probability_calc((dE) / temp) == true)
            {
            }
            else
            {
                spin->flip_state();
            }
        }
    }
}