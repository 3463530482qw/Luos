namespace Gnik_luos {
    void Picture::update() {
        if (!dirty) {
            return;   // 参数没动:顶点还是上一次算的,不重算
        }
        cache.clear();
        private_rebuild_route();   // 路由:按脏标记装这次要跑的步骤
        private_run_route();       // 分派:顺次跑步骤出顶点
        dirty = false;
    }
}
