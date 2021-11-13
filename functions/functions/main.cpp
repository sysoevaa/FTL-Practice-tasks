#include <SFML/Graphics.hpp>

using namespace sf;

int kSize = 4;
int kScale = 16;

bool IsFill(int x, int y, int axis) {
    x -= axis, y -= axis;
    bool line_1 = -3 * x - kSize * kScale >= y;
    bool circle = (x + 5 * kSize * kScale / 2) * (x + 5 * kSize * kScale / 2) +
        (y - 2 * kScale * kSize) * (y - 2 * kScale * kSize) >=
        (3 * kSize * kScale / 2) * (3 * kSize * kScale / 2);
    bool root = (-x + kSize * kScale) * kSize * kScale <=
        (y - 5 * kSize * kScale / 2) * (y - 5 * kSize * kScale / 2);
    bool line_2 = 3 * x / 5 + 14 * kSize * kScale / 5 >= y;
    bool axis_x = y > 0;
    bool axis_y = x > 0;
    bool y_block_2 = (y > 3 * kSize * kScale);
    bool parabola = (y - 2 * kScale * kSize) * kScale * kSize >=
        -(x - 5 * kSize * kScale / 2) * (x - 5 * kSize * kScale / 2);
    bool romb = abs(2 * x - 7 * kSize * kScale) + abs(y + 7 * kSize * kScale / 2) >= 3 * kSize * kScale;
    bool rectangle = y >= -3 * kSize * kScale / 2 && y <=  5 * kSize * kScale / 2 &&
        x >= 5 * kSize * kScale / 2 && x <= 9 * kSize * kScale / 2;
    bool line_3 = x < -2 * kScale * kSize;
    bool block_1 = line_1 && circle && root && line_2 && parabola;
    bool block_2 = line_1 && !line_2 && circle && root && axis_x && y_block_2;
    bool block_3 = !parabola && romb && rectangle;
    bool block_4 = line_2 && parabola && !rectangle && axis_x && axis_y && root;
    bool block_5 = circle && !root && line_2 && line_3;
    return block_1 || block_2 || block_3 || block_4 || block_5;
}

bool IsBorder(int x, int y, int axis) {
    x -= axis, y -= axis;
    bool parabola, root;
    bool line_1 = -3 * x - kSize * kScale == y,
        circle = abs((x + 5 * kSize * kScale / 2) * (x + 5 * kSize * kScale / 2) +
            (y - 2 * kScale * kSize) * (y - 2 * kScale * kSize) -
            (3 * kSize * kScale / 2) * (3 * kSize * kScale / 2)) < kSize * kScale,
        line_2 = 3 * x / 5 + 14 * kSize * kScale / 5 == y,
        romb = abs(2 * x - 7 * kSize * kScale) + abs(y + 7 * kSize * kScale / 2) == 3 * kSize * kScale,
        rectangle = (y == -3 * kSize * kScale / 2 || y == 5 * kSize * kScale / 2) &&
        x < 9 * kScale * kSize / 2 && x > 5 * kSize * kScale / 2 ||
        (x == 5 * kSize * kScale / 2 || x == 9 * kSize * kScale / 2) &&
        y > -3 * kSize * kScale / 2 && y < 5 * kSize * kScale / 2;
    if (abs(x) <= 5 * kSize * kScale && abs(y) <= 5 * kSize * kScale) {
        parabola = abs((y - 2 * kScale * kSize) * kScale * kSize +
            (x - 5 * kSize * kScale / 2) * (x - 5 * kSize * kScale / 2)) < kSize * kScale;
        root = abs((-x + kSize * kScale) * kSize * kScale -
            (y - 5 * kSize * kScale / 2) * (y - 5 * kSize * kScale / 2)) < kSize * kScale;

    } else{
        parabola = abs((y - 2 * kScale * kSize) * kScale * kSize +
            (x - 5 * kSize * kScale / 2) * (x - 5 * kSize * kScale / 2)) < 5 * kSize * kScale;
        root = abs((-x + kSize * kScale) * kSize * kScale -
            (y - 5 * kSize * kScale / 2) * (y - 5 * kSize * kScale / 2)) < 5 * kSize * kScale;
    }
    return line_1 || circle || root || line_2 || parabola || romb || rectangle;
}

