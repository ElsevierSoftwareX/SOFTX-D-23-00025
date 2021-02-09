#include "GrowthModel_LIN.h"

double soot::GrowthModel_LIN::getGrowthRate(const GasState& gasState, const SootState& sootState) const
{
	/**
	 * Nucleation by Leung_Lindstedt (1991)
	 *
	 * Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
	 * Returns chemical nucleation rate in #/m3*s.
	 */

	const double cC2H2 = sootState.getRho() * gasState.getC2H2Frac() / MW_C2H2; // kmol/m3
	const double rSoot = 750.0 * std::exp(-12100.0 / gasState.getT()) * cC2H2 * 2.0 * MW_C; // kg/m^2*s

	return rSoot;
}
