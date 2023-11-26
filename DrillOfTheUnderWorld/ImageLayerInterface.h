#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include <Windows.h>

#ifndef IMAGE_LAYER_INTERFACE_H
#define IMAGE_LAYER_INTERFACE_H

	typedef struct {
		char* fileName;
		int x, y;
		double scale;
		int isHide;
	}Image;

	typedef struct _ImageLayer {
		Image* images;
		int imageCount;
		int NUM;
		UINT transparentColor;

		HWND _windowHandle;
		HDC _consoleDC;

		void (*initialize)(struct _ImageLayer*);
		void (*renderAll)(struct _ImageLayer*);
		void (*renderCertain)(struct _ImageLayer*, int*, int);
		void (*fadeIn)(struct _ImageLayer*, void(*applyToBackDC)(HDC));
		void (*fadeOut)(struct _ImageLayer*, void(*applyToBackDC)(HDC));
		void (*applyToDC)(HDC);
	}ImageLayer;

#endif


#ifdef __cplusplus
}
#endif