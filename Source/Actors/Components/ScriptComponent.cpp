#include "ScriptComponent.h"
#include <iostream>
#include <Windows.h>
#include "../../Engines/Game.h"

ScriptComponent::ScriptComponent(std::string _name)
{
	pL = luaL_newstate();
	luaL_openlibs(pL);
	name = _name;
	isFileAvailable = CheckLua(luaL_dofile(pL, name.c_str()));
}

ScriptComponent::~ScriptComponent()
{
	lua_close(pL);
}

void ScriptComponent::VInitialize()
{
	if (isFileAvailable)
	{
		lua_getglobal(pL, "Initialize");
		if (lua_isfunction(pL, -1))
		{
			if (CheckLua(lua_pcall(pL, 0, 1, 0)))
			{
			}
		}
	}
}

void ScriptComponent::VStart()
{
	if (isFileAvailable)
	{
		lua_getglobal(pL, "Start");
		if (lua_isfunction(pL, -1))
		{
			//lua_pcall = Calls a function in protected mode. 
			// int lua_pcall (lua_State *L, int nargs, int nresults, int msgh);
			if (CheckLua(lua_pcall(pL, 0, 1, 0)))
			{
				//printf("Lua start");
				/*HWND hWnd = Game::hWnd;
				MessageBox(hWnd, ((std::string)lua_tostring(pL, -1)).c_str(), NULL, MB_OK);*/
				//std::cout << "Lua file name: " << name << " and Start function returns : [ "
				//	<< (std::string)lua_tostring(pL, -1) << " ] " << std::endl;
			}
		}
	}
}

void ScriptComponent::VUpdate(float dt)
{
	if (isFileAvailable)
	{
		lua_getglobal(pL, "Update");
		if (lua_isfunction(pL, -1))
		{
			if (CheckLua(lua_pcall(pL, 0, 1, 0)))
			{
			/*	HWND hWnd = Game::hWnd;
				HDC hdc = GetDC(hWnd);
				LPCSTR message = ((std::string)lua_tostring(pL, -1)).c_str();
				TextOut(hdc, 10, 200, ((std::string)lua_tostring(pL, -1)).c_str(), strlen(message));*/
				/*std::cout << "Lua file name: " << name << " and Update function returns: [ "
					<< (std::string)lua_tostring(pL, -1) << " ] " << std::endl;*/
			}
		}
	}
}

bool ScriptComponent::CheckLua(int r)
{
	if (r != LUA_OK)
	{
		HWND hWnd = Game::hWnd;
		std::string errormsg = lua_tostring(pL, -1);
		MessageBox(hWnd, (errormsg).c_str(), NULL, MB_OK);
		return false;
	}
	return true;
}