
#pragma once

#include <AzCore/Component/Component.h>
#include <GemT3/RandomPowerUpInterface.h>
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>
#include <AZCore/Math/Vector3.h>
#include <AzCore/Component/TickBus.h>
#include <string>

namespace GemT3
{
    /*
    * TODO: Register this component in your Gem's AZ::Module interface by inserting the following into the list of m_descriptors:
    *       RandomPowerUpComponent::CreateDescriptor(),
    */

    class RandomPowerUpComponent
        : public AZ::Component
        , public RandomPowerUpRequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        AZ_COMPONENT(GemT3::RandomPowerUpComponent, "{102A6418-A623-45DA-A5BD-9B67CE926B90}");

        /*
        * Reflects component data into the reflection contexts, including the serialization, edit, and behavior contexts.
        */
        static void Reflect(AZ::ReflectContext* context);

        /*
        * Specifies the services that this component provides.
        * Other components can declare a dependency on these services. The system uses this
        * information to determine the order of component activation.
        */
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);

        /*
        * Specifies the services that this component requires.
        * The system activates the required services before it activates this component.
        * It also deactivates the required services after it deactivates this component.
        * If a required service is missing before this component is activated, the system
        * returns an error and does not activate this component.
        */
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);

        void OnTick(float dt, AZ::ScriptTimePoint) override;
        void GetRandomPowerUp() override;
        void SetToNormal() override;
        void Throw();
        void GravityOff();
        void Shrink();
        void Invencibility();

    protected:
        /*
        * Puts this component into an active state.
        * The system calls this function once during activation of each entity that owns the
        * component. You must override this function. The system calls a component's Activate()
        * function only if all services and components that the component depends on are present
        * and active.
        */
        void Activate() override;

        /*
        * Deactivates this component.
        * The system calls this function when the owning entity is being deactivated. You must
        * override this function. As a best practice, ensure that this function returns this component
        * to a minimal footprint. The order of deactivation is the reverse of activation, so your
        * component is deactivated before the components it depends on.
        *
        * The system always calls a component's Deactivate() function before destroying the component.
        * However, deactivation is not always followed by the destruction of the component. An entity and
        * its components can be deactivated and reactivated without being destroyed. Ensure that your
        * Deactivate() implementation can handle this scenario.
        */
        void Deactivate() override;

    private:
        float mForceThrow;
        float mOriginalScale;
        float mShrinkSize;
        float mCurrentTime = 0.f;
        float mTimer = -1;
        float mTimeOfPowerUp;
        AZStd::vector<float> mTimers;
        AZStd::string mOriginalCollisionGroup;
        AZStd::string mInvencibleCollisionGroup;
    };
} // namespace GemT3
