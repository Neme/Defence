#ifndef __CONST_GAME_H__
#define __CONST_GAME_H__

#if defined(_MSC_VER)
#if _MSC_VER < 1900
#define _constexpr const
#define _noexcept throw()
#endif
#endif

enum class SceneTags : int {
	SCENE_NONE,
	SCENE_GAME,
};


#endif // __CONST_GAME_H__
