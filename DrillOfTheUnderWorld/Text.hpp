#include "common.hpp"

#pragma once

// ������ �ִ� ��츦 ó���ϴ� �Լ�
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, wchar_t* text, int maxWidth) {
    if (weight == 0) weight = 900;
    size = (int)(size * RESOLUTION_MULTIPLIER);
    const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
        0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("��"));

    SelectObject(hdc, font);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, textColor);
    SetTextAlign(hdc, align);

    x = (int)(x * RESOLUTION_MULTIPLIER);
    y = (int)(y * RESOLUTION_MULTIPLIER);

    int currentX = x;
    int currentY = y;

    int textLength = lstrlen(text);
    int i = 0;

    while (i < textLength) {
        int charLength = 1;
        SIZE charSize;

        // ���� ������ ũ�� ���
        GetTextExtentPoint32(hdc, &text[i], charLength, &charSize);

        // ���� ��ġ�� ���ڸ� �׷��� �� maxWidth�� �ʰ��ϸ� �� �ٲ�
        if (currentX + charSize.cx > x + maxWidth) {
            currentX = x;
            currentY += charSize.cy;
        }

        // ���� ���� ���
        TextOut(hdc, currentX, currentY, &text[i], charLength);

        // ���� ���ڷ� �̵�
        currentX += charSize.cx;
        i += charLength;
    }

    PAINTSTRUCT paint;
    EndPaint(GetConsoleWindow(), &paint);

    DeleteObject(font);
}

// ������ ���� ��츦 ó���ϴ� �Լ�
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, wchar_t* text, int maxWidth = 1000) {
    printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text, maxWidth);
}