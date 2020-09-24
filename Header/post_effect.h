#ifndef POST_EFFECT__H__
#define POST_EFFECT__H__

#include <SFML/System/NonCopyable.hpp>


namespace sf{
	class RenderTarget;
	class RenderTexture;
	class Shader;
}

class PostEffect : sf::NonCopyable{
	public:
		virtual ~PostEffect();
		virtual void apply(const sf::RenderTexture & input, sf::RenderTarget & output) = 0;
		static bool isSupported();
	protected:
		static void applyShader(const sf::Shader & shader, sf::RenderTarget & output);
};

#endif
