/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#include "Client.hpp"

static bool isRunning;

void sigHandler(int sig)
{
    isRunning = false;
}

Client::Client(std::string host, const std::string& coreLibPath) : Network::AClient<Network::RequestsTypes>(), _coreLoader(coreLibPath)
{
    _isClientRunning = true;
    isRunning = true;

    auto createCoreFunc = _coreLoader.getFunction<Graphics::ICore*(*)()>("CreateCore");
    _core.reset(createCoreFunc());
    this->connect(host, 60000);
    signal(SIGINT, sigHandler);
}

Client::~Client()
{
}

void Client::init()
{
    _core->InitGame();
}

void Client::run()
{
    while (_isClientRunning) {
        if (isRunning == false)
            break;
        _core->Caillou(&_isClientRunning);
        checkForInput();
        while (this->getIncomingRequests().getSize() > 0)
            handleData();
    }
}

void Client::stop()
{
    this->disconnect();
    _core->getGame().getGraphics()->CloseGraphics();
}

void Client::handleData()
{
    auto request = this->getIncomingRequests().popFront();
    switch (request.request.header.id) {
        case Network::RequestsTypes::SetSpritePosition:
            addPosEventInCore(request.request);
            break;
        case Network::RequestsTypes::NotifyKilledSprite:
            destroyID(request.request);
            break;
        case Network::RequestsTypes::ServerAcceptance:
            registerID(request.request);
            break;
        case Network::RequestsTypes::ServerDenial:
        case Network::RequestsTypes::ClientDisconnection:
            _isClientRunning = false;
            break;
        default:
            break;
    }
}

void Client::destroyID(Network::Request<Network::RequestsTypes> request)
{
    auto response = _factory.transformKilledRequest(request);
    _core->getGame().DestroyEntity(response.spriteID);
}

void Client::registerID(Network::Request<Network::RequestsTypes> request)
{
    int playerID = _factory.transformConnectionAccepted(request);
    _id = playerID;
}

void Client::addPosEventInCore(Network::Request<Network::RequestsTypes> request)
{
    Network::SpritePositions positions = _factory.transformPositionsRequest(request);
    std::string entityName;
    switch (positions.entityType) {
        case Network::SpritesTypes::Bug:
            entityName = "bug";
            break;
        case Network::SpritesTypes::Geld:
            entityName = "geld";
            break;
        case Network::SpritesTypes::Wick:
            entityName = "wick";
            break;
        case Network::SpritesTypes::Win:
            entityName = "win";
            break;
        case Network::SpritesTypes::PataPata:
            entityName = "pata-pata";
            break;
        case Network::SpritesTypes::Player:
            entityName = "player";
            break;
        case Network::SpritesTypes::Missile:
            entityName = "missile";
            break;
    }
    std::string params = "position:" + std::to_string(positions.poxX) + "," + std::to_string(positions.poxY) + ";texture:" + entityName + ";";
    _core->getGame().UpdateEntity(positions.spriteID, params);
}

void Client::checkForInput()
{
    if (!_core->getGame().getClientAction().empty()) {
        if (_core->getGame().getGameState() == Graphics::GameState::MENU || _core->getGame().getGameState() == Graphics::GameState::SETTINGS)
            return;
        for (auto &action : _core->getGame().getClientAction()) {
            Network::Request<Network::RequestsTypes> request;
            if (action == "start") {
                request = _factory.createLaunchGameRequest();
            } else {
                request = _factory.createInputRequest(_id, action);
            }
            sendRequest(request);
        }
    }
}
