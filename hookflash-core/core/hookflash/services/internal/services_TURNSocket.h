/*
 
 Copyright (c) 2012, SMB Phone Inc.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 
 */

#pragma once

#include <hookflash/services/ITURNSocket.h>
#include <hookflash/services/ISTUNRequester.h>
#include <hookflash/services/IDNS.h>
#include <hookflash/services/internal/hookflashTypes.h>
#include <zsLib/MessageQueueAssociator.h>
#include <zsLib/ISocket.h>
#include <zsLib/Timer.h>

#define HOOKFLASH_SERVICES_TURN_MAX_CHANNEL_DATA_IN_BYTES ((1 << (sizeof(WORD)*8)) - 1)

// *** DEBUGGING ONLY - DO _NOT_ ENABLE OTHERWISE ***
// #define HOOKFLASH_SERVICES_TURNSOCKET_DEBUGGING_FORCE_USE_TURN_TCP

// *** DEBUGGING ONLY - DO _NOT_ ENABLE OTHERWISE ***
// #define HOOKFLASH_SERVICES_TURNSOCKET_DEBUGGING_FORCE_USE_TURN_WITH_UDP
// #define HOOKFLASH_SERVICES_TURNSOCKET_DEBUGGING_FORCE_USE_TURN_WITH_SERVER_IP "23.22.109.183"

#include <list>
#include <map>
#include <utility>

namespace hookflash
{
  namespace services
  {
    namespace internal
    {
      interaction ITURNSocketAsyncDelegate
      {
        virtual void onStep() = 0;
      };

