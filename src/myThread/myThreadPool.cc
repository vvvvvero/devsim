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

#include "myThreadPool.hh"
#include "myqueue.hh"
#include "GlobalData.hh"
#include "OutputStream.hh"
#include "ObjectHolder.hh"
#include <sstream>



myThreadPool *myThreadPool::instance_ = 0;
myqueue      *myThreadPool::queue_ = 0;

myThreadPool &myThreadPool::GetInstance()
{
  if (!instance_)
  {
    instance_ = new myThreadPool;
  }
  return *instance_;
}


void myThreadPool::DestroyInstance()
{
  if (instance_)
  {
    delete instance_;
  }
  instance_ = 0;
}

namespace {
size_t GetThreadsToStart()
{
  //// TODO: built default elsewhere
  size_t ret = 0;
  GlobalData &gdata = GlobalData::GetInstance();
  GlobalData::DBEntry_t dbent = gdata.GetDBEntryOnGlobal("threads_available");
  if (dbent.first)
  {
    ObjectHolder::IntegerEntry_t ient = dbent.second.GetInteger();
    if (!ient.first || ient.second < 0)
    {
//// TODO: callback validation for global parameters
      std::ostringstream os;
      os << "Expected valid positive number for \"threads_available\" parameter, but " << dbent.second.GetString() << " was given.\n";
      OutputStream::WriteOut(OutputStream::INFO, os.str());
      ret = 0;
    }
    else
    {
      ret = ient.second;
    }
  }

  return ret;
}

size_t GetMinimumTaskSize()
{
  //// TODO: built default elsewhere
  size_t ret = 0;
  GlobalData &gdata = GlobalData::GetInstance();
  GlobalData::DBEntry_t dbent = gdata.GetDBEntryOnGlobal("threads_task_size");
  if (dbent.first)
  {
    ObjectHolder::IntegerEntry_t ient = dbent.second.GetInteger();
    if (!ient.first || ient.second < 0)
    {
//// TODO: callback validation for global parameters
      std::ostringstream os;
      os << "Expected valid positive number for \"threads_task_size\" parameter, but " << dbent.second.GetString() << " was given.\n";
      OutputStream::WriteOut(OutputStream::INFO, os.str());
      ret = 0;
    }
    else
    {
      ret = ient.second;
    }
  }

  return ret;
}
}

myThreadPool::myThreadPool()
{
  //// The interpreter must be created at this point
  const size_t numthreads = GetThreadsToStart();  
  const size_t mintasksize = GetMinimumTaskSize();  
  queue_ = new myqueue(numthreads, mintasksize);
  if (numthreads > 1)
  {
    queue_->StartThreads();
  }
}


myqueue &myThreadPool::GetQueue()
{
  //// Check to see if requirement changed
  const size_t threads_set = GetThreadsToStart();
  if (queue_->GetNumberThreads() != threads_set)
  {
    queue_->ChangeNumberThreads(threads_set);
  }

  const size_t task_size = GetMinimumTaskSize();
  queue_->SetMinimumTaskSize(task_size);

  return *queue_;
}

myThreadPool::~myThreadPool()
{
  queue_->ExitThreads();
  delete queue_;
}

