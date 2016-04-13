/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "StackFactory.h"

namespace StackFactory
{

static void connect(ProtocolStack &stack)
{
  stack.application->setSender([&stack](const Outgoing::Message &message){
    const auto encoded = stack.encoder(message);
    stack.session->send(encoded);
  });

  stack.session->setMessageCallback([&stack](const std::string &message){
    const auto decoded = stack.decoder(message);
    stack.application->received(decoded);
  });
}

static ProtocolStack initialize(const Configuration &configuration)
{
  ProtocolStack stack;
  stack.session = std::unique_ptr<Session>{configuration.session};
  stack.encoder = configuration.presentation.first;
  stack.decoder = configuration.presentation.second;
  std::unique_ptr<Application> application{configuration.application};
  stack.application = std::unique_ptr<ActiveApplication>{new ActiveApplication(std::move(application))};

  return stack;
}

ProtocolStack produce(const Configuration &configuration)
{
  ProtocolStack stack = initialize(configuration);
  connect(stack);
  return stack;
}

}
