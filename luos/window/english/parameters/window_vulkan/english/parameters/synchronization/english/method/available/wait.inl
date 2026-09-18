namespace Gnik_luos {
    void Vulkan_synchronization::wait(const vk::raii::Device& device) {
        auto result = device.waitForFences({*frame_fence}, true, std::numeric_limits<uint64_t>::max());
        if (result != vk::Result::eSuccess) {
            throw std::runtime_error("Vulkan_synchronization::wait => Waiting for the frame fence failed");
        }
        device.resetFences({*frame_fence});
    }
}
