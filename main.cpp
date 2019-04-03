#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Sprite{
    std::vector<sf::IntRect> Frames;
    int CurrentFrame = 0;
    float AnimationFPS = 4.f;
    sf::Time CurrentFrameTime;
public:
    AnimatedSprite(const sf::Texture &Texture) : sf::Sprite(Texture){}

    void AddAnimationFrame(const sf::IntRect &Frame){
        if(Frames.empty()){
            setTextureRect(Frame);
        }
        Frames.push_back(Frame);
    }

    void Step(sf::Time TimeElapsed){
        CurrentFrameTime += TimeElapsed;
        if(CurrentFrameTime.asSeconds() >= 1.f/AnimationFPS){
            setTextureRect(Frames[CurrentFrame]);
            CurrentFrame = (CurrentFrame + 1) % Frames.size();
            CurrentFrameTime.Zero;
        }
    }
};

int main()
{
    sf::Vector2i WindowSize = sf::Vector2i(800,600);
    std::vector<sf::Texture> TextureCollection;

    sf::RenderWindow Window(sf::VideoMode(static_cast <unsigned int>(WindowSize.x), static_cast <unsigned int>(WindowSize.y)), "My window");

    sf::Event Event;
    sf::Clock GameClock;
    sf::Time TimeElapsed;

    Window.setVerticalSyncEnabled(true);

    sf::Texture Texture;

    if(Texture.loadFromFile("Images\\Character\\character.png")){
        TextureCollection.push_back(Texture);
    }

    AnimatedSprite CharacterSprite(TextureCollection[0]);

    CharacterSprite.scale(5,5);

    CharacterSprite.AddAnimationFrame(sf::IntRect(0,0,50,37));
    CharacterSprite.AddAnimationFrame(sf::IntRect(50,0,50,37));
    CharacterSprite.AddAnimationFrame(sf::IntRect(100,0,50,37));

    while (Window.isOpen()) {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed){
                Window.close();
            }
        }

        Window.clear(sf::Color::Black);
        Window.draw(CharacterSprite);

        TimeElapsed = GameClock.getElapsedTime();

        CharacterSprite.Step(TimeElapsed);

        GameClock.restart();
        Window.display();
    }
    return 0;
}
