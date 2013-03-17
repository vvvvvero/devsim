/***
DEVSIM
Copyright 2013 Devsim LLC

This file is part of DEVSIM.

DEVSIM is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, version 3.

DEVSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with DEVSIM.  If not, see <http://www.gnu.org/licenses/>.
***/

#include "UnitVec.hh"
#include "Region.hh"
#include "Node.hh"
#include "Edge.hh"
#include "Vector.hh"
#include "EdgeSubModel.hh"
#include "dsAssert.hh"

UnitVec::~UnitVec()
{
}

UnitVec::UnitVec(RegionPtr rp) :
EdgeModel("unitx", rp, EdgeModel::SCALAR)
{
    if (rp->GetDimension() > 1)
    {
        unity = EdgeSubModel::CreateEdgeSubModel("unity", rp, EdgeModel::SCALAR, this->GetSelfPtr());
    }

    if (rp->GetDimension() > 2)
    {
        unitz = EdgeSubModel::CreateEdgeSubModel("unitz", rp, EdgeModel::SCALAR, this->GetSelfPtr());
    }
}


void UnitVec::calcEdgeScalarValues() const
{
  const ConstEdgeList &el = GetRegion().GetEdgeList();
  std::vector<double> ux(el.size());
  std::vector<double> uy(el.size());
  std::vector<double> uz(el.size());

  for (size_t i = 0; i < el.size(); ++i)
  {
     const Vector &v = calcUnitVec(el[i]);
     ux[i] = v.Getx();
     uy[i] = v.Gety();
     uz[i] = v.Getz();
  }

  SetValues(ux);
  if (!unity.expired())
  {
    unity.lock()->SetValues(uy);
  }
  if (!unitz.expired())
  {
    unitz.lock()->SetValues(uz);
  }
}

Vector UnitVec::calcUnitVec(ConstEdgePtr ep) const
{
    const Vector &p0 = ep->GetHead()->Position();
    const Vector &p1 = ep->GetTail()->Position();

    Vector vm = p1;
    vm -= p0;
    vm /= vm.magnitude();

    return vm;
}

void UnitVec::Serialize(std::ostream &of) const
{
  SerializeBuiltIn(of);
}

