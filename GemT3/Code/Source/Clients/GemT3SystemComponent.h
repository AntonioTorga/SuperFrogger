
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <GemT3/GemT3Bus.h>

namespace GemT3
{
    class GemT3SystemComponent
        : public AZ::Component
        , protected GemT3RequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        AZ_COMPONENT(GemT3SystemComponent, "{DA11C18D-2BCC-457E-9C13-F188FDC8CDDF}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        GemT3SystemComponent();
        ~GemT3SystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // GemT3RequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZTickBus interface implementation
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
        ////////////////////////////////////////////////////////////////////////
    };

} // namespace GemT3
