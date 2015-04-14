#ifndef __CONST_GAME_H__
#define __CONST_GAME_H__

#if defined(_MSC_VER)
#if _MSC_VER < 1900
#define CROW_MSVC_WORKAROUND
#define constexpr const
#define noexcept throw()
#endif
#endif

enum class NodeTags : int {
	TAG_REMOVE = -13,
	TAG_TOWER = 1,
};

enum class SceneTags : int {
	SCENE_NONE,
	SCENE_GAME,
};

enum class LayerTags : int {
	LAYER_NONE,
	LAYER_GAME,
	LAYER_GUI,
};


#endif // __CONST_GAME_H__