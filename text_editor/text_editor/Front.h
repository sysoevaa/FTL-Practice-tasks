#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

void DrawBackground(RenderWindow& window) {
    RectangleShape border_1(Vector2f(900.f, 2.f));
    border_1.setPosition(1000, 0);
    border_1.rotate(90.f);
    border_1.setFillColor({ 0, 0, 0 });
    RectangleShape border_2(Vector2f(1400.f, 2.f));
    border_2.setFillColor({ 0, 0, 0 });
    window.draw(border_1);
    window.draw(border_2);
    border_2.setPosition(0, 100);
    window.draw(border_2);
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text list;
    list.setFont(font);
    list.setString("список доступных");
    list.setFillColor({ 0, 0, 0 });
    list.setCharacterSize(28);
    list.setPosition(1050, 10);
    window.draw(list);
    list.setString("команд");
    list.setPosition(1150, 50);
    window.draw(list);
    list.setPosition(350, 30);
    list.setString("набранный текст");
    window.draw(list);
}

void DrawButtons(RenderWindow& window) {
    RectangleShape button(Vector2f{ 360.f, 100.f });
    button.setFillColor({ 200, 200, 200 });
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setCharacterSize(24);
    text.setFont(font);
    text.setFillColor({ 0, 0, 0 });

    button.setPosition(1020, 140);
    window.draw(button);
    text.setString("добавление строки");
    text.setPosition(1070, 170);
    window.draw(text);

    button.setPosition(1020, 280);
    window.draw(button);
    text.setString("изменение строки");
    text.setPosition(1070, 310);
    window.draw(text);
    
    button.setPosition(1020, 420);
    window.draw(button);
    text.setString("алгоритмические");
    text.setPosition(1080, 440);
    window.draw(text);
    text.setString("замены");
    text.setPosition(1140, 470);
    window.draw(text);

    button.setPosition(1020, 560);
    window.draw(button);
    text.setString("удаление строк");
    text.setPosition(1090, 590);
    window.draw(text);
}

void AddStringFront(RenderWindow& window) {
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text announce;
    announce.setFont(font);
    announce.setString("Введите количество вводимых строк: ");
    announce.setFillColor(Color::Black);
    announce.setCharacterSize(30);
    announce.setPosition(20, 50);
    window.draw(announce);
    announce.setString("Введите место, куда будут вставлены строки");
    announce.setPosition(20, 170);
    window.draw(announce);
    announce.setString("Введите строки: ");
    announce.setPosition(20, 300);
    window.draw(announce);
    RectangleShape count(Vector2f{ 200.f, 50.f });
    count.setFillColor({ 200, 200, 200 });
    count.setPosition(20, 100);
    window.draw(count);
    RectangleShape loc(Vector2f{ 200.f, 50.f });
    loc.setFillColor({200, 200, 200});
    loc.setPosition(20, 220);
    window.draw(loc);
    RectangleShape str(Vector2f(950.f, 500.f));
    str.setFillColor({ 200, 200, 200 });
    str.setPosition(20, 350);
    window.draw(str);
}

void ChangeStringFront(RenderWindow& window) {
    RectangleShape button(Vector2f(300.f, 70.f));
    button.setFillColor({ 200, 200, 200 });
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor({ 0, 0, 0 });

    button.setPosition(680, 50);
    text.setString("Замена подстроки");
    text.setPosition(700, 70);
    window.draw(button);
    window.draw(text);

    button.setPosition(680, 140);
    text.setString("Замена символа");
    text.setPosition(710, 160);
    window.draw(button);
    window.draw(text);

    button.setPosition(680, 230);
    text.setString("Вставка подстроки");
    text.setPosition(700, 250);
    window.draw(button);
    window.draw(text);
}

void ChangeSubstringFront(RenderWindow& window){
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setFillColor(Color::Black);
    text.setFont(font);
    RectangleShape loc (Vector2f{ 200, 50 });
    Text help;
    help.setFont(font);
    help.setString("начальная строка - конечная строка");
    help.setCharacterSize(16);
    help.setFillColor({ 150, 150, 150 });

    text.setString("Введите диапазон: ");
    text.setPosition(50, 50);
    loc.setFillColor({200, 200, 200 });
    loc.setPosition(50, 100);
    help.setPosition(50, 160);
    window.draw(help);
    window.draw(loc);
    window.draw(text);
    
    RectangleShape string(Vector2f{ 500, 50 });
    text.setString("Введите заменяемую подстроку: ");
    text.setPosition(50, 190);
    string.setFillColor({ 200, 200, 200 });
    string.setPosition(50, 240);
    window.draw(string);
    window.draw(text);
    
    text.setString("Введите подстроку,");
    text.setPosition(50, 330);
    window.draw(text);
    text.setString("являющуюся заменой:");
    text.setPosition(50, 360);
    window.draw(text);
    string.setPosition(50, 420);
    window.draw(string);
}

