#include "main.hpp"

ICore* getCore = nullptr;

void GameMode::onLoad(ICore *core)
{
    c = core;
    getCore = c;

    // Add player event
    c->getPlayers().getPlayerConnectDispatcher().addEventHandler(this);
    c->getPlayers().getPlayerSpawnDispatcher().addEventHandler(this);
}

void GameMode::onInit(IComponentList *components)
{
    using namespace ompgdk;
    using namespace std;

    cout << "\n";

    // Initialize open.mp gdk
    GDKManager::Get()->Init(c, components);
    c->printLn("[Server] GDK Initialize.");

    c->useStuntBonuses(false); // No Stunt bonus
	c->setData(SettableCoreDataType::ServerName, "C++ GameMode");
	c->setData(SettableCoreDataType::ModeText, "open.mp");
	c->setData(SettableCoreDataType::MapName, "San Andreas");
	c->setData(SettableCoreDataType::Language, "English");
	c->setData(SettableCoreDataType::URL, "https://discord.gg/tpBJCEGRmQ");

    // Create pickup
    pickupId = CreatePickup(19134, 1, 2200.8652f, 1392.9286f, 10.8203f, 0);
}

void GameMode::onFree(IComponent *component)
{
    using namespace ompgdk;

    // Destroy pickup
    DestroyPickup(pickupId);

    // Remove player event
    c->getPlayers().getPlayerConnectDispatcher().removeEventHandler(this);
    c->getPlayers().getPlayerSpawnDispatcher().removeEventHandler(this);
}

void GameMode::onPlayerConnect(IPlayer &player)
{
    // Add PlayerData in to player
    player.addExtension(new PlayerData(), true);
    
    PlayerData* data = queryExtension<PlayerData>(player);

    player.sendClientMessage(Colour::FromARGB(0x00FF00), "Hi " + std::string(player.getName()) + "!");

    // Set Variable for player
    data->OnGame = true;
}

void GameMode::onPlayerSpawn(IPlayer& player)
{
    PlayerData* data = queryExtension<PlayerData>(player);

    player.sendGameText("~b~Welcome ~r~" + std::string(player.getName()), Seconds(2), 1);

    // Set player position
    player.setPosition(Vector3(data->dx, data->dy, data->dz));
    player.setRotation(GTAQuat(0.0f, 0.0f, data->da)); // Set player facingangle

    player.setCameraBehind();
}

void GameMode::onPlayerDisconnect(IPlayer &player, PeerDisconnectReason reason)
{
    PlayerData* data = queryExtension<PlayerData>(player);

    data->OnGame = false;
}

void GameMode::onTick(Microseconds elapsed, TimePoint now)
{
}

void PlayerData::freeExtension()
{
    // Get player pool T_T
    for (IPlayer* player : getCore->getPlayers().players())
    {
        PlayerData* data = queryExtension<PlayerData>(player);

        if (player->isBot())
            continue;
        
        if (OnGame)
        {
            OnGame = false;
        }
    }

    delete this;
}

COMPONENT_ENTRY_POINT()
{
	return new GameMode();
}