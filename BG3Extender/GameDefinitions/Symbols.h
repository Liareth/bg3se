#pragma once

#include <GameDefinitions/Character.h>
#include <GameDefinitions/EntityManager.h>
#include <GameDefinitions/Item.h>
#include <GameDefinitions/Level.h>
#include <GameDefinitions/Misc.h>
#include <GameDefinitions/Osiris.h>
#include <GameDefinitions/RootTemplates.h>
#include <GameDefinitions/Stats/Stats.h>
#include <GameDefinitions/Passives.h>
#include <GameDefinitions/Status.h>
#include <GameDefinitions/Surface.h>

namespace bg3se
{
	struct GuidResourceDefinitions;
	struct ResourceManager;
	struct App;

	struct StaticSymbols : Noncopyable<StaticSymbols>
	{
		std::unordered_map<int32_t*, char*> SymbolIdToNameMaps;

		struct EoCLibraryInfo
		{
			uint8_t const * initFunc;
			uint8_t const * freeFunc;
			uint32_t refs;
		};

		FixedString::CreateFromStringProc* ls__FixedString__CreateFromString{ nullptr };
		FixedString::GetStringProc* ls__FixedString__GetString{ nullptr };
		FixedString::IncRefProc* ls__FixedString__IncRef{ nullptr };
		FixedString::DecRefProc* ls__FixedString__DecRef{ nullptr };
		GlobalStringTable** ls__gGlobalStringTable{ nullptr };

		FileReader::CtorProc* ls__FileReader__ctor{ nullptr };
		FileReader::DtorProc* ls__FileReader__dtor{ nullptr };
		STDString** ls__PathRoots{ nullptr };

		ecl::EoCClient** ecl__EoCClient{ nullptr };
		esv::EoCServer** esv__EoCServer{ nullptr };

		ecl::EoCClient::HandleErrorProc* ecl__EoCClient__HandleError{ nullptr };

		TranslatedStringRepository** ls__gTranslatedStringRepository{ nullptr };

		void** ecl__gGameStateEventManager{ nullptr };
		ecl::GameStateEventManager__ExecuteGameStateChangedEvent ecl__GameStateEventManager__ExecuteGameStateChangedEvent{ nullptr };
		ecl::GameStateThreaded__GameStateWorker__DoWork ecl__GameStateThreaded__GameStateWorker__DoWork{ nullptr };
		esv::GameStateThreaded__GameStateWorker__DoWork esv__GameStateThreaded__GameStateWorker__DoWork{ nullptr };
		esv::GameStateMachine__Update ecl__GameStateMachine__Update{ nullptr };
		esv::GameStateMachine__Update esv__GameStateMachine__Update{ nullptr };

		esv::SurfaceActionFactory** esv__SurfaceActionFactory{ nullptr };
		esv::SurfaceActionFactory::CreateActionProc* esv__SurfaceActionFactory__CreateAction{ nullptr };
		esv::SurfaceManager::AddActionProc* esv__SurfaceManager__AddAction{ nullptr };

		SpellPrototypeManager** eoc__SpellPrototypeManager{ nullptr };
		SpellPrototype::InitProc* eoc__SpellPrototype__Init{ nullptr };

		StatusPrototypeManager** eoc__StatusPrototypeManager{ nullptr };
		StatusPrototype::InitProc* eoc__StatusPrototype__Init{ nullptr };

		PassiveManager** eoc__PassiveManager{ nullptr };
		Passive::InitProc* eoc__Passive__Init{ nullptr };

		esv::StatusMachine::CreateStatusProc* esv__StatusMachine__CreateStatus{ nullptr };
		esv::StatusMachine::ApplyStatusProc* esv__StatusMachine__ApplyStatus{ nullptr };

		DealDamageFunctor::ApplyDamageProc* eoc__DealDamageFunctor__ApplyDamage{ nullptr };

		StatsFunctorSet::ExecuteType1Proc* eoc__StatsFunctorSet__ExecuteType1{ nullptr };
		StatsFunctorSet::ExecuteType2Proc* eoc__StatsFunctorSet__ExecuteType2{ nullptr };
		StatsFunctorSet::ExecuteType3Proc* eoc__StatsFunctorSet__ExecuteType3{ nullptr };
		StatsFunctorSet::ExecuteType4Proc* eoc__StatsFunctorSet__ExecuteType4{ nullptr };
		StatsFunctorSet::ExecuteType5Proc* eoc__StatsFunctorSet__ExecuteType5{ nullptr };
		StatsFunctorSet::ExecuteType6Proc* eoc__StatsFunctorSet__ExecuteType6{ nullptr };
		StatsFunctorSet::ExecuteType7Proc* eoc__StatsFunctorSet__ExecuteType7{ nullptr };
		StatsFunctorSet::ExecuteType8Proc* eoc__StatsFunctorSet__ExecuteType8{ nullptr };

		RPGStats::LoadProc* RPGStats__Load{ nullptr };
		/*RPGStats::ParsePropertiesProc* RPGStats__ParseProperties{nullptr};
		SkillPrototypeManager** eoc__SkillPrototypeManager{ nullptr };
		StatusPrototypeManager** eoc__StatusPrototypeManager{ nullptr };*/

		RPGStats** Stats{ nullptr };
		esv::SavegameManager** esv__SavegameManager{ nullptr };

		App** AppInstance{ nullptr };

		std::map<uint8_t const *, EoCLibraryInfo> Libraries;

		ls__GlobalAllocator__AllocProc* ls__GlobalAllocator__Alloc{ nullptr };
		ls__GlobalAllocator__FreeProc* ls__GlobalAllocator__Free{ nullptr };

		GuidResourceDefinitions** ResourceDefns{ nullptr };
		ResourceManager** ResourceMgr{ nullptr };

		GlobalSwitches** ls__GlobalSwitches{ nullptr };

		inline StaticSymbols() {}
		StaticSymbols(StaticSymbols const &) = delete;
		StaticSymbols & operator = (StaticSymbols const &) = delete;

		inline GlobalSwitches * GetGlobalSwitches() const
		{
			if (ls__GlobalSwitches && *ls__GlobalSwitches) {
				return *ls__GlobalSwitches;
			} else {
				return nullptr;
			}
		}

		inline ecl::EoCClient * GetEoCClient() const
		{
			if (ecl__EoCClient == nullptr || *ecl__EoCClient == nullptr) {
				return nullptr;
			} else {
				return *ecl__EoCClient;
			}
		}

		inline esv::EoCServer* GetEoCServer() const
		{
			if (esv__EoCServer == nullptr || *esv__EoCServer == nullptr) {
				return nullptr;
			} else {
				return *esv__EoCServer;
			}
		}

		inline ModManager* GetModManagerClient() const
		{
			auto client = GetEoCClient();
			if (client == nullptr || client->ModManager == nullptr) {
				return nullptr;
			} else {
				return client->ModManager;
			}
		}

		inline ModManager* GetModManagerServer() const
		{
			auto server = GetEoCServer();
			if (server == nullptr) {
				return nullptr;
			} else {
				return &server->ModManager;
			}
		}

		inline RPGStats* GetStats() const
		{
			if (Stats && *Stats) {
				return *Stats;
			} else {
				return nullptr;
			}
		}

		inline std::optional<ecl::GameState> GetClientState() const
		{
			if (ecl__EoCClient != nullptr
				&& *ecl__EoCClient != nullptr
				&& (*ecl__EoCClient)->GameStateMachine != nullptr) {
				return (*ecl__EoCClient)->GameStateMachine->State;
			} else {
				return {};
			}
		}

		inline std::optional<esv::GameState> GetServerState() const
		{
			if (esv__EoCServer != nullptr
				&& *esv__EoCServer != nullptr
				&& (*esv__EoCServer)->GameStateMachine != nullptr) {
				return (*esv__EoCServer)->GameStateMachine->State;
			} else {
				return {};
			}
		}

		inline ecl::EntityWorld* GetClientEntityWorld() const
		{
			if (ecl__EoCClient != nullptr
				&& *ecl__EoCClient != nullptr
				&& (*ecl__EoCClient)->EntityWorld != nullptr) {
				return (*ecl__EoCClient)->EntityWorld;
			} else {
				return {};
			}
		}

		inline esv::EntityWorld* GetServerEntityWorld() const
		{
			if (esv__EoCServer != nullptr
				&& *esv__EoCServer != nullptr
				&& (*esv__EoCServer)->EntityWorld != nullptr) {
				return (*esv__EoCServer)->EntityWorld;
			} else {
				return {};
			}
		}

		inline esv::SurfaceActionFactory* GetSurfaceActionFactory() const
		{
			/*if (esv__SavegameManager != nullptr
				&& *esv__SavegameManager != nullptr
				&& (*esv__SavegameManager)->ComponentFactories.Size > 21) {
				return reinterpret_cast<esv::SurfaceActionFactory*>((*esv__SavegameManager)->ComponentFactories[21]);*/
			if (esv__SurfaceActionFactory != nullptr) {
				return *esv__SurfaceActionFactory;
			} else {
				return {};
			}
		}

		inline esv::LevelManager* GetServerLevelManager() const
		{
			/*if (esv__EoCServer != nullptr
				&& *esv__EoCServer != nullptr
				&& (*esv__EoCServer)->EntityManager != nullptr
				&& (*esv__EoCServer)->EntityManager->LevelManager != nullptr) {
				return reinterpret_cast<esv::LevelManager *>((*esv__EoCServer)->EntityManager->LevelManager);
			} else {
				return {};
			}*/
			return nullptr;
		}

		inline esv::Level* GetCurrentServerLevel() const
		{
			auto levelMgr = GetServerLevelManager();
			if (levelMgr) {
				return static_cast<esv::Level*>(levelMgr->CurrentLevel);
			} else {
				return nullptr;
			}
		}

		inline FixedString GetCurrentServerLevelName() const
		{
			auto levelMgr = GetServerLevelManager();
			if (levelMgr && levelMgr->CurrentLevel) {
				return levelMgr->CurrentLevel->LevelData->LevelDesc->LevelName;
			} else {
				return {};
			}
		}

		void CanonicalizePath(STDString & path) const;
		STDString ToPath(StringView path, PathRootType root, bool canonicalize = true) const;
		FileReaderPin MakeFileReader(StringView path, PathRootType root = PathRootType::Data, bool canonicalize = true) const;
		void DestroyFileReader(FileReader* reader);
		bool FileExists(StringView path, PathRootType root = PathRootType::Data, bool canonicalize = true) const;
	};

	extern StaticSymbols* gStaticSymbols;

	void InitStaticSymbols();

	inline StaticSymbols& GetStaticSymbols()
	{
		return *gStaticSymbols;
	}
}
