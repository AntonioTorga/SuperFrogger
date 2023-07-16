
#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace GemT3
{
    class ShootingSpawnerRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(GemT3::ShootingSpawnerRequests, "{31720828-5E90-4E25-93A7-BEC29B7F9787}");

        // Put your public request methods here.
        virtual void shoot() = 0;
        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;
        
    };

    using ShootingSpawnerRequestBus = AZ::EBus<ShootingSpawnerRequests>;

} // namespace GemT3
