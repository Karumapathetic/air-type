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
    template <typename T>
    class RequestsFactory
    {
        public:
            Request<T> createPositionsRequests(std::string entityName, int spriteID, float posX, float posY)
            {
                Request<T> request;
                request.header.id = T::SetSpritePosition;
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

            Request<T> createKilledSprite(int spriteID, float posX, float posY)
            {
                Request<T> request;
                request.header.id = T::NotifyKilledSprite;
                KilledSprite requestBody = {spriteID, posX, posY};
                std::vector<uint8_t> body(reinterpret_cast<uint8_t *>(&requestBody), reinterpret_cast<uint8_t *>(&requestBody) + sizeof(KilledSprite));
                request.body.insert(request.body.end(), body.begin(), body.end());
                request.header.size = request.getSize();
                return request;
            }

            Request<T> createInputRequest(int clientID, std::string action)
            {
                Request<T> request;
                request.header.id = T::SetInput;
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

            Request<T> createConnectionAccepted(int spriteID)
            {
                Request<T> request;
                request.header.id = T::ServerAcceptance;
                PlayerID playerid = {spriteID};
                std::vector<uint8_t> body(reinterpret_cast<uint8_t *>(&spriteID), reinterpret_cast<uint8_t *>(&spriteID) + sizeof(PlayerID));
                request.body.insert(request.body.end(), body.begin(), body.end());
                request.header.size = request.getSize();
                return request;
            }

            Request<T> createLaunchGameRequest()
            {
                Request<T> request;
                request.header.id = T::LaunchGame;
                return request;
            }

            SpritePositions transformPositionsRequest(Request<T> request)
            {
                SpritePositions result;
                std::memcpy(&result, request.body.data(), sizeof(SpritePositions));
                return result;
            }

            KilledSprite transformKilledRequest(Request<T> request)
            {
                KilledSprite result;
                std::memcpy(&result, request.body.data(), sizeof(KilledSprite));
                return result;
            }

            Input transformInputRequest(Request<T> request)
            {
                Input result;
                std::memcpy(&result, request.body.data(), sizeof(Input));
                return result;
            }

            PlayerID transformConnectionAccepted(Request<T> request)
            {
                PlayerID result;
                std::memcpy(&result, request.body.data(), sizeof(PlayerID));
                return result;
            }
    };

};