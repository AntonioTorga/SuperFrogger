
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <Clients/GemT3SystemComponent.h>
#include <Clients/ShootingSpawnerComponent.h>

namespace GemT3
{
    class GemT3ModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(GemT3ModuleInterface, "{6C137E69-9425-486F-B8BF-CCFC15221CEC}", AZ::Module);
        AZ_CLASS_ALLOCATOR(GemT3ModuleInterface, AZ::SystemAllocator, 0);

        GemT3ModuleInterface()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                GemT3SystemComponent::CreateDescriptor(),
                ShootingSpawnerComponent::CreateDescriptor(),
                });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<GemT3SystemComponent>(),
            };
        }
    };
}// namespace GemT3
