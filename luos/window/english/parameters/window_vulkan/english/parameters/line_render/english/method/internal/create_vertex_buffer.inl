namespace Gnik_luos {
    void Vulkan_line_render::create_vertex_buffer(size_t bytes) {
        vk::BufferCreateInfo buffer_info;
        buffer_info.setSize(bytes);
        buffer_info.setUsage(vk::BufferUsageFlagBits::eVertexBuffer);
        buffer_info.setSharingMode(vk::SharingMode::eExclusive);

        for (uint32_t index = 0; index < 2; index++) {
            vertex_buffer[index] = vk::raii::Buffer((*vulkan)->device, buffer_info);
            vk::MemoryRequirements requirement = vertex_buffer[index].getMemoryRequirements();
            vk::MemoryAllocateInfo allocate_info;
            allocate_info.setAllocationSize(requirement.size);
            allocate_info.setMemoryTypeIndex(find_memory_type(
                requirement.memoryTypeBits,
                vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
            ));
            vertex_memory[index] = vk::raii::DeviceMemory((*vulkan)->device, allocate_info);
            vertex_buffer[index].bindMemory(*vertex_memory[index], 0);
        }
        vertex_capacity = bytes;
    }
}