void DrawArrows(RenderWindow& window, int axis) {
    int k = kScale;
    k = (k >= 16 ? 16 : k);
    k = (k <= 8 ? 8 : k);
    RectangleShape arrow_1(Vector2f(kSize * k * 14 / 40, 2.f)), arrow_2(Vector2f(kSize * k * 14 / 40, 2.f)),
        arrow_3(Vector2f(kSize * k * 14 / 40, 2.f)), arrow_4(Vector2f(kSize * k * 14 / 40, 2.f));
    arrow_1.rotate(45.f), arrow_2.rotate(135.f), arrow_3.rotate(225.f), arrow_4.rotate(315.f);
    arrow_1.move(1024 - kSize * k / 4, axis - kSize * k / 4),
        arrow_2.move(1024, axis), arrow_3.move(kSize * k / 4 + axis, kSize * k / 4),
        arrow_4.move(axis - kSize * k / 4, kSize * k / 4);
    arrow_1.setFillColor({ 0, 0, 0 }), arrow_2.setFillColor({ 0, 0, 0 }),
        arrow_3.setFillColor({ 0, 0, 0 }), arrow_4.setFillColor({ 0, 0, 0 });
    window.draw(arrow_1), window.draw(arrow_2), window.draw(arrow_3), window.draw(arrow_4);
    Font font;
    font.loadFromFile("C:\\Users\\salex\\source\\repos\\functions\\functions\\Debug\\lato-bold.ttf");
    Text x, y;
    x.setFont(font), y.setFont(font);
    x.setString("x"), y.setString("y");
    x.setCharacterSize(k * kSize / 2 + 1), y.setCharacterSize(k * kSize / 2 + 1);
    x.setFillColor(Color::Black), y.setFillColor(Color::Black);
    x.setPosition(1024 - kSize * k / 3, axis + kSize * k / 8);
    y.setPosition(axis - kSize * k / 2, kSize * k / 8);
    window.draw(x), window.draw(y);

}

void DrawWindow(RenderWindow& window) {
    int axis = 512 / (kSize * kScale) * kSize * kScale;
    RectangleShape pixel;
    pixel.setSize({ 1.f, 1.f });
    for (int x = 0; x < 1024; ++x) {
        for (int y = 0; y < 1024; ++y) {
            if (x % (kSize * kScale) == 0 || y % (kSize * kScale) == 0) {
                pixel.setFillColor({ 150, 150, 150, 150 });
                pixel.setPosition(x, y);
                window.draw(pixel);
            }
            if (x == axis || y == axis) {
                pixel.setSize({ 2.f, 2.f });
                pixel.setFillColor({ 0, 0, 0 });
                pixel.setPosition(x, y);
                window.draw(pixel);
                pixel.setSize({ 1.f, 1.f });
            }
            if (IsFill(x, y, axis)) {
                pixel.setFillColor({ 0, 242, 246, 100 });
                pixel.setPosition(x, y);
                window.draw(pixel);
            }
            if (IsBorder(x, y, axis)) {
                pixel.setSize({ 4.f, 4.f });
                pixel.setFillColor({ 0, 242, 246, 255 });
                pixel.setPosition(x, y);
                window.draw(pixel);
                pixel.setSize({ 1.f, 1.f });
            }
        }
    }
    DrawArrows(window, axis);
}

int main() {
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1024, 1024), "Functions", Style::Default, settings);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    if (kScale != 64) {
                        kScale *= 2;
                    }
                }
                if (event.key.code == Keyboard::Down) {
                    if (kScale != 4) {
                        kScale /= 2;
                    }
                }
            }
        }
        window.clear(Color::White);
        DrawWindow(window);
        window.display();
    }
    return 0;
}
