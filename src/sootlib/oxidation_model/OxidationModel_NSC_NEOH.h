#ifndef OXIDATIONMODEL_NSC_NEOH_H
#define OXIDATIONMODEL_NSC_NEOH_H

#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_NSC_NEOH : public OxidationModel
{
public:
	// TODO implement
	[[nodiscard]] double getOxidationRate(const GasState& gasState, const MomentSootState& sootState) const override;

	~OxidationModel_NSC_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_NSC_NEOH_H
