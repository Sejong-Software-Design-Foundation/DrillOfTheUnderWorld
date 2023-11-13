#ifdef __cplusplus

extern "C" {

#endif

#pragma once
#include <Windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H
LPCWSTR ConvertToLPCWSTR(const char* ansiStr);

//PlaySound �Լ��� ������ ���������
inline void playBGM(char* fileName) {
	PlaySound(ConvertToLPCWSTR(fileName), NULL, SND_ASYNC | SND_LOOP);
}

//�� ���������� ������� ���� ������̴� ������ ����
inline void stopBGM() {
	PlaySound(ConvertToLPCWSTR("null_sound.wav"), NULL, SND_ASYNC);
}

//mci�� ����Ͽ� �Ҹ��� ����ϱ� ���� �Լ�
inline void playSound(char* fileName) {
	char command[100];
	sprintf_s(command, "play %s", fileName);
	mciSendString(ConvertToLPCWSTR(command), NULL, 0, NULL);
}

//������̴� �Ҹ��� ���߱� ���� �Լ�
inline void stopSound(char* fileName) {
	char command[100];
	sprintf_s(command, "stop %s", fileName);
	mciSendString(ConvertToLPCWSTR(command), NULL, 0, NULL);
}

#endif


#ifdef __cplusplus
}
#endif