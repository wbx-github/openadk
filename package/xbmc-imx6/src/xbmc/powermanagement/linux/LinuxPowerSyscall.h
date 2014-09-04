#pragma once
/*
 *      Copyright (C) 2014 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#if defined (_LINUX)
#include "powermanagement/IPowerSyscall.h"

class CLinuxPowerSyscall : public CPowerSyscallWithoutEvents
{
public:
  CLinuxPowerSyscall();
  ~CLinuxPowerSyscall();

  virtual bool Powerdown();
  virtual bool Suspend(void) { return false; }
  virtual bool Hibernate(void) { return false; }
  virtual bool Reboot();

  virtual bool CanPowerdown(void) { return true; }
  virtual bool CanSuspend(void) { return false; }
  virtual bool CanHibernate(void) { return false; }
  virtual bool CanReboot(void) { return true; }
  virtual int  BatteryLevel(void);

  virtual bool PumpPowerEvents(IPowerEventsCallback *callback);
};
#endif

