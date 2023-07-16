
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/GemT3SystemComponent.h>

namespace GemT3
{
    /// System component for GemT3 editor
    class GemT3EditorSystemComponent
        : public GemT3SystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = GemT3SystemComponent;
    public:
        AZ_COMPONENT(GemT3EditorSystemComponent, "{B776ADA4-262B-4E93-81AD-1035C99F22B8}", BaseSystemComponent);
        static void Reflect(AZ::ReflectContext* context);

        GemT3EditorSystemComponent();
        ~GemT3EditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace GemT3
