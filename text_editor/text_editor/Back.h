#pragma once
#include<SFML/Graphics.hpp>
#include"Front.h"
using namespace sf;

void AddStringBack(std::vector<std::wstring*>& main_text, int& flag, Font font) {
    RenderWindow query(VideoMode(1000, 900), "Add string");
    std::wstring len, loc, str;
    std::vector<std::wstring> in_text;
    int last_backspace = -1;
    str = (wchar_t)"";
    int down = 0, field = 0, scroll = 0;
    while (query.isOpen()) {
        query.clear(Color::White);
        AddStringFront(query);
        Event e;
        for (int i = 0; i < in_text.size(); ++i) {
            Text string;
            string.setFont(font);
            string.setString(in_text[i]);
            string.setPosition(20, 350 + 30 * i);
            string.setFillColor({ 0, 0, 0 });
            query.draw(string);
        }
        while (query.pollEvent(e)) {
            if (e.type == Event::Closed) {
                query.close();
                if (str != (wchar_t)"" && len.size() != 0 && std::stoi(loc) <= main_text.size()) {
                    std::wstring* new_string = new std::wstring;
                    *new_string = str;
                    main_text.insert(main_text.begin() + stoi(loc) + down, new_string);
                }
                flag = 0;
            }
            if (e.type == Event::MouseButtonPressed) {
                Vector2i pos = Mouse::getPosition(query);
                if (pos.x >= 20 && pos.x <= 220 && pos.y >= 100 && pos.y <= 150) {
                    field = 1;
                } else if (pos.x >= 20 && pos.x <= 220 && pos.y >= 220 && pos.y <= 270) {
                    field = 2;
                } else if (pos.x >= 20 && pos.x <= 820 && pos.y >= 350 && pos.y <= 750) {
                    field = 3;
                }
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::BackSpace) {
                    if (len.size() != 0 && field == 1) len.pop_back();
                    if (loc.size() != 0 && field == 2) loc.pop_back();
                    if (str.size() != 0 && field == 3) str.pop_back();
                }
            }
            if (e.type == Event::TextEntered && in_text.size() < 16) {
                if (e.text.unicode < 128 && e.text.unicode != 8 ||
                    e.text.unicode >= 1040 && e.text.unicode <= 1103 || 
                    e.text.unicode == 1025 || e.text.unicode == 1105) {
                    if (field == 1) len += (wchar_t)e.text.unicode;
                    else if (field == 2) loc += (wchar_t)e.text.unicode;
                    else if (field == 3 && e.text.unicode != 13 && str.size() <= 45) {
                        if (str == (wchar_t)"") {
                            str = (wchar_t)e.text.unicode;
                        } else {
                            if ((wchar_t)e.text.unicode == ' ') {
                                last_backspace = str.size();
                            }
                            str += (wchar_t)e.text.unicode;
                        }
                    } else if (len.size() != 0 && std::stoi(loc) <= main_text.size()) {
                        if (str.size() > 45) {
                            str += (wchar_t)e.text.unicode;
                            if (last_backspace == -1) {
                                std::wstring* new_string = new std::wstring;
                                *new_string = str;
                                main_text.insert(main_text.begin() + stoi(loc) + down, new_string);
                                ++down;
                                in_text.push_back(str);
                                str = (wchar_t)"";
                            } else {
                                std::wstring last = str.substr(last_backspace);
                                str.erase(str.begin() + last_backspace, str.end());
                                std::wstring* new_string = new std::wstring;
                                *new_string = str;
                                main_text.insert(main_text.begin() + stoi(loc) + down, new_string);
                                ++down;
                                in_text.push_back(str);
                                str = last;
                                str.erase(str.begin());
                                last_backspace = -1;
                            }
                        } else {
                            std::wstring* new_string = new std::wstring;
                            *new_string = str;
                            main_text.insert(main_text.begin() + stoi(loc) + down, new_string);
                            ++down;
                            in_text.push_back(str);
                            str = (wchar_t)"";
                            last_backspace = -1;
                        }
                    }
                }
            }
        }
        Text text;
        text.setFont(font);
        text.setFillColor(Color::Black);
        text.setString(len);
        text.setPosition(20, 100);
        query.draw(text);
        text.setString(loc);
        text.setPosition(20, 220);
        query.draw(text);
        text.setString(str);
        text.setPosition(20, 350 + 30 * down);
        if (str != (wchar_t)"") query.draw(text);
        query.display();
    }
}

std::vector<int> z_function(std::wstring& main_string, std::wstring& find_string) {
    std::wstring new_string = find_string + 'Є' + main_string;
    std::vector<int> z(new_string.size(), 0);
    z[0] = z.size();
    int l = 0, r = 0;
    for (int i = 1; i < new_string.size(); ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < new_string.size() && 
            new_string[z[i]] == new_string[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    std::vector<int> ans(main_string.size(), 0);
    for (int i = find_string.size() + 1; i < new_string.size(); ++i) {
        if (z[i] == find_string.size()) {
            ans[i - find_string.size() - 1] = 1;
        }
    }
    return ans;
}

void ChangeSubstringBack(std::vector<std::wstring*>& main_text, 
    std::wstring& substring_before, std::wstring& substring_after, int from, int to) {
    for (int number = from; number <= to; ++number) {
        std::vector<int> change = z_function(*main_text[number], substring_before);
        int delta = substring_after.size() - substring_before.size(), count = 0;
        for (int i = 0; i < change.size(); ++i) {
            if (change[i] == 1) {
                main_text[number]->erase(main_text[number]->begin() + i + delta * count,
                    main_text[number]->begin() + i + delta * count + substring_before.size());
                for (int j = 0; j < substring_after.size(); ++j) {
                    main_text[number]->insert(main_text[number]->begin() + i + j + delta * count, substring_after[j]);
                }
                ++count;
            }
        }
    }
}

std::pair<int, int> FindRange(std::wstring str) {
    std::pair<int, int> ans;
    for (int i = 0; i < str.size(); ++i) {
        if (!((static_cast<int>(str[i]) >= 48 && (static_cast<int>(str[i]) <= 57)) || str[i] == '-')) {
            return { 10000000, 10000000 };
        }
        if (i == 0 && !((static_cast<int>(str[i]) >= 48 && (static_cast<int>(str[i]) <= 57)))) {
            return { 10000000, 10000000 };
        }
    }
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == (wchar_t)'-') {
            ans.first = std::stoi(str.substr(0, i));
            ans.second = std::stoi(str.substr(i + 1, str.size() - i));
        }
    }
    return ans;
}

