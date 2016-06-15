#include "ZE_EventManager.h"
#include "ZE_Core.h"

using namespace std;

std::atomic_bool EventManagerSingleton_AreCtor{ false };

EventManager::EventManager()
{
	if (EventManagerSingleton_AreCtor.exchange(true))
	{
		throw std::runtime_error("EventManager::EventManager Singleton error");
	}
}

EventManager::~EventManager()
{
}

void EventManager::handleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			GlobalState->ZE_QUIT_MAIN_LOOP = true;
		}
		else
		{
			// �������Ϣģʽ
			if (!RegistedEvent.empty())
			{
				// �ȼ���Ƿ��б�ע��
				if (RegistedEvent.find(e.type) != RegistedEvent.end())
				{
					// ��ȡ�����͵ļ�����
					auto itp = AllEvents.get<EventContainerTag::EventType>().equal_range(e.type);
					// ����Ƿ񲢲�����
					if (itp.first == itp.second)
					{
						// ���������ʾRegistedEvent��ʱ�ˣ����������־λ
						RegistedEvent.erase(e.type);
					}
					else
					{
						// �������������Ҫ���������Ϣ�ļ�������ִ��
						while (itp.first != itp.second)
						{
							itp.first->event_data.func(e);
							++itp.first;
						}
					}
				}
			}
			// TODO �������ģʽ
			if (
				e.type == SDL_MOUSEMOTION ||
				e.type == SDL_MOUSEWHEEL ||
				e.type == SDL_MOUSEBUTTONDOWN ||
				e.type == SDL_MOUSEBUTTONUP
				)
			{

			}
			// TODO �����¼���ģʽ
			if (
				e.type == SDL_KEYDOWN ||
				e.type == SDL_KEYUP
				)
			{

			}
			//Get mouse position 
			int x, y;
			SDL_GetMouseState(&x, &y);
			const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
		}
	}
}

size_t EventManager::addEventFunction(size_t dispatch_index, SDL_EventType type, EventDispatcher* signedObject, function<void(SDL_Event)> func)
{
	size_t index = ++event_index;
	EventData temp;
	temp.type = type;
	temp.signedObject = signedObject;
	temp.func = func;
	temp.eventIndex = index;
	AllEvents.emplace_back(index, dispatch_index, type, temp);
	RegistedEvent.insert(type);
	return index;
}

void EventManager::removeEventOfIndex(size_t event_index)
{
	AllEvents.get<EventContainerTag::Index>().erase(event_index);
}

void EventManager::removeAllEventOfDispatch(size_t dispatch_index)
{
	AllEvents.get<EventContainerTag::DispatchIndex>().erase(dispatch_index);
}

void EventManager::removeAllEventOfDispatchAndType(size_t dispatch_index, SDL_EventType type)
{
	AllEvents.get<EventContainerTag::DispatchIndexAndEventType>().erase(
		AllEvents.get<EventContainerTag::DispatchIndexAndEventType>().find(
			std::make_tuple(dispatch_index, type)
		)
	);
}

void EventManager::removeAllEvent()
{
	AllEvents.clear();
}

size_t EventManager::dispatchIndexDistributor()
{
	return ++dispatch_index;
}
