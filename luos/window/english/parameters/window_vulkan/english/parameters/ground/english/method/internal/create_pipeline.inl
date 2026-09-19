namespace Gnik_luos {
    void Vulkan_ground::create_pipeline(const vk::raii::RenderPass& render_pass) {
        std::vector<uint32_t> vertex_code = load_shader(vertex_shader_file.c_str());
        std::vector<uint32_t> fragment_code = load_shader(fragment_shader_file.c_str());

        vk::ShaderModuleCreateInfo vertex_info;
        vertex_info.setCodeSize(vertex_code.size() * sizeof(uint32_t));
        vertex_info.setPCode(vertex_code.data());
        vk::raii::ShaderModule vertex_shader((*vulkan)->device, vertex_info);

        vk::ShaderModuleCreateInfo fragment_info;
        fragment_info.setCodeSize(fragment_code.size() * sizeof(uint32_t));
        fragment_info.setPCode(fragment_code.data());
        vk::raii::ShaderModule fragment_shader((*vulkan)->device, fragment_info);

        vk::PipelineShaderStageCreateInfo stages[2];
        stages[0].setStage(vk::ShaderStageFlagBits::eVertex);
        stages[0].setModule(*vertex_shader);
        stages[0].setPName("main");
        stages[1].setStage(vk::ShaderStageFlagBits::eFragment);
        stages[1].setModule(*fragment_shader);
        stages[1].setPName("main");

        // 地面四边形由 gl_VertexIndex 在顶点着色器里展开,管线不吃顶点缓冲
        vk::PipelineVertexInputStateCreateInfo vertex_input;

        vk::PipelineInputAssemblyStateCreateInfo input_assembly;
        input_assembly.setTopology(vk::PrimitiveTopology::eTriangleList);
        input_assembly.setPrimitiveRestartEnable(false);

        // 视口与裁剪每帧由窗口设定(内接矩形),管线这边只声明动态
        vk::PipelineViewportStateCreateInfo viewport_state;
        viewport_state.setViewportCount(1);
        viewport_state.setScissorCount(1);

        // 地面是躺在 y=0 平面上的薄片,两面都要看得见
        vk::PipelineRasterizationStateCreateInfo rasterizer;
        rasterizer.setDepthClampEnable(false);
        rasterizer.setRasterizerDiscardEnable(false);
        rasterizer.setPolygonMode(vk::PolygonMode::eFill);
        rasterizer.setLineWidth(1.0f);
        rasterizer.setCullMode(vk::CullModeFlagBits::eNone);
        rasterizer.setFrontFace(vk::FrontFace::eClockwise);
        rasterizer.setDepthBiasEnable(false);

        vk::PipelineMultisampleStateCreateInfo multisample;
        multisample.setSampleShadingEnable(false);
        multisample.setRasterizationSamples(vk::SampleCountFlagBits::e1);

        // 与线条同一套深度口径:比较用 LessOrEqual,格线之间那些片元在着色器里 discard 掉,不写深度
        vk::PipelineDepthStencilStateCreateInfo depth_stencil;
        depth_stencil.setDepthTestEnable(true);
        depth_stencil.setDepthWriteEnable(true);
        depth_stencil.setDepthCompareOp(vk::CompareOp::eLessOrEqual);
        depth_stencil.setDepthBoundsTestEnable(false);
        depth_stencil.setStencilTestEnable(false);

        vk::PipelineColorBlendAttachmentState blend_attachment;
        blend_attachment.setBlendEnable(true);
        blend_attachment.setSrcColorBlendFactor(vk::BlendFactor::eSrcAlpha);
        blend_attachment.setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha);
        blend_attachment.setColorBlendOp(vk::BlendOp::eAdd);
        blend_attachment.setSrcAlphaBlendFactor(vk::BlendFactor::eOne);
        blend_attachment.setDstAlphaBlendFactor(vk::BlendFactor::eZero);
        blend_attachment.setAlphaBlendOp(vk::BlendOp::eAdd);
        blend_attachment.setColorWriteMask(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
            | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

        vk::PipelineColorBlendStateCreateInfo color_blend;
        color_blend.setLogicOpEnable(false);
        color_blend.setAttachmentCount(1);
        color_blend.setPAttachments(&blend_attachment);

        std::array<vk::DynamicState, 2> dynamic_states{vk::DynamicState::eViewport, vk::DynamicState::eScissor};
        vk::PipelineDynamicStateCreateInfo dynamic_state;
        dynamic_state.setDynamicStateCount(static_cast<uint32_t>(dynamic_states.size()));
        dynamic_state.setPDynamicStates(dynamic_states.data());

        // 推常量:顶点(矩阵)与片元(格线参数)两边都要读
        vk::PushConstantRange push_range;
        push_range.setStageFlags(vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment);
        push_range.setOffset(0);
        push_range.setSize(sizeof(Ground_push_constants));

        vk::PipelineLayoutCreateInfo layout_info;
        layout_info.setPushConstantRangeCount(1);
        layout_info.setPPushConstantRanges(&push_range);
        pipeline_layout = vk::raii::PipelineLayout((*vulkan)->device, layout_info);

        vk::GraphicsPipelineCreateInfo pipeline_info;
        pipeline_info.setStageCount(2);
        pipeline_info.setPStages(stages);
        pipeline_info.setPVertexInputState(&vertex_input);
        pipeline_info.setPInputAssemblyState(&input_assembly);
        pipeline_info.setPViewportState(&viewport_state);
        pipeline_info.setPRasterizationState(&rasterizer);
        pipeline_info.setPMultisampleState(&multisample);
        pipeline_info.setPDepthStencilState(&depth_stencil);
        pipeline_info.setPColorBlendState(&color_blend);
        pipeline_info.setPDynamicState(&dynamic_state);
        pipeline_info.setLayout(*pipeline_layout);
        pipeline_info.setRenderPass(*render_pass);
        pipeline = vk::raii::Pipeline((*vulkan)->device, nullptr, pipeline_info);
    }
}
