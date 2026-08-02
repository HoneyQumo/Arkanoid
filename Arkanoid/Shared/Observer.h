#pragma once
#include <algorithm>
#include <memory>
#include <vector>

namespace ArkanoidGame
{
    enum class ObservableEvent
    {
        BrickDestroyed = 0,
        BallFallen,
    };

    class IObservable;

    class IObserver
    {
    public:
        virtual ~IObserver() = default;

        virtual void Notify(std::shared_ptr<IObservable> observable, ObservableEvent event) = 0;
    };

    class IObservable : public std::enable_shared_from_this<IObservable>
    {
    public:
        virtual ~IObservable() = default;

        void AddObserver(std::weak_ptr<IObserver> observer)
        {
            _observers.push_back(std::move(observer));
        }

    protected:
        void Emit(const ObservableEvent event)
        {
            _observers.erase(
                std::remove_if(
                    _observers.begin(),
                    _observers.end(),
                    [](const std::weak_ptr<IObserver>& observer) { return observer.expired(); }),
                _observers.end());

            const auto self = shared_from_this();

            for (const auto& observer : _observers)
            {
                if (const auto locked = observer.lock())
                {
                    locked->Notify(self, event);
                }
            }
        }

    private:
        std::vector<std::weak_ptr<IObserver>> _observers;
    };
}
