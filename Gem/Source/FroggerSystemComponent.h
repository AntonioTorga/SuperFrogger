
#pragma once

#include <AzCore/Component/Component.h>

#include <Frogger/FroggerBus.h>

namespace Frogger
{
    class FroggerSystemComponent
        : public AZ::Component
        , protected FroggerRequestBus::Handler
    {
    public:
        AZ_COMPONENT(FroggerSystemComponent, "{5C20293E-1892-4202-9550-9A0225DD0D55}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        FroggerSystemComponent();
        ~FroggerSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // FroggerRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
