#pragma once

#include <map>
#include <unordered_set>

#include "Entity.h"
#include "FrameInfo.h"

namespace EngineCore
{

    class TinyEngineRT;
    class SceneSystem
    {
    public:
        SceneSystem(TinyEngineRT* engine);
        ~SceneSystem();
        
        EntityId AddEntity(Entity* entity);
        void RemoveEntity(const EntityId& entity);
        void UpdateEntities(const FrameInfo& frameInfo);

    private:
        std::map<EntityId, Entity*>* _entities;
        std::unordered_set<EntityId, EntityIdHashFunction>* _toDestroy;

        TinyEngineRT* _engine;

        EntityId _nextId = { 0 };
    };
}
