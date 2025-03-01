#pragma once

#include <GameDefinitions/Base/Base.h>
#include <GameDefinitions/EntitySystem.h>
#include <GameDefinitions/EntitySystemHelpers.h>

BEGIN_SE()
class EntitySystemHelpersBase;
END_SE()

namespace bg3se::lua
{
	class EntityProxy : public Userdata<EntityProxy>, public Indexable, public Stringifiable, public Pushable
	{
	public:
		static char const* const MetatableName;

		EntityProxy(EntityHandle const& handle, EntitySystemHelpersBase* entitySystem);

		template <class T>
		bool HasComponent()
		{
			return this->entitySystem_->GetEntityComponent<T>(handle_, false) != nullptr;
		}

		template <class T>
		T* GetComponent()
		{
			return this->entitySystem_->GetEntityComponent<T>(handle_, false);
		}

		static int HasRawComponent(lua_State* L);
		static int GetComponentHandles(lua_State* L);
		static int GetComponent(lua_State* L);
		static int GetAllComponents(lua_State* L);
		static int GetEntityType(lua_State* L);
		static int GetSalt(lua_State* L);
		static int GetIndex(lua_State* L);
		static int IsAlive(lua_State* L);

		int Index(lua_State* L);
		int ToString(lua_State* L);

		inline EntityHandle const& Handle() const
		{
			return handle_;
		}

		inline EntitySystemHelpersBase* EntitySystem() const
		{
			return entitySystem_;
		}

	private:
		EntityHandle handle_;
		EntitySystemHelpersBase* entitySystem_;
	};


	class ComponentHandleProxy : public Userdata<ComponentHandleProxy>, public Indexable, public Stringifiable, public Pushable
	{
	public:
		static char const* const MetatableName;

		ComponentHandleProxy(ComponentHandle const& handle, EntitySystemHelpersBase* entitySystem);

		static int GetType(lua_State* L);
		static int GetTypeName(lua_State* L);
		static int GetSalt(lua_State* L);
		static int GetIndex(lua_State* L);
		static int GetComponent(lua_State* L);
		static void PopulateMetatable(lua_State* L);

		int Index(lua_State* L);
		int ToString(lua_State* L);

		inline ComponentHandle const& Handle() const
		{
			return handle_;
		}

		inline EntitySystemHelpersBase* EntitySystem() const
		{
			return entitySystem_;
		}

	private:
		ComponentHandle handle_;
		EntitySystemHelpersBase* entitySystem_;
	};

}
