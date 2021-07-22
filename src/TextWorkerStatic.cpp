#include "TextWorkerStatic.h"
#include <TextField.h>
#include <math.h>

TextWorkerStatic::TextWorkerStatic():
    m_parent(NULL)
{
}

TextWorkerStatic::TextWorkerStatic(void* parentObj):
    m_parent(parentObj)
{
}

TextWorkerStatic::~TextWorkerStatic()
{

}

void TextWorkerStatic::SetUpdateTickCount(const uint32_t count, const uint64_t microPerTick)
{
}

bool TextWorkerStatic::Update(const sf::Int64 elapsed)
{
    TextField* field = static_cast<TextField*>(m_parent);
    field->EnsureRecalculate();
    return false;
}

bool TextWorkerStatic::UpdateTick(const sf::Int64 elapsed)
{
    TextField* field = static_cast<TextField*>(m_parent);
    field->EnsureRecalculate();
    return false;
}

void TextWorkerStatic::Draw(sf::RenderWindow& window)
{
    //printf("Worker static draw\n");
    TextField* field = static_cast<TextField*>(m_parent);
    field->EnsureRecalculate();

    if(field->GetUsingGoodFont() == false) return;
    window.draw(*(field->GetSprite()));
}

void TextWorkerStatic::Recalculate()
{
    TextField* field = static_cast<TextField*>(m_parent);
    if(field->GetUsingGoodFont() == false) return;

    sf::FloatRect bounds(0, 0, 0, 0);
    sf::Text* fieldTextObj = field->GetTextObject();
    fieldTextObj->setString(L"Hxj");
    fieldTextObj->setStyle(field->GetTextStyle());
    fieldTextObj->setCharacterSize(field->GetTextSize());
    fieldTextObj->setFillColor(field->GetTextColor());
    sf::FloatRect temp = fieldTextObj->getLocalBounds();
    bounds.height = temp.height;
    bounds.top = temp.top;
    //calc horizontal bounds
    fieldTextObj->setString(field->GetTextString());
    temp = fieldTextObj->getLocalBounds();
    bounds.left = temp.left;
    bounds.width = temp.width;

    float origX, origY;
    //calc horiz origin
    switch(field->GetTextHorizontalAlign())
    {
        case TextField::TextAlignHorizontal::tahCenter: origX = floor((field->GetInternalBounds().width / 2) - (bounds.width / 2) - bounds.left) + 1;break;
        case TextField::TextAlignHorizontal::tahRight: origX = (field->GetInternalBounds().width - bounds.width - bounds.left) - 1;break;
        default: origX = 1 - bounds.left;
    }
    //calc vertical origin
    switch(field->GetTextVerticalAlign())
    {
        case TextField::TextAlignVectical::tavCenter: origY = floor((field->GetInternalBounds().height / 2) - (bounds.height / 2) - bounds.top) + 1;break;
        case TextField::TextAlignVectical::tavBottom: origY = floor(field->GetInternalBounds().height - bounds.height - bounds.top) - 1;break;
        default: origY = 1 - bounds.top;
    }
    //set text origin
    fieldTextObj->setOrigin(-origX, -origY);

    //draw
    field->GetRenderTexture()->clear(field->GetBGColor());
    field->GetRenderTexture()->draw(*fieldTextObj);
    field->GetRenderTexture()->display();

    field->GetSprite()->setTexture(field->GetRenderTexture()->getTexture(), true);
    field->GetSprite()->setPosition(field->GetInternalBounds().left, field->GetInternalBounds().top);

    field->SetNeedsRecalculate(false);
}