void ChangeStringBack(std::vector<std::wstring*>& main_text, int& flag, Font font) {
    RenderWindow query(VideoMode(1000, 600), "Change string");
    int type = 0;
    int field = 0;
    std::wstring len, string_1, string_2;
    while (query.isOpen()) {
        Event e;
        query.clear(Color::White);
        while (query.pollEvent(e)) {
            if (e.type == Event::Closed) {
                query.close();
                if (type == 1 && (len.size() != 0 || string_1.size() != 0 ||
                    string_2.size() != 0)) {
                    auto [from, to] = FindRange(len);
                    if (from >= 1 && to <= main_text.size()) {
                        ChangeSubstringBack(main_text, string_1, string_2, from - 1, to - 1);
                    }
                } else if (type == 2 && (len.size() != 0 || string_1.size() != 0 ||
                    string_2.size() != 0)) {
                    int string = std::stoi(len), symbol = std::stoi(string_1);
                    if (string_2.size() != 0) {
                        (*main_text[string - 1])[symbol - 1] = string_2[0];
                    } else {
                        main_text[string - 1]->erase(main_text[string - 1] -> begin() + symbol - 1, 
                            main_text[string - 1]->begin() + symbol);
                    }
                } else if (type == 3 && (len.size() != 0 || string_1.size() != 0 ||
                    string_2.size() != 0)) {
                    int number = std::stoi(len) - 1, index = std::stoi(string_1);
                    for (int j = 0; j < string_2.size(); ++j) {
                        main_text[number]->insert(main_text[number]->begin() + index - 1 + j, string_2[j]);
                    }
                }
                flag = 0;
            }
            if (e.type == Event::MouseButtonPressed) {
                Vector2i pos = Mouse::getPosition(query);
                if (pos.x >= 680 && pos.x <= 980) {
                    if (pos.y >= 50 && pos.y <= 120) {
                        type = 1;
                    } else if (pos.y >= 140 && pos.y <= 210) {
                        type = 2;
                    } else if (pos.y >= 230 && pos.y <= 300) {
                        type = 3;
                    }
                } else if (pos.x >= 50 && pos.x <= 250 && pos.y >= 100 && pos.y <= 150) {
                    field = 1;
                } else if (pos.x >= 50 && pos.x <= 550 && pos.y >= 240 && pos.y <= 290) {
                    field = 2;
                } else if (pos.x >= 50 && pos.x <= 550 && pos.y >= 420 && pos.y <= 470) {
                    field = 3;
                }
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::BackSpace) {
                    if (len.size() != 0 && field == 1) {
                        len.pop_back();
                    } else if (string_1.size() != 0 && field == 2) {
                        string_1.pop_back();
                    } else if (string_2.size() != 0 && field == 3) {
                        string_2.pop_back();
                    }
                }
            }
            if (e.type == Event::TextEntered) {
                if (e.text.unicode < 128 && e.text.unicode != 8 ||
                    e.text.unicode >= 1040 && e.text.unicode <= 1103 || 
                    e.text.unicode == 1025 || e.text.unicode == 1105) {
                    if (field == 1) {
                        len += (wchar_t)e.text.unicode;
                    } else if (field == 2) {
                        string_1 += (wchar_t)e.text.unicode;
                    } else if (field == 3) {
                        string_2 += (wchar_t)e.text.unicode;
                    }
                }
            }
        }
        ChangeStringFront(query);
        if (type == 1) {
            ChangeSubstringFront(query);
        } else if (type == 2) {
            ChangeSymbol(query);
        } else if (type == 3) {
            InsertSubstring(query);
        }
        Text text;
        text.setFont(font);
        text.setFillColor({ 0, 0, 0 });
        text.setString(len);
        text.setPosition(50, 110);
        query.draw(text);
        text.setString(string_1);
        text.setPosition(50, 250);
        query.draw(text);
        text.setString(string_2);
        text.setPosition(50, 430);
        query.draw(text);
        query.display();
    }
}

void DeleteLeadingZeros(std::vector<std::wstring*>& main_text, int from, int to) {
    for (int i = from; i <= to; ++i) {
        std::wstring* current_string = main_text[i];
        for (int j = 0; j < current_string->size();) {
            if (j == 0 || (*current_string)[j] == ' ') {
                if (j + 1 < current_string->size() && (*current_string)[j + 1] == '0'){
                    int begin_index = j + 1, end_index = j + 1;
                    j += 2;
                    while ((*current_string)[j] == '0' && j < current_string -> size()) {
                        ++j;
                    }
                    end_index = j - 1;
                    if (j == current_string->size()) {
                        current_string->erase(current_string->begin() + begin_index,
                            current_string->begin() + end_index);
                    } else if (static_cast<int>((*current_string)[j]) >= 49 &&
                        static_cast<int>((*current_string)[j]) <= 57) {
                        current_string->erase(current_string->begin() + begin_index,
                            current_string->begin() + end_index + 1);
                    } else {
                        current_string->erase(current_string->begin() + begin_index,
                            current_string->begin() + end_index);
                    }
                } else {
                    ++j;
                }
            } else {
                ++j;
            }
        }
    }
}

void IncreaseSubsequence(std::vector<std::wstring*>& main_text, int from, int to) {
    for (int i = from; i <= to; ++i) {
        std::wstring* current_string = main_text[i];
        int begin_index = -1, end_index = -1;
        for (int j = 0; j < current_string->size();) {
            if (static_cast<int>((*current_string)[j]) >= 48 &&
                static_cast<int>((*current_string)[j]) <= 57) {
                begin_index = j;
                ++j;
                while (static_cast<int>((*current_string)[j]) >= 48 &&
                    static_cast<int>((*current_string)[j]) <= 57 && j < current_string->size()) {
                    ++j;
                }
                end_index = j - 1;
                for (int k = begin_index + 1; k < end_index ; ++k) {
                    if ((*current_string)[k - 1] - '0' >= (*current_string)[k] - '0') {
                        current_string->erase(current_string->begin() + begin_index,
                            current_string->begin() + end_index + 1);
                        j = begin_index;
                        begin_index = -1, end_index = -1;
                        break;
                    }
                }
            } else {
                ++j;
            }
        }
    }
}

