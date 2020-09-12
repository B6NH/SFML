#ifndef RESOURCE_IDENTIFIERS__H__
#define RESOURCE_IDENTIFIERS__H__

namespace sf{
	class Texture;
	class Font;
}

namespace Textures{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed
	};
}


namespace Fonts{
	enum ID{
		Main,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif
