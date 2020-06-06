#pragma once

#include "Widget.hpp"

namespace mf
{
	class Image : public Widget
	{
	private:
		Image(/* args */);
		~Image();

		/**
		 * Components
		 **/
		component::Background mBackground;

	public:
		void	Render(sf::RenderWindow	*tWindow);

		/**
		 * Create
		 **/
		static Image *Create(std::string tPath);

		/**
		 * Setters
		 **/
		void	SetImage(std::string tPath);
		void	SetImage(sf::Texture &tTexture);

		Image	*SetOutlineThickness(float tThickness);
		Image	*SetOutlineColor(sf::Color tColor);

		/**
		 * Overides
		 **/
		Image			*SetPositionType(ePosition tPosType){Widget::SetPositionType(tPosType); return (this);}
		Image			*SetPosition(sf::Vector2f tPos){Widget::SetPosition(tPos); return (this);}
		Image			*SetSize(sf::Vector2f tSize){Widget::SetSize(tSize); return (this);}
	};
} // namespace mf
