#pragma once

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <SDL.h>

class EventDispatcher;

//��eventDispatcher���õ�Ԫ�ؽṹ��
struct EventData
{
	SDL_EventType type;
	EventDispatcher* signedObject;
	std::function<void(SDL_Event)> func;
	size_t eventIndex;
};

// �¼��������ýṹ��
struct EventStruct
{
	explicit EventStruct(size_t index, SDL_EventType type, EventData &event_data)
		:index(index), type(type), event_data(event_data) {}
	size_t index;
	SDL_EventType type;
	EventData event_data;
	bool operator<(const EventStruct& o) const
	{
		return index < o.index;
	}
};

namespace EventContainerTag
{
	class Index {};
	class Type {};
}

// �¼���������������
using EventContainer = ::boost::multi_index_container<
	EventStruct,
	::boost::multi_index::indexed_by<
	::boost::multi_index::ordered_unique<
	::boost::multi_index::identity<EventStruct>
	>,
	::boost::multi_index::ordered_unique<
	::boost::multi_index::tag<EventContainerTag::Index>,
	::boost::multi_index::member<EventStruct, size_t, &EventStruct::index>
	>,
	::boost::multi_index::ordered_non_unique<
	::boost::multi_index::tag<EventContainerTag::Type>,
	::boost::multi_index::member<EventStruct, SDL_EventType, &EventStruct::type>
	>
	>
>;

