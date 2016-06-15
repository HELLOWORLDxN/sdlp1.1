#include "ZE_EngineGlobalState.h"
#include <assert.h>

std::atomic_bool EngineGlobalState_Singleton{ false };

EngineGlobalState::EngineGlobalState()
{
	if (EngineGlobalState_Singleton.exchange(true))
	{
		throw std::runtime_error("EngineGlobalState Re Ctor");
	}
}


EngineGlobalState::~EngineGlobalState()
{
	// �������ն��� �˶�����DEBUGģʽ�¼����������Ƿ�Ϊ��
	// ������������µ�ָ���Ƿ���ȷ�ÿ�
	assert(NULL == g_ZE_Window);
	assert(NULL == g_ZE_MainSurface);
	assert(NULL == g_ZE_MainRenderer);
}
