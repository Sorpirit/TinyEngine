#pragma once

namespace EngineRender::Mesh
{
    class Mesh
    {
    public:
        virtual void Attach() const = 0;
        virtual unsigned int GetDrawSize() const = 0;
    };
}
