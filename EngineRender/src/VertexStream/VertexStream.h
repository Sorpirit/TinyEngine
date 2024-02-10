#pragma once

namespace EngineRender::VertexStream
{
    class VertexStream 
    {
    public:
        virtual void InitAttributePointers() = 0;
        virtual int GetSize() = 0;
    };
}
