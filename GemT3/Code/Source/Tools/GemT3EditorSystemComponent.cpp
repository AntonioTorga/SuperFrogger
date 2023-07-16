
#include <AzCore/Serialization/SerializeContext.h>
#include "GemT3EditorSystemComponent.h"

namespace GemT3
{
    void GemT3EditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<GemT3EditorSystemComponent, GemT3SystemComponent>()
                ->Version(0);
        }
    }

    GemT3EditorSystemComponent::GemT3EditorSystemComponent() = default;

    GemT3EditorSystemComponent::~GemT3EditorSystemComponent() = default;

    void GemT3EditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("GemT3EditorService"));
    }

    void GemT3EditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("GemT3EditorService"));
    }

    void GemT3EditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void GemT3EditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void GemT3EditorSystemComponent::Activate()
    {
        GemT3SystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void GemT3EditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        GemT3SystemComponent::Deactivate();
    }

} // namespace GemT3
