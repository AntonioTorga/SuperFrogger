
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

#include "FroggerSystemComponent.h"

namespace Frogger
{
    void FroggerSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<FroggerSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<FroggerSystemComponent>("Frogger", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void FroggerSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("FroggerService"));
    }

    void FroggerSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("FroggerService"));
    }

    void FroggerSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void FroggerSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    FroggerSystemComponent::FroggerSystemComponent()
    {
        if (FroggerInterface::Get() == nullptr)
        {
            FroggerInterface::Register(this);
        }
    }

    FroggerSystemComponent::~FroggerSystemComponent()
    {
        if (FroggerInterface::Get() == this)
        {
            FroggerInterface::Unregister(this);
        }
    }

    void FroggerSystemComponent::Init()
    {
    }

    void FroggerSystemComponent::Activate()
    {
        FroggerRequestBus::Handler::BusConnect();
    }

    void FroggerSystemComponent::Deactivate()
    {
        FroggerRequestBus::Handler::BusDisconnect();
    }
}
