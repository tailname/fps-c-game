#include"../include/GameMenu.h"
#include "../include/Level.h"
#include<box2d/box2d.h>
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

void game_start()
{
    RenderWindow Play(VideoMode::getDesktopMode(), L"Óðîâåíü 1", Style::Fullscreen);

    RectangleShape background_play(Vector2f(1920, 1080));

    Texture texture_play;
    if (!texture_play.loadFromFile("Image/serious_sam.jpg")) exit(2);
    background_play.setTexture(&texture_play);

    while (Play.isOpen())
    {
        Event event_play;
        while (Play.pollEvent(event_play))
        {
            if (event_play.key.code == Keyboard::Escape)
                Play.close();
        }

        Play.clear();
        Play.draw(background_play);
        Play.display();
    }
}

int main()
{
    b2Vec2 gravity(0.0f, 9.81f);
    auto world = std::make_unique<b2World>(gravity);
    Level level;
	level.loadFromFile("..\\..\\..\\Image\\level1.xml", *world);
    // Ñîçäà¸ì îêíî windows
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Ìîÿ èãðà", Style::Fullscreen);
    
    // Îòêëþ÷àåì âèäèìîñòü êóðñîðà
    window.setMouseCursorVisible(false);

    //Ðàçìåð ýêðàíà
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    // Óñòàíàâëèâàåì ôîí ýêðàíà ìåíþ
    RectangleShape background(Vector2f(width, height));

    Texture texture_window;
    if (!texture_window.loadFromFile("Image/destroyed_city.jpg"))
    {
        return 1;
    }
    background.setTexture(&texture_window);

    // Øðèôò äëÿ íàçâàíèÿ ýêðàíà
    Font font;
    if (!font.loadFromFile("Font/troika.otf"))
    {
        return 2;
    }
    Text Titul;
    Titul.setFont(font);
    InitText(Titul, 480, 50, L"Àïîêàëèïñèñ", 150, Color(237, 147, 0), 3);

    // íàçâàíèå ïóíêòîâ ìåíþ
    String name_menu[4]{ L"Èãðàòü",L"Ïðîäîëæèòü", L"Î èãðå", L"Âûõîä" };
    std::vector<String> name_vector(std::begin(name_menu), std::end(name_menu));
    // îáúåêò ìåíþ
    game::GameMenu my_menu(window, 950, 350, name_vector, 100, 120);

    // Óñòàíîâêà öâåòà îòîáðàæàåìîãî ìåíþ
    my_menu.set_color_text_menu(Color(237,147,0), Color::Red, Color::Black);
    my_menu.Allign_menu(2);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {

                if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) my_menu.move_up();
                if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) my_menu.move_down();
                if (event.key.code == Keyboard::Enter)
                {
                    // ïåðåõîäèì íà âûáðàííûé ïóíêò ìåíþ
                    switch (my_menu.get_select_menu_number())
                    {
                    case 0:
                        game_start();
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        window.close();
                        break;
                    }
                }
            }
            
        }

        window.clear();
        window.draw(background);
        window.draw(Titul);
        my_menu.draw();
        window.display();
    }

    return 0;
}

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font, Color menu_text_color,
    int bord, Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);

}