#pragma once

// messages
enum ENGINE_API ENetMessage {
	MSG_NONE = 0,
	SYS_CONNECT,
	SYS_DISCONNECT,

	M_CHAT,
	M_REMOTE_UPDATE,			
	M_REMOTE_WEAPON_CHANGE,	
	M_REMOTE_FIRE,			
	M_REMOTE_FIRE_STOP,			
	M_REMOTE_KILLED,

	net_last,
	net_forcedword = DWORD(-1)
};

// registered messages
struct ENGINE_API	MSG_DEF
{
	DWORD	dwType;
	char*	pName;
	BOOL	bBroadcast;
};

extern 	void	net_RegisterMessages	();
extern 	void	net_LogMessage			(char *op, DWORD dwType);
extern 			vector<MSG_DEF*>		net_messages;
