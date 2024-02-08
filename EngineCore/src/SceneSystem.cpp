#include "SceneSystem.h"

namespace EngineCore
{
    SceneSystem::SceneSystem(TinyEngineRT* engine) : _engine(engine)
    {
        _entities = new std::map<EntityId, Entity*>();
        _toDestroy = new std::unordered_set<EntityId, EntityIdHashFunction>();
    }

    SceneSystem::~SceneSystem()
    {
        for (const auto& [id, entity] : *_entities) {
            entity->Destroy();
            delete entity;
        }
        
        delete _entities;
        delete _toDestroy;
    }

    EntityId SceneSystem::AddEntity(Entity* entity)
    {
        auto id = _nextId;
        _entities->insert(std::pair<EntityId, Entity*>(id, entity));
        _nextId.ID++;

        entity->Init(_engine);
        
        return id;
    }

    void SceneSystem::RemoveEntity(const EntityId& entity)
    {
        _toDestroy->insert(entity);
    }

    void SceneSystem::UpdateEntities(const FrameInfo& frameInfo)
    {
        for (const auto& [id, entity] : *_entities) {
            entity->Update(frameInfo);
        }

        for (const auto& entityId : *_toDestroy)
        {
            _entities->at(entityId)->Destroy();
            _entities->erase(entityId);
        }
        _toDestroy->clear();
    }
}
