#include "Slider.hpp"

namespace mf
{
	Slider::Slider(/* args */)
	:mBackground(&mTransform.mPosition, &mTransform.mSize)
	{
		LoadClickFunction();
	}

	Slider::~Slider()
	{
	}


	void		Slider::LoadClickFunction()
	{
		component::EventManager	*manager = &mEventManager;
		eDirection *direction = &mDirection;

		mEventManager.AddEventListener(eEvent::LEFT_CLICK, [this, manager, direction] {
			float	relpos;
			if (*direction == eDirection::HORIZONTAL)
				relpos = (manager->GetMousePosition().x - this->GetPosition().x) / (this->GetSize().x  - mButton->GetSize().x) - ((mButton->GetSize().x / 2.f) / this->GetSize().x);
			else
				relpos = (manager->GetMousePosition().y - this->GetPosition().y) / (this->GetSize().y  - mButton->GetSize().y) - ((mButton->GetSize().y / 2.f) / this->GetSize().y);
			this->SetValue(relpos);
			this->mChangeListener();
		});
	}

	void		Slider::SetButtonHeight()
	{
		if (mDirection == eDirection::HORIZONTAL)
			mButton->SetSize(mButton->GetSize().x, mTransform.mSize.y);
		else
			mButton->SetSize(mTransform.mSize.x, mButton->GetSize().y);
	}

	Slider      *Slider::Create()
	{
		Slider   *slider = new Slider();
		slider->mButton = Button::Create();
		slider->AddWidget(slider->mButton);
		slider->SetSize(200, 40);
		slider->SetOutlineColor(sf::Color::Black)->SetOutlineThickness(1.f);
		slider->mButton->SetSize(30, 40)->SetBackground(sf::Color::Red);
		slider->mButton->SetPosition(0, 0);
		return (slider);
	}

	void		Slider::Render(sf::RenderWindow *tWindow)
	{
		mBackground.Draw(tWindow);
		Widget::Render(tWindow);
	}

	void		Slider::HandleEvent(sf::Event &tEvent)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mEventManager.GetEvent() == eEvent::INSIDE)
		{
			if (mDirection == eDirection::HORIZONTAL)
				SetValue((mEventManager.GetMousePosition().x - this->GetPosition().x) / (this->GetSize().x  - mButton->GetSize().x) - ((mButton->GetSize().x / 2.f) / this->GetSize().x));
			else
				SetValue((mEventManager.GetMousePosition().y - this->GetPosition().y) / (this->GetSize().y  - mButton->GetSize().y) - ((mButton->GetSize().y / 2.f) / this->GetSize().y));
			this->mChangeListener();
		}
		Widget::HandleEvent(tEvent);
	}


	Slider		*Slider::SetValue(float tValue)
	{
		mValue = tValue;
		float newpos;
		if (mDirection == eDirection::HORIZONTAL)
		{
			newpos = tValue * (mTransform.mSize.x - mButton->GetSize().x);
			newpos = std::clamp(newpos, 0.f, mTransform.mSize.x - mButton->GetSize().x);
			mButton->SetPosition(newpos, 0);
		}
		else
		{
			newpos = tValue * (mTransform.mSize.y - mButton->GetSize().y);
			newpos = std::clamp(newpos, 0.f, mTransform.mSize.y - mButton->GetSize().y);
			mButton->SetPosition(0, newpos);
		}
		return (this);
	};

	Slider		*Slider::SetChangeEventListener(std::function<void()> tListener)
	{
		mChangeListener = tListener;
		return (this);
	}


	Slider		*Slider::SetDirection(eDirection tDirection)
	{
		mDirection = tDirection;
		SetButtonHeight();
		return (this);
	}

	Slider		*Slider::SetSize(sf::Vector2f tSize)
	{
		Widget::SetSize(tSize);
		SetButtonHeight();
		return (this);
	}

	Slider		*Slider::SetSize(float tX, float tY)
	{
		Widget::SetSize(tX, tY);
		SetButtonHeight();
		return (this);
	}

}
