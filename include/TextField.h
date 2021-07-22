#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <FieldBase.h>
#include <TextWorkerBase.h>

class TextField : public FieldBase
{
    public:
    enum TextFieldType {tfStatic, tfOptionalRunning, tfAlwaysRunning, tfScrollUp, tfScrollDown, tfScrollUpReplace, tfScrollDownReplace, tfDateTime};
    enum TextAlignHorizontal {tahLeft, tahCenter, tahRight};
    enum TextAlignVectical {tavTop, tavCenter, tavBottom};
    enum TextRunningSpacing {trsNone, trsSpace, trs3Space, trsRemaining, trs0_5, trs1_0, trs1_5, trs2_0};

        TextField();
        TextField(const sf::FloatRect bounds);
        TextField(const sf::FloatRect bounds, std::string fontPath, sf::Int32 fontSize);
        virtual ~TextField();

        virtual bool Update(const sf::Uint64 elapsedMicro);
        virtual bool UpdateTick(const sf::Uint64 elapsedMicro);
        virtual void Draw(sf::RenderWindow& window);

        void SetFieldUpdateTickCount(const sf::Uint32 count, const sf::Uint64 microsecPerTick);

        void SetInternalBounds(sf::FloatRect value);

        virtual void EnsureRecalculate();
        //getter
        bool GetUsingGoodFont() const;
        sf::Text* GetTextObject() const;
        sf::Text::Style GetTextStyle() const;
        sf::Uint32 GetTextSpeed() const;
        sf::Uint32 GetTextSize() const;
        sf::Color GetTextColor() const;
        std::string GetTextString() const;
        TextField::TextAlignHorizontal GetTextHorizontalAlign() const;
        TextField::TextAlignVectical GetTextVerticalAlign() const;
        TextField::TextRunningSpacing GetTextRunningSpacing() const;
        //setter
        void SetTextFieldType(const TextField::TextFieldType value);
        void SetTextString(const std::string& value);
        void SetTextColor(const sf::Color& value);
        void SetTextSpeed(const sf::Uint32 value);
        void SetTextHorizontalAlign(const TextField::TextAlignHorizontal value);
        void SetTextVertialAlign(const TextField::TextAlignVectical value);
    protected:
        virtual void Recalculate();
    private:
        sf::Text* m_textObject;
        sf::Font* m_fontObject;
        std::string m_fontPath;
        sf::Uint32 m_fieldUpdateTickCount;
        std::string m_textString;
        sf::Uint32 m_textSize;
        sf::Color m_textColor;
        sf::Text::Style m_textStyle;
        sf::Uint32 m_textSpeed;
        TextField::TextFieldType m_textFieldType;
        TextField::TextAlignHorizontal m_textHorizontalAlign;
        TextField::TextAlignVectical m_textVerticalAlign;
        TextField::TextRunningSpacing m_textRunningSpace;
        bool m_usingGoodFont;

        ITextWorker* m_behaviourWorker;

        void CheckUsingGoodFont();
        void CreateBehaviour();
};

#endif // TEXTFIELD_H
