#include "common.hpp"

#pragma once

// 각도가 ?�는 경우�?처리?�는 ?�수
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, wchar_t* text, int maxWidth) {
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

    int currentX = x;
    int currentY = y;

    int textLength = lstrlen(text);
    int i = 0;

    while (i < textLength) {
        int charLength = 1;
        SIZE charSize;

        // ?�재 글?�의 ?�기 계산
        GetTextExtentPoint32(hdc, &text[i], charLength, &charSize);

        // ?�재 ?�치??글?��? 그렸????maxWidth�?초과?�면 �?바꿈
        if (currentX + charSize.cx > x + maxWidth) {
            currentX = x;
            currentY += charSize.cy;
        }

        // ?�재 글??출력
        TextOut(hdc, currentX, currentY, &text[i], charLength);

        // ?�음 글?�로 ?�동
        currentX += charSize.cx;
        i += charLength;
    }

    PAINTSTRUCT paint;
    EndPaint(GetConsoleWindow(), &paint);

    DeleteObject(font);
}

// 각도가 ?�는 경우�?처리?�는 ?�수
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, wchar_t* text, int maxWidth = 1000) {
    printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text, maxWidth);
}