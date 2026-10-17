namespace Gnik_luos {
    void Text::update() {
        const bool placeholder = face == nullptr;   // 没绑字体:改画默认字形贴图(不是不出顶点)
        if (!dirty) {
            if (placeholder) {
                return;   // 占位那一档没有"字体图集被别人改了"这回事:排一次就够
            }
            const std::shared_ptr<const Atlas_info> current = face->atlas(static_cast<double>(font_size));
            if (current == nullptr || current->revision == texture_revision) {
                return;   // 参数没动、图集也没被别的命令改动:顶点与贴图都还是上一次那份
            }
            dirty = true;   // 图集内容变了(有新字形烤进去):手上的 uv 与像素都过期了,重排
        }
        cache.clear();
        private_rebuild_route();   // 路由:按脏标记装这次要跑的步骤
        private_run_route();       // 分派:顺次跑步骤出顶点
        dirty = false;
    }
}
