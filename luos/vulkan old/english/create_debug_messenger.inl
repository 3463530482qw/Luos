namespace Gnik_luos {
    #ifndef NDEBUG
        bool Vulkan::create_debug_messenger(Vulkan_info& vulkan_info) {
            auto available_layers = context.enumerateInstanceLayerProperties();
            for (const auto& layer : available_layers) {
                if (strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0) {
                    layers.push_back("VK_LAYER_KHRONOS_validation");
                    break;
                }
            }
            if (layers.empty()) {
                return false;
            }

            // 扩展不一定存在:确认可用后再启用,否则 vkCreateInstance 会直接失败
            auto available_extensions = context.enumerateInstanceExtensionProperties();
            bool support_debug_utils = false;
            for (const auto& extension : available_extensions) {
                if (strcmp(extension.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0) {
                    support_debug_utils = true;
                    break;
                }
            }
            if (!support_debug_utils) {
                return false;
            }
            vulkan_info.extension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

            // 启用项必须落在成员 vector 上:局部 vector 出函数即销毁,
            // validation_features 里的指针会变成悬垂(校验层会报枚举值越界 49)
            enabled_features = collect_validation_features(vulkan_info.debug_info);
            validation_features.setEnabledValidationFeatures(enabled_features);

            debug_create_info.setMessageSeverity(vulkan_info.debug_info.severity);
            debug_create_info.setMessageType(vulkan_info.debug_info.message_type);
            debug_create_info.setPfnUserCallback(debug_message_callback);
            debug_create_info.setPUserData(nullptr);
            // 实例创建期的消息靠这条 pNext 链兜住(此时 messenger 尚未建立)
            debug_create_info.setPNext(&validation_features);
            return true;
        }
    #else
        bool Vulkan::create_debug_messenger(Vulkan_info& vulkan_info) {
            return false;
        }
    #endif
}
