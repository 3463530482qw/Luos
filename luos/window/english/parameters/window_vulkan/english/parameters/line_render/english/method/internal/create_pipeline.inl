namespace Gnik_luos {
    void Vulkan_line_render::create_pipeline(const vk::raii::RenderPass& render_pass) {
        std::vector<uint32_t> vertex_code = load_shader(vertex_shader_file.c_str());
        std::vector<uint32_t> fragment_code = load_shader(fragment_shader_file.c_str());

        vk::ShaderModuleCreateInfo vertex_info;
        vertex_info.setCodeSize(vertex_code.size() * sizeof(uint32_t));
        vertex_info.setPCode(vertex_code.data());
        vk::raii::ShaderModule vertex_shader(vulkan().device, vertex_info);

        vk::ShaderModuleCreateInfo fragment_info;
        fragment_info.setCodeSize(fragment_code.size() * sizeof(uint32_t));
        fragment_info.setPCode(fragment_code.data());
        vk::raii::ShaderModule fragment_shader(vulkan().device, fragment_info);

        vk::PipelineShaderStageCreateInfo stages[2];
        stages[0].setStage(vk::ShaderStageFlagBits::eVertex);
        stages[0].setModule(*vertex_shader);
        stages[0].setPName("main");
        stages[1].setStage(vk::ShaderStageFlagBits::eFragment);
        stages[1].setModule(*fragment_shader);
        stages[1].setPName("main");

        // 顶点输入:Vertex{x,y,z,u,v,r,g,b,a,use_texture} → pos(3)+uv(2)+color(4)+贴图开关(1)
        vk::VertexInputBindingDescription binding_description;
        binding_description.setBinding(0);
        binding_description.setStride(sizeof(Vertex));
        binding_description.setInputRate(vk::VertexInputRate::eVertex);

        std::array<vk::VertexInputAttributeDescription, 4> attributes;
        attributes[0].setLocation(0); attributes[0].setBinding(0); attributes[0].setFormat(vk::Format::eR32G32B32Sfloat); attributes[0].setOffset(0);
        attributes[1].setLocation(1); attributes[1].setBinding(0); attributes[1].setFormat(vk::Format::eR32G32Sfloat); attributes[1].setOffset(3 * sizeof(float));
        attributes[2].setLocation(2); attributes[2].setBinding(0); attributes[2].setFormat(vk::Format::eR32G32B32A32Sfloat); attributes[2].setOffset(5 * sizeof(float));
        attributes[3].setLocation(3); attributes[3].setBinding(0); attributes[3].setFormat(vk::Format::eR32Sfloat); attributes[3].setOffset(9 * sizeof(float));

        vk::PipelineVertexInputStateCreateInfo vertex_input;
        vertex_input.setVertexBindingDescriptionCount(1);
        vertex_input.setPVertexBindingDescriptions(&binding_description);
        vertex_input.setVertexAttributeDescriptionCount(static_cast<uint32_t>(attributes.size()));
        vertex_input.setPVertexAttributeDescriptions(attributes.data());

        vk::PipelineInputAssemblyStateCreateInfo input_assembly;
        input_assembly.setTopology(vk::PrimitiveTopology::eTriangleList);
        input_assembly.setPrimitiveRestartEnable(false);

        // 视口与裁剪每帧由窗口设定(内接矩形),管线这边只声明动态
        vk::PipelineViewportStateCreateInfo viewport_state;
        viewport_state.setViewportCount(1);
        viewport_state.setScissorCount(1);

        vk::PipelineRasterizationStateCreateInfo rasterizer;
        rasterizer.setDepthClampEnable(false);
        rasterizer.setRasterizerDiscardEnable(false);
        rasterizer.setPolygonMode(vk::PolygonMode::eFill);
        rasterizer.setLineWidth(1.0f);
        // 线条是闭合的立体盒子(见 Line::private_box 的面表,绕序朝外),所以剔背面:
        // 背对相机的面本来就被前脸挡住,剔掉只省光栅化;alpha < 1 的线也不会被前后两面叠混一次
        rasterizer.setCullMode(vk::CullModeFlagBits::eBack);
        rasterizer.setFrontFace(vk::FrontFace::eClockwise);
        rasterizer.setDepthBiasEnable(false);

        vk::PipelineMultisampleStateCreateInfo multisample;
        multisample.setSampleShadingEnable(false);
        multisample.setRasterizationSamples(vk::SampleCountFlagBits::e1);

        // 深度:比较用 LessOrEqual 而不是 Less —— 同一 z 上按绘制顺序后者覆盖,
        // 于是 2D(全部 z=0)的填充在下、线条在上的层序照旧,三维内容又能被 z 分出前后
        vk::PipelineDepthStencilStateCreateInfo depth_stencil;
        depth_stencil.setDepthTestEnable(true);
        depth_stencil.setDepthWriteEnable(true);
        depth_stencil.setDepthCompareOp(vk::CompareOp::eLessOrEqual);
        depth_stencil.setDepthBoundsTestEnable(false);
        depth_stencil.setStencilTestEnable(false);

        // 线条按常规 alpha 混合叠在场景上
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

        vk::PushConstantRange push_range;
        push_range.setStageFlags(vk::ShaderStageFlagBits::eVertex);
        push_range.setOffset(0);
        push_range.setSize(sizeof(Line_push_constants));

        vk::PipelineLayoutCreateInfo layout_info;
        layout_info.setSetLayoutCount(1);
        layout_info.setPSetLayouts(&*descriptor_layout);   // 线条贴图:片元阶段的组合图像采样器
        layout_info.setPushConstantRangeCount(1);
        layout_info.setPPushConstantRanges(&push_range);
        pipeline_layout = vk::raii::PipelineLayout(vulkan().device, layout_info);

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
        pipeline = vk::raii::Pipeline(vulkan().device, nullptr, pipeline_info);
    }
}
