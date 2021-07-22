#ifndef TEXTWORKERBASE_H
#define TEXTWORKERBASE_H

#include <SFML/Graphics.hpp>

class ITextWorker
{
    public:
    virtual void SetUpdateTickCount(const uint32_t count, const uint64_t microPerTick) = 0;
    virtual bool Update(const sf::Int64 elapsed) = 0;
    virtual bool UpdateTick(const sf::Int64 elapsed) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Recalculate() = 0;
    virtual ~ITextWorker() {};
};

#endif // TEXTWORKERBASE_H
