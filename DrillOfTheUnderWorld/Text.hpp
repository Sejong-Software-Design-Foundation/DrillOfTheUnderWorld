#include "common.hpp"

#pragma once

// ê°ë„ê°€ ?ˆëŠ” ê²½ìš°ë¥?ì²˜ë¦¬?˜ëŠ” ?¨ìˆ˜
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, wchar_t* text, int maxWidth) {
    if (weight == 0) weight = 900;
    size = (int)(size * RESOLUTION_MULTIPLIER);
    const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
        0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ğ²Ã")); 

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

        // ?„ì¬ ê¸€?ì˜ ?¬ê¸° ê³„ì‚°
        GetTextExtentPoint32(hdc, &text[i], charLength, &charSize);

        // ?„ì¬ ?„ì¹˜??ê¸€?ë? ê·¸ë ¸????maxWidthë¥?ì´ˆê³¼?˜ë©´ ì¤?ë°”ê¿ˆ
        if (currentX + charSize.cx > x + maxWidth) {
            currentX = x;
            currentY += charSize.cy;
        }

        // ?„ì¬ ê¸€??ì¶œë ¥
        TextOut(hdc, currentX, currentY, &text[i], charLength);

        // ?¤ìŒ ê¸€?ë¡œ ?´ë™
        currentX += charSize.cx;
        i += charLength;
    }

    PAINTSTRUCT paint;
    EndPaint(GetConsoleWindow(), &paint);

    DeleteObject(font);
}

// ê°ë„ê°€ ?†ëŠ” ê²½ìš°ë¥?ì²˜ë¦¬?˜ëŠ” ?¨ìˆ˜
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, wchar_t* text, int maxWidth = 1000) {
    printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text, maxWidth);
}