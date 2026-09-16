namespace Gnik_luos {
    void Vulkan::create_logical_device(uint32_t graphics_queue_family) {
        if (device != vk::raii::Device{nullptr}) {
            return;
        }

        std::vector<const char*> device_extension;
        for (const auto& extension : physical_device.enumerateDeviceExtensionProperties()) {
            if (strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
                device_extension.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
                break;
            }
        }
        if (device_extension.empty()) {
            throw std::runtime_error("Vulkan::create_logical_device => The device does not support VK_KHR_swapchain");
        }

        float queue_priority = 1.0f;
        vk::DeviceQueueCreateInfo queue_create_info;
        queue_create_info.setQueueFamilyIndex(graphics_queue_family);
        queue_create_info.setQueueCount(1);
        queue_create_info.setPQueuePriorities(&queue_priority);

        vk::PhysicalDeviceFeatures device_features;

        vk::DeviceCreateInfo create_info;
        create_info.setQueueCreateInfoCount(1);
        create_info.setPQueueCreateInfos(&queue_create_info);
        create_info.setPEnabledFeatures(&device_features);
        create_info.setEnabledExtensionCount(static_cast<uint32_t>(device_extension.size()));
        create_info.setPpEnabledExtensionNames(device_extension.data());

        device = vk::raii::Device(physical_device, create_info);
        graphics_queue = device.getQueue(graphics_queue_family, 0);
    }
}