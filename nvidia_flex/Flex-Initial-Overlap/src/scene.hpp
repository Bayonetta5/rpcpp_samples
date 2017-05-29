/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016, Center of human-centered interaction for coexistence.
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

#pragma once

#include <NvFlex.h>

#include <rpflex/plugin.hpp>
#include <rpflex/instance_interface.hpp>
#include <rpflex/flex_buffer.hpp>
#include <rpflex/utils/shape_box.hpp>

#include "mesh.hpp"

class Scene: public rpflex::InstanceInterface
{
public:
    void initialize(rpflex::Plugin& rpflex_plugin) final
    {
        auto& buffer = rpflex_plugin.modify_flex_buffer();
        auto& params = rpflex_plugin.modify_flex_params();
        params.radius = 0.1f;
        params.numIterations = 2;

        // test max acceleration clamping is working, test at 5x gravity
        params.maxAcceleration = 50.0f;

        // plinth
        entities_.push_back(std::make_shared<FlexShapeEntity>(rpflex_plugin, std::make_shared<rpflex::RPFlexShapeBox>(buffer, 1.0f, LVecBase3f(0.0f, 0.0f, 0.0f))));

        buffer.positions_.push_back(LVecBase4f(0.0f, 0.0f, 0.5f, 1.0f));
        buffer.velocities_.push_back(LVecBase3f(0.0f));
        buffer.phases_.push_back(0);

        entities_.push_back(std::make_shared<FlexParticlesEntity>(rpflex_plugin));

        for (auto& entity: entities_)
            entity->update(rpflex_plugin);
    }

    void sync_flex(rpflex::Plugin& rpflex_plugin) final
    {
        auto& buffer = rpflex_plugin.modify_flex_buffer();
        for (auto& entity: entities_)
            entity->update(rpflex_plugin);
    }

private:
    std::vector<std::shared_ptr<FlexEntity>> entities_;
};
