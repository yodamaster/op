/*

 Copyright (c) 2013, SMB Phone Inc.
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

#include <openpeer/stack/message/IMessageFactory.h>


namespace openpeer
{
  namespace stack
  {
    namespace message
    {
      namespace identity
      {
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        #pragma mark
        #pragma mark MessageFactoryIdentity
        #pragma mark

        class MessageFactoryIdentity : public IMessageFactory
        {
        public:
          enum Methods
          {
            Method_Invalid = Message::Method_Invalid,

            Method_IdentityAccessWindow,
            Method_IdentityAccessStart,
            Method_IdentityAccessComplete,
            Method_IdentityAccessLockboxUpdate,
            Method_IdentityAccessRolodexCredentialsGetUpdate,
            Method_IdentityLookupUpdate,
            Method_IdentitySign,

            Method_Last = Method_IdentitySign,
          };

        protected:
          static MessageFactoryIdentityPtr create();

        public:
          static MessageFactoryIdentityPtr singleton();

          //-------------------------------------------------------------------
          #pragma mark
          #pragma mark MessageFactoryIdentity => IMessageFactory
          #pragma mark

          virtual const char *getHandler() const;

          virtual Message::Methods toMethod(const char *method) const;
          virtual const char *toString(Message::Methods method) const;

          virtual MessagePtr create(
                                    ElementPtr root,
                                    IMessageSourcePtr messageSource
                                    );
        };
      }
    }
  }
}