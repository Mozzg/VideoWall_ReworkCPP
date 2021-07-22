#include "TextField.h"
#include <TextWorkerStatic.h>
#include <TextWorkerAlwaysRunning.h>

//////////////////////////////////////
//TextField
//////////////////////////////////////

TextField::TextField() : TextField(sf::FloatRect(0, 0, 100, 100))
{
}

TextField::TextField(const sf::FloatRect bounds) : TextField(bounds, "", 12)
{
}

TextField::TextField(const sf::FloatRect bounds, std::string fontPath, sf::Int32 fontSize): FieldBase(bounds),
m_textObject(NULL),
m_fontObject(NULL),
m_fontPath(fontPath),
m_fieldUpdateTickCount(1),
m_textString(""),
m_textSize(fontSize),
m_textColor(sf::Color::White),
m_textStyle(sf::Text::Regular),
m_textSpeed(60),
m_textFieldType(TextField::TextFieldType::tfStatic),
m_textHorizontalAlign(TextField::TextAlignHorizontal::tahLeft),
m_textVerticalAlign(TextField::TextAlignVectical::tavTop),
m_textRunningSpace(TextField::TextRunningSpacing::trs3Space),
m_usingGoodFont(false)
{
    m_fontObject = new sf::Font();
    m_textObject = new sf::Text();

    CheckUsingGoodFont();
    CreateBehaviour();
}

TextField::~TextField()
{
    delete m_textObject;
    delete m_fontObject;
}

void TextField::CheckUsingGoodFont()
{
    m_usingGoodFont = m_fontObject->loadFromFile(m_fontPath);
    if(m_usingGoodFont) m_textObject->setFont(*m_fontObject);
}

void TextField::CreateBehaviour()
{
    delete m_behaviourWorker;

    switch(m_textFieldType)
    {
    case tfAlwaysRunning: m_behaviourWorker = new TextWorkerAlwaysRunning(this);break;
    default: m_behaviourWorker = new TextWorkerStatic(this);break;
    }
}

bool TextField::Update(const sf::Uint64 elapsedMicro)
{
    //printf("TextField::Update enter, elapsed=%d\n", elapsedMicro);
    SetInternalMicro(GetInternalMicro() + elapsedMicro);
    if(m_behaviourWorker){
        return m_behaviourWorker->Update(elapsedMicro);
    }else return false;
}

bool TextField::UpdateTick(const sf::Uint64 elapsedMicro)
{
    SetInternalMicro(GetInternalMicro() + elapsedMicro);
    if(m_behaviourWorker){
        return m_behaviourWorker->UpdateTick(elapsedMicro);
    }else return false;
}

void TextField::Draw(sf::RenderWindow& window)
{
    if(m_behaviourWorker) m_behaviourWorker->Draw(window);
    if(GetDebugMode()) window.draw(*(GetDebugRect()));
}

void TextField::SetFieldUpdateTickCount(const sf::Uint32 count, const sf::Uint64 microsecPerTick)
{
    m_fieldUpdateTickCount = count;
    if(m_behaviourWorker) m_behaviourWorker->SetUpdateTickCount(count, microsecPerTick);
}

void TextField::SetInternalBounds(sf::FloatRect value)
{
    FieldBase::SetInternalBounds(value);
    m_needsRecalculate = true;
}

void TextField::Recalculate()
{
    if(m_behaviourWorker) m_behaviourWorker->Recalculate();
}

void TextField::EnsureRecalculate()
{
    if(m_needsRecalculate) Recalculate();
}

//getter
bool TextField::GetUsingGoodFont() const
{
    return m_usingGoodFont;
}

sf::Text* TextField::GetTextObject() const
{
    return m_textObject;
}

sf::Text::Style TextField::GetTextStyle() const
{
    return m_textStyle;
}

sf::Uint32 TextField::GetTextSpeed() const
{
    return m_textSpeed;
}

sf::Uint32 TextField::GetTextSize() const
{
    return m_textSize;
}

sf::Color TextField::GetTextColor() const
{
    return m_textColor;
}

std::string TextField::GetTextString() const
{
    return m_textString;
}

TextField::TextAlignHorizontal TextField::GetTextHorizontalAlign() const
{
    return m_textHorizontalAlign;
}

TextField::TextAlignVectical TextField::GetTextVerticalAlign() const
{
    return m_textVerticalAlign;
}

TextField::TextRunningSpacing TextField::GetTextRunningSpacing() const
{
    return m_textRunningSpace;
}

//setter
void TextField::SetTextFieldType(const TextField::TextFieldType value)
{
    if(value != m_textFieldType)
    {
        m_textFieldType = value;
        CreateBehaviour();
        m_needsRecalculate = true;
    }
}

void TextField::SetTextString(const std::string& value)
{
    if(value != m_textString)
    {
        m_textString = value;
        m_needsRecalculate = true;
    }
}

void TextField::SetTextColor(const sf::Color& value)
{
    if(value != m_textColor)
    {
        m_textColor = value;
        m_needsRecalculate = true;
    }
}

void TextField::SetTextSpeed(const sf::Uint32 value)
{
    if(value != m_textSpeed)
    {
        m_textSpeed = value;
        m_needsRecalculate = true;
    }
}

void TextField::SetTextHorizontalAlign(const TextField::TextAlignHorizontal value)
{
    if(value != m_textHorizontalAlign)
    {
        m_textHorizontalAlign = value;
        m_needsRecalculate = true;
    }
}

void TextField::SetTextVertialAlign(const TextField::TextAlignVectical value)
{
    if(value != m_textVerticalAlign)
    {
        m_textVerticalAlign = value;
        m_needsRecalculate = true;
    }
}
