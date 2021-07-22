#ifndef TEXTWORKERSTATIC_H
#define TEXTWORKERSTATIC_H

#include <TextWorkerBase.h>

class TextWorkerStatic : public ITextWorker
{
public:
    TextWorkerStatic();
    TextWorkerStatic(void* parentObj);
    ~TextWorkerStatic();

    virtual void SetUpdateTickCount(const uint32_t count, const uint64_t microPerTick);
    virtual bool Update(const sf::Int64 elapsed);
    virtual bool UpdateTick(const sf::Int64 elapsed);
    virtual void Draw(sf::RenderWindow& window);
    virtual void Recalculate();
private:
    void* m_parent;
};

#endif // TEXTWORKERSTATIC_H
