
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace Frogger
{
    class FroggerRequests
    {
    public:
        AZ_RTTI(FroggerRequests, "{A01555BB-A4DC-4769-A3D5-70986763FADA}");
        virtual ~FroggerRequests() = default;
        // Put your public methods here
    };

    class FroggerBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using FroggerRequestBus = AZ::EBus<FroggerRequests, FroggerBusTraits>;
    using FroggerInterface = AZ::Interface<FroggerRequests>;

} // namespace Frogger
