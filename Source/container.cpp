#include "../Header/container.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI{

Container::Container() :
mChildren(), mSelectedChild(-1){
  //
}


// Add components to container
void Container::pack(Component::Ptr component){
	mChildren.push_back(component);

	// Select added component if nothing is selected
	if (!hasSelection() && component->isSelectable()){
    select(mChildren.size() - 1);
  }

}

// Container is not selectable
bool Container::isSelectable() const{
    return false;
}

void Container::handleEvent(const sf::Event& event){
	if(hasSelection() && mChildren[mSelectedChild]->isActive()){
		mChildren[mSelectedChild]->handleEvent(event);
	}else if (event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up){
			selectPrevious();
		}else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down){
			selectNext();
		}else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space){
			if(hasSelection()){
        mChildren[mSelectedChild]->activate();
      }
		}
	}
}

// Draw all container components
void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  states.transform *= getTransform();

	for(const Component::Ptr & child : mChildren){
    target.draw(*child, states);
  }

}

// Component has selection if mSelectedChild index is greater than 0
bool Container::hasSelection() const{
	return mSelectedChild >= 0;
}


// Deselect old component, select new component and set selection index.
void Container::select(std::size_t index){
	if (mChildren[index]->isSelectable()){
		if(hasSelection()){
      mChildren[mSelectedChild]->deselect();
    }

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

// Select next selectable component
void Container::selectNext(){
	if (!hasSelection()){
    return;
  }

	int next = mSelectedChild;
	do{
    next = (next + 1) % mChildren.size();
  } while (!mChildren[next]->isSelectable());

	select(next);
}


// Select previous selectable component
void Container::selectPrevious(){

	if(!hasSelection()){
    return;
  }

	int prev = mSelectedChild;
	do{
    prev = (prev + mChildren.size() - 1) % mChildren.size();
  }while (!mChildren[prev]->isSelectable());

	select(prev);
}

}
