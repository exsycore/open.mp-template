#pragma once

#include <Server/Components/Classes/classes.hpp>
#include <Server/Components/Timers/timers.hpp>
#include <Server/Components/Dialogs/dialogs.hpp>

#include <ompgdk.hpp>

#include <iostream>

class PlayerData final : public IExtension
{
	public:
        // Get UID in https://open.mp/uid
		PROVIDE_EXT_UID(/* UID GOES HERE */);

		void freeExtension() override;

		void reset() override {}

		~PlayerData() {}

        static constexpr float dx = 2200.8652f;
        static constexpr float dy = 1392.9286f;
        static constexpr float dz = 10.8203f;
        static constexpr float da = 179.8621f;

        bool OnGame = false;
};

class GameMode : public IComponent
    , public PlayerConnectEventHandler
    , public CoreEventHandler
    , public PlayerSpawnEventHandler
{
    public:
        // Get UID in https://open.mp/uid
        PROVIDE_UID(/* UID GOES HERE */);

        SemanticVersion componentVersion() const override
		{
			return SemanticVersion(1, 0, 0, 0);
		}

        StringView componentName() const override
		{
			return "C++ GameMode";
		}

        void onLoad(ICore *core) override;
        void onInit(IComponentList *components) override;
        void onFree(IComponent *component) override;

        void onPlayerConnect(IPlayer& player) override;
        void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override;
        void onPlayerSpawn(IPlayer& player) override;

        void onTick(Microseconds elapsed, TimePoint now) override;

        void free() override { delete this; }
        void reset() override {}

        GameMode() {}
        ~GameMode() {}

    private:
        ICore* c = nullptr;

        int pickupId;
};

extern ICore* getCore;