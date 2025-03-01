#pragma once

#include <Lua/LuaHelpers.h>
#include <Lua/LuaSerializers.h>
#include <Lua/Shared/LuaLifetime.h>

namespace bg3se::lua
{
	LifetimeHandle GetCurrentLifetime();

	class SetProxyImplBase
	{
	public:
		inline virtual ~SetProxyImplBase() {};
		virtual char const* GetTypeName() const = 0;
		virtual void* GetRaw() = 0;
		virtual bool HasElement(lua_State* L, int luaIndex) = 0;
		virtual bool AddElement(lua_State* L, int luaIndex) = 0;
		virtual bool RemoveElement(lua_State* L, int luaIndex) = 0;
		virtual int Next(lua_State* L, int index) = 0;
		virtual unsigned Length() = 0;
	};

	
	template <class T>
	class MultiHashSetProxyImpl : public SetProxyImplBase
	{
	public:
		static_assert(!std::is_pointer_v<T>, "MultiHashSetProxyImpl template parameter should not be a pointer type!");

		MultiHashSetProxyImpl(LifetimeHandle const& lifetime, MultiHashSet<T> * obj)
			: object_(obj), lifetime_(lifetime)
		{}
		
		~MultiHashSetProxyImpl() override
		{}

		T* Get() const
		{
			return object_;
		}

		void* GetRaw() override
		{
			return object_;
		}

		char const* GetTypeName() const override
		{
			return TypeInfo<T>::TypeName;
		}

		bool HasElement(lua_State* L, int luaIndex) override
		{
			T element;
			lua_pushvalue(L, luaIndex);
			LuaRead(L, element);
			lua_pop(L, 1);

			return object_->FindIndex(element) != -1;
		}

		bool AddElement(lua_State* L, int luaIndex) override
		{
			T element;
			lua_pushvalue(L, luaIndex);
			LuaRead(L, element);
			lua_pop(L, 1);

			object_->Add(element);
			return true;
		}

		bool RemoveElement(lua_State* L, int luaIndex) override
		{
			T element;
			lua_pushvalue(L, luaIndex);
			LuaRead(L, element);
			lua_pop(L, 1);

			auto index = object_->FindIndex(element);
			// FIXME - add support for remove() in hashsets!
			// object_->RemoveIndex(index);
			return true;
		}

		unsigned Length() override
		{
			return object_->Keys.Size();
		}

		int Next(lua_State* L, int key) override
		{
			if (key >= -1 && key < (int)object_->Keys.Size() - 1) {
				push(L, ++key);
				LuaWrite(L, object_->Keys[key]);
				return 2;
			} else {
				return 0;
			}
		}

	private:
		MultiHashSet<T>* object_;
		LifetimeHandle lifetime_;
	};


	class SetProxy : private Userdata<SetProxy>, public Indexable, public NewIndexable,
		public Lengthable, public Iterable, public Stringifiable, public Pushable, public GarbageCollected
	{
	public:
		static char const * const MetatableName;

		template <class T>
		inline static MultiHashSetProxyImpl<T>* Make(lua_State* L, MultiHashSet<T>* object, LifetimeHandle const& lifetime)
		{
			auto self = NewWithExtraData(L, sizeof(MultiHashSetProxyImpl<T>), lifetime);
			return new (self->GetImpl()) MultiHashSetProxyImpl<T>(lifetime, object);
		}

		inline SetProxyImplBase* GetImpl()
		{
			return reinterpret_cast<SetProxyImplBase*>(this + 1);
		}

		inline bool IsAlive(lua_State* L) const
		{
			return lifetime_.IsAlive(L);
		}

		template <class T>
		T* Get(lua_State* L)
		{
			if (!lifetime_.IsAlive(L)) {
				return nullptr;
			}
			
			if (strcmp(GetImpl()->GetTypeName(), TypeInfo<T>::TypeName) == 0) {
				return reinterpret_cast<T*>(GetImpl()->GetRaw(L));
			} else {
				return nullptr;
			}
		}

	private:
		LifetimeHandle lifetime_;

		SetProxy(LifetimeHandle const& lifetime)
			: lifetime_(lifetime)
		{}

		~SetProxy()
		{
			GetImpl()->~SetProxyImplBase();
		}

	protected:
		friend Userdata<SetProxy>;

		int Index(lua_State* L);
		int NewIndex(lua_State* L);
		int Length(lua_State* L);
		int Next(lua_State* L);
		int ToString(lua_State* L);
		int GC(lua_State* L);
	};

	template <class T>
	struct IsSetLike { static constexpr bool Value = false; };

	template <class TK>
	struct IsSetLike<MultiHashSet<TK>>
	{ 
		static constexpr bool Value = true;
		using TKey = TK;
	};

	template <class TK>
	struct IsSetLike<VirtualMultiHashSet<TK>>
	{ 
		static constexpr bool Value = true;
		using TKey = TK;
	};

	template <class T>
	inline void push_set_proxy(lua_State* L, LifetimeHandle const& lifetime, T* v)
	{
		SetProxy::Make<T>(L, v, lifetime);
	}

	template <class T>
	inline T* checked_get_set_proxy(lua_State* L, int index)
	{
		auto proxy = Userdata<SetProxy>::CheckUserData(L, index);
		auto const& typeName = TypeInfo<T>::TypeName;
		if (strcmp(proxy->GetImpl()->GetTypeName(), typeName) == 0) {
			auto obj = proxy->Get<T>();
			if (obj == nullptr) {
				luaL_error(L, "Argument %d: got Set<%s> whose lifetime has expired", index, typeName);
				return nullptr;
			} else {
				return obj;
			}
		} else {
			luaL_error(L, "Argument %d: expected Set<%s>, got Set<%s>", index, typeName, proxy->GetImpl()->GetTypeName());
			return nullptr;
		}
	}
}
