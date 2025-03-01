#include <stdafx.h>
#include <Extender/ScriptExtender.h>
#include <Lua/LuaBinding.h>
#include <Lua/LuaSerializers.h>
#include <Lua/Shared/Proxies/LuaPropertyMapHelpers.h>
#include <Lua/Shared/Proxies/LuaObjectProxy.inl>
#include <Lua/Shared/Proxies/LuaArrayProxy.inl>
#include <Lua/Shared/Proxies/LuaSetProxy.inl>
#include <Lua/Shared/Proxies/LuaMapProxy.inl>
#include <Lua/Shared/LuaEvent.inl>
#include <Lua/Shared/LuaCharacter.inl>
#include <Lua/Shared/LuaItem.inl>
#include <Lua/Shared/StatEntries.inl>
#include <Lua/Shared/StatEnumerators.inl>
#include <Lua/Shared/StatAttributes.inl>
#include <Lua/Shared/StatMisc.inl>


namespace bg3se::lua::stats
{
	void PushStatsFunctor(lua_State* L, LifetimeHandle const& lifetime, StatsFunctorBase* functor)
	{
#define V(cls) case cls::FunctorId: \
		MakeObjectRef(L, lifetime, static_cast<cls*>(functor)); \
		break;

		switch (functor->TypeId) {
			V(CustomDescriptionFunctor)
			V(ResurrectFunctor)
			V(SabotageFunctor)
			V(SummonFunctor)
			V(ForceFunctor)
			V(DouseFunctor)
			V(SwapPlacesFunctor)
			V(EqualizeFunctor)
			V(PickupFunctor)
			V(CreateSurfaceFunctor)
			V(CreateConeSurfaceFunctor)
			V(RemoveStatusFunctor)
			V(ExecuteWeaponFunctorsFunctor)
			V(TeleportSourceFunctor)
			V(SetStatusDurationFunctor)
			V(UseAttackFunctor)
			V(BreakConcentrationFunctor)
			V(RestoreResourceFunctor)
			V(SpawnFunctor)
			V(StabilizeFunctor)
			V(UnlockFunctor)
			V(ResetCombatTurnFunctor)
			V(RemoveAuraByChildStatusFunctor)
			V(ApplyStatusFunctor)
			V(DealDamageFunctor)
			V(UseActionResourceFunctor)
			V(CreateExplosionFunctor)
			V(SurfaceChangeFunctor)
			V(ApplyEquipmentStatusFunctor)
			V(RegainHitPointsFunctor)
			V(UseSpellFunctor)
			V(SummonInInventoryFunctor)
			V(SpawnInInventoryFunctor)
			V(RemoveUniqueStatusFunctor)
			V(DisarmWeaponFunctor)
			V(ExtenderFunctor)

		default:
			ERR("Unable to push unknown stats functor type %d to Lua!", functor->TypeId);
			push(L, nullptr);
			break;
		}
#undef V
	}

	StatsFunctorSetProxy::StatsFunctorSetProxy(LifetimeHandle const& lifetime, StatsFunctorSet* obj)
		: object_(obj), lifetime_(lifetime)
	{}

	StatsFunctorSetProxy::~StatsFunctorSetProxy()
	{}

	void* StatsFunctorSetProxy::GetRaw()
	{
		return object_;
	}

	char const* StatsFunctorSetProxy::GetTypeName() const
	{
		return "StatsFunctorSet";
	}

	bool StatsFunctorSetProxy::GetElement(lua_State* L, unsigned arrayIndex)
	{
		if (object_ != nullptr && arrayIndex > 0 && arrayIndex <= object_->FunctorList.Size) {
			PushStatsFunctor(L, lifetime_, object_->FunctorList[arrayIndex - 1]);
			return true;
		} else {
			return false;
		}
	}

	bool StatsFunctorSetProxy::SetElement(lua_State* L, unsigned arrayIndex, int luaIndex)
	{
		return false;
	}

	unsigned StatsFunctorSetProxy::Length()
	{
		return object_ != nullptr ? object_->FunctorList.Size : 0;
	}

	int StatsFunctorSetProxy::Next(lua_State* L, int key)
	{
		if (object_ != nullptr && key >= 0 && key < (int)object_->FunctorList.Size) {
			push(L, ++key);
			PushStatsFunctor(L, lifetime_, object_->FunctorList[key - 1]);
			return 2;
		} else {
			return 0;
		}
	}


	void RegisterStatsLib(lua_State* L)
	{
		static const luaL_Reg statsLib[] = {
			{"GetAllStats", GetAllStats},
			{"GetStatsLoadedBefore", GetStatsLoadedBefore},

			{"GetStat", GetStat},
			{"CreateStat", CreateStat},

			{"GetModifierAttributes", GetModifierAttributes},
			{"EnumIndexToLabel", EnumIndexToLabel},
			{"EnumLabelToIndex", EnumLabelToIndex},

			{"UpdateTreasureTable", UpdateTreasureTable},
			{"UpdateTreasureCategory", UpdateTreasureCategory},

			/*{"ExecuteSkillPropertiesOnTarget", ExecuteSkillPropertiesOnTarget},
			{"ExecuteSkillPropertiesOnPosition", ExecuteSkillPropertiesOnPosition},*/
			{0,0}
		};

		RegisterLib(L, "Stats", statsLib);
		RegisterStatsObjects(L);
	}
}

namespace bg3se::lua
{
	void InitObjectProxyPropertyMaps();

	void RegisterSharedLibraries(lua_State* L)
	{
		Userdata<ObjectProxy>::RegisterMetatable(L);
		Userdata<ArrayProxy>::RegisterMetatable(L);
		Userdata<SetProxy>::RegisterMetatable(L);
		Userdata<MapProxy>::RegisterMetatable(L);
		Userdata<EventObject>::RegisterMetatable(L);
		InitObjectProxyPropertyMaps();

		RegisterEntityProxy(L);
		stats::RegisterStatsLib(L);
		utils::RegisterStaticDataLib(L);
		utils::RegisterUtilsLib(L);
		utils::RegisterLocalizationLib(L);
		utils::RegisterJsonLib(L);
		utils::RegisterIOLib(L);
		utils::RegisterMathLib(L);
	}
}
