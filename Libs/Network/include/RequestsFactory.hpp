/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** RequestsFactory
*/

#pragma once

#include "Requests.hpp"
#include "RequestsTypes.hpp"

namespace Network
{
    /**
     * @brief Requests Factory class
     * 
     */
    class RequestsFactory
    {
        public:
            /**
             * @brief Create a Positions Requests object
             * 
             * @param entityName Type of the entity's sprite
             * @param spriteID ID of the sprite
             * @param posX Position X of the sprite
             * @param posY Position Y of the sprite
             * @return Request<Network::RequestsTypes> Request of the sprite
             */
            Request<Network::RequestsTypes> createPositionsRequests(std::string entityName, int spriteID, float posX, float posY)
            {
                Request<Network::RequestsTypes> request;
                request.header.id = RequestsTypes::SetSpritePosition;
                SpritesTypes spriteType = SpritesTypes::Default;
                if (entityName == "pata-pata")
                    spriteType = SpritesTypes::PataPata;
                if (entityName == "win")
                    spriteType = SpritesTypes::Win;
                if (entityName == "wick")
                    spriteType = SpritesTypes::Wick;
                if (entityName == "geld")
                    spriteType = SpritesTypes::Geld;
                if (entityName == "bug")
                    spriteType = SpritesTypes::Bug;
                if (entityName == "player")
                    spriteType = SpritesTypes::Player;
                if (entityName == "missile")
                    spriteType = SpritesTypes::Missile;
                SpritePositions requestBody = {spriteType, spriteID, posX, posY};
                std::vector<uint8_t> body(reinterpret_cast<uint8_t *>(&requestBody), reinterpret_cast<uint8_t *>(&requestBody) + sizeof(SpritePositions));
                request.body.insert(request.body.end(), body.begin(), body.end());
                request.header.size = request.getSize();
                return request;
            }

            /**
             * @brief Create a Killed Sprite object
             * 
             * @param spriteID ID of the sprite killed
             * @param entityType Type of the sprite killed
             * @return Request<Network::RequestsTypes> Request of the killed sprite
             */
            Request<Network::RequestsTypes> createKilledSprite(int spriteID, std::string entityType)
            {
                Request<Network::RequestsTypes> request;
                request.header.id = RequestsTypes::NotifyKilledSprite;
                KilledSprite requestBody;
                requestBody.spriteID = spriteID;
                requestBody.entityType = SpritesTypes::Default;
                if (entityType == "pata-pata")
                    requestBody.entityType = SpritesTypes::PataPata;
                if (entityType == "win")
                    requestBody.entityType = SpritesTypes::Win;
                if (entityType == "wick")
                    requestBody.entityType = SpritesTypes::Wick;
                if (entityType == "geld")
                    requestBody.entityType = SpritesTypes::Geld;
                if (entityType == "bug")
                    requestBody.entityType = SpritesTypes::Bug;
                if (entityType == "player")
                    requestBody.entityType = SpritesTypes::Player;
                if (entityType == "missile")
                    requestBody.entityType = SpritesTypes::Missile;
                std::vector<uint8_t> body(reinterpret_cast<uint8_t *>(&requestBody), reinterpret_cast<uint8_t *>(&requestBody) + sizeof(KilledSprite));
                request.body.insert(request.body.end(), body.begin(), body.end());
                request.header.size = request.getSize();
                return request;
            }

            /**
             * @brief Create a Input Request object
             * 
             * @param clientID ID of the client
             * @param action Action done by the user
             * @return Request<Network::RequestsTypes> Request of the input
             */
            Request<Network::RequestsTypes> createInputRequest(int clientID, std::string action)
            {
                Request<Network::RequestsTypes> request;
                request.header.id = RequestsTypes::SetInput;
                InputActions inputAction;
                if (action == "up")
                    inputAction = InputActions::UP;
                if (action == "down")
                    inputAction = InputActions::DOWN;
                if (action == "left")
                    inputAction = InputActions::LEFT;
                if (action == "right")
                    inputAction = InputActions::RIGHT;
                if (action == "shoot")
                    inputAction = InputActions::SHOOT;
                Input requestBody = {clientID, inputAction};
                std::vector<uint8_t> body(reinterpret_cast<uint8_t *>(&requestBody), reinterpret_cast<uint8_t *>(&requestBody) + sizeof(Input));
                request.body.insert(request.body.end(), body.begin(), body.end());
                request.header.size = request.getSize();
                return request;
            }

            /**
             * @brief Create a Connection Accepted object
             * 
             * @param spriteID ID of the player's sprite
             * @return Request<Network::RequestsTypes> Request of the connection accepted
             */
            Request<Network::RequestsTypes> createConnectionAccepted(int spriteID)
            {
                Request<Network::RequestsTypes> request;
                request.header.id = RequestsTypes::ServerAcceptance;
                std::vector<uint8_t> body(reinterpret_cast<uint8_t *>(&spriteID), reinterpret_cast<uint8_t *>(&spriteID) + sizeof(int));
                request.body.insert(request.body.end(), body.begin(), body.end());
                request.header.size = request.getSize();
                return request;
            }

            /**
             * @brief Create a Launch Game Request object
             * 
             * @return Request<Network::RequestsTypes> Request of the game launch
             */
            Request<Network::RequestsTypes> createLaunchGameRequest()
            {
                Request<Network::RequestsTypes> request;
                request.header.id = RequestsTypes::LaunchGame;
                request.header.size = 0;
                return request;
            }

            Request<Network::RequestsTypes> createClientDisconnection()
            {
                Request<Network::RequestsTypes> request;
                request.header.id = RequestsTypes::ClientDisconnection;
                request.header.size = 0;
                return request;
            }

            /**
             * @brief Transform the Positions request to SpritePositions struct
             * 
             * @param request Request received
             * @return SpritePositions Struct containing the infos of the sprite
             */
            SpritePositions transformPositionsRequest(Request<Network::RequestsTypes> request)
            {
                SpritePositions result;
                std::memcpy(&result, request.body.data(), sizeof(SpritePositions));
                return result;
            }

            /**
             * @brief Transform the Killed request to KilledSprite struct
             * 
             * @param request Request received
             * @return KilledSprite Struct containing the infos of the killed sprite
             */
            KilledSprite transformKilledRequest(Request<Network::RequestsTypes> request)
            {
                KilledSprite result;
                std::memcpy(&result, request.body.data(), sizeof(KilledSprite));
                return result;
            }

            /**
             * @brief Transform the Input request to Input struct
             * 
             * @param request Request received
             * @return Input Struct containing the infos of the input
             */
            Input transformInputRequest(Request<Network::RequestsTypes> request)
            {
                Input result;
                std::memcpy(&result, request.body.data(), sizeof(Input));
                return result;
            }

            /**
             * @brief Transform the Connection accepted to player ID
             * 
             * @param request Request received
             * @return int Player ID
             */
            int transformConnectionAccepted(Request<Network::RequestsTypes> request)
            {
                int result;
                std::memcpy(&result, request.body.data(), sizeof(int));
                return result;
            }
    };

};