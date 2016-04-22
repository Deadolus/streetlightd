/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SASTOKEN_H
#define SASTOKEN_H

#include <vector>
#include <string>
#include <functional>
#include <chrono>

class SasTokenFactory
{
public:
  typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> Time;
  typedef std::function<Time()> GetTime;

  static GetTime currentTimeReader();

  SasTokenFactory(const std::string &encodedKey, const std::string &scope);
  SasTokenFactory(const std::string &encodedKey, const std::string &scope, GetTime getTime);

  std::string produce() const;

private:
  std::vector<uint8_t> key;
  std::string scope;
  GetTime getTime;

  std::string calcExpirationString() const;

};

namespace sastoken
{

  std::vector<uint8_t> hash(const std::vector<uint8_t> &key, const std::string &secret);
  std::string encode(const std::vector<uint8_t> &data);
  std::vector<uint8_t> decode(const std::string &data);
  std::string urlEncode(const std::string &data);
  std::string sharedAccessSignature(const std::string &scope, const std::string &signature, const std::string &expiration, const std::string &keyname);
  std::string secret(const std::string &scope, const std::string &expiration);

}

#endif
