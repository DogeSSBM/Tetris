#pragma once
//typedef enum{P_U, P_D, P_R, M_L, M_R, M_D, M_U, NA}action;

void events()
{
	static SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			printf("Quitting now!\n");
			exit(0);
			break;
		case SDL_MOUSEMOTION:
			//printf("Mouse position (%d, %d)\n", event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			printf("Mouse click at (%d, %d)\n", event.button.x, event.button.y);
			break;
		case SDL_MOUSEBUTTONUP:
			printf("Mouse click at (%d, %d)\n", event.button.x, event.button.y);
			break;
		case SDL_KEYDOWN:
			//printf("Key pressed\n");
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				printf("Quitting now!\n");
				exit(0);
				break;
			default:
				break;
			}
			break;
		default:
			//printf("Unknown event!\n");
			break;
		}
	}
}
