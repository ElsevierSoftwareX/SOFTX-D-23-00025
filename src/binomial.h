///////////////////////////////////////////////////////////////////////////////
///
/// Josh Bedwell - June 2021
///
/// This file holds a binomial coefficient function
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <exception>

///////////////////////////////////////////////////////////////////////////////
///
/// This function calculates a binomial coefficient efficiently by enumerating several factorials
/// Hardcoded factorials.
/// 
/// @param r \input    r < 35 and r-k < 35
/// @param k \input    k < 35 and r-k < 35
/// @return binomal coefficient of r and k
///
///////////////////////////////////////////////////////////////////////////////

double binomial_coefficient(unsigned r, unsigned k) {
    constexpr double factorials[] = {
        1.0,
        1.0,
        2.0,
        6.0,
        24.0,
        120.0,
        720.0,
        5040.0,
        40320.0,
        362880.0,
        3628800.0,
        39916800.0,
        479001600.0,
        6227020800.0,
        87178291200.0,
        1307674368000.0,
        20922789888000.0,
        355687428096000.0,
        6402373705728000.0,
        121645100408832000.0,
        0.243290200817664e19,
        0.5109094217170944e20,
        0.112400072777760768e22,
        0.2585201673888497664e23,
        0.62044840173323943936e24,
        0.15511210043330985984e26,
        0.403291461126605635584e27,
        0.10888869450418352160768e29,
        0.304888344611713860501504e30,
        0.8841761993739701954543616e31,
        0.26525285981219105863630848e33,
        0.822283865417792281772556288e34,
        0.26313083693369353016721801216e36,
        0.868331761881188649551819440128e37,
        0.29523279903960414084761860964352e39,
    };

    if (r >= 35 || k >= 35 || (r - k) >= 35)
        throw std::runtime_error("binomial coefficient parameters out of bounds");

    return factorials[r] / (factorials[k] * factorials[r - k]);
}
