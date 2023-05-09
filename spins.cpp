#include "spins.hpp"
#include <numeric>
#include <cmath>
#include <random>
#include <cassert>

int const &phys::Spin::get_x() const
{
    return x_;
}
int const &phys::Spin::get_y() const
{
    return y_;
}
void phys::Spin::set_x(int &a)
{
    x_ = a;
}
void phys::Spin::set_y(int &c)
{
    y_ = c;
}
void phys::Spin::set_state(bool &b)
{
    state_ = b;
}
int phys::Spin::get_state() const
{
    if (state_ == true && x_ != 0 && y_ != 0)
    {
        return 1;
    }
    else if (state_ == false && x_ != 0 && y_ != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void phys::Spin::flip_state()
{
    state_ = !state_;
}

auto phys::Board::get_spin(int a, int b)
{
    if ((500 * (a - 1) + b - 1) > 0 && (500 * (a - 1) + b - 1) < 250001)
    {
        return spins_.begin() + (500 * (a - 1) + b - 1);
    }
    else
    {
        return spins_.begin() + 250000;
    }
}

phys::Spin const &phys::Board::get_spin_const(int const &a, int const &b) const
{
    assert(a > 0 && b > 0 && a < 501 && b < 501);
    return spins_.at(500 * (a - 1) + b - 1);
}

std::array<phys::Spin, 250001> &phys::Board::spins()
{
    return spins_;
}

std::array<phys::Spin, 250001> const &phys::Board::spins_const() const
{
    return spins_;
}

double phys::Board::magnetization()
{
    auto spin_sum = [](double n, phys::Spin const spin2) -> int
    {
        return n + spin2.get_state();
    };
    double sum = std::accumulate(spins_.begin(), spins_.end(), 0, spin_sum);
    return sum / 250001;
}