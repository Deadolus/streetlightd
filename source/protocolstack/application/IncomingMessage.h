/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef INCOMINGMESSAGE_H
#define INCOMINGMESSAGE_H

#include "MessageValue.h"

namespace Incoming
{

  class Message
  {
  public:
    message::Value<double> luminosity{};

  };

}

#endif
