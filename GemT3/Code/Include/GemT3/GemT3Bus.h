
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace GemT3
{
    class GemT3Requests
    {
    public:
        AZ_RTTI(GemT3Requests, "{A983AB42-BA26-4886-A209-987EFE062D87}");
        virtual ~GemT3Requests() = default;
        // Put your public methods here
    };
    
    class GemT3BusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using GemT3RequestBus = AZ::EBus<GemT3Requests, GemT3BusTraits>;
    using GemT3Interface = AZ::Interface<GemT3Requests>;

} // namespace GemT3
