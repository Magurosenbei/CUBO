#pragma once

//class GameStat
//{
//public:
//	static	bool	PlayerDead;
//	static	int		TimeLimit;
//	static	int		CurrentTime;
//
//	static	int		Level;
//	static	int		MaxLevel;
//
//	inline	static	bool	HasPlayerDied()	{	return	PlayerDead;	}
//	inline	static	void	GoNextLevel()	{	(Level <  MaxLevel}? Level ++ : Level = MaxLevel;	}
//	inline	static	bool	IsLastLevel()	{	return	(Level == MaxLevel);						}
//};

#define STD_COLORCHANGEFACTOR 3.0f
#define STD_BOXDROPDURATION 0.7f

#define STD_COLORCHANGEFACTOR_MAX 0.75f
#define STD_BOXDROPDURATION_MAX 0.25f

#define STD_DIFFICULTYELAPSED 2.3f

extern	float	g_fColorChangeFactor;
extern	float	g_fBoxDropDuration;