namespace Gnik_luos {
    // 火山的唯一取用口:引用别名只在 Window_vulkan 内部出现一次,外面一律走这里
    // 没 init 就调用属于用法错误(和原来直接解引用 vulkan 指针一样),这里显式抛出来
    Vulkan& Window_vulkan::vulkan_engine() {
        if (vulkan_borrowed == nullptr) {
            throw std::runtime_error("Window_vulkan::vulkan_engine => Vulkan engine not attached yet");
        }
        return *vulkan_borrowed;
    }
}