void StarsToPlus(std::vector<std::wstring*>& main_text, int from, int to) {
    for (int i = from; i <= to; ++i) {
        std::wstring* current_string = main_text[i];
        int begin_index = -1;
        for (int j = 0; j < current_string->size();) {
            int count = 0;
            if (static_cast<int>((*current_string)[j]) == '*') {
                begin_index = j;
                while (static_cast<int>((*current_string)[j]) == '*' && j < current_string->size()) {
                    ++j;
                    count++;
                }
                if (count != 1) {
                    int a;
                    current_string->erase(current_string->begin() + begin_index,
                        current_string->begin() + begin_index + count);
                    for (int k = 0; k < count / 2; ++k) {
                        current_string->insert(current_string->begin() + begin_index + k, '+');
                    }
                    j -= count / 2;
                }
            } else {
                ++j;
            }
        }
    }
}

void DeleteBetweenBrackets(std::vector<std::wstring*>& main_text, int from, int to) {
    for (int i = from; i <= to; ++i) {
        std::wstring* current_string = main_text[i];
        int begin_index = -1, end_index = -1;
        for (int j = 0; j < current_string->size(); ++j) {
            if ((*current_string)[j] == '{') {
                begin_index = j;
            }
            if ((*current_string)[j] == '}') {
                end_index = j;
                if (begin_index != -1) {
                    current_string->erase(current_string->begin() + begin_index,
                        current_string->begin() + end_index + 1);
                }
            }
        }
    }
}

void Algorithm(std::vector<std::wstring*>& main_text, int& flag, Font font) {
    RenderWindow query(VideoMode(1000, 550), "Algorithmic changes");
    int type = 0;
    bool input = false;
    std::wstring len;
    while (query.isOpen()) {
        Event e;
        query.clear(Color::White);
        while (query.pollEvent(e)) {
            if (e.type == Event::Closed) {
                query.close();
                auto [from, to] = FindRange(len);
                if (from >= 1 && to <= main_text.size()) {
                    if (type == 1) {
                        DeleteLeadingZeros(main_text, from - 1, to - 1);
                    } else if (type == 2) {
                        IncreaseSubsequence(main_text, from - 1, to - 1);
                    } else if (type == 3) {
                        StarsToPlus(main_text, from - 1, to - 1);
                    } else if (type == 4) {
                        DeleteBetweenBrackets(main_text, from - 1, to - 1);
                    }
                }
                flag = 0;
            } else if (e.type == Event::MouseButtonPressed) {
                Vector2i pos = Mouse::getPosition(query);
                if (pos.x >= 680 && pos.x <= 980) {
                    if (pos.y >= 50 && pos.y <= 150) {
                        type = 1;
                    } else if (pos.y >= 170 && pos.y <= 270) {
                        type = 2;
                    } else if (pos.y >= 290 && pos.y <= 390) {
                        type = 3;
                    } else if (pos.y >= 420 && pos.y <= 520) {
                        type = 4;
                    }
                }
                if (pos.x >= 50 && pos.x <= 250 && pos.y >= 100 && pos.y <= 150) {
                    input = true;
                }
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::BackSpace) {
                    if (len.size() != 0 && input) {
                        len.pop_back();
                    }
                }
            }
            if (e.type == Event::TextEntered) {
                if ((e.text.unicode < 128 && e.text.unicode != 8 ||
                    e.text.unicode >= 1040 && e.text.unicode <= 1103) && input) {
                    len += (wchar_t)e.text.unicode;
                }
            }
        }
        AlgorithmFront(query);
        Text text;
        text.setString(len);
        text.setCharacterSize(30);
        text.setFont(font);
        text.setFillColor({ 0, 0, 0 });
        text.setPosition(70, 100);
        query.draw(text);
        query.display();
    }
}

