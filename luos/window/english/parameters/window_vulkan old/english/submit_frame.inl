namespace Gnik_luos {
    void Window_vulkan::submit_frame() {
        uint32_t image_index = 0;
        vk::ResultValue<uint32_t> acquired = vk::ResultValue<uint32_t>(vk::Result::eSuccess, 0);
        try {
            acquired = swapchain.swapchain.acquireNextImage(
                std::numeric_limits<uint64_t>::max(),
                *synchronization.image_available_per_frame[0],
                nullptr
            );
        } catch (const vk::OutOfDateKHRError&) {
            rebuild_flag = true;
            return;
        } catch (const vk::SurfaceLostKHRError&) {
            rebuild_flag = true;
            return;
        }
        if (acquired.result == vk::Result::eErrorOutOfDateKHR) {
            rebuild_flag = true;
            return;
        }
        image_index = acquired.value;

        vk::PipelineStageFlags wait_stage{vk::PipelineStageFlagBits::eColorAttachmentOutput};
        vk::SubmitInfo submit_info;
        submit_info.setWaitSemaphoreCount(1);
        submit_info.setPWaitSemaphores(&*synchronization.image_available_per_frame[0]);
        submit_info.setPWaitDstStageMask(&wait_stage);
        submit_info.setCommandBufferCount(1);
        submit_info.setPCommandBuffers(&*command_buffer.command_buffers[image_index]);
        submit_info.setSignalSemaphoreCount(1);
        submit_info.setPSignalSemaphores(&*synchronization.render_finished_per_image[image_index]);

        vulkan->graphics_queue.submit(submit_info, *synchronization.frame_fence);

        vk::PresentInfoKHR present_info;
        present_info.setWaitSemaphoreCount(1);
        present_info.setPWaitSemaphores(&*synchronization.render_finished_per_image[image_index]);
        present_info.setSwapchainCount(1);
        present_info.setPSwapchains(&*swapchain.swapchain);
        present_info.setPImageIndices(&image_index);

        // 呈现期的尺寸失配同样只是"下帧重建",不应当作异常抛出
        vk::Result present_result = vk::Result::eSuccess;
        try {
            present_result = vulkan->graphics_queue.presentKHR(present_info);
        } catch (const vk::OutOfDateKHRError&) {
            rebuild_flag = true;
            return;
        }
        if (present_result == vk::Result::eSuboptimalKHR || present_result == vk::Result::eErrorOutOfDateKHR) {
            rebuild_flag = true;
        }
    }
}
