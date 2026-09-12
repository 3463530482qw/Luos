vk::raii::Context context;
std::vector<const char*> layers;
vk::ValidationFeaturesEXT validation_features;
vk::DebugUtilsMessengerCreateInfoEXT debug_create_info;
#ifndef NDEBUG
    vk::raii::DebugUtilsMessengerEXT debug_messenger{nullptr};
#endif
