#include <stdafx.h>
#include <Extender/ScriptExtender.h>
#include <Extender/Shared/ScriptHelpers.h>
#include <Lua/LuaSerializers.h>

namespace bg3se::lua::utils
{
	void AddVoiceMetaData(lua_State * L, char const* speakerGuid, char const* translatedStringKey, char const* source, 
		float length, std::optional<int> priority)
	{
		/*auto speakerMgr = GetStaticSymbols().eoc__SpeakerManager;
		if (speakerMgr == nullptr || *speakerMgr == nullptr) {
			OsiError("Speaker manager not initialized!");
			return;
		}

		auto speaker = (*speakerMgr)->SpeakerMetaDataHashMap->Insert(MakeFixedString(speakerGuid));
		auto voiceMeta = speaker->Insert(MakeFixedString(translatedStringKey));
		voiceMeta->CodecID = 4;
		voiceMeta->IsRecorded = true;
		voiceMeta->Length = (float)length;
		voiceMeta->Priority = priority ? *priority : 0;

		auto path = GetStaticSymbols().ToPath(source, PathRootType::Data);
		voiceMeta->Source.Name = path;*/
	}

	WrapLuaFunction(AddVoiceMetaData)

	STDString GetTranslatedString(lua_State* L, char const* translatedStringKey, std::optional<char const*> fallbackText)
	{
		STDString translated;
		if (script::GetTranslatedString(translatedStringKey, translated)) {
			return translated;
		} else {
			return fallbackText ? *fallbackText : "";
		}
	}

	WrapLuaFunction(GetTranslatedString)

	std::tuple<STDString, FixedString> GetTranslatedStringFromKey(lua_State* L, FixedString key)
	{
		/*TranslatedString translated;
		if (script::GetTranslatedStringFromKey(key, translated)) {
			return { ToUTF8(translated.Handle.ReferenceString), translated.Handle.Handle };
		} else {*/
			return {};
		//}
	}

	WrapLuaFunction(GetTranslatedStringFromKey)

	unsigned NextDynamicStringHandleId{ 1 };

	std::optional<STDString> CreateTranslatedString(lua_State* L, char const* keyStr, char const* value)
	{
		auto key = FixedString(keyStr);

		STDString handleStr = "ExtStr_";
		handleStr += std::to_string(NextDynamicStringHandleId++);
		FixedString handle(handleStr.c_str());

		if (script::CreateTranslatedStringKey(key, handle)) {
			if (script::CreateTranslatedString(handle, value)) {
				return handleStr;
			}
		}

		return {};
	}

	WrapLuaFunction(CreateTranslatedString)

	bool CreateTranslatedStringKey(lua_State* L, char const* keyStr, char const* handleStr)
	{
		FixedString key(keyStr);
		FixedString handle(handleStr);
		return script::CreateTranslatedStringKey(key, handle);
	}

	WrapLuaFunction(CreateTranslatedStringKey)

	bool CreateTranslatedStringHandle(lua_State* L, char const* handleStr, char const* value)
	{
		FixedString handle(handleStr);

		return script::CreateTranslatedString(handle, value);
	}

	WrapLuaFunction(CreateTranslatedStringHandle)

	void RegisterLocalizationLib(lua_State * L)
	{
		static const luaL_Reg locaLib[] = {
			{"AddVoiceMetaData", AddVoiceMetaDataWrapper},
			{"GetTranslatedString", GetTranslatedStringWrapper},
			{"GetTranslatedStringFromKey", GetTranslatedStringFromKeyWrapper},
			{"CreateTranslatedString", CreateTranslatedStringWrapper},
			{"CreateTranslatedStringKey", CreateTranslatedStringKeyWrapper},
			{"CreateTranslatedStringHandle", CreateTranslatedStringHandleWrapper},
			{0,0}
		};

		RegisterLib(L, "Localization", locaLib);
	}
}
