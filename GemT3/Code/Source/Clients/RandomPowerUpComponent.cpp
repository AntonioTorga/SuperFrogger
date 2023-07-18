
#include "RandomPowerUpComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzFramework/Physics/CollisionBus.h>
#include <AzFramework/Physics/RigidBodyBus.h>
#include <AzCore/Component/TransformBus.h>
#include <string>


namespace GemT3
{
    void RandomPowerUpComponent::Activate()
    {
        AZ::TransformBus::EventResult(mOriginalScale, GetEntityId(), &AZ::TransformBus::Events::GetWorldUniformScale);
        Physics::CollisionFilteringRequestBus::EventResult(mOriginalCollisionGroup, GetEntityId(), &Physics::CollisionFilteringRequestBus::Events::GetCollisionGroupName);
        AZ_Printf("RandomPowerUpComponent", "Iniciando con escala: %f Collision Group: %s", mOriginalScale, mOriginalCollisionGroup.c_str());
        AZ_Printf("RandomPowerUpComponent", "Invencible Collision Group: %s", mInvencibleCollisionGroup.c_str());
        AZ::TickBus::Handler::BusConnect();
        RandomPowerUpRequestBus::Handler::BusConnect(GetEntityId());
    }

    void RandomPowerUpComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        RandomPowerUpRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void RandomPowerUpComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<RandomPowerUpComponent, AZ::Component>()
                ->Field("Fuerza tiro", &RandomPowerUpComponent::mForceThrow)
                ->Field("Tamaño al achicarse", &RandomPowerUpComponent::mShrinkSize)
                ->Field("Nombre Group Invencible", &RandomPowerUpComponent::mInvencibleCollisionGroup)
                ->Field("Tiempo de PowerUp", &RandomPowerUpComponent::mTimeOfPowerUp)
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<RandomPowerUpComponent>("RandomPowerUpComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->DataElement(nullptr, &RandomPowerUpComponent::mForceThrow,"Fuerza tiro", "[Fuerza con la que se tira.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mShrinkSize, "Tamano al achicarse", "[Escala a la que se transforma cuando el objeto se achica.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mInvencibleCollisionGroup, "Nombre Group Invencible", "[Nombre de Group donde colisiona solo con el ambiente y no enemigos ni balas.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mTimeOfPowerUp, "Tiempo de PowerUp", "[Tiempo de duración del PowerUp antes de volver a la normalidad.]")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->EBus<RandomPowerUpRequestBus>("RandomPowerUp Component Group")
                ->Attribute(AZ::Script::Attributes::Category, "GemT3 Gem Group")
                ->Event("GetRandomPowerUp",&RandomPowerUpRequestBus::Events::GetRandomPowerUp)
                ->Event("SetToNormal", &RandomPowerUpRequestBus::Events::SetToNormal)
                ;
        }
    }


    void RandomPowerUpComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("RandomPowerUpComponentService"));
    }

    void RandomPowerUpComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("TransformService"));
        required.push_back(AZ_CRC_CE("PhysicsRigidBodyService"));
    }

    void RandomPowerUpComponent::OnTick(float dt, AZ::ScriptTimePoint)
    {
        mCurrentTime += dt;
        if (mTimer > 0 && mCurrentTime > mTimer) {
            RandomPowerUpComponent::SetToNormal();
        }
    }


    void GemT3::RandomPowerUpComponent::GetRandomPowerUp()
    {
        int random_number = rand() % 100;
        if (random_number < 25) 
        {
            AZ_Printf("RandomPowerUpComponent", "Throwing to");
            GemT3::RandomPowerUpComponent::Throw();
        }
        else if (25 <= random_number && random_number < 50)
        {
            AZ_Printf("RandomPowerUpComponent", "Turning off gravity");
            GemT3::RandomPowerUpComponent::GravityOff();
        }
        else if (50 <= random_number && random_number < 75){
            AZ_Printf("RandomPowerUpComponent", "Shrinking to: %f", mShrinkSize);
            GemT3::RandomPowerUpComponent::Shrink();
        }
        else {
            AZ_Printf("RandomPowerUpComponent", "Making invincible");
            GemT3::RandomPowerUpComponent::Invencibility();
        }
        mTimer = mCurrentTime + mTimeOfPowerUp;
    }

    void GemT3::RandomPowerUpComponent::Throw() {
        int random_number = rand() % 100;

        AZ::Vector3 ThrowDirection;
        if (random_number < 50) ThrowDirection = AZ::Vector3(0, -1, 0);
        else{ ThrowDirection = AZ::Vector3(0, 1, 0); }
        Physics::RigidBodyRequestBus::Event(GetEntityId(), &Physics::RigidBodyRequestBus::Events::ApplyLinearImpulse , ThrowDirection * mForceThrow);
    }

    void GemT3::RandomPowerUpComponent::GravityOff()
    {
        Physics::RigidBodyRequestBus::Event(GetEntityId(), &Physics::RigidBodyRequestBus::Events::SetGravityEnabled, false);
    }

    void GemT3::RandomPowerUpComponent::Shrink()
    {
        AZ::TransformBus::Event(GetEntityId(), &AZ::TransformBus::Events::SetLocalUniformScale, mShrinkSize);
    }

    void GemT3::RandomPowerUpComponent::Invencibility()
    {
        Physics::CollisionFilteringRequestBus::Event(GetEntityId(), &Physics::CollisionFilteringRequestBus::Events::SetCollisionGroup, mInvencibleCollisionGroup, AZ::Crc32());
    }

    void GemT3::RandomPowerUpComponent::SetToNormal()
    {
        AZ_Printf("RandomPowerUpComponent", "Turning normal");
        Physics::RigidBodyRequestBus::Event(GetEntityId(), &Physics::RigidBodyRequestBus::Events::SetGravityEnabled, true);
        AZ::TransformBus::Event(GetEntityId(), &AZ::TransformBus::Events::SetLocalUniformScale, mOriginalScale);
        Physics::CollisionFilteringRequestBus::Event(GetEntityId(), &Physics::CollisionFilteringRequestBus::Events::SetCollisionGroup, mOriginalCollisionGroup, AZ::Crc32());
        mTimer = -1;
    }

} // namespace GemT3
