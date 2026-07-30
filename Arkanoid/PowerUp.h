#pragma once
#include "Collidable.h"
#include "GameObject.h"

namespace ArkanoidGame
{
    class PowerUp : public GameObject, public Collidable
    {
    public:
        /* Порядок должен совпадать с порядком капсул в powerups.png */
        enum class Type
        {
            Expand = 0, // E — шире платформа
            Reduce, // R — уже платформа
            MultiBall, // M — размножение мячей
            Catch, // C — платформа ловит мяч
            Slow, // S — замедление мяча
            Life, // L — дополнительная жизнь
            // TODO: сделать стреляющие турели. Лежат в спрайтазх
        };

        PowerUp(Type type, sf::Vector2f position);

        void Init(Game& game) override;
        void Update(Game& game, float dt) override;
        bool IsDestroyed() const override;

        Type GetType() const { return _type; }
        void Collect() { _isCollected = true; }

        /* Пока не используется */
        static bool IsInstant(Type type);
        static sf::IntRect GetIconRect(Type type);
        static Type GetRandomType();

        bool HasCollisionWith(const Collidable& other) const override;

        sf::FloatRect GetBounds() const override { return _sprite.getGlobalBounds(); }

    protected:
        void OnHit(Collidable& other) override;

    private:
        Type _type = Type::Expand;
        bool _isCollected = false;
    };
}
