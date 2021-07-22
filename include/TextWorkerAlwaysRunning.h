#ifndef TEXTWORKERALWAYSRUNNING_H
#define TEXTWORKERALWAYSRUNNING_H

#include <TextWorkerBase.h>

class TextWorkerAlwaysRunning : public ITextWorker
{
public:
    TextWorkerAlwaysRunning();
    TextWorkerAlwaysRunning(void* parentObj);
    virtual ~TextWorkerAlwaysRunning();

    virtual void SetUpdateTickCount(const uint32_t count, const uint64_t microPerTick);
    virtual bool Update(const sf::Int64 elapsed);
    virtual bool UpdateTick(const sf::Int64 elapsed);
    virtual void Draw(sf::RenderWindow& window);
    virtual void Recalculate();
private:
    void* m_parent;

    double m_textRunningRealPos;
    sf::IntRect m_textRunningClipRect;
    double m_pixelsPerMicrosecond;
    double m_textRunningThreshold;
    sf::Uint32 m_updateTickCount;
    sf::Uint32 m_updateTickCurrent;

    void CalculateAndDrawRunning(sf::FloatRect& abounds);
};

#endif // TEXTWORKERALWAYSRUNNING_H
