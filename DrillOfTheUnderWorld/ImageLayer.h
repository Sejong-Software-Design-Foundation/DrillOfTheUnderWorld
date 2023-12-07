#ifdef __cplusplus
extern "C" {
#endif


#pragma once
#include "ImageLayerInterface.h"
#include "ImageLayerImpl.h"
#include "ImageFading.h"

#ifndef IMAGE_LAYER_H
#define IMAGE_LAYER_H

	static const ImageLayer DEFAULT_IMAGE_LAYER = { 400, 0, 960, 800, NULL, 0, RGB(0,0,0), NULL, NULL,_initialize, _renderAll, _renderCertain, _renderAndFadeIn, _renderAndFadeOut, NULL };
	static const ImageLayer UI_IMAGE_LAYER = { 0, 0, 400, 800, NULL, 0, RGB(255,0,0), NULL, NULL,_initialize, _renderAll, _renderCertain, _renderAndFadeIn, _renderAndFadeOut, NULL };

#endif

#ifdef __cplusplus
}
#endif