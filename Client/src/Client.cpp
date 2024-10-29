/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(std::string host, const std::string& coreLibPath) : Network::AClient<Network::RequestsTypes>(), _coreLoader(coreLibPath)
{
    _isClientRunning = true;

    auto createCoreFunc = _coreLoader.getFunction<Graphics::ICore*(*)()>("CreateCore");
    _core.reset(createCoreFunc());
    this->connect(host, 60000);
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
        _core->Caillou(&_isClientRunning);
        checkForInput();
        std::cout << "Start handle -> " << this->getIncomingRequests().getSize() << std::endl;
        while (this->getIncomingRequests().getSize() > 0)
            handleData();
        std::cout << "Stop handle" << std::endl;
    }
    this->stop();
}

void Client::stop()
{
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
            break;
        default:
            break;
    }
}

void Client::addPosEventInCore(Network::Request<Network::RequestsTypes> request)
{
    Network::SpritePositions positions = _factory.transformPositionsRequest(request);
    std::string entityType = (positions.entityType == Network::SpritesTypes::Enemy ? "enemy" : (positions.entityType == Network::SpritesTypes::Missile ? "missile" : "player"));
    std::string params = "position:" + std::to_string(positions.poxX) + "," + std::to_string(positions.poxY) + ";" + entityType + ";";
    std::cout << "Pos: " << positions.spriteID << ", Params: '" + params + "'" << std::endl;
    _core->getGame().UpdateEntity(positions.spriteID, params);
}

// void Client::setSpritePos(std::vector<std::string> command)
// {
//     std::string pos = "position:" + command[3] + "," + command[4] + ";" + "texture:" + command[1] + ";";
//     _core->getGame().UpdateEntity(std::stoi(command[2]), pos);
// }

void Client::checkForInput()
{
    if (!_core->getGame().getClientAction().empty()) {
        if (_core->getGame().getGameState() == Graphics::GameState::MENU || _core->getGame().getGameState() == Graphics::GameState::SETTINGS)
            return;
        Network::Request<Network::RequestsTypes> request = _factory.createInputRequest(_id, _core->getGame().getClientAction()[0]);
        sendRequest(request);
    }
}
