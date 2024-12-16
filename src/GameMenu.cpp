#include "GameMenu.h"
#include <vector>
void game::GameMenu::SetInitText(Text& text, String str, float xpos, float ypos)
{
    text.setFont(font);
    text.setFillColor(menu_text_color);
    text.setString(str);
    text.setCharacterSize(size_font);
    text.setPosition(xpos, ypos);
    text.setOutlineThickness(3);
    text.setOutlineColor(border_color);
}

void game::GameMenu::Allign_menu(int posx)
{
    float nullx = 0;

    for (int i = 0; i < max_menu;++i)
    {
        switch (posx)
        {
        case 0:
            nullx = 0;
            break;
        case 1:
            nullx = main_menu[i].getLocalBounds().width;
            break;
        case 2:
            nullx = nullx = main_menu[i].getLocalBounds().width/2;
            break;
        }

        main_menu[i].setPosition(main_menu[i].getPosition().x - nullx, main_menu[i].getPosition().y);
    }
}

game::GameMenu::GameMenu(RenderWindow& window, float menux, float menuy, const std::vector<String>& name, int size_font, int step)
    : my_window(window), menu_x(menux), menu_y(menuy), size_font(size_font), menu_step(step)
{
    // Загрузка шрифта
    if (!font.loadFromFile("Font/troika.otf")) exit(1);
    max_menu = name.size(); // Используем size() для получения размера
    main_menu.resize(max_menu); // Резервируем место в векторе

    for (int i = 0, ypos = menu_y; i < max_menu; ++i, ypos += menu_step) {
        SetInitText(main_menu[i], name[i], menu_x, ypos);
    }
    main_menu_selected = 0;
    main_menu[main_menu_selected].setFillColor(Color::Yellow);
}

void game::GameMenu::move_up()
{
    main_menu_selected--;

    if (main_menu_selected >= 0)
    {
        main_menu[main_menu_selected].setFillColor(chose_text_color);
        main_menu[main_menu_selected+1].setFillColor(menu_text_color);
    }
    else
    {
        main_menu[0].setFillColor(menu_text_color);
        main_menu_selected = max_menu - 1;
        main_menu[main_menu_selected].setFillColor(chose_text_color);
    }
}

void game::GameMenu::move_down()
{
    main_menu_selected++;

    if (main_menu_selected < max_menu)
    {
        main_menu[main_menu_selected-1].setFillColor(menu_text_color);
        main_menu[main_menu_selected].setFillColor(chose_text_color);
    }
    else
    {
        main_menu[max_menu-1].setFillColor(menu_text_color);
        main_menu_selected = 0;
        main_menu[main_menu_selected].setFillColor(chose_text_color);
    }
}

void game::GameMenu::draw()
{
    for (int i = 0; i < max_menu; i++) my_window.draw(main_menu[i]);
}

void game::GameMenu::set_color_text_menu(Color men_color, Color cho_color, Color bord_color)
{
    menu_text_color = men_color;
    chose_text_color = cho_color;
    border_color = bord_color;

    for (int i = 0; i < max_menu; i++)
    {
        main_menu[i].setFillColor(menu_text_color);
        main_menu[i].setOutlineColor(border_color);
    }

    main_menu[main_menu_selected].setFillColor(chose_text_color);
}

void game::GameMenu::update_menu_texts(const std::vector<String>& new_names) {
    max_menu = new_names.size(); // Обновляем размер
    main_menu.resize(max_menu); // Обновляем размер вектора

    for (int i = 0; i < max_menu; ++i) {
        SetInitText(main_menu[i], new_names[i], menu_x, menu_y + i * menu_step);
    }
}