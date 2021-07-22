#include "TextWorkerAlwaysRunning.h"
#include <TextField.h>
#include <math.h>

TextWorkerAlwaysRunning::TextWorkerAlwaysRunning():
m_parent(NULL),
m_textRunningRealPos(0),
m_textRunningClipRect(0, 0, 10, 10),
m_pixelsPerMicrosecond(1),
m_textRunningThreshold(100),
m_updateTickCount(1),
m_updateTickCurrent(0)
{
}

TextWorkerAlwaysRunning::TextWorkerAlwaysRunning(void* parentObj):
m_parent(parentObj),
m_textRunningRealPos(0),
m_textRunningClipRect(0, 0, 10, 10),
m_pixelsPerMicrosecond(1),
m_textRunningThreshold(100),
m_updateTickCount(1),
m_updateTickCurrent(0)
{
    TextField* field = static_cast<TextField*>(m_parent);
    m_textRunningClipRect = sf::IntRect(0, 0, field->GetInternalBounds().width, field->GetInternalBounds().height);
    m_pixelsPerMicrosecond = field->GetTextSpeed() / 1000000.0;
    //printf("TextWorkerAlwaysRunning create, textspeed=%f, pixPer=%20.20f\n", pixPer, m_pixelsPerMicrosecond);
}

TextWorkerAlwaysRunning::~TextWorkerAlwaysRunning()
{
}

void TextWorkerAlwaysRunning::CalculateAndDrawRunning(sf::FloatRect& abounds)
{
    printf("TextWorkerAlwaysRunning::CalculateAndDrawRunning enter\n");
    TextField* field = static_cast<TextField*>(m_parent);
    sf::Text* fieldTextObj = field->GetTextObject();
    fieldTextObj->setString(L" ");
    sf::FloatRect tempBounds = fieldTextObj->getLocalBounds();
    fieldTextObj->setString(field->GetTextString());

    double spaceDistance = 3;
    switch(field->GetTextRunningSpacing())
    {
        case TextField::trsNone:spaceDistance = 3;break;
        case TextField::trsSpace:spaceDistance = tempBounds.width;break;
        case TextField::trs3Space:spaceDistance = tempBounds.width * 3;break;
        case TextField::trsRemaining:spaceDistance = field->GetInternalBounds().width - abounds.width + 1;break;
        case TextField::trs0_5:spaceDistance = field->GetInternalBounds().width / 2;break;
        case TextField::trs1_0:spaceDistance = field->GetInternalBounds().width;break;
        case TextField::trs1_5:spaceDistance = field->GetInternalBounds().width * 1.5;break;
        case TextField::trs2_0:spaceDistance = field->GetInternalBounds().width * 2;break;
    }
    if(spaceDistance < 3) spaceDistance = 3;
    spaceDistance = floor(spaceDistance);

    //getting origin and shifting to draw second text
    sf::Vector2f tempOrigin = fieldTextObj->getOrigin();
    tempOrigin.x += abounds.width + spaceDistance;
    //geting current X coordinate
    m_textRunningThreshold = tempOrigin.x - fieldTextObj->getOrigin().x;
    //drawing other texts if needed
    sf::FloatRect tempBoundsInternal = field->GetInternalBounds();
    while((tempOrigin.x + abounds.width + spaceDistance - m_textRunningThreshold) < tempBoundsInternal.width)
    {
        tempOrigin.x += abounds.width + spaceDistance;
    }

    //resizing texture
    field->GetRenderTexture()->create(floor(tempOrigin.x + abounds.width + spaceDistance), floor(field->GetInternalBounds().height), false);

    //drawing
    //drawing background color
    field->GetRenderTexture()->clear(field->GetBGColor());
    //always drawing first text in begining
    tempOrigin = sf::Vector2f(0, 0);
    fieldTextObj->setPosition(tempOrigin);
    field->GetRenderTexture()->draw(*fieldTextObj);
    //always drawing second text
    tempOrigin.x += abounds.width + spaceDistance;
    fieldTextObj->setPosition(tempOrigin);
    field->GetRenderTexture()->draw(*fieldTextObj);
    //drawing other texts if needed
    while((tempOrigin.x + abounds.width + spaceDistance - m_textRunningThreshold) < tempBoundsInternal.width)
    {
        tempOrigin.x += abounds.width + spaceDistance;
        fieldTextObj->setPosition(tempOrigin);
        field->GetRenderTexture()->draw(*fieldTextObj);
    }
    field->GetRenderTexture()->display();
}

void TextWorkerAlwaysRunning::SetUpdateTickCount(const uint32_t count, const uint64_t microPerTick)
{
    m_updateTickCount = count;
}

bool TextWorkerAlwaysRunning::Update(const sf::Int64 elapsed)
{
    //printf("TextWorkerAlwaysRunning::Update enter, cliprect=%d, Running pos=%10.10f, elapsed=%d, pixelsper=%f\n", m_textRunningClipRect.left, m_textRunningRealPos, elapsed, m_pixelsPerMicrosecond);
    TextField* field = static_cast<TextField*>(m_parent);
    field->EnsureRecalculate();

    m_textRunningRealPos += elapsed * m_pixelsPerMicrosecond;
    if(m_textRunningRealPos > m_textRunningThreshold) m_textRunningRealPos -= m_textRunningThreshold;
    int pos = m_textRunningRealPos;
    if(pos != m_textRunningClipRect.left)
    {
        //printf("condition inside Update\n");
        m_textRunningClipRect.left = pos;
        field->GetSprite()->setTextureRect(m_textRunningClipRect);
        return true;
    }else return false;
}

bool TextWorkerAlwaysRunning::UpdateTick(const sf::Int64 elapsed)
{
    TextField* field = static_cast<TextField*>(m_parent);
    field->EnsureRecalculate();

    m_updateTickCurrent++;
    if(m_updateTickCurrent >= m_updateTickCount)
    {
        m_textRunningRealPos += 1;
        if(m_textRunningRealPos > m_textRunningThreshold) m_textRunningRealPos -= m_textRunningThreshold;
        int pos = m_textRunningRealPos;
        m_textRunningClipRect.left = pos;
        field->GetSprite()->setTextureRect(m_textRunningClipRect);
        m_updateTickCurrent = 0;
        return true;
    }else return false;
}

void TextWorkerAlwaysRunning::Draw(sf::RenderWindow& window)
{
    TextField* field = static_cast<TextField*>(m_parent);
    field->EnsureRecalculate();

    if(field->GetUsingGoodFont() == false) return;
    window.draw(*(field->GetSprite()));
}

void TextWorkerAlwaysRunning::Recalculate()
{
    printf("TextWorkerAlwaysRunning::Recalculate enter\n");
    TextField* field = static_cast<TextField*>(m_parent);
    if(field->GetUsingGoodFont() == false) return;

    //calc vertical bounds
    sf::FloatRect bounds(0, 0, 0, 0);
    sf::Text* fieldTextObj = field->GetTextObject();
    fieldTextObj->setString(L"Hxj");
    fieldTextObj->setStyle(field->GetTextStyle());
    fieldTextObj->setCharacterSize(field->GetTextSize());
    fieldTextObj->setFillColor(field->GetTextColor());
    sf::FloatRect temp = fieldTextObj->getLocalBounds();
    bounds.height = temp.height;
    bounds.top = temp.top;

    fieldTextObj->setString(field->GetTextString());
    temp = fieldTextObj->getLocalBounds();
    bounds.left = temp.left;
    bounds.width = temp.width;

    float origX, origY;
    //calc vertical origin
    switch(field->GetTextVerticalAlign())
    {
        case TextField::TextAlignVectical::tavCenter: origY = floor((field->GetInternalBounds().height / 2) - (bounds.height / 2) - bounds.top) + 1;break;
        case TextField::TextAlignVectical::tavBottom: origY = floor(field->GetInternalBounds().height - bounds.height - bounds.top) - 1;break;
        default: origY = 1 - bounds.top;
    }
    //calc horiz origin
    origX = 1 - bounds.left;
    //set text origin
    fieldTextObj->setOrigin(-origX, -origY);

    CalculateAndDrawRunning(bounds);

    field->GetSprite()->setTexture(field->GetRenderTexture()->getTexture(), true);
    field->GetSprite()->setPosition(field->GetInternalBounds().left, field->GetInternalBounds().top);

    field->SetNeedsRecalculate(false);
}
