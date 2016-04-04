/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESSSENSOR_H
#define BRIGHTNESSSENSOR_H

#include "StreetlightProxy.h"

#include <application/Brightness.h>

#include <dbus-c++/dbus.h>

class BrightnessSensor :
    public ch::bbv::StreetLight::Brightness_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy,
    public Brightness
{
public:
  BrightnessSensor(DBus::Connection& connection);

  void update(const double& value);

  double value() override;

};

#endif
