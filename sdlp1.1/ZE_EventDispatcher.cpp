#include "ZE_Core.h"
#include "ZE_EventDispatcher.h"

using namespace std;

// FIXME��������������ڶ��߳��е��ã���ΪGlobalStateû���ڹ��캯���г�ʼ���������ڴ����͵�ĳ�������ʼ��ʱ���GlobalState��
void EventDispatcher::addEventListener(EventMode event_mode, SDL_EventType type, function<void(SDL_Event)> func)
{
	if (~0 == dispatch_index.load())
	{
		dispatch_index.store(GlobalState->ZE_eventHandler->dispatchIndexDistributor());
	}
	GlobalState->ZE_eventHandler->addEventFunction(dispatch_index, event_mode, type, this, func);
}

void EventDispatcher::removeEventListeners(SDL_EventType type) const
{
	GlobalState->ZE_eventHandler->removeAllEventOfDispatchAndType(dispatch_index, type);
}

void EventDispatcher::removeAllEvents() const
{
	GlobalState->ZE_eventHandler->removeAllEventOfDispatch(this->dispatch_index);
}

EventDispatcher::EventDispatcher()
{}

EventDispatcher::~EventDispatcher()
{
	removeAllEvents();
}
