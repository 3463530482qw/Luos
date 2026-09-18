namespace Gnik_luos {
    void Vulkan_swapchain::create(const vk::raii::PhysicalDevice& physical_device, const vk::raii::Device& device) {
        auto capabilities = physical_device.getSurfaceCapabilitiesKHR(*surface);
        auto formats = physical_device.getSurfaceFormatsKHR(*surface);
        auto present_modes = physical_device.getSurfacePresentModesKHR(*surface);

        if (capabilities.minImageExtent.width == 0 || capabilities.minImageExtent.height == 0 ||
            capabilities.maxImageExtent.width == 0 || capabilities.maxImageExtent.height == 0) {
            // 最小化时表面能力归 0:必须原样抛 vk 的 OutOfDate,draw_frame 里那两个 catch 才接得住
            // (包成 std::runtime_error 会被切片,异常直接冲出窗口循环)
            throw vk::OutOfDateKHRError("surface is not ready");
        }

        vk::SurfaceFormatKHR chosen_format;
        if (formats.size() == 1 && formats[0].format == vk::Format::eUndefined) {
            chosen_format.format = vk::Format::eB8G8R8A8Srgb;
            chosen_format.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
        } else {
            chosen_format = formats[0];
            for (const auto& candidate : formats) {
                bool srgb_format = candidate.format == vk::Format::eB8G8R8A8Srgb;
                bool srgb_colorspace = candidate.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
                if (srgb_format && srgb_colorspace) {
                    chosen_format = candidate;
                    break;
                }
            }
        }
        format = chosen_format.format;

        // 三重缓冲优先,回退到必然可用的 FIFO
        vk::PresentModeKHR chosen_present_mode = vk::PresentModeKHR::eFifo;
        for (const auto& candidate : present_modes) {
            if (candidate == vk::PresentModeKHR::eMailbox) {
                chosen_present_mode = candidate;
                break;
            }
        }

        extent.width = std::clamp(*width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        extent.height = std::clamp(*height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        preferred_image_count = capabilities.minImageCount + 1;
        if (capabilities.maxImageCount > 0 && preferred_image_count > capabilities.maxImageCount) {
            preferred_image_count = capabilities.maxImageCount;
        }

        vk::SwapchainCreateInfoKHR create_info;
        create_info.setSurface(*surface);
        create_info.setMinImageCount(preferred_image_count);
        create_info.setImageFormat(chosen_format.format);
        create_info.setImageColorSpace(chosen_format.colorSpace);
        create_info.setImageExtent(extent);
        create_info.setImageArrayLayers(1);
        create_info.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
        create_info.setImageSharingMode(vk::SharingMode::eExclusive);
        create_info.setPreTransform(capabilities.currentTransform);
        create_info.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
        create_info.setPresentMode(chosen_present_mode);
        create_info.setClipped(true);

        swapchain = vk::raii::SwapchainKHR(device, create_info);
        images = swapchain.getImages();
    }
}