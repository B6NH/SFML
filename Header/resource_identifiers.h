#ifndef RESOURCE_IDENTIFIERS__H__
#define RESOURCE_IDENTIFIERS__H__

namespace sf{
	class Texture;
	class Font;
}

// namespace Textures{
// 	enum ID{
// 		Eagle,
// 		Raptor,
// 		Avenger,
// 		Bullet,
// 		Missile,
// 		Desert,
// 		HealthRefill,
// 		MissileRefill,
// 		FireSpread,
// 		FireRate,
// 		TitleScreen,
// 		ButtonNormal,
// 		ButtonSelected,
// 		ButtonPressed
// 	};
// }

namespace Textures{
	enum ID{
		Entities,
		Jungle,
		TitleScreen,
		Buttons,
		Explosion,
		Particle,
		FinishLine
	};
};


namespace Fonts{
	enum ID{
		Main,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
