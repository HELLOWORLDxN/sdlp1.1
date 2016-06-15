#include "ZE_EngineGlobalState.h"
#include <assert.h>

#include <type_traits>

std::atomic_bool EngineGlobalState_Singleton{ false };


// ���������Թ�����
void test()
{

	auto z = make_sdl_unique_ptr((SDL_Texture*)nullptr, SDL_DestroyTexture);

	

	auto a = unique_ptr<SDL_Texture, decltype(SDL_DestroyTexture)*>((SDL_Texture*)nullptr, SDL_DestroyTexture);
	//auto b = unique_ptr<int>();
	//auto c = unique_ptr<int>();

	z.reset();

}




EngineGlobalState::EngineGlobalState()
{
	if (EngineGlobalState_Singleton.exchange(true))
	{
		throw std::runtime_error("EngineGlobalState Re Ctor");
	}
	test();
}


EngineGlobalState::~EngineGlobalState()
{
	// �������ն��� �˶�����DEBUGģʽ�¼����������Ƿ�Ϊ��
	// ������������µ�ָ���Ƿ���ȷ�ÿ�
	assert(NULL == g_ZE_Window);
	assert(NULL == g_ZE_MainSurface);
	assert(NULL == g_ZE_MainRenderer);
}
