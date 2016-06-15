#pragma once
#include <functional>
#include <SDL.h>
#include <atomic>
#include <unordered_map>

using namespace std;

//���п�ע���¼���Ļ���
class EventDispatcher
{
public:
	EventDispatcher();
	virtual ~EventDispatcher();
	void addEventListener(SDL_EventType type, function<void(SDL_Event)>);
	void removeEventListeners(SDL_EventType type) const;
	void removeAllEvents() const;
private:
	atomic_size_t dispatch_index{ ~0 };
};

