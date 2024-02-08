#pragma once
#include <functional>

#include "FrameInfo.h"

namespace EngineCore
{
    class EntityId
    {
    public:
        unsigned long ID;

        bool operator==(const EntityId &o) const
        {
            return ID == o.ID;
        }

        bool operator<(const EntityId &o) const
        {
            return ID < o.ID;
        }
    };

    struct EntityIdHashFunction
    {
        size_t operator()(const EntityId& entityId) const
        {
            return std::hash<int>()(entityId.ID);
        }
    };

    class TinyEngineRT;
    class Entity
    {
    public:
        virtual ~Entity() = default;

        virtual void Init(const TinyEngineRT* engine) = 0;
        virtual void Update(const FrameInfo& frameInfo) = 0;
        virtual void Destroy() { }
        
    };
}