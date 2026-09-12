vk::DebugUtilsMessageSeverityFlagsEXT severity{
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
};
vk::DebugUtilsMessageTypeFlagsEXT message_type{
    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
};
bool best_practices{true};
bool synchronization_validation{true};
const void* pnext{nullptr};
