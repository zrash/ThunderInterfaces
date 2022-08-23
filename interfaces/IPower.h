/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IPower : virtual public Core::IUnknown {
        enum { ID = ID_POWER };

        enum PCState : uint8_t {
            On = 1 /* @text:on */, // S0.
            ActiveStandby = 2 /* @text:activestandby */, // S1.
            PassiveStandby = 3 /* @text:passivestandby */, // S2.
            SuspendToRAM = 4 /* @text:suspendtoram */, // S3.
            Hibernate = 5 /* @text:hibernate */, // S4.
            PowerOff = 6 /* @text:poweroff */, // S5.
        };

        enum PCPhase : uint8_t {
            Before = 1,
            After  = 2
        };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_POWER_NOTIFICATION };

            virtual void StateChange(const PCState powerstate, const PCState destination, const PCPhase phase) = 0;
        };

        virtual void Register(IPower::INotification* sink) = 0;
        virtual void Unregister(IPower::INotification* sink) = 0;

        virtual PCState GetState() const = 0;
        virtual uint32_t SetState(const PCState powerstate, const uint32_t timeout) = 0;
        virtual void PowerKey() = 0;
    };
}
}