void ChangeSymbol(RenderWindow& window) {
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setCharacterSize(30);
    text.setFillColor(Color::Black);
    text.setFont(font);
    RectangleShape loc(Vector2f{ 200, 50 });

    text.setString("Введите номер строки: ");
    text.setPosition(50, 50);
    loc.setFillColor({ 200, 200, 200 });
    loc.setPosition(50, 100);
    window.draw(loc);
    window.draw(text);

    text.setString("Введите номер символа: ");
    text.setPosition(50, 190);
    loc.setPosition(50, 240);
    window.draw(loc);
    window.draw(text);

    text.setString("Введите символ,");
    text.setPosition(50, 330);
    window.draw(text);
    text.setString("являющийся заменой:");
    text.setPosition(50, 360);
    window.draw(text);
    loc.setPosition(50, 420);
    window.draw(loc);
}

void InsertSubstring(RenderWindow& window) {
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setCharacterSize(29);
    text.setFillColor(Color::Black);
    text.setFont(font);
    RectangleShape loc(Vector2f{ 200, 50 });

    text.setString("Введите номер строки: ");
    text.setPosition(50, 50);
    loc.setFillColor({ 200, 200, 200 });
    loc.setPosition(50, 100);
    window.draw(loc);
    window.draw(text);

    text.setString("Введите индекс начала подстроки: ");
    text.setPosition(50, 190);
    loc.setPosition(50, 240);
    window.draw(loc);
    window.draw(text);

    RectangleShape str(Vector2f(500.f, 50.f));
    text.setString("Введите подстроку,");
    text.setPosition(50, 330);
    window.draw(text);
    text.setString("которая будет вставлена:");
    text.setPosition(50, 360);
    window.draw(text);
    loc.setPosition(50, 420);
    loc.setSize(Vector2f{ 500, 50 });
    window.draw(loc);
}

void AlgorithmFront(RenderWindow& window) {
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setCharacterSize(29);
    text.setFillColor(Color::Black);
    text.setFont(font);
    RectangleShape loc(Vector2f{ 200, 50 });
    loc.setFillColor({ 200, 200, 200 });
    Text help;
    help.setFont(font);
    help.setString("начальная строка - конечная строка");
    help.setCharacterSize(16);
    help.setFillColor({ 150, 150, 150 });

    text.setString("Введите диапазон применения: ");
    text.setPosition(50, 50);
    loc.setPosition(50, 100);
    help.setPosition(50, 160);
    window.draw(help);
    window.draw(loc);
    window.draw(text);

    RectangleShape button(Vector2f{ 300, 100 });
    button.setFillColor({ 200, 200, 200 });
    text.setCharacterSize(24);

    button.setPosition(680, 50);
    text.setString("Удалить ведущие");
    text.setPosition(710, 70);
    window.draw(button);
    window.draw(text);
    text.setString("нули");
    text.setPosition(790, 100);
    window.draw(text);

    text.setCharacterSize(16);
    button.setPosition(680, 170);
    text.setString("Оставить группы цифр,");
    text.setPosition(710, 190);
    window.draw(button);
    window.draw(text);
    text.setString("составляющие возрастающую");
    text.setPosition(700, 210);
    window.draw(text);
    text.setString("последовательность");
    text.setPosition(730, 230);
    window.draw(text);

    text.setString("Заменить группу *  ");
    button.setPosition(680, 290);
    text.setPosition(730, 310);
    window.draw(button);
    window.draw(text);
    text.setString("на группу +");
    text.setPosition(760, 330);
    window.draw(text);
    text.setString("вдвое меньшего размера");
    text.setPosition(710, 350);
    window.draw(text);

    text.setCharacterSize(24);
    text.setString("Удалить символы");
    button.setPosition(680, 410);
    text.setPosition(710, 430);
    window.draw(button);
    window.draw(text);
    text.setString("между {}");
    text.setPosition(760, 460);
    window.draw(text);
}

void DeleteStringFront(RenderWindow& window) {
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    Text text;
    text.setCharacterSize(29);
    text.setFillColor(Color::Black);
    text.setFont(font);
    RectangleShape loc(Vector2f{ 200, 50 });
    loc.setFillColor({ 200, 200, 200 });
    Text help;
    help.setFont(font);
    help.setString("начальная строка - конечная строка");
    help.setCharacterSize(16);
    help.setFillColor({ 150, 150, 150 });

    text.setString("Введите диапазон применения: ");
    text.setPosition(50, 50);
    loc.setPosition(50, 100);
    help.setPosition(50, 150);
    window.draw(help);
    window.draw(loc);
    window.draw(text);
}
