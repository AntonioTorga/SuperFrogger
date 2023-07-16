
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "FroggerSystemComponent.h"

namespace Frogger
{
    class FroggerModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(FroggerModule, "{58EA3F9C-6D5E-4B09-BD4A-F65EBE469E3D}", AZ::Module);
        AZ_CLASS_ALLOCATOR(FroggerModule, AZ::SystemAllocator, 0);

        FroggerModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                FroggerSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<FroggerSystemComponent>(),
            };
        }
    };
}// namespace Frogger

AZ_DECLARE_MODULE_CLASS(Gem_Frogger, Frogger::FroggerModule)
