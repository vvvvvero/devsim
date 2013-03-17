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

#include "GetGlobalParameter.hh"
#include "GlobalData.hh"
#include "ObjectHolder.hh"
std::string GetGlobalParameterStringOptional(const std::string &name)
{
  std::string ret;
  const GlobalData &ginst = GlobalData::GetInstance();
  GlobalData::DBEntry_t dbent = ginst.GetDBEntryOnGlobal(name);
  if (dbent.first)
  {
    ret = dbent.second.GetString();
  }
  return ret;
}

void *GetMainInterpreter()
{
  return GlobalData::GetInstance().GetInterpreter();
}

void SetMainInterpreter(void *interp)
{
  GlobalData::GetInstance().SetInterpreter(interp);
}

