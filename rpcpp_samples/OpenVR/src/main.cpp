/**
 * MIT License
 * 
 * Copyright (c) 2016-2017 Center of Human-centered Interaction for Coexistence
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <load_prc_file.h>

#include <render_pipeline/rppanda/showbase/showbase.hpp>
#include <render_pipeline/rppanda/showbase/messenger.hpp>
#include <render_pipeline/rpcore/mount_manager.hpp>
#include <render_pipeline/rpcore/globals.hpp>
#include <render_pipeline/rpcore/loader.hpp>
#include <render_pipeline/rpcore/pluginbase/manager.hpp>

#include <openvr_plugin.hpp>

#include "world.hpp"

int main(int argc, char* argv[])
{
    // Setup window size, title and so on
    load_prc_file_data("",
        "sync-video false\n"
        "window-title Render Pipeline - Shading Models VR Demo");

    // configure panda3d in program.
    auto render_pipeline = std::make_unique<rpcore::RenderPipeline>(argc, argv);

    {
        render_pipeline->get_mount_mgr()->set_config_dir("../etc/rpsamples/vr");
        render_pipeline->create();

        if (!render_pipeline->get_plugin_mgr()->is_plugin_enabled("openvr"))
        {
            render_pipeline->error("OpenVR is not enabled!");
            render_pipeline->error("Enable openvr in plugins.yaml");
            return 0;
        }

        PT(World) world = new World(*render_pipeline);
        world->start();

        render_pipeline->run();
    }

    // release explicitly
    render_pipeline.reset();

    return 0;
}