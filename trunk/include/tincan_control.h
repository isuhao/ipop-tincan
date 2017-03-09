/*
* ipop-project
* Copyright 2016, University of Florida
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#ifndef TINCAN_TINCAN_CONTROL_H_
#define TINCAN_TINCAN_CONTROL_H_
#include "tincan_base.h"
#pragma warning( push )
#pragma warning(disable:4996)
#include "webrtc/base/json.h"
#include "webrtc/base/socketaddress.h"
#pragma warning( pop )

namespace tincan {
using namespace rtc;

class TincanControl
{
public:
enum ControlTypeEnum
{
  CTTincanRequest,
  CTTincanResponse,
  CTInvalid,
  CTMax = CTInvalid,
};
const array<const char*, 3> ControlTypeStrings = { {"TincanRequest", "TincanResponse", "control type invalid"} };

  TincanControl();
  TincanControl(unique_ptr<Json::Value> req);
  TincanControl(unique_ptr<Json::Value> req, unique_ptr<Json::Value> resp);
  TincanControl(const char * const req_data, const size_t len);
  TincanControl(TincanControl & ctrl);
  TincanControl(TincanControl && ctrl);
  ~TincanControl();
  TincanControl& operator= (TincanControl & rhs);
  TincanControl& operator= (TincanControl && rhs);

  Json::Value & GetRequest();
  void SetRequest(unique_ptr<Json::Value> req);

  Json::Value & GetResponse();
  void SetResponse(unique_ptr<Json::Value> resp);
  void SetResponse(const string & resp_msg, bool success);

  string GetCommand() const;
  void SetCommand(string cmd);

  uint64_t GetTransactionId() const;
  void SetTransactionId(uint64_t tag);

  ControlTypeEnum GetControlType() const;
  void SetControlType(ControlTypeEnum type);

  string StyledString();

  static uint64_t NextTagValue()
  {
    static uint64_t tincan_control_tag_value__ = 0;
    return ++tincan_control_tag_value__;
  }

  static const Json::StaticString AddRoutes;
  static const Json::StaticString Command;
  static const Json::StaticString CAS;
  static const Json::StaticString ConnectToPeer;
  static const Json::StaticString ControlType;
  static const Json::StaticString CreateCtrlRespLink;
  static const Json::StaticString CreateLinkListener;
  static const Json::StaticString CreateVnet;
  static const Json::StaticString Echo;
  static const Json::StaticString EncryptionEnabled;
  static const Json::StaticString Fingerprint;
  static const Json::StaticString ICC;
  static const Json::StaticString IgnoredNetInterfaces;
  static const Json::StaticString InterfaceName;
  static const Json::StaticString IPOP;
  static const Json::StaticString LogLevel;
  static const Json::StaticString MAC;
  static const Json::StaticString Message;
  static const Json::StaticString Data;
  static const Json::StaticString PeerInfo;
  static const Json::StaticString ProtocolVersion;
  static const Json::StaticString QueryNodeInfo;
  static const Json::StaticString QueryStunCandidates;
  static const Json::StaticString Recipient;
  static const Json::StaticString RecipientMac;
  static const Json::StaticString RemovePeer;
  static const Json::StaticString RemoveRoutes;
  static const Json::StaticString Request;
  static const Json::StaticString Response;
  static const Json::StaticString Routes;
  static const Json::StaticString UpdateRoutes;
  static const Json::StaticString Sender;
  static const Json::StaticString SetIgnoredNetInterfaces;
  static const Json::StaticString SetLoggingLevel;
  static const Json::StaticString Stats;
  static const Json::StaticString Status;
  static const Json::StaticString Success;
  static const Json::StaticString TincanRequest;
  static const Json::StaticString TincanResponse;
  static const Json::StaticString TransactionId;
  static const Json::StaticString Type;
  static const Json::StaticString VIP4;
  static const Json::StaticString VIP6;
  static const Json::StaticString UID;
  static const Json::StaticString VnetDescription;
private:
  uint32_t proto_ver_;
  uint64_t tag_;
  ControlTypeEnum type_;
  Json::Value * dict_req_;
  Json::Value * dict_resp_;
};
} // namespace tincan
#endif  // TINCAN_TINCAN_CONTROL_H_
