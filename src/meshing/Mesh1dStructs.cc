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

#include "Mesh1dStructs.hh"
#include "dsAssert.hh"

namespace dsMesh {
MeshLine1d::MeshLine1d(double p, double ps, double ns) :
    position(p), posSpacing(ps), negSpacing(ns)
{
}

MeshLine1d::MeshLine1d(double p, double ps, double ns, const std::string &t) :
    position(p), posSpacing(ps), negSpacing(ns), tag(t)
{
}

MeshRegion1d::MeshRegion1d(const std::string &r, const std::string &m, const std::string &t1, const std::string &t2)
: name(r), material(m), tag0(t1), tag1(t2), tagssorted(false)
{
}
const std::string &MeshRegion1d::GetName() const
{
    return name;
}

const std::string &MeshRegion1d::GetMaterial() const
{
    return material;
}

const std::string &MeshRegion1d::GetTag0() const
{
    dsAssert(tagssorted, "UNEXPECTED");
    return tag0;
}

const std::string &MeshRegion1d::GetTag1() const
{
    dsAssert(tagssorted, "UNEXPECTED");
    return tag1;
}

const size_t &MeshRegion1d::GetIndex0() const
{
    dsAssert(tagssorted, "UNEXPECTED");
    return index0;
}

const size_t &MeshRegion1d::GetIndex1() const
{
    dsAssert(tagssorted, "UNEXPECTED");
    return index1;
}

void MeshRegion1d::sortTags(const std::map<std::string, size_t> &v)
{
    dsAssert(v.count(tag0) != 0, "UNEXPECTED");
    dsAssert(v.count(tag1) != 0, "UNEXPECTED");

    index0 = v.find(tag0)->second;
    index1 = v.find(tag1)->second;

    dsAssert(index0 != index1, "UNEXPECTED");

    if (index1 < index0)
    {
        size_t t = index0;
        index0   = index1;
        index1   = t;
    }
    tagssorted = true;
}

MeshInterface1d::MeshInterface1d(const std::string &n, const std::string &t) : name(n), tag(t)
{
}

const std::string &MeshInterface1d::GetName()
{
    return name;
}

const std::string &MeshInterface1d::GetTag()
{
    return tag;
}

MeshContact1d::MeshContact1d(const std::string &n, const std::string &t) : name(n), tag(t)
{
}

const std::string &MeshContact1d::GetName()
{
    return name;
}

const std::string &MeshContact1d::GetTag()
{
    return tag;
}
}
