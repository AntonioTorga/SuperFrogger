
#include "GemT3SystemComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace GemT3
{
    void GemT3SystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<GemT3SystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<GemT3SystemComponent>("GemT3", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void GemT3SystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("GemT3Service"));
    }

    void GemT3SystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("GemT3Service"));
    }

    void GemT3SystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void GemT3SystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    GemT3SystemComponent::GemT3SystemComponent()
    {
        if (GemT3Interface::Get() == nullptr)
        {
            GemT3Interface::Register(this);
        }
    }

    GemT3SystemComponent::~GemT3SystemComponent()
    {
        if (GemT3Interface::Get() == this)
        {
            GemT3Interface::Unregister(this);
        }
    }

    void GemT3SystemComponent::Init()
    {
    }

    void GemT3SystemComponent::Activate()
    {
        GemT3RequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void GemT3SystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        GemT3RequestBus::Handler::BusDisconnect();
    }

    void GemT3SystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace GemT3
