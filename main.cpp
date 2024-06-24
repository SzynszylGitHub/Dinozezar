#include "Window.h"
#include "Bird.h"
#include "Cactus.h"
#include "Background.h"
#include "Bar.h"
#include "SFML/System.hpp"
#include <vector>
#include <random>

// window size
const int Y = 500;
const int X = 800;

// obstacle 
Bird* bird;
Cactus* cactus;

// background 
Background* cloud;
Background* deathBush;

bool Hit(sf::Event& event, Actor& player, std::vector<Actor*>& Characters);
void Move(std::vector<Actor*>& Characters, float force);
void setPos(Actor* p, sf::Vector2f);
void create_obj();
std::vector<Actor*> generateObstacle();
std::vector<Actor*> generatePicture();
void SumVectors(std::vector<Actor*>& A, std::vector<Actor*> B);
bool S(sf::Time& Time, sf::Time& t1, sf::Time delay);
bool background(Actor* pawn);
int generateRandomNumber(int min, int max);
bool OpenMenu(std::string name);
bool press_sth(sf::Event& event, sf::Keyboard::Key code);
sf::Texture loadT(std::string name);

int main()
{
    if (!OpenMenu("asset/Menu.png")) return 0;
    bool IsEnd = false;

    while (!IsEnd) {
        Window Game("World!", X, Y);
        Game.setBackground("asset/background.png");

        // set game 
        std::vector<Actor*> Characters;
        Actor player(std::string("SNS"), loadT("asset/Dino1.png"));
        sf::Texture p1, p2;
        p1.loadFromFile("asset/Dino_step_R.png");
        p2.loadFromFile("asset/Dino_step_L.png");
        player.setAnimetionTXT(p1, p2);
        setPos(&player, sf::Vector2f(0, 0));
        player.corect_hitbox(sf::Vector2f(40, 40));
        player.hitbox_visibility(false);

        //obstacle
        cactus = new Cactus(std::string("Cactus"), loadT("asset/cactus.png"));
        bird = new Bird(std::string("Birds"), loadT("asset/birds.png"));

        // background 
        cloud = new Background(std::string("Cloud"), loadT("asset/cloud.png"));
        deathBush = new Background(std::string("Death Bush"), loadT("asset/Death_bush.png"));

        // End Screen
        float score = 0;
        bool clear = true;
        sf::Font font;
        font.loadFromFile("asset/font/EnglishTowne.ttf");
        std::string info = std::string("You'r score: ") + std::to_string(score / 300.f);

        Bar StartView("Press up to Jump!", font, sf::Vector2f(0, 100), sf::Vector2f(800, 200));
        StartView.reSizeCharacter(40);
        StartView.center();
        sf::Color color3(100, 170, 170, 255 * 0.8);
        StartView.setColorRectangle(color3);

        Bar GameIsEnd(info, font, sf::Vector2f(0, 100), sf::Vector2f(800, 300));
        GameIsEnd.reSizeCharacter(50);
        GameIsEnd.center();
        sf::Color color(100, 170, 170, 255 * 0.8);
        GameIsEnd.setColorRectangle(color);

        Bar Scoreview("", font, sf::Vector2f(600, 0), sf::Vector2f(100, 100));
        Scoreview.reSizeCharacter(40);
        Scoreview.center();
        sf::Color color2(0, 0, 0, 0);
        Scoreview.setColorRectangle(color2);

        Characters.clear();

        //time duration
        sf::Clock Clock;
        Clock.restart();

        sf::Time Delay = sf::Time::Zero;
        sf::Time D1 = sf::Time::Zero;
        sf::Time Delay_obstacle = sf::Time::Zero;
        sf::Time Delay_picture = sf::Time::Zero;
        sf::Time time;
        create_obj();

        //stats
        score = 0;

        //settings 
        float force = 5.f;
        sf::Event event;

        while (Game.isOpen()) {
            Clock.restart();
            while (Game.pollEvent(event)) {
                if (!IsEnd) {
                    Delay = Clock.getElapsedTime();
                    time += Delay;
                    Scoreview.setString(
                        std::to_string(
                            (time.asSeconds() - 300.f) / 1000 > 0 ? (time.asSeconds() - 300.f) / 1000 : 0));
                    player.animate(Delay);
                    player.jump(event, force);
                    IsEnd = Hit(event, player, Characters);

                    // cleaning characters form memory
                    if (Characters.size() > 20) {
                        Characters.erase(Characters.begin() + 1, Characters.begin() + 11);
                        //std::cout << "cleaning" << std::endl;
                    }
                    
                    if (S(Delay, D1, sf::seconds(4)))
                        force += 2;

                    if (S(Delay, Delay_obstacle, sf::seconds(2)))
                        SumVectors(Characters, generateObstacle());

                    if (S(Delay, Delay_picture, sf::seconds(3)))
                        SumVectors(Characters, generatePicture());

                    Move(Characters, force);
                }
                if (IsEnd && clear) {
                    for (auto& n : Characters)
                        n->setForce(sf::Vector2f(0, 0));

                    player.setForce(sf::Vector2f(0, 0));

                    //seting score   
                    info = std::string("You'r score: ") + Scoreview.getTitle();
                    info += "\n Press R to restart";
                    GameIsEnd.setString(info);
                }

                if (event.key.code == sf::Keyboard::Escape) {
                    Game.close();
                    IsEnd = true;
                }

                if (event.type == event.Closed) {
                    Game.close();
                    IsEnd = true;
                }

                Game.Render(player, Characters);
                if (IsEnd) {
                    GameIsEnd.draw(Game.getHandle());
                    if (press_sth(event, sf::Keyboard::Key::R)) {
                        IsEnd = false;
                        Game.close();
                    }
                }
                if (std::atof(Scoreview.getTitle().c_str()) == 0) {
                    StartView.draw(Game.getHandle());
                }
                Scoreview.draw(Game.getHandle());
                Game.display();
            }
            Game.close();
        }
    }
    return 0;
}

