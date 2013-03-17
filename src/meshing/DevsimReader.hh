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

#ifndef DEVSIM_READER_HH
#define DEVSIM_READER_HH
#include <string>
#include <cstddef>

//TODO: ensure stack size can trigger realloc

namespace dsMesh {
class DevsimLoader;
typedef DevsimLoader   *DevsimLoaderPtr;

class MeshRegion;
typedef MeshRegion   *MeshRegionPtr;

class MeshContact;
typedef MeshContact   *MeshContactPtr;

class MeshInterface;
typedef MeshInterface   *MeshInterfacePtr;

class Solution;
typedef Solution   *SolutionPtr;

class Equation;
typedef Equation   *EquationPtr;
}

namespace dsDevsimParse {
extern int meshlineno;
extern dsMesh::DevsimLoaderPtr    DevsimLoader;
extern dsMesh::MeshRegionPtr    MeshRegion;
extern dsMesh::MeshContactPtr   MeshContact;
extern dsMesh::MeshInterfacePtr MeshInterface;
extern dsMesh::SolutionPtr      Sol;
extern dsMesh::EquationPtr      Equation;
extern std::string errors;

void DeletePointers();

bool LoadMeshes(const std::string &/*filename*/, std::string &/*errorString*/);
}

#endif


