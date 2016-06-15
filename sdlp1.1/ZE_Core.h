#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <deque>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ZE_error.h"
#include "ZE_Sprite.h"
#include "ZE_EventManager.h"
#include "ZE_Controller.h"
#include "ZE_Fraps.h"
#include "ZE_Font.h"
#include "ZE_EngineGlobalState.h"

using namespace std;

//[Global]ZE�汾��
extern string ZE_version;
//[Global]����ȫ��״̬����
extern unique_ptr<EngineGlobalState> GlobalState;


//��ɫ�ṹ�壬Ҳ��������̨��ɫ��ʱ������
struct Color
{
	int red;
	int green;
	int blue;
};

//��Game�࣬�û�Ӧ�̳д��ಢ��дMainLoop��Close������Ȼ��һ�������ָ�봫�ݸ�start����
class Game
{
public:
	virtual void MainLoop() = 0;
	virtual void Close() = 0;
	virtual ~Game() {}
};

//ͷ�ļ��������࣬cpp�ж����࣬ȫ��һ��
//���ļ���ZE�ĺ����࣬��������������Ķ����ڴ�����
//ʹ��ʱ���̳б��ಢ����Draw()����������ͼ����д��Draw������
class ZeroEngine
{
public:
	ZeroEngine();
	~ZeroEngine();
	//��̨��ɫ��Ĭ��Ϊ��
	Color stageColor = { 0, 0, 0 };
	//��ʼ��������ʹ��ZEǰ������ô˷���
	//�÷��������˱����е����������������ֱ��ʼ�����ⲿ��SDL��SDL_IMAGE
	//�÷����᷵��һ��boolֵ��������ģ���ʼ���ɹ��򷵻�true�����򷵻�false
	//�ⲿ��ı���д�ڶ�Ӧ������
	bool Init(string, int, int, bool, std::string defaultFontFile = "data/ttf/SourceHanSansSC-Normal.otf");
	//�÷�����ZE����ѭ��������Ŀǰ�����ð�
	void Start(Game*);

private:
	//�����Ⱦ����̨�ϣ���ʾһЩ���ӱ���
	unique_ptr<Fraps> fraps;
	//SDL�ĳ�ʼ���������÷��������������ֱ��Ǵ��ڱ��⡢���ڿ�ȡ����ڸ߶�
	bool Init_SDL(string, int, int);
	//��ʼ����SDL_IMAGE��������
	bool Init_SDL_Image(bool);
	//��ʼ����SDL_TTF��������
	bool Init_SDL_ttf();
	bool Init_SDL_Mixer();
	//����������ȫ�Ĺر�SDL���˳�����
	void Close();
	//�û�����Ϸ����
	Game* maingame{ nullptr };
};