#ifndef RESOURCE_IDENTIFIERS__H__
#define RESOURCE_IDENTIFIERS__H__

namespace sf{
	class Texture;
	class Font;
	class Shader;
}

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

namespace Shaders{
	enum ID{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}


namespace Fonts{
	enum ID{
		Main,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;

#endif
