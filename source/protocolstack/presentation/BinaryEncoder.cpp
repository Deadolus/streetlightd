/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryEncoder.h"

#include "Binary.h"

#include <protocolstack/application/message/Printer.h>
#include <protocolstack/application/message/PrintFormat.h>

#include <cmath>

namespace Binary
{

class Format :
    public message::PrintFormat
{
public:
  typedef std::function<int(message::Property)> PropertyNumberGetter;

  Format(std::vector<uint8_t> &_output, PropertyNumberGetter _propertyNumber) :
    output{_output},
    propertyNumber{_propertyNumber}
  {
  }

  void writeValue(double value) override
  {
    output.push_back(uint8_t(std::round(value * 255)));
  }

  void writeValue(const std::string &value) override
  {
    output.push_back(value.size());
    output.insert(output.end(), value.begin(), value.end());
  }

  void writeKey(message::Property key) override
  {
    output.push_back(propertyNumber(key));
  }

  void writeKeyValueSeparator() override
  {
  }

  void writeSeparator(bool) override
  {
  }

private:
  std::vector<uint8_t> &output;
  PropertyNumberGetter propertyNumber{};

};

presentation::Message encode(const message::Outgoing &message)
{
  std::vector<uint8_t> data{};
  Format format{data, Binary::propertyNumber};
  message::Printer printer{format};

  message.accept(printer);

  return presentation::Message{data};
}

}
