/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef KEYVALUEENCODER_H
#define KEYVALUEENCODER_H

#include "Session.h"

#include <application/Presentation.h>

class KeyValueEncoder :
    public Presentation
{
public:
  KeyValueEncoder(Session &session);

  void brightness(double value) override;

private:
  Session &session;

};

#endif