bool Hit(sf::Event& event, Actor& player, std::vector<Actor*>& Characters) {
    player.Update();

    for (int i = 0; i < Characters.size(); i++) {
        if (player.getHit(*Characters[i]) && !background(Characters[i])) {
            return true;
        }
    }
    return false;
}

sf::Texture loadT(std::string name) {
    sf::Texture txt;
    txt.loadFromFile(name);
    return txt;
}

void setPos(Actor* p, sf::Vector2f pos) {
    pos += p->getSize();
    p->setPosition(sf::Vector2f(pos.x, Y - pos.y));
}

void Move(std::vector<Actor*>& Characters, float force) {
    for (auto& n : Characters)
        n->setForce(sf::Vector2f(-force, 0));
}

void create_obj() {
    setPos(bird, sf::Vector2f(700, generateRandomNumber(120, 200)));
    bird->corect_hitbox(sf::Vector2f(5, 5));

    setPos(cactus, sf::Vector2f(800, 0));
    cactus->corect_hitbox(sf::Vector2f(30, 10));

    setPos(deathBush, sf::Vector2f(850, -10));
    deathBush->corect_hitbox(sf::Vector2f(0, 0));

    setPos(cloud, sf::Vector2f(850, generateRandomNumber(300, 400)));
    cloud->corect_hitbox(sf::Vector2f(0, 0));
}

std::vector<Actor*> generateObstacle() {
    std::vector<Actor*> Characters;
    int option = generateRandomNumber(1, 2);
    setPos(bird, sf::Vector2f(500, generateRandomNumber(120, 200)));

    int ile = generateRandomNumber(1, 3);
    for (int i = 0; i < ile; i++) {
        switch (option) {
        case 1: Characters.push_back(new Bird(*bird)); break;
        case 2: Characters.push_back(new Cactus(*cactus)); break;
        }
    }
    return Characters;
}

std::vector<Actor*> generatePicture() {
    std::vector<Actor*> Characters;
    setPos(cloud, sf::Vector2f(500, generateRandomNumber(300, 400)));

    int option = generateRandomNumber(1, 2);
    switch (option) {
    case 1: Characters.push_back(new Background(*cloud)); break;
    case 2: Characters.push_back(new Background(*deathBush)); break;
    }
    return Characters;
}

bool S(sf::Time& Time, sf::Time& t1, sf::Time delay) {
    if ((Time - t1) > delay) {
        t1 = Time;
        return true;
    }
    return false;
}

bool background(Actor* pawn) {
    return pawn->getName() == "Cloud" || pawn->getName() == "Death Bush";
}

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

void SumVectors(std::vector<Actor*>& A, std::vector<Actor*> B) {
    for (auto& el : B)
        A.push_back(el);
}

bool OpenMenu(std::string name) {
    sf::RenderWindow Menu(sf::VideoMode(800, 800), "Menu!", sf::Style::Close);
    sf::Event event;
    sf::Texture t1;
    if (!t1.loadFromFile("asset/Menu.png"))
        std::cerr << "asset/Menu.png\n";
    sf::Sprite bg(t1);

    std::string Instruct = "Click up  !";
    std::vector<std::string> menuItems = { "Start Game", "Exit" };
    int selectedItemIndex = 1;

    sf::Font font;
    if (!font.loadFromFile("asset/font/EnglishTowne.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return -1;
    }

    sf::Text Title(Instruct, font, 50);
    Title.setFillColor(sf::Color::Black);
    Title.setPosition((Menu.getSize().x - Title.getGlobalBounds().width) / 2.f, (Title.getGlobalBounds().height + 150));
    std::vector<sf::Text> texts;
    for (const auto& item : menuItems) {
        sf::Text text(item, font, 40);
        text.setFillColor(sf::Color::White);
        texts.push_back(text);
    }

    float totalHeight = texts.size() * texts[0].getGlobalBounds().height;
    float startY = (Menu.getSize().y - totalHeight) / 2.0f;
    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i].setPosition((Menu.getSize().x - texts[i].getGlobalBounds().width) / 2.0f, startY + i * (texts[i].getGlobalBounds().height + 10));
    }

    sf::Event _event;
    while (Menu.isOpen()) {
        Menu.clear();
        Menu.draw(bg);
        Menu.draw(Title);
        for (const auto& text : texts) {
            Menu.draw(text);
        }
        Menu.display();
        while (Menu.pollEvent(_event)) {
            if (_event.type == sf::Event::KeyPressed) {
                if (_event.key.code == sf::Keyboard::Up) {
                    if (selectedItemIndex > 0) {
                        texts[selectedItemIndex].setFillColor(sf::Color::White);
                        selectedItemIndex--;
                        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
                    }
                }
                if (_event.key.code == sf::Keyboard::Down) {
                    if (selectedItemIndex < menuItems.size() - 1) {
                        texts[selectedItemIndex].setFillColor(sf::Color::White);
                        selectedItemIndex++;
                        texts[selectedItemIndex].setFillColor(sf::Color::Yellow);
                    }
                }
                if (_event.key.code == sf::Keyboard::Return) {
                    if (selectedItemIndex == 0) {
                        Menu.close();
                        return true;
                    }
                    else if (selectedItemIndex == 1) {
                        Menu.close();
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

bool press_sth(sf::Event& event, sf::Keyboard::Key code) {
    if (event.key.code == code) {
        return true;
    }
    return false;
}
