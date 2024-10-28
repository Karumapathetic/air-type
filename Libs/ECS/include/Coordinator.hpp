/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

#define MAX_X 1920
#define MAX_Y 1080

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
             * @brief Constructor of the coordinator.
             */
            Coordinator();
            /**
             * @brief Registers a component type.
             * 
             * @tparam T The type of the component.
             */
            template<typename T>
            void registerComponent()
            {
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
            void addComponent(Entity entity, T component)
            {
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
            void removeComponent(Entity entity)
            {
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
            T& getComponent(Entity entity)
            {
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
            ComponentType getComponentType()
            {
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
            std::shared_ptr<T> registerSystem()
            {
                return systemManager->registerSystem<T>();
            }

            /**
             * @brief Sets the system signature.
             * 
             * @tparam T The type of the system.
             * @param signature The signature of the system.
             */
            template<typename T>
            std::shared_ptr<T> getCoordSystem()
            {
                return systemManager->getSystem<T>();
            }

            /**
             * @brief Sets the signature of a system.
             * 
             * @tparam T The type of the system.
             * @param signature The signature of the system.
             */
            template<typename T>
            void setSystemSignature(Signature signature)
            {
                systemManager->setSignature<T>(signature);
            }

            /**
             * @brief Initializes the entities in the ECS.
             * 
             * This function is responsible for creating and initializing various entities in the ECS.
             * It registers entity handlers for different entity types and calls the respective handlers
             * to create and initialize the entities.
             * 
             * @return void
             */
            void initEntities();

            /**
             * @brief Creates an entity.
             * 
             * @param name The name of the entity.
             * 
             * @return The entity.
             */
            Entity createEntity(const std::string& name); // Here

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
            void setEntityName(Entity entity, const std::string& name);

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

            /**
             * @brief Retrieves the entities.
             * 
             * @return The entities.
             */
            std::vector<Entity> getEntities() const;

            /**
             * @brief Retrieves the entity.
             * 
             * @param name The name of the entity.
             * 
             * @return The entity.
             */
            Entity getEntity(std::string name);

            /**
             * @brief Retrieves the entity by ID.
             * 
             * @param id The ID of the entity type.
             * 
             * @return The entity.
             */
            Entity getEntityById(int id);

            /**
             * @brief Sets the entities.
             * 
             * @param index The index of the entity.
             * @param entity The entity.
             */
            void setEntities(std::size_t index, Entity entity);

                        /**
             * @brief Retrieves the signature of a system.
             * 
             * @tparam T The type of the system.
             * 
             * @return The signature of the system.
             */

            Signature getSystemSignature(const std::string& typeName);

            /**
             * @brief Retrieves the systems registered in the ECS.
             * 
             * This function returns a constant reference to an unordered map that contains the 
             * registered systems in the ECS. The map is keyed by the system type names and 
             * the values are shared pointers to the system interfaces.
             * 
             * @return A constant reference to an unordered map containing the system type names 
             *         as keys and shared pointers to the system interfaces as values.
             */
            const std::unordered_map<std::string, std::shared_ptr<ISystem>>& getSystems() const;

            /**
             * @brief Sets the updated status of an entity.
             * 
             * This function updates the 'updated' status of a specific entity in the ECS.
             * The updated status indicates whether the entity has been updated or not.
             * 
             * @param entity The unique identifier of the entity.
             * @param updated The updated status of the entity.
             * 
             * @return void
             */
            void setEntityUpdated(Entity entity, const bool updated);

            /**
             * @brief Retrieves the updated status of an entity.
             * 
             * This function checks the 'updated' status of a specific entity in the ECS.
             * The updated status indicates whether the entity has been updated or not.
             * 
             * @param entity The entity whose updated status is to be retrieved.
             * 
             * @return True if the entity has been updated, false otherwise.
             */
            bool getEntityUpdated(Entity entity);

            /**
             * @brief Spawns an entity in the ECS based on the provided name and parameters.
             * 
             * This function creates an entity with the given name and initializes it using the provided parameters.
             * It then registers the entity handler for the given name and calls the handler to perform additional
             * initialization tasks specific to the entity type.
             * 
             * @param coordinator The ECS coordinator.
             * @param name The name of the entity to be spawned.
             * @param params The parameters string containing additional information for initializing the entity.
             * 
             * @return void
             */
            void spawnEntity(Coordinator& coordinator, const std::string& name, const std::string& params);

            /**
             * @brief Checks if the entity has a specific component.
             * 
             * @param entity The entity to check.
             * @param componentType The type of the component.
             *
             * @return True if the entity has the component, false otherwise.
             */
            bool hasComponent(Entity entity, ComponentType componentType);

            /**
             * @brief Check if the entity is valid or Invalid.
             * 
             * @param entity The entity to check.
             *
             * @return True if the entity is valid, false otherwise.
             */
            bool isEntityValid(Entity entity) const;

            void updateGame();

            /**
             * @brief Updates the systems in the ECS.
             * 
             * This function iterates through all the registered systems in the ECS and calls their update functions.
             * The update function of each system is responsible for processing the entities that match its signature.
             * 
             * @return void
             */
            void updateSystems();

            /**
             * @brief Retrieves the action queue containing entity-action pairs.
             * 
             * This function returns a deque of pairs, where each pair consists of an entity and a string representing an action.
             * The action queue is used to store and retrieve actions that need to be performed on specific entities.
             * 
             * @return A deque of pairs containing entity-action pairs.
             */
            std::deque<std::pair<Entity, std::string>> getActionQueue();

            /**
             * @brief Adds an event to the action queue.
             * 
             * This function adds a new event to the action queue, consisting of an entity ID and an action string.
             * The event is placed at the end of the queue.
             * 
             * @param id The unique identifier of the entity associated with the event.
             * @param action The action string representing the event to be performed.
             * 
             * @return void
             */
            void addEvent(Entity id, const std::string& action);

            /**
             * @brief Retrieves the first event from the action queue.
             * 
             * This function retrieves the first event from the action queue, which is a deque of pairs.
             * Each pair consists of an entity and a string representing an action.
             * 
             * @return A pair containing the entity ID and the action string of the first event.
             *         If the action queue is empty, it returns a pair with -1 as the entity ID and an empty string as the action.
             */
            std::pair<Entity, std::string> getFirstEvent() const;

            /**
             * @brief Removes the first event from the action queue.
             * 
             * This function removes the first event from the action queue, which is a deque of pairs.
             * Each pair consists of an entity and a string representing an action. The function 
             * ensures that the queue is not empty before attempting to remove an event.
             * 
             * @return void
             */
            void removeFirstEvent();

            /**
             * @brief Moves the last added event to the end of the action queue.
             * 
             * This function is used to ensure that a specific event, which might be required to be processed last,
             * is moved to the end of the action queue. This is useful when there are multiple events that need to be
             * processed in a specific order.
             * 
             * @return void
             * 
             * @note This function does not remove the event from its current position in the queue. It simply moves
             *       it to the end. If the action queue is empty, this function does nothing.
             */
            void putEventAtEnd();
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

            /**
             * @brief Variable that stores the entity handlers.
             */
            std::unordered_map<std::string, std::function<void(Coordinator&, std::uint32_t)>> entityHandlers;

            /**
             * @brief Variable that stores the entities.
             */
            std::vector<Entity> _entities;

            /**
             * @brief A double-ended queue (deque) that stores pairs of entities and their associated actions.
             *        This queue is used to manage and process events or actions related to entities in the ECS.
             * 
             * @note The deque is implemented using a doubly-linked list, allowing efficient insertion and removal
             *       of elements from both ends.
             */
            std::deque<std::pair<Entity, std::string>> _actionQueue;

            /**
             * @brief Creates an entity based on the specified type.
             * 
             * This function is responsible for creating an entity of a specific type based on the provided
             * type string. It then registers the entity handler for the given type and calls the handler
             * to initialize the entity.
             * 
             * @param type The type of the entity to be created.
             * @param entity The unique identifier of the entity.
             * 
             * @return void
             */
            void createEntityFromType(const std::string &type, std::uint32_t entity);

            /**
             * @brief Updates the value of a specific member variable in a component.
             * 
             * This function is used to update the value of a specific member variable in a component 
             * based on the provided parameters. It uses template specialization to handle different 
             * data types.
             * 
             * @param coordinator The ECS coordinator.
             * @param entity The entity to which the component belongs.
             * @param params The parameters string containing the new value.
             * @param key The key of the member variable to be updated.
             * @param member A pointer to the member variable in the component.
             * 
             * @return void
             */
            template <typename T, typename MemberType>
            void updateComponentValue(Coordinator& coordinator, Entity entity, const std::string& params, const std::string& key, MemberType T::*member);

            /**
             * @brief Updates the value of a specific member variable in a component that is a vector.
             * 
             * This function is used to update the value of a specific member variable in a component 
             * that is a vector based on the provided parameters. It parses the input string to extract 
             * the new vector values and updates the corresponding member variable in the component.
             * 
             * @param coordinator The ECS coordinator.
             * @param entity The entity to which the component belongs.
             * @param params The parameters string containing the new vector values.
             * @param key The key of the member variable to be updated.
             * 
             * @return void
             */
            void updateComponentVector(Coordinator& coordinator, Entity entity, const std::string& params, const std::string& key);
    };

    /**
     * @brief Function that handles the player entity.
     * 
     * @param gCoordinator The coordinator.
     * @param entity The entity.
     */
    void playerHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the missile entity.
     * 
     * @param gCoordinator The coordinator.
     * @param entity The entity.
     */
    void missileHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the background entity.
     * 
     * @param gCoordinator The coordinator.
     * @param entity The entity.
     */
    void backgroundHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the settings entity.
     * 
     * @param gCoordinator The coordinator.
     * @param entity The entity.
     */
    void settingsHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the collectible entity.
     * 
     * @param gCoordinator The coordinator.
     * @param entity The entity.
     */
    void collectibleHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the pata-pata entity.
     * 
     * This function handles the pata-pata entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void patapataHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the win entity.
     * 
     * This function handles the win entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void winHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the bug entity.
     * 
     * This function handles the bug entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void bugHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the wick entity.
     * 
     * This function handles the wick entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void wickHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the geld entity.
     * 
     * This function handles the geld entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void geldHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
