namespace Gnik_luos {
    void Vulkan::pick_physical_device() {
        auto physical_devices = instance.enumeratePhysicalDevices();
        if (physical_devices.empty()) {
            throw std::runtime_error("Vulkan::pick_physical_device => No physical device supports Vulkan");
        }

        bool found = false;
        size_t best_index = 0;
        uint32_t best_score = 0;
        for (size_t index = 0; index < physical_devices.size(); index++) {
            bool support_swapchain = false;
            for (const auto& extension : physical_devices[index].enumerateDeviceExtensionProperties()) {
                if (strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
                    support_swapchain = true;
                    break;
                }
            }
            if (!support_swapchain) {
                continue;
            }
            uint32_t score = rate_physical_device(physical_devices[index]);
            if (!found || score > best_score) {
                found = true;
                best_index = index;
                best_score = score;
            }
        }
        if (!found) {
            throw std::runtime_error("Vulkan::pick_physical_device => No physical device supports VK_KHR_swapchain");
        }

        physical_device = std::move(physical_devices[best_index]);
    }
}
