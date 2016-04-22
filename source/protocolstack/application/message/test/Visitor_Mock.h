/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_VISITOR_MOCK
#define MESSAGE_VISITOR_MOCK

#include "../Visitor.h"

#include <vector>

class VisitorMock :
    public message::Visitor
{
public:
  typedef std::vector<std::pair<message::Property, const message::Value<double>*>> VisitDouble;
  VisitDouble visitDouble{};

  void visit(message::Property property, const message::Value<double> &value) override
  {
    visitDouble.emplace_back(property, &value);
  }

  typedef std::vector<std::pair<message::Property, const message::Value<std::string>*>> VisitString;
  VisitString visitString{};

  void visit(message::Property property, const message::Value<std::string> &value) override
  {
    visitString.emplace_back(property, &value);
  }


};

#endif
