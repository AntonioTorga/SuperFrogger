
#include "ShootingSpawnerComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace GemT3
{
    void ShootingSpawnerComponent::Activate()
    {
        ShootingSpawnerRequestBus::Handler::BusConnect(GetEntityId());
        AZ_Printf("ShootingSpawner", "Activando Shooting Spawner.");
    }

    void ShootingSpawnerComponent::Deactivate()
    {
        ShootingSpawnerRequestBus::Handler::BusDisconnect(GetEntityId());
        AZ_Printf("ShootingSpawner", "Desactivando Shooting Spawner.")
    }

    void ShootingSpawnerComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<ShootingSpawnerComponent, AZ::Component>()
                ->Field("Velocidad inicial", &ShootingSpawnerComponent::mVelocity)
                ->Field("Prefab", &ShootingSpawnerComponent::mSpawnableAsset)
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<ShootingSpawnerComponent>("ShootingSpawnerComponent", "[Componente que instancia un prefab con velocidad inicial.]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->DataElement(nullptr, &ShootingSpawnerComponent::mVelocity, "Velocidad inicial", "[Float usado como velocidad inicial para el proyectil.]")
                    ->DataElement(nullptr, &ShootingSpawnerComponent::mSpawnableAsset, "Prefab", "[PrefabXD]")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->EBus<ShootingSpawnerRequestBus>("ShootingSpawner Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "GemT3")
                ->Event("shoot", &ShootingSpawnerRequestBus::Events::shoot)
                ;
        }
    }
    void GemT3::ShootingSpawnerComponent::shoot()
    {
        AZ_Printf("ShootingSpawner", "bangbang %f", mVelocity);
    }

    void ShootingSpawnerComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("ShootingSpawnerComponentService"));
    }

    void ShootingSpawnerComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
    }

    void ShootingSpawnerComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void ShootingSpawnerComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
} // namespace GemT3
