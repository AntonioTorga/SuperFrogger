
#include "RandomPowerUpComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace GemT3
{
    void RandomPowerUpComponent::Activate()
    {
        RandomPowerUpRequestBus::Handler::BusConnect(GetEntityId());
    }

    void RandomPowerUpComponent::Deactivate()
    {
        RandomPowerUpRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void RandomPowerUpComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<RandomPowerUpComponent, AZ::Component>()
                ->Field("Fuerza tiro", &RandomPowerUpComponent::mForceThrow)
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<RandomPowerUpComponent>("RandomPowerUpComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->DataElement(nullptr, &RandomPowerUpComponent::mForceThrow,"Fuerza tiro", "[Fuerza con la que se tira]")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<RandomPowerUpComponent>("RandomPowerUp Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "GemT3 Gem Group")
                ;
        }
    }

    void RandomPowerUpComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("RandomPowerUpComponentService"));
    }

    void RandomPowerUpComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

} // namespace GemT3
