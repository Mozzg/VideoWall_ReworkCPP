#ifndef FIELDBASE_H
#define FIELDBASE_H

#include <SFML/Graphics.hpp>


class FieldBase
{
    public:
        FieldBase();
        FieldBase(sf::FloatRect bounds);
        virtual ~FieldBase();

        virtual bool Update(const sf::Uint64 elapsedMicro) = 0;
        virtual bool UpdateTick(const sf::Uint64 elapsedMicro) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;

        sf::Color GetBGColor() const;
        void SetBGColor(const sf::Color value);

        sf::Uint64 GetInternalMicro() const;
        void SetInternalMicro(sf::Uint64 value);

        sf::FloatRect GetInternalBounds() const;
        void SetInternalBounds(sf::FloatRect value);

        bool GetDebugMode() const;
        void SetDebugMode(bool value);

        bool GetNeedsRecalculate() const;
        void SetNeedsRecalculate(const bool value);

        sf::Sprite* GetSprite() const;
        sf::RenderTexture* GetRenderTexture() const;
        sf::RectangleShape* GetDebugRect() const;
    protected:
        bool m_needsRecalculate;
        sf::Sprite* m_renderSprite;
        sf::RenderTexture* m_renderTexture;
        sf::RectangleShape* m_debugRect;

        virtual void Recalculate() = 0;
        virtual void EnsureRecalculate() = 0;
    private:
        sf::FloatRect m_boundRect;
        sf::Color m_BGColor;
        sf::Uint64 m_elapsedMicroseconds;
        bool m_debugMode;
};

#endif // FIELDBASE_H
