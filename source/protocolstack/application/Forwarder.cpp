/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Forwarder.h"

void Forwarder::timeout()
{
  message::Outgoing message;

  message.brightness = brightnessSensor();

  sender(message);
}

void Forwarder::received(const message::Incoming &message)
{
  if (message.luminosity.isValid()) {
    luminosityActor(message.luminosity());
  }
  if (message.warning.isValid()) {
    warningActor(message.warning());
  }
}

void Forwarder::setBrightnessSensor(Forwarder::Sensor value)
{
  brightnessSensor = value;
}

void Forwarder::setLuminosityActor(Actor<double> value)
{
  luminosityActor = value;
}

void Forwarder::setWarningActor(Actor<std::string> value)
{
  warningActor = value;
}

void Forwarder::setSender(Forwarder::Sender value)
{
  sender = value;
}

