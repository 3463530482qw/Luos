namespace Gnik_luos {
    void Vulkan_texture::destroy() {
        slot.clear();   // 槽位里的池与描述符一起放:集的释放靠池还在,raii 按成员声明序析构(池在集之后)
        descriptor_layout = nullptr;
        image_cache.clear();   // 像素归缓存所有,这里一并还回去
    }
}
