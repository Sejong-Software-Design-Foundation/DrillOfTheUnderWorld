#include "common.hpp"

int main() {
	initialize();

	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageLayer.initialize(&imageLayer);

	char bmpNamePC[] = "PlayerCharacter.bmp";
	Image imagePC[1] = {{bmpNamePC, 240, 48, 1}};
	imageLayer.imageCount = 1;
	imageLayer.images = imagePC;
	imageLayer.renderAll(&imageLayer);

	while (1) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case S:
				break;
			case LEFT:
				break;
			case RIGHT:
				break;
			case UP:
				break;
			case DOWN:
				break;
			case ESC:
				return 0;
				break;
			}
		}
	}

	return 0;
}