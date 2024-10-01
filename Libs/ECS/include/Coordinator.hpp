/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#pragma once

#include <memory>

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace ECS {
    /**
     * @brief Main class of the ECS that will handle the coordination of everything.
     * 
     * This class is used to handle the coordination of the ECS. It provides functions to register
     * components and systems, add and remove components, create and destroy entities, and set and
     * get entity signatures.
     * 
     */
    class Coordinator {
        public:
            /**
             * @brief Registers a component type.
             * 
             * @tparam T The type of the component.
             */
            template<typename T>
            void registerComponent() {
                componentManager->registerComponent<T>();
            }

            /**
             * @brief Adds a component to an entity.
             * 
             * @tparam T The type of the component.
             * @param entity The entity to which the component is added.
             * @param component The component to be added.
             */
            template<typename T>
            void addComponent(Entity entity, T component) {
                componentManager->addComponent<T>(entity, component);

                auto signature = entityManager->getSignature(entity);
                signature.set(componentManager->getComponentType<T>(), true);
                entityManager->setSignature(entity, signature);

                systemManager->entitySignatureChanged(entity, signature);
            }

            /**
             * @brief Removes a component from an entity.
             * 
             * @tparam T The type of the component.
             * @param entity The entity from which the component is removed.
             */
            template<typename T>
            void removeComponent(Entity entity) {
                componentManager->removeComponent<T>(entity);

                auto signature = entityManager->getSignature(entity);
                signature.set(componentManager->getComponentType<T>(), false);
                entityManager->setSignature(entity, signature);

                systemManager->entitySignatureChanged(entity, signature);
            }

            /**
             * @brief Retrieves the component associated with an entity.
             * 
             * @tparam T The type of the component.
             * @param entity The entity whose component is to be retrieved.
             * 
             * @return The component associated with the entity.
             */
            template<typename T>
            T& getComponent(Entity entity) {
                return componentManager->getComponent<T>(entity);
            }

            /**
             * @brief Retrieves the component type.
             * 
             * @tparam T The type of the component.
             * 
             * @return The component type.
             */
            template<typename T>
            ComponentType getComponentType() {
                return componentManager->getComponentType<T>();
            }

            /**
             * @brief Registers a system type.
             * 
             * @tparam T The type of the system.
             * 
             * @return The system.
             */
            template<typename T>
            std::shared_ptr<T> registerSystem() {
                return systemManager->registerSystem<T>();
            }

            /**
             * @brief Sets the signature of a system.
             * 
             * @tparam T The type of the system.
             * @param signature The signature of the system.
             */
            template<typename T>
            void setSystemSignature(Signature signature) {
                systemManager->setSignature<T>(signature);
            }

            /**
             * @brief Initializes the coordinator.
             * 
             * This function initializes the coordinator. It creates the component manager, entity manager,
             * and system manager. It also registers the component types.
             */
            void init();

            /**
             * @brief Creates an entity.
             * 
             * @param name The name of the entity.
             * 
             * @return The entity.
             */
            Entity createEntity(const std::string& name);

            /**
             * @brief Destroys an entity.
             * 
             * @param entity The entity to be destroyed.
             */
            void destroyEntity(Entity entity);

            /**
             * @brief Retrieves the name of an entity.
             * 
             * @param entity The entity whose name is to be retrieved.
             * 
             * @return The name of the entity.
             */
            std::string getEntityName(Entity entity);

            /**
             * @brief Sets the name of an entity.
             * 
             * @param entity The entity whose name is to be set.
             * @param name The name of the entity.
             */
            void setEntityName(Entity entity, bool initialized);

            /**
             * @brief Retrieves the initialized status of an entity.
             * 
             * @param entity The entity whose initialized status is to be retrieved.
             * 
             * @return The initialized status of the entity.
             */
            bool getEntityInitialized(Entity entity);

            /**
             * @brief Sets the initialized status of an entity.
             * 
             * @param entity The entity whose initialized status is to be set.
             * @param initialized The initialized status of the entity.
             */
            void setEntityInitialized(Entity entity, bool initialized);

            /**
             * @brief Retrieves the signature of an entity.
             * 
             * @param entity The entity whose signature is to be retrieved.
             * 
             * @return The signature of the entity.
             */
            Signature getEntitySignature(Entity entity);

            /**
             * @brief Sets the signature of an entity.
             * 
             * @param entity The entity whose signature is to be set.
             * @param signature The signature of the entity.
             */
            void setEntitySignature(Entity entity, Signature signature);

        private:
            /**
             * @brief Variable that stores the component manager.
             */
            std::unique_ptr<ComponentManager> componentManager;

            /**
             * @brief Variable that stores the entity manager.
             */
            std::unique_ptr<EntityManager> entityManager;

            /**
             * @brief Variable that stores the system manager.
             */
            std::unique_ptr<SystemManager> systemManager;
    };
}