      class TURNSocket : public zsLib::MessageQueueAssociator,
                         public ITURNSocket,
                         public ITURNSocketAsyncDelegate,
                         public ISTUNRequesterDelegate,
                         public IDNSDelegate,
                         public zsLib::ISocketDelegate,
                         public zsLib::ITimerDelegate
      {
      public:
        typedef zsLib::BYTE BYTE;
        typedef zsLib::DWORD DWORD;
        typedef zsLib::ULONG ULONG;
        typedef zsLib::String String;
        typedef zsLib::Time Time;
        typedef zsLib::IPAddress IPAddress;
        typedef zsLib::RecursiveLock RecursiveLock;
        typedef zsLib::ISocketPtr ISocketPtr;
        typedef zsLib::SocketPtr SocketPtr;
        typedef zsLib::TimerPtr TimerPtr;
        typedef boost::shared_array<BYTE> RecycledPacketBuffer;
        typedef std::list<RecycledPacketBuffer> RecycledPacketBufferList;
        typedef std::list<IPAddress> IPAddressList;
        typedef IDNS::SRVResultPtr SRVResultPtr;

        struct Server;
        typedef boost::shared_ptr<Server> ServerPtr;

        struct Permission;
        typedef boost::shared_ptr<Permission> PermissionPtr;

        struct ChannelInfo;
        typedef boost::shared_ptr<ChannelInfo> ChannelInfoPtr;

      protected:

        TURNSocket(
                   IMessageQueuePtr queue,
                   ITURNSocketDelegatePtr delegate,
                   const char *turnServer,
                   const char *turnServerUsername,
                   const char *turnServerPassword,
                   bool useChannelBinding,
                   WORD limitChannelToRangeStart,
                   WORD limitChannelRoRangeEnd
                   );

        TURNSocket(
                   IMessageQueuePtr queue,
                   ITURNSocketDelegatePtr delegate,
                   IDNS::SRVResultPtr srvTURNUDP,
                   IDNS::SRVResultPtr srvTURNTCP,
                   const char *turnServerUsername,
                   const char *turnServerPassword,
                   bool useChannelBinding,
                   WORD limitChannelToRangeStart,
                   WORD limitChannelRoRangeEnd
                   );

        void init();

      public:
        ~TURNSocket();

        static TURNSocketPtr create(
                                    IMessageQueuePtr queue,
                                    ITURNSocketDelegatePtr delegate,
                                    const char *turnServer,
                                    const char *turnServerUsername,
                                    const char *turnServerPassword,
                                    bool useChannelBinding = false,
                                    WORD limitChannelToRangeStart = HOOKFLASH_SERVICES_TURN_CHANNEL_RANGE_START,
                                    WORD limitChannelRoRangeEnd = HOOKFLASH_SERVICES_TURN_CHANNEL_RANGE_END
                                    );

        static TURNSocketPtr create(
                                    IMessageQueuePtr queue,
                                    ITURNSocketDelegatePtr delegate,
                                    IDNS::SRVResultPtr srvTURNUDP,
                                    IDNS::SRVResultPtr srvTURNTCP,
                                    const char *turnServerUsername,
                                    const char *turnServerPassword,
                                    bool useChannelBinding = false,
                                    WORD limitChannelToRangeStart = HOOKFLASH_SERVICES_TURN_CHANNEL_RANGE_START,
                                    WORD limitChannelRoRangeEnd = HOOKFLASH_SERVICES_TURN_CHANNEL_RANGE_END
                                    );

        //ITURNSocket
        virtual PUID getID() const {return mID;}

        virtual TURNSocketStates getState() const;
        virtual TURNSocketErrors getLastError() const;

        virtual bool isRelayingUDP() const;

        virtual void shutdown();

        virtual bool sendPacket(
                                IPAddress destination,
                                const BYTE *buffer,
                                ULONG bufferLengthInBytes,
                                bool bindChannelIfPossible = false
                                );

        virtual IPAddress getRelayedIP();
        virtual IPAddress getReflectedIP();

        virtual bool handleSTUNPacket(
                                      IPAddress fromIPAddress,
                                      STUNPacketPtr turnPacket
                                      );

        virtual bool handleChannelData(
                                       IPAddress fromIPAddress,
                                       const BYTE *buffer,
                                       ULONG bufferLengthInBytes
                                       );

        virtual void notifyWriteReady();

        // ITURNSocketAsyncDelegate
        virtual void onStep();

        //ISTUNRequesterDelegate
        virtual void onSTUNRequesterSendPacket(
                                               ISTUNRequesterPtr requester,
                                               IPAddress destination,
                                               boost::shared_array<BYTE> packet,
                                               ULONG packetLengthInBytes
                                               );

        virtual bool handleSTUNRequesterResponse(
                                                 ISTUNRequesterPtr requester,
                                                 IPAddress fromIPAddress,
                                                 STUNPacketPtr response
                                                 );

        virtual void onSTUNRequesterTimedOut(ISTUNRequesterPtr requester);

        // IDNSDelegate
        virtual void onLookupCompleted(IDNSQueryPtr query);

        // ISocketDelegate
        virtual void onReadReady(ISocketPtr socket);
        virtual void onWriteReady(ISocketPtr socket);
        virtual void onException(ISocketPtr socket);

        // ITimer
        virtual void onTimer(TimerPtr timer);

      protected:
        bool isReady() const {return ITURNSocket::TURNSocketState_Ready ==  mCurrentState;}
        bool isShuttingDown() const {return ITURNSocket::TURNSocketState_ShuttingDown ==  mCurrentState;}
        bool isShutdown() const {return ITURNSocket::TURNSocketState_Shutdown ==  mCurrentState;}
        String log(const char *message) const;
        void fix(STUNPacketPtr stun) const;

        IPAddress stepGetNextServer(
                                    IPAddressList &previouslyAdded,
                                    SRVResultPtr &srv
                                    );
        bool stepPrepareServers();
        void step();
        void cancel();

        void setState(TURNSocketStates newState);

        void consumeBuffer(
                           ServerPtr &server,
                           ULONG bufferSizeInBytes
                           );

        bool handleAllocateRequester(
                                     ISTUNRequesterPtr requester,
                                     IPAddress fromIPAddress,
                                     STUNPacketPtr response
                                     );

        bool handleRefreshRequester(
                                    ISTUNRequesterPtr requester,
                                    STUNPacketPtr response
                                    );

        bool handleDeallocRequester(
                                    ISTUNRequesterPtr requester,
                                    STUNPacketPtr response
                                    );

        bool handlePermissionRequester(
                                       ISTUNRequesterPtr requester,
                                       STUNPacketPtr response
                                       );

        bool handleChannelRequester(
                                    ISTUNRequesterPtr requester,
                                    STUNPacketPtr response
                                    );

        void requestPermissionsNow();

        void refreshChannels();

        bool sendPacketOrDopPacketIfBufferFull(
                                               ServerPtr server,
                                               const BYTE *buffer,
                                               ULONG bufferSizeInBytes
                                               );

        bool sendPacketOverTCPOrDropIfBufferFull(
                                                 ServerPtr server,
                                                 const BYTE *buffer,
                                                 ULONG bufferSizeInBytes
                                                 );

        void informWriteReady();

        WORD getNextChannelNumber();

        ISTUNRequesterPtr handleAuthorizationErrors(ISTUNRequesterPtr requester, STUNPacketPtr response);

        void getBuffer(RecycledPacketBuffer &outBuffer);
        void recycleBuffer(RecycledPacketBuffer &buffer);

        class AutoRecycleBuffer
        {
        public:
          AutoRecycleBuffer(TURNSocket &outer, RecycledPacketBuffer &buffer) : mOuter(outer), mBuffer(buffer) {}
          ~AutoRecycleBuffer() {mOuter.recycleBuffer(mBuffer);}
        private:
          TURNSocket &mOuter;
          RecycledPacketBuffer &mBuffer;
        };

      public:
        struct Server
        {
          Server();
          ~Server();

          static ServerPtr create();

          bool mIsUDP;  // true for UDP, false for TCP
          IPAddress mServerIP;

          SocketPtr mTCPSocket;
          bool mIsConnected;
          bool mInformedWriteReady;

          Time mActivateAfter;

          ISTUNRequesterPtr mAllocateRequester;

          BYTE mReadBuffer[HOOKFLASH_SERVICES_TURN_MAX_CHANNEL_DATA_IN_BYTES+sizeof(DWORD)];
          ULONG mReadBufferFilledSizeInBytes;

          BYTE mWriteBuffer[HOOKFLASH_SERVICES_TURN_MAX_CHANNEL_DATA_IN_BYTES+sizeof(DWORD)];
          ULONG mWriteBufferFilledSizeInBytes;
        };

        class CompareIP { // simple comparison function
        public:
          bool operator()(const IPAddress &op1, const IPAddress &op2) const;
        };

        struct Permission
        {
          static PermissionPtr create();

          bool mInstalled;
          IPAddress mPeerAddress;
          Time mLastSentDataAt;
          ISTUNRequesterPtr mInstallingWithRequester;

          typedef std::list< std::pair<boost::shared_array<BYTE>, ULONG> > PendingDataList;
          PendingDataList mPendingData;
        };

        struct ChannelInfo
        {
          static ChannelInfoPtr create();

          bool mBound;
          WORD mChannelNumber;
          IPAddress mPeerAddress;
          Time mLastSentDataAt;
          TimerPtr mRefreshTimer;
          ISTUNRequesterPtr mChannelBindRequester;
        };

      protected:
        mutable RecursiveLock mLock;
        TURNSocketWeakPtr mThisWeak;
        TURNSocketPtr mGracefulShutdownReference;
        PUID mID;

        TURNSocketStates mCurrentState;
        TURNSocketErrors mLastError;

        WORD mLimitChannelToRangeStart;
        WORD mLimitChannelToRangeEnd;

        ITURNSocketDelegatePtr mDelegate;

        String mServerName;
        String mUsername;
        String mPassword;
        String mRealm;
        String mNonce;

        IDNSQueryPtr mTURNUDPQuery;
        IDNSQueryPtr mTURNTCPQuery;

        SRVResultPtr mTURNUDPSRVResult;
        SRVResultPtr mTURNTCPSRVResult;

        bool mUseChannelBinding;

        IPAddress mAllocateResponseIP;
        IPAddress mRelayedIP;
        IPAddress mReflectedIP;

        ServerPtr mActiveServer;

        DWORD mLifetime;

        ISTUNRequesterPtr mRefreshRequester;

        TimerPtr mRefreshTimer;
        Time mLastSentDataToServer;
        Time mLastRefreshTimerWasSentAt;

        ISTUNRequesterPtr mDeallocateRequester;

        typedef std::list<ServerPtr> ServerList;
        ServerList mServers;
        TimerPtr mActivationTimer;

        typedef std::map<IPAddress, PermissionPtr, CompareIP> PermissionMap;
        PermissionMap mPermissions;
        TimerPtr mPermissionTimer;
        ISTUNRequesterPtr mPermissionRequester;
        ULONG mPermissionRequesterMaxCapacity;

        typedef std::map<IPAddress, ChannelInfoPtr, CompareIP> ChannelIPMap;
        typedef std::map<WORD, ChannelInfoPtr> ChannelNumberMap;

        ChannelIPMap mChannelIPMap;
        ChannelNumberMap mChannelNumberMap;

        RecycledPacketBufferList mRecycledBuffers;
      };
    }
  }
}

ZS_DECLARE_PROXY_BEGIN(hookflash::services::internal::ITURNSocketAsyncDelegate)
ZS_DECLARE_PROXY_METHOD_0(onStep)
ZS_DECLARE_PROXY_END()
