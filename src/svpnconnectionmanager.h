
#ifndef SJINGLE_SVPNCONNECTIONMANAGER_H_
#define SJINGLE_SVPNCONNECTIONMANAGER_H_
#pragma once

#include <string>
#include <map>
#include <set>

#include "talk/base/sigslot.h"
#include "talk/p2p/base/p2ptransport.h"
#include "talk/p2p/client/basicportallocator.h"
#include "talk/p2p/base/transportdescription.h"
#include "talk/p2p/base/transportchannelimpl.h"
#include "talk/base/opensslidentity.h"
#include "talk/p2p/base/dtlstransportchannel.h"
#include "talk/p2p/base/dtlstransport.h"
#include "talk/base/base64.h"

#include "xmppnetwork.h"

namespace sjingle {

static const int kDigestSize = 64;

class SvpnConnectionManager : public talk_base::MessageHandler,
                              public sigslot::has_slots<> {

 public:
  SvpnConnectionManager(SocialNetworkSenderInterface* social_sender,
                        talk_base::AsyncPacketSocket* socket,
                        talk_base::Thread* signaling_thread,
                        talk_base::Thread* worker_thread,
                        const std::string& uid);

  const std::string fingerprint() const { 
    return fingerprint_->GetRfc4752Fingerprint(); 
  }

  // Inherited from MessageHandler
  virtual void OnMessage(talk_base::Message* msg);

  // Signal handler for SocialNetworkSenderInterface
  virtual void HandlePeer(const std::string& uid, const std::string& data);

  // Signal handler for PacketSenderInterface
  virtual void HandlePacket(talk_base::AsyncPacketSocket* socket,
      const char* data, size_t len, const talk_base::SocketAddress& addr);

  // Signal handlers for TransportChannelImpl
  virtual void OnRequestSignaling(cricket::TransportChannelImpl* channel);
  virtual void OnCandidateReady(cricket::TransportChannelImpl* channel,
                                const cricket::Candidate& candidate);
  virtual void OnCandidatesAllocationDone(
      cricket::TransportChannelImpl* channel);
  virtual void OnRoleConflict(cricket::TransportChannelImpl* channel);
  virtual void OnReadableState(cricket::TransportChannel* channel);
  virtual void OnWritableState(cricket::TransportChannel* channel);
  virtual void OnReadPacket(cricket::TransportChannel* channel, 
                            const char* data, size_t len, int flags);
  virtual void OnRouteChange(cricket::TransportChannel* channel,
                             const cricket::Candidate& candidate);
  virtual void OnDestroyed(cricket::TransportChannel* channel);

  struct PeerState {
    int peer_idx;
    std::string uid;
    cricket::TransportChannelImpl* channel;
    std::set<std::string> addresses;
  };

 private:
  int peer_idx_;
  const std::string content_name_;
  SocialNetworkSenderInterface* social_sender_;
  talk_base::AsyncPacketSocket* socket_;
  std::map<std::string, PeerState> uid_map_;
  std::map<cricket::TransportChannel*, PeerState> channel_map_;
  std::set<std::string> addresses_;
  talk_base::SocketAddress stun_server_;
  talk_base::BasicNetworkManager network_manager_;
  cricket::BasicPortAllocator port_allocator_;
  talk_base::OpenSSLIdentity* identity_;
  talk_base::SSLFingerprint* fingerprint_;
  cricket::DtlsTransport<cricket::P2PTransport> transport_;
  cricket::TransportDescription* local_description_;
  cricket::TransportDescription* remote_description_;

  void HandlePeer_w(const std::string& uid, const std::string& data);
  void HandlePacket_w(const char* data, size_t len,
                      const talk_base::SocketAddress& addr);
  void SetRemoteFingerprint(const std::string& uid, 
                            const std::string& fingerprint);
  void CreateConnection(const std::string& uid, 
                        const std::string& fingerprint);
  void DeleteConnection(const std::string& uid);
  void AddPeerAddress(const std::string& uid, const std::string& addr_string);
  void DestroyChannel(cricket::TransportChannel* channel);

  std::string get_key(const std::string& uid) {
    return uid.substr(uid.size() - kResourceSize);
  }
};

}  // namespace sjingle

#endif  // SJINGLE_SVPNCONNECTIONMANAGER_H_

