/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonDecoder.h"

#include <jsoncpp/json/json.h>

namespace presentation
{
namespace json
{

static void write(message::Value<double> &value, const Json::Value &raw)
{
  value = raw.asDouble();
}

static void write(message::Value<std::string> &value, const Json::Value &raw)
{
  value = raw.asString();
}

template<typename T>
static void writeIfValid(message::Value<T> &destination, const Json::Value &value)
{
  if (!value.isNull()) {
    write(destination, value);
  }
}

message::Incoming decode(const presentation::Message &message)
{
  Json::Reader reader;
  Json::Value root;

  if (!reader.parse(message.asString(), root)) {
    throw std::invalid_argument("not valid json: " + message.asString());
  }

  message::Incoming result{};

  writeIfValid(result.luminosity, root["luminosity"]);
  writeIfValid(result.warning, root["warning"]);

  return result;
}

}
}