void DeleteStrings(std::vector<std::wstring*>& main_text, int& flag, Font font) {
    RenderWindow query(VideoMode(1000, 300), "Delete strings");
    std::wstring len;
    bool input = false;
    while (query.isOpen()) {
        Event e;
        query.clear({ 255, 255, 255 });
        while (query.pollEvent(e)) {
            if (e.type == Event::Closed) {
                query.close();
                auto [from, to] = FindRange(len);
                if (from >= 1 && to <= main_text.size()) {
                    main_text.erase(main_text.begin() + from - 1, main_text.begin() + to);
                }
                flag = 0;
            }
            if (e.type == Event::MouseButtonPressed) {
                Vector2i pos = Mouse::getPosition(query);
                if (pos.x >= 50 && pos.x <= 250 && pos.y >= 100 && pos.y <= 150) {
                    input = true;
                }
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::BackSpace) {
                    if (len.size() != 0 && input) {
                        len.pop_back();
                    } 
                }
            }
            if (e.type == Event::TextEntered) {
                if ((e.text.unicode < 128 && e.text.unicode != 8 ||
                    e.text.unicode >= 1040 && e.text.unicode <= 1103) && input) {
                    len += (wchar_t)e.text.unicode;
                }
            }
        }
        DeleteStringFront(query);
        Text text;
        text.setFillColor({ 0, 0, 0 });
        text.setString(len);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setPosition(50, 100);
        query.draw(text);
        query.display();
    }
}

void BackEnd(RenderWindow& app) {
    Font font;
    font.loadFromFile("C:/Users/salex/source/repos/text_editor/Debug/couriernew.ttf");
    int flag = 0;
    int scroll = 0;
    std::vector<std::wstring*> main_text;
    while (app.isOpen()) {
        Event event;
        app.clear(Color::White);
        for (int i = scroll; i < std::min(scroll + 25, static_cast<int>(main_text.size())); ++i) {
            Text string;
            string.setFont(font);
            if (main_text[i]->size() > 47) {
                std::wstring substr = main_text[i]->substr(47);
                main_text[i]->erase(main_text[i]->begin() + 47, main_text[i]->end());
                std::wstring* in_string = new std::wstring;
                *in_string = substr;
                main_text.insert(main_text.begin() + i + 1, in_string);
                
            }
            string.setString(*main_text[i]);
            string.setPosition(20, 100 + 30 * (i - scroll));
            string.setFillColor({ 0, 0, 0 });
            app.draw(string);
        }
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) {
                app.close();
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                if (main_text.size() >= 26) {
                    if (event.mouseWheelScroll.delta < 0) {
                        scroll = std::max(0, scroll - 1);
                    } else {
                        scroll = std::min(static_cast<int>(main_text.size()) - 27, scroll + 1);
                    }
                }
            }
            else if (flag == 0 && event.type == Event::MouseButtonPressed) {
                Vector2i pos = Mouse::getPosition(app);
                int x = pos.x, y = pos.y;
                if (x >= 1020 && x <= 1380 && y >= 140 && y <= 240) { // добавление строки
                    flag = 1;
                } else if (x >= 1020 && x <= 1380 && y >= 280 && y <= 380) { // изменение строки
                    flag = 2;
                } else if (x >= 1020 && x <= 1380 && y >= 420 && y <= 520) { // алгоритмические замены
                    flag = 3;
                } else if (x >= 1020 && x <= 1380 && y >= 560 && y <= 660) { // изменение расположени€ строк
                    flag = 4;
                }
            } else if (flag == 1) {
                AddStringBack(main_text, flag, font);
            } else if (flag == 2) {
                ChangeStringBack(main_text, flag, font);
            } else if (flag == 3) {
                Algorithm(main_text, flag, font);
            } else if (flag == 4) {
                DeleteStrings(main_text, flag, font);
            }
        }
        DrawBackground(app);
        DrawButtons(app);
        app.display();
    }
}
