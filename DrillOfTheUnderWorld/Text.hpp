#include "common.hpp"

#pragma once


// ������ �ִ� ��츦 ó���ϴ� �Լ�
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, wchar_t* text) {
    if (weight == 0) weight = 900;
    size = (int)(size * RESOLUTION_MULTIPLIER);
    const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
        0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ձٸ��"));

    SelectObject(hdc, font);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, textColor);
    SetTextAlign(hdc, align);

    x = (int)(x * RESOLUTION_MULTIPLIER);
    y = (int)(y * RESOLUTION_MULTIPLIER);
    TextOut(hdc, x, y, text, lstrlen(text));

    PAINTSTRUCT paint;
    EndPaint(GetConsoleWindow(), &paint);

    DeleteObject(font);
}

// ������ ���� ��츦 ó���ϴ� �Լ�
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, wchar_t* text) {
    printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text);
}
