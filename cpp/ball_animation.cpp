#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

// Ball sınıfı - toplarin özelliklerini ve hareketlerini içerir
class Ball {
private:
    sf::CircleShape shape;
    float dx, dy;
    float speed;
    bool is_running;

public:
    Ball(float size, sf::Color color, float speed) {
        this->speed = speed;
        is_running = false;

        // Rastgele yön belirleme
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dir_dist(0, 1);
        
        dx = (dir_dist(gen) == 0 ? -1 : 1) * speed;
        dy = (dir_dist(gen) == 0 ? -1 : 1) * speed;

        // Top oluşturma
        shape.setRadius(size);
        shape.setFillColor(color);
        shape.setOrigin(size, size);

        // Rastgele konum belirleme
        std::uniform_int_distribution<> x_dist(size, 400 - size);
        std::uniform_int_distribution<> y_dist(size, 300 - size);
        
        shape.setPosition(x_dist(gen), y_dist(gen));
    }

    void move(const sf::Vector2u& windowSize) {
        sf::Vector2f position = shape.getPosition();
        float radius = shape.getRadius();

        // Kenarlardan sekme kontrolü
        if (position.x - radius <= 0 || position.x + radius >= windowSize.x) {
            dx = -dx;
        }
        if (position.y - radius <= 0 || position.y + radius >= windowSize.y) {
            dy = -dy;
        }

        // Topu hareket ettirme
        shape.move(dx, dy);
    }

    void updateSpeed(float newSpeed) {
        // Yönü koruyarak hızı güncelleme
        dx = (dx > 0) ? newSpeed : -newSpeed;
        dy = (dy > 0) ? newSpeed : -newSpeed;
        speed = newSpeed;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

// Button sınıfı - arayüzde kullanılan butonları temsil eder
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;

public:
    Button(float x, float y, float width, float height, 
           sf::Font& font, std::string text_str, 
           sf::Color idleColor, sf::Color hoverColor) {
        
        this->idleColor = idleColor;
        this->hoverColor = hoverColor;

        shape.setPosition(sf::Vector2f(x, y));
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(idleColor);

        text.setFont(font);
        text.setString(text_str);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(14);
        
        // Buton içinde metni ortalama
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(shape.getPosition().x + shape.getSize().x / 2.0f, 
                         shape.getPosition().y + shape.getSize().y / 2.0f);
    }

    // Butonun tıklanıp tıklanmadığını kontrol eder
    bool isClicked(sf::Vector2f mousePos) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            return true;
        }
        return false;
    }

    // Mouse butonun üzerinde mi kontrol eder ve rengi değiştirir
    void update(sf::Vector2f mousePos) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setFillColor(hoverColor);
        } else {
            shape.setFillColor(idleColor);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};

// CircleButton sınıfı - top ekleme butonlarını temsil eder
class CircleButton {
private:
    sf::CircleShape shape;
    float size;
    sf::Color color;

public:
    CircleButton(float x, float y, float radius, sf::Color color) {
        this->size = radius;
        this->color = color;
        
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setPosition(x, y);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
    }

