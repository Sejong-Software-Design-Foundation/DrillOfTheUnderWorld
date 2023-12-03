#include "common.hpp"

#pragma once

// 각도가 있는 경우를 처리하는 함수
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, wchar_t* text, int maxWidth) {
    if (weight == 0) weight = 900;
    size = (int)(size * RESOLUTION_MULTIPLIER);
    const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
        0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("꼴"));

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

        // 현재 글자의 크기 계산
        GetTextExtentPoint32(hdc, &text[i], charLength, &charSize);

        // 현재 위치에 글자를 그렸을 때 maxWidth를 초과하면 줄 바꿈
        if (currentX + charSize.cx > x + maxWidth) {
            currentX = x;
            currentY += charSize.cy;
        }

        // 현재 글자 출력
        TextOut(hdc, currentX, currentY, &text[i], charLength);

        // 다음 글자로 이동
        currentX += charSize.cx;
        i += charLength;
    }

    PAINTSTRUCT paint;
    EndPaint(GetConsoleWindow(), &paint);

    DeleteObject(font);
}

// 각도가 없는 경우를 처리하는 함수
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, wchar_t* text, int maxWidth = 1000) {
    printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text, maxWidth);
}