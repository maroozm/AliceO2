// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// @file   RawParser.cxx
/// @author Matthias Richter
/// @since  2019-10-15
/// @brief  Generic parser for consecutive raw pages

#include "DPLUtils/RawParser.h"
#include "fmt/format.h"
#include <iostream>

namespace o2::framework::raw_parser
{

int RawParserHelper::sErrorMode = getenv("O2_DPL_RAWPARSER_ERRORMODE") ? atoi(getenv("O2_DPL_RAWPARSER_ERRORMODE")) : 1;
int RawParserHelper::sCheckIncompleteHBF = getenv("O2_DPL_RAWPARSER_CHECKINCOMPLETEHBF") ? atoi(getenv("O2_DPL_RAWPARSER_CHECKINCOMPLETEHBF")) : 1;
unsigned long RawParserHelper::sErrors = 0;
unsigned long RawParserHelper::sErrorLimit = getenv("O2_DPL_RAWPARSER_ERRORLIMIT") ? atoi(getenv("O2_DPL_RAWPARSER_ERRORLIMIT")) : 5;
unsigned long RawParserHelper::sErrorScale = 1;

bool RawParserHelper::checkPrintError(size_t& localCounter)
{
  localCounter++;
  sErrors++;
  if (sErrorLimit == 0) {
    return false;
  }
  if (sErrors > sErrorLimit * sErrorScale) {
    sErrorScale *= 10;
  }
  return sErrors % sErrorScale == 0;
}

const char* RDHFormatter<V7>::sFormatString = "{:>5} {:>4} {:>4} {:>4} {:>4} {:>3} {:>3} {:>3}  {:>1} {:>2}";
void RDHFormatter<V7>::apply(std::ostream& os, V7 const& header, FormatSpec choice, const char* delimiter)
{
  if (choice == FormatSpec::Info) {
    os << "RDH v7";
  } else if (choice == FormatSpec::TableHeader) {
    os << fmt::format(sFormatString, "PkC", "pCnt", "fId", "sId", "Mem", "CRU", "EP", "LID", "s", "df");
  } else if (choice == FormatSpec::Entry) {
    os << fmt::format(sFormatString,
                      header.packetCounter,
                      header.pageCnt,
                      header.feeId,
                      header.sourceID,
                      header.memorySize,
                      header.cruID,
                      header.endPointID,
                      header.linkID,
                      header.stop,
                      header.dataFormat);
  }
  os << delimiter;
}
const char* RDHFormatter<V6>::sFormatString = "{:>5} {:>4} {:>4} {:>4} {:>4} {:>3} {:>3} {:>3}  {:>1}";
void RDHFormatter<V6>::apply(std::ostream& os, V6 const& header, FormatSpec choice, const char* delimiter)
{
  if (choice == FormatSpec::Info) {
    os << "RDH v6";
  } else if (choice == FormatSpec::TableHeader) {
    os << fmt::format(sFormatString, "PkC", "pCnt", "fId", "sId", "Mem", "CRU", "EP", "LID", "s");
  } else if (choice == FormatSpec::Entry) {
    os << fmt::format(sFormatString,
                      header.packetCounter,
                      header.pageCnt,
                      header.feeId,
                      header.sourceID,
                      header.memorySize,
                      header.cruID,
                      header.endPointID,
                      header.linkID,
                      header.stop);
  }
  os << delimiter;
}

const char* RDHFormatter<V5>::sFormatString = "{:>5} {:>4} {:>4} {:>4} {:>3} {:>3} {:>3}  {:>1}";
void RDHFormatter<V5>::apply(std::ostream& os, V5 const& header, FormatSpec choice, const char* delimiter)
{
  if (choice == FormatSpec::Info) {
    os << "RDH v5";
  } else if (choice == FormatSpec::TableHeader) {
    os << fmt::format(sFormatString, "PkC", "pCnt", "fId", "Mem", "CRU", "EP", "LID", "s");
  } else if (choice == FormatSpec::Entry) {
    os << fmt::format(sFormatString,
                      header.packetCounter,
                      header.pageCnt,
                      header.feeId,
                      header.memorySize,
                      header.cruID,
                      header.endPointID,
                      header.linkID,
                      header.stop);
  }
  os << delimiter;
}

const char* RDHFormatter<V4>::sFormatString = "{:>5} {:>4} {:>4} {:>4} {:>3} {:>3} {:>3} {:>10} {:>5}  {:>1}";
void RDHFormatter<V4>::apply(std::ostream& os, V4 const& header, FormatSpec choice, const char* delimiter)
{
  if (choice == FormatSpec::Info) {
    os << "RDH v4";
  } else if (choice == FormatSpec::TableHeader) {
    os << fmt::format(sFormatString, "PkC", "pCnt", "fId", "Mem", "CRU", "EP", "LID", "HBOrbit", "HBBC", "s");
  } else if (choice == FormatSpec::Entry) {
    os << fmt::format(sFormatString,
                      header.packetCounter,
                      header.pageCnt,
                      header.feeId,
                      header.memorySize,
                      header.cruID,
                      header.endPointID,
                      header.linkID,
                      header.heartbeatOrbit,
                      header.heartbeatBC,
                      header.stop);
  }
  os << delimiter;
}

} // namespace o2::framework::raw_parser
