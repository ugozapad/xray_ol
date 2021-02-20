#include "stdafx.h"
#include "net_messages.h"
#include "log.h"

MSG_DEF _messages[net_last] = {
	{ MSG_NONE,					"msg_none",					false	},
	{ SYS_CONNECT,				"sys_connect",				true	},
	{ SYS_DISCONNECT,			"sys_disconnect",			true	},
	{ M_CHAT,					"m_chat",					true	},
	{ M_REMOTE_UPDATE,			"m_remote_update",			true	},
	{ M_REMOTE_WEAPON_CHANGE,	"m_remote_weapon_change",	true	},
	{ M_REMOTE_FIRE,			"m_remote_fire",			true	},
	{ M_REMOTE_FIRE_STOP,		"m_remote_fire_stop",		true	},
	{ M_REMOTE_KILLED,			"m_remote_killed",			true	}
};

vector<MSG_DEF*>		net_messages;

void net_RegisterMessages()
{
	MSG_DEF *pdef  = _messages;
	int		 count = net_last;
	MSG_DEF *plast = pdef+count;
	while (pdef<plast) {
		DWORD dwType = pdef->dwType;
		if (net_messages.size()<=dwType) {
			// resize net_messages
			net_messages.resize(dwType+2);
		}
		net_messages[dwType] = pdef;
		pdef++;
	}
}

void net_LogMessage(char *op, DWORD dwType) {
	Msg("* NET [%8s] :: %s", op, net_messages[dwType]->pName);
}
