#include <SFML/Graphics.hpp>
#include <TextField.h>
#include <thread>
#include <math.h>
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock mainClock;
    sf::Clock forceRedrawClock;
    sf::Clock fpsClock;

    /*TextField* f1 = new TextField(sf::FloatRect(200, 200, 500, 70), "H:\\CodeBlocksProjects\\SFML_test4\\bin\\Release\\arial.ttf", 28);
    f1->SetTextString("Test12345 fsdhjtoejot43w6");
    //f1->SetTextFieldType(TextField::tfStatic);
    f1->SetTextFieldType(TextField::tfAlwaysRunning);
    f1->SetTextColor(sf::Color::Yellow);
    f1->SetBGColor(sf::Color(0, 0, 255, 100));
    f1->SetTextSpeed(60);
    f1->SetTextHorizontalAlign(TextField::tahLeft);
    f1->SetTextVertialAlign(TextField::tavCenter);

    std::vector<TextField*> mess;
    mess.push_back(f1);*/

    std::vector<TextField*> mass;
    for(int i=0; i<10; i++)
    {
        TextField* f1 = new TextField(sf::FloatRect(rand() % 700, rand() % 700, 200, 70), "H:\\CodeBlocksProjects\\SFML_test4\\bin\\Release\\arial.ttf", 28);
        f1->SetTextString("Test"+std::to_string(i));
        //f1->SetTextFieldType(TextField::tfStatic);
        f1->SetTextFieldType(TextField::tfAlwaysRunning);
        f1->SetTextColor(sf::Color::Yellow);
        f1->SetBGColor(sf::Color(rand() % 250, rand() % 250, rand() % 250, rand() % 100 + 150));
        f1->SetTextSpeed(60);
        f1->SetTextHorizontalAlign(TextField::tahLeft);
        f1->SetTextVertialAlign(TextField::tavCenter);
        mass.push_back(f1);
    }

    sf::Font font;
    if(!font.loadFromFile("H:\\CodeBlocksProjects\\SFML_test4\\bin\\Release\\arial.ttf")) printf("Error loading font\n");
    else printf("Font loaded\n");

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(12);
    //text.setPosition(200, 300);
    //text.setString("Test12345 отдельная строка");

    sf::Int32 fpsCounter = 0;
    sf::Int32 cyclesCounter = 0;

    while (window.isOpen())
    {
        cyclesCounter++;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Uint64 elapsed = mainClock.restart().asMicroseconds();
        sf::Uint64 forceElapsed = forceRedrawClock.getElapsedTime().asMicroseconds();
        //bool fieldUpdated = f1->Update(elapsed);
        bool fieldUpdated = false;
        for(int i=0; i<mass.size(); i++)
        {
            fieldUpdated |= (mass[i]->Update(elapsed));
        }

        if((fieldUpdated == false)&&(forceElapsed < 1000000))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            std::this_thread::yield();
            continue;
        }

        if(forceElapsed >= 1000000) forceRedrawClock.restart();

        fpsCounter++;

        if(fpsClock.getElapsedTime().asMicroseconds() >= 1000000)
        {
            sf::Int64 temp = fpsClock.restart().asMicroseconds();
            float fpsNum = (1000000.0 / temp) * fpsCounter;
            float cyclesNum = (1000000.0 / temp) * cyclesCounter;
            std::string fpsStr = "FPS=" + std::to_string(floor(fpsNum)) + "\nCycles=" + std::to_string(cyclesNum) + "\nMicroSec=" + std::to_string(temp);
            text.setString(fpsStr);
            fpsCounter = 0;
            cyclesCounter = 0;
        }

        window.clear();
        //window.draw(shape);
        //f1->Draw(window);
        for(int i=0; i<mass.size(); i++)
        {
            mass[i]->Draw(window);
        }
        window.draw(text);
        window.display();
    }

    return 0;
}
