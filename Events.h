#pragma once
typedef enum{MOVE_U, MOVE_D, MOVE_L, MOVE_R, ROTATE_L, ROTATE_R, PLACE, NOTHING}event;

event events()
{
	static SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
		case SDL_QUIT:
			printf("Quitting now!\n");
			exit(0);
			return NOTHING;
			break;
		case SDL_MOUSEMOTION:
			//printf("Mouse position (%d, %d)\n", event.motion.x, event.motion.y);
			return NOTHING;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//printf("Mouse click at (%d, %d)\n", event.button.x, event.button.y);
			return NOTHING;
			break;
		case SDL_KEYDOWN:
			//printf("Key pressed\n");
			switch(e.key.keysym.sym){
			case SDLK_ESCAPE:
				printf("Quitting now!\n");
				exit(0);
				break;
			case SDLK_s:
				return MOVE_D;
				break;
			case SDLK_w:
				return MOVE_U;
				break;
			case SDLK_a:
				return MOVE_L;
				break;
			case SDLK_d:
				return MOVE_R;
				break;
			case SDLK_q:
				return ROTATE_L;
				break;
			case SDLK_e:
				return ROTATE_R;
				break;
			case SDLK_SPACE:
				return PLACE;
				break;
			default:
				return NOTHING;
				break;
			}
			break;
		default:
			return NOTHING;
			//printf("Unknown event!\n");
			break;
		}
	}
	return NOTHING;
}
