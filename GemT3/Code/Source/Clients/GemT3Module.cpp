

#include <GemT3ModuleInterface.h>
#include "GemT3SystemComponent.h"

namespace GemT3
{
    class GemT3Module
        : public GemT3ModuleInterface
    {
    public:
        AZ_RTTI(GemT3Module, "{09B2F92B-15C4-4A4A-88B2-5B1984ADD5FE}", GemT3ModuleInterface);
        AZ_CLASS_ALLOCATOR(GemT3Module, AZ::SystemAllocator, 0);
    };
}// namespace GemT3

AZ_DECLARE_MODULE_CLASS(Gem_GemT3, GemT3::GemT3Module)
