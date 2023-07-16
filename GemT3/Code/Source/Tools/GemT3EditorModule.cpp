
#include <GemT3ModuleInterface.h>
#include "GemT3EditorSystemComponent.h"

namespace GemT3
{
    class GemT3EditorModule
        : public GemT3ModuleInterface
    {
    public:
        AZ_RTTI(GemT3EditorModule, "{09B2F92B-15C4-4A4A-88B2-5B1984ADD5FE}", GemT3ModuleInterface);
        AZ_CLASS_ALLOCATOR(GemT3EditorModule, AZ::SystemAllocator, 0);

        GemT3EditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                GemT3EditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<GemT3EditorSystemComponent>(),
            };
        }
    };
}// namespace GemT3

AZ_DECLARE_MODULE_CLASS(Gem_GemT3, GemT3::GemT3EditorModule)
