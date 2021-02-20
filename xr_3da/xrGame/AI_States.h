#pragma once

namespace AI {
	enum AI_States 
	{
		aiDie					=0,
			
		aiGoInThisDirection,	// идти по направлению: "бесконечно" 
		aiGoToThatPosition,		// идти в заданную позицию:			
		aiHoldPosition,			// удерживать позицию				
		aiFreeHunting,			// свободная охота					
		aiNeedBackup,			// идти ко мне (нужна помощь)		
			
		aiAttack,				// attack mode
		aiPursuit,				// преследование после потери цели
		aiRetreating,			// retreating
			
		aiLAST,
		aiFORCEDWORD			= DWORD(-1)
	};
	class State
	{
	public:
		AI_States	Type;
		
		AI_State(AI_States T) : Type(T) {};
		
		virtual BOOL Parse		(CCustomMonster* Me)=0;	// returns true if state changes
	};
	//----------------------------------------------------------------------------------
	class _GoDirection			: public State
	{
	public:
		Fvector					direction;

		_GoDirection(Fvector& D) : State(aiGoInThisDirection)
		{
			direction.set		(D);
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _GoPosition			: public State
	{
	public:
		Fvector					position;
		DWORD					nodeID;

		_GoPosition(Fvector& P) : State(aiGoToThatPosition)
		{
			position.set		(P);
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _HoldPosition			: public State
	{
	public:
		Fvector					position;
		DWORD					nodeID;

		_HoldPosition(Fvector& P) : State(aiHoldPosition)
		{
			position.set		(P);
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _FreeHunting			: public State
	{
	public:
		_FreeHunting()			: State(aiFreeHunting)
		{
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _NeedBackup			: public State
	{
	public:
		_NeedBackup()			: State(aiNeedBackup)
		{
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _Attack				: public State
	{
	public:
		CEntity*				victim;				// жертва
		_Attack(CEntity* E)		: State(aiAttack)
		{
			victim				= E;
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _Pursuit				: public State
	{
	public:
		CEntity*				victim;				// жертва
		_Pursuit(CEntity* E)	: State(aiPursuit)
		{
			victim				= E;
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
	class _Retreating			: public State
	{
	public:
		_Retreating()			: State(aiPursuit)
		{
		}
		virtual BOOL Parse		(CCustomMonster* Me);
	};
	//----------------------------------------------------------------------------------
};