    bool isClicked(sf::Vector2f mousePos) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            return true;
        }
        return false;
    }

    void setColor(sf::Color newColor) {
        color = newColor;
        shape.setFillColor(newColor);
    }

    float getSize() const {
        return size;
    }

    sf::Color getColor() const {
        return color;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

// BallAnimation sınıfı - ana uygulama sınıfı
class BallAnimation {
private:
    sf::RenderWindow window;
    std::vector<Ball> balls;
    std::vector<Button> buttons;
    std::vector<CircleButton> sizeButtons;
    std::vector<Button> colorButtons;
    
    sf::Font font;
    sf::Color selectedColor;
    float speed;
    bool isRunning;

public:
    BallAnimation() : window(sf::VideoMode(400, 500), "Ball Animation"), 
                      selectedColor(sf::Color::White), speed(2.0f), isRunning(false) {
        
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Font yüklenemedi! Varsayılan font kullanılacak." << std::endl;
        }

        // Start, Stop, Reset, Speedup butonları oluşturma
        buttons.push_back(Button(10, 320, 90, 30, font, "Start", sf::Color::White, sf::Color(200, 200, 200)));
        buttons.push_back(Button(110, 320, 90, 30, font, "Stop", sf::Color::White, sf::Color(200, 200, 200)));
        buttons.push_back(Button(210, 320, 90, 30, font, "Reset", sf::Color::White, sf::Color(200, 200, 200)));
        buttons.push_back(Button(310, 320, 80, 30, font, "Speedup", sf::Color::White, sf::Color(200, 200, 200)));

        // Renk butonları oluşturma
        colorButtons.push_back(Button(20, 370, 40, 30, font, "", sf::Color::Red, sf::Color::Red));
        colorButtons.push_back(Button(70, 370, 40, 30, font, "", sf::Color::Blue, sf::Color::Blue));
        colorButtons.push_back(Button(120, 370, 40, 30, font, "", sf::Color::Yellow, sf::Color::Yellow));

        // Boyut butonları oluşturma
        sizeButtons.push_back(CircleButton(200, 385, 10, sf::Color::White));
        sizeButtons.push_back(CircleButton(240, 385, 20, sf::Color::White));
        sizeButtons.push_back(CircleButton(300, 385, 30, sf::Color::White));
    }

    void run() {
        sf::Clock clock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                        handleMouseClick(mousePos);
                    }
                }
            }

            // Mouse pozisyonunu alarak butonları güncelle
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (auto& button : buttons) {
                button.update(mousePos);
            }

            // Animasyon güncellemesi
            if (isRunning) {
                for (auto& ball : balls) {
                    ball.move(window.getSize());
                }
            }

            render();
        }
    }

private:
    void handleMouseClick(sf::Vector2f mousePos) {
        // Start butonu
        if (buttons[0].isClicked(mousePos)) {
            isRunning = true;
        }
        // Stop butonu
        else if (buttons[1].isClicked(mousePos)) {
            isRunning = false;
        }
        // Reset butonu
        else if (buttons[2].isClicked(mousePos)) {
            balls.clear();
            isRunning = false;
        }
        // Speedup butonu
        else if (buttons[3].isClicked(mousePos)) {
            speed += 1.0f;
            for (auto& ball : balls) {
                ball.updateSpeed(speed);
            }
        }

        // Renk butonları
        for (size_t i = 0; i < colorButtons.size(); i++) {
            if (colorButtons[i].isClicked(mousePos)) {
                if (i == 0) selectedColor = sf::Color::Red;
                else if (i == 1) selectedColor = sf::Color::Blue;
                else if (i == 2) selectedColor = sf::Color::Yellow;
                
                // Boyut butonlarının rengini güncelle
                for (auto& sizeButton : sizeButtons) {
                    sizeButton.setColor(selectedColor);
                }
            }
        }

        // Boyut butonları
        for (auto& sizeButton : sizeButtons) {
            if (sizeButton.isClicked(mousePos)) {
                // Yeni top oluştur
                balls.push_back(Ball(sizeButton.getSize(), selectedColor, speed));
            }
        }
    }

    void render() {
        window.clear(sf::Color(211, 211, 211)); // lightgray

        // Animasyon alanı için çizgi
        sf::RectangleShape line(sf::Vector2f(400, 2));
        line.setPosition(0, 310);
        line.setFillColor(sf::Color::Black);
        window.draw(line);

        // Topları çiz
        for (auto& ball : balls) {
            ball.draw(window);
        }

        // Butonları çiz
        for (auto& button : buttons) {
            button.draw(window);
        }

        // Renk butonlarını çiz
        for (auto& colorButton : colorButtons) {
            colorButton.draw(window);
        }

        // Boyut butonlarını çiz
        for (auto& sizeButton : sizeButtons) {
            sizeButton.draw(window);
        }

        window.display();
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    
    BallAnimation app;
    app.run();
    
    return 0;
}