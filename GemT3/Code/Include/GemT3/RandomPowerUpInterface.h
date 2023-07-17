
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace GemT3
{
    class RandomPowerUpRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(GemT3::RandomPowerUpRequests, "{B4A0D478-FFE3-438C-905C-2B3ACAD1F598}");

        // Put your public request methods here.
        
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using RandomPowerUpRequestBus = AZ::EBus<RandomPowerUpRequests>;

} // namespace GemT3
