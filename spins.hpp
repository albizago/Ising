#ifndef SPINS_HPP
#define SPINS_HPP

#include <array>
#include <cassert>
#include <random>

namespace phys
{
    class Spin
    {
        int x_;
        int y_;
        bool state_;

    public:
        Spin(int x = 1, int y = 1, bool st = false) : x_(x), y_(y), state_(st) {}
        int const &get_x() const;
        int const &get_y() const;
        void set_x(int &a);
        void set_y(int &c);
        void set_state(bool &b);
        int get_state() const;
        void flip_state();
    };

    class Board
    {
        std::array<Spin, 250001> spins_;

    public:
        Board()
        {
            Spin *it = spins_.begin();
            std::random_device ran;
            for (int i = 0; i <= 249999; ++i)
            {
                int a = i / 500;
                a += 1;
                int b = i % 500;
                b += 1;
                it->set_x(a);
                it->set_y(b);
                std::uniform_int_distribution<int> ar(0, 1);
                bool stt = ar(ran);
                it->set_state(stt);
                ++it;
            }
        }
        std::array<Spin, 250001> &spins();
        std::array<Spin, 250001> const &spins_const() const;

        auto get_spin(int a, int b);
        Spin const &get_spin_const(int const &a, int const &b) const;
        double magnetization();
    };
}

#endif