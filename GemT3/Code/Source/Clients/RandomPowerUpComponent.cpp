
#include "RandomPowerUpComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzFramework/Physics/CollisionBus.h>
#include <AzFramework/Physics/RigidBodyBus.h>
#include <AzCore/Component/TransformBus.h>
#include <string>
#include <cstdlib>


namespace GemT3
{
    void RandomPowerUpComponent::Activate()
    {
        AZ_Printf("RandomPowerUpComponent", "Activando...");
        //Setting default values for Collision Group and Uniform Scale.
        AZ::TransformBus::EventResult(mOriginalScale, GetEntityId(), &AZ::TransformBus::Events::GetWorldUniformScale);
        Physics::CollisionFilteringRequestBus::EventResult(mOriginalCollisionGroup, GetEntityId(), &Physics::CollisionFilteringRequestBus::Events::GetCollisionGroupName);
        //Bus Connections.
        AZ::TickBus::Handler::BusConnect();
        RandomPowerUpRequestBus::Handler::BusConnect(GetEntityId());
        //Randomizer setup.
        srand((unsigned int)time(NULL));
        //Setting up lists for choosing random PowerUp and track timers.
        if (mTimeOfShrink > 0 && mShrinkSize != mOriginalScale) { mPowerUps.push_back("Shrink"); mTimers.push_back(-1); mSetTimers.push_back(mTimeOfShrink); }
        if (mTimeOfInvencible > 0 && mInvencibleCollisionGroup.c_str() != std::string("")) { mPowerUps.push_back("Invencible"); mTimers.push_back(-1); mSetTimers.push_back(mTimeOfInvencible); }
        if (mTimeOfGravityOff > 0) { mPowerUps.push_back("GravityOff"); mTimers.push_back(-1); mSetTimers.push_back(mTimeOfGravityOff);}
        if (mForceThrow > 0) mPowerUps.push_back("Throw");
    }

    void RandomPowerUpComponent::Deactivate()
    {
        AZ_Printf("RandomPowerUpComponent", "Desactivando...");
        AZ::TickBus::Handler::BusDisconnect();
        RandomPowerUpRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void RandomPowerUpComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<RandomPowerUpComponent, AZ::Component>()
                ->Field("Tiempo sin gravedad", &RandomPowerUpComponent::mTimeOfGravityOff)
                ->Field("Tiempo encogido", &RandomPowerUpComponent::mTimeOfShrink)
                ->Field("Tiempo invencibilidad", &RandomPowerUpComponent::mTimeOfInvencible)
                ->Field("Fuerza tiro", &RandomPowerUpComponent::mForceThrow)
                ->Field("Tamaño al achicarse", &RandomPowerUpComponent::mShrinkSize)
                ->Field("Nombre Group Invencible", &RandomPowerUpComponent::mInvencibleCollisionGroup)
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<RandomPowerUpComponent>("RandomPowerUpComponent", "[Description of functionality provided by this component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "ComponentCategory")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->DataElement(nullptr, &RandomPowerUpComponent::mTimeOfGravityOff, "Tiempo sin gravedad", "[Tiempo en el que la gravedad se desactiva como efecto de PowerUp.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mTimeOfShrink, "Tiempo encogido", "[Tiempo que dura encogido como efecto de PowerUp.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mTimeOfInvencible, "Tiempo invencibilidad", "[Tiempo que dura invencible como efecto de PowerUp.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mForceThrow,"Fuerza tiro", "[Fuerza con la que se tira.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mShrinkSize, "Tamano al achicarse", "[Escala a la que se transforma cuando el objeto se achica.]")
                    ->DataElement(nullptr, &RandomPowerUpComponent::mInvencibleCollisionGroup, "Nombre Group Invencible", "[Nombre de Group donde colisiona solo con el ambiente y no enemigos ni balas.]")
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

    //Override from TickBus, called every tick.
    void RandomPowerUpComponent::OnTick(float dt, AZ::ScriptTimePoint)
    {
        mCurrentTime += dt;
        for (int i = 0; i < mTimers.size(); i++)
        {
            if (mTimers[i] > 0 && mTimers[i] < mCurrentTime)
            {
                RandomPowerUpComponent::SetBack(mPowerUps[i]);
                mTimers[i] = -1;
            }
        }
    }

    //Chooses a random power up to give to the player, callable from ScriptCanvas.
    void GemT3::RandomPowerUpComponent::GetRandomPowerUp()
    {
        int random_number = rand() % mPowerUps.size();
        std::string chosen = mPowerUps[random_number];
        if (chosen == "Throw")
        {
            AZ_Printf("RandomPowerUpComponent", "Throwing to");
            GemT3::RandomPowerUpComponent::Throw();
            return;
        }
        else if (chosen == "GravityOff")
        {
            AZ_Printf("RandomPowerUpComponent", "Turning off gravity");
            GemT3::RandomPowerUpComponent::GravityOff();
        }
        else if (chosen == "Shrink") {
            AZ_Printf("RandomPowerUpComponent", "Shrinking to: %f", mShrinkSize);
            GemT3::RandomPowerUpComponent::Shrink();
        }
        else if (chosen == "Invencible") {
            AZ_Printf("RandomPowerUpComponent", "Making invincible");
            GemT3::RandomPowerUpComponent::Invencibility();
        }
        mTimers[random_number] = mSetTimers[random_number]+mCurrentTime;
        AZ_Printf("RandomPowerUpComponent", "Actual time: %f , Setted timer to: %f", mCurrentTime ,mTimers[random_number])
    }
    //Receives a string with the name of a powerup and turns that PowerUp off.
    void GemT3::RandomPowerUpComponent::SetBack(const std::string powerUp)
    {
        if (powerUp == "GravityOff") GemT3::RandomPowerUpComponent::GravityOn();
        else if (powerUp == "Shrink") GemT3::RandomPowerUpComponent::Enlarge();
        else if (powerUp == "Invencible") GemT3::RandomPowerUpComponent::Vulnerability();
    }
    //Throws the entity that owns the component.
    void GemT3::RandomPowerUpComponent::Throw() {
        int random_number = rand() % 100;
        AZ::Vector3 ThrowDirection;
        if (random_number < 50) ThrowDirection = AZ::Vector3(0, -1, 0);
        else{ ThrowDirection = AZ::Vector3(0, 1, 0); }

        Physics::RigidBodyRequestBus::Event(GemT3::RandomPowerUpComponent::GetEntityId(), &Physics::RigidBodyRequestBus::Events::ApplyLinearImpulse , ThrowDirection * mForceThrow);
    }
    //Turns gravity off for the entity that owns the component.
    void GemT3::RandomPowerUpComponent::GravityOff()
    {
        Physics::RigidBodyRequestBus::Event(GemT3::RandomPowerUpComponent::GetEntityId(), &Physics::RigidBodyRequestBus::Events::SetGravityEnabled, false);
    }
    //Turns gravity on for the entity that owns the component.
    void GemT3::RandomPowerUpComponent::GravityOn()
    {

        Physics::RigidBodyRequestBus::Event(GetEntityId(), &Physics::RigidBodyRequestBus::Events::SetGravityEnabled, true);
    }
    //Shrinks the entity that owns the component.
    void GemT3::RandomPowerUpComponent::Shrink()
    {

        AZ::TransformBus::Event(GetEntityId(), &AZ::TransformBus::Events::SetLocalUniformScale, mShrinkSize);
    }
    //Enlarges the entity that owns the component.
    void GemT3::RandomPowerUpComponent::Enlarge()
    {
        AZ::TransformBus::Event(GetEntityId(), &AZ::TransformBus::Events::SetLocalUniformScale, mOriginalScale);
    }
    //Turns the entity that owns the component invincible.
    void GemT3::RandomPowerUpComponent::Invencibility()
    {
        Physics::CollisionFilteringRequestBus::Event(GetEntityId(), &Physics::CollisionFilteringRequestBus::Events::SetCollisionGroup, mInvencibleCollisionGroup, AZ::Crc32());
    }
    //Turns the entity that owns the component vulnerable.
    void GemT3::RandomPowerUpComponent::Vulnerability()
    {
        Physics::CollisionFilteringRequestBus::Event(GetEntityId(), &Physics::CollisionFilteringRequestBus::Events::SetCollisionGroup, mOriginalCollisionGroup, AZ::Crc32());
    }
    //Sets everything to normal, callable from ScriptCanvas.
    void GemT3::RandomPowerUpComponent::SetToNormal()
    {
        AZ_Printf("RandomPowerUpComponent", "Turning normal");
        GemT3::RandomPowerUpComponent::GravityOn();
        GemT3::RandomPowerUpComponent::Enlarge();
        GemT3::RandomPowerUpComponent::Vulnerability();

        for (int i = 0; i < mTimers.size(); i++)
        {
            mTimers[i] = -1;
        }
    }

} // namespace GemT3
