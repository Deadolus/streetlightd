/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Forwarder.h"

void Forwarder::timeout()
{
  Outgoing::Message message;

  message[Outgoing::Type::Brightness] = brightnessSensor();

  sender(message);
}

void Forwarder::received(const Incoming::Message &message)
{
  const auto luminosity = message.find(Incoming::Type::Luminosity);   //TODO use contains
  if (luminosity != message.end()) {
    luminosityActor(luminosity->second);
  }
}

void Forwarder::setBrightnessSensor(Forwarder::Sensor value)
{
  brightnessSensor = value;
}

void Forwarder::setLuminosityActor(Forwarder::Actor value)
{
  luminosityActor = value;
}

void Forwarder::setSender(Forwarder::Sender value)
{
  sender = value;
}

