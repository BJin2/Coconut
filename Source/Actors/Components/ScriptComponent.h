#pragma once
#include<string>
#include "ActorComponent.h"

extern "C"
{
#include "../../../Libs/Lua535/include/lua.h"
#include "../../../Libs/Lua535/include/lauxlib.h"
#include "../../../Libs/Lua535/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "..//..//..//Libs/Lua535/liblua53.a")
#endif

class ScriptComponent : public ActorComponent
{
protected:
	lua_State* pL;
	std::string name;
public:
	ScriptComponent(std::string _name);
	virtual ~ScriptComponent();

	virtual void VStart() override;
	virtual void VUpdate(float dt) override;
private:
	bool CheckLua(int r);
	bool isFileAvailable;
};