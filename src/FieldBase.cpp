#include "FieldBase.h"

FieldBase::FieldBase() : FieldBase(sf::FloatRect(0, 0, 100, 100))
{
}

FieldBase::FieldBase(sf::FloatRect bounds):
    m_needsRecalculate(true),
    m_renderSprite(NULL),
    m_renderTexture(NULL),
    m_debugRect(NULL),
    m_boundRect(bounds),
    m_BGColor(sf::Color::Transparent),
    m_elapsedMicroseconds(0),
    m_debugMode(false)
{
    m_renderTexture = new sf::RenderTexture();
    m_renderTexture->create(m_boundRect.width, m_boundRect.height);
    m_renderTexture->setSmooth(true);
    m_renderSprite = new sf::Sprite(m_renderTexture->getTexture());
    m_renderSprite->setPosition(m_boundRect.left, m_boundRect.top);
    m_debugRect = new sf::RectangleShape();
    m_debugRect->setPosition(m_boundRect.left + 1, m_boundRect.top + 1);
    m_debugRect->setSize(sf::Vector2f(m_boundRect.width - 2, m_boundRect.height - 2));
    m_debugRect->setFillColor(sf::Color::Transparent);
    m_debugRect->setOutlineColor(sf::Color(0, 255, 0, 100));
    m_debugRect->setOutlineThickness(1.0);
}

FieldBase::~FieldBase()
{
    delete m_renderSprite;
    delete m_renderTexture;
    delete m_debugRect;
}

sf::Color FieldBase::GetBGColor() const
{
    return m_BGColor;
}

void FieldBase::SetBGColor(const sf::Color value)
{
    m_BGColor = value;
}

sf::Uint64 FieldBase::GetInternalMicro() const
{
    return m_elapsedMicroseconds;
}

void FieldBase::SetInternalMicro(sf::Uint64 value)
{
    m_elapsedMicroseconds = value;
}

sf::FloatRect FieldBase::GetInternalBounds() const
{
    return m_boundRect;
}

void FieldBase::SetInternalBounds(sf::FloatRect value)
{
    m_boundRect = value;
}

bool FieldBase::GetDebugMode() const
{
    return m_debugMode;
}

void FieldBase::SetDebugMode(bool value)
{
    m_debugMode = value;
}

bool FieldBase::GetNeedsRecalculate() const
{
    return m_needsRecalculate;
}

void FieldBase::SetNeedsRecalculate(const bool value)
{
    m_needsRecalculate = value;
}

sf::Sprite* FieldBase::GetSprite() const
{
    return m_renderSprite;
}

sf::RenderTexture* FieldBase::GetRenderTexture() const
{
    return m_renderTexture;
}

sf::RectangleShape* FieldBase::GetDebugRect() const
{
    return m_debugRect;
}
