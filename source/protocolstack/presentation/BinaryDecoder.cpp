/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryDecoder.h"
#include "Decoder.h"

#include <protocolstack/application/message/propertyNumbers.h>
#include <protocolstack/application/message/Property.h>

#include <algorithm>
#include <list>

namespace presentation
{

namespace binary
{

class Parser :
    public presentation::Parser
{
public:
  Parser(const presentation::Message &message)
  {
    const auto values = message.asBinary();
    data = std::list<uint8_t>{values.cbegin(), values.cend()};
  }

  message::Property parseProperty() override
  {
    if (!hasMore()) {
      throw std::invalid_argument("no more data");
    }

    auto key = data.front();
    data.pop_front();
    if (key == message::propertyNumber(message::Property::Luminosity)) {
      return message::Property::Luminosity;
    }
    if (key == message::propertyNumber(message::Property::Warning)) {
      return message::Property::Warning;
    }
    throw std::invalid_argument("unknown property: " + std::to_string(key));
  }

  bool hasMore() const override
  {
    return !data.empty();
  }

  void parse(double &value) override
  {
    if (data.empty()) {
      throw std::invalid_argument("expected 1 byte, got nothing");
    }


    const int8_t raw = static_cast<int8_t>(data.front());
    data.pop_front();

    value = double(raw) / 100;
  }

  void parse(std::string &value) override
  {
    if (data.empty()) {
      throw std::invalid_argument("expected 1 byte, got nothing");
    }

    const uint8_t length = data.front();
    data.pop_front();

    if (data.size() < length) {
      throw std::invalid_argument("invalid length for string: " + std::to_string(length));
    }

    std::string text{};
    auto textEnd = data.begin();
    std::advance(textEnd, length);
    text.resize(length);
    std::transform(data.begin(), textEnd, text.begin(), [](uint8_t sym){return sym;});
    data.erase(data.begin(), textEnd);

    value = text;
  }



private:
  std::list<uint8_t> data;

};



message::Incoming decode(const presentation::Message &message)
{
  Parser parser{message};
  return decode(parser);
}

}
}
