
#include "scene_win.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"


/* Internal Variables*/

static ALLEGRO_BITMAP* gameWin = NULL;
static ALLEGRO_SAMPLE_ID winBGM;
static int gameWinW;
static int gameWinH;


// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first. 

//	[HACKATHON 3-1]
//	TODO: Declare variable for button
//	Uncomment and fill the code below
// static ... btnSettings;

static void init() {

	// [HACKATHON 3-2]
	// TODO: Create button to settings
	//	Uncomment and fill the code below
	//btnSettings = button_create(730, 20, 50, 50, "...", "...");

	gameWin = load_bitmap("Assets/winning_picture.png");
	gameWinW = al_get_bitmap_width(gameWin);
	gameWinH = al_get_bitmap_height(gameWin);
	stop_bgm(winBGM);
	winBGM = play_bgm(winMusic, music_volume);

}


static void draw() {

	al_clear_to_color(al_map_rgb(0, 0, 0));

	const float scale = 0.7;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameWinW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameWinH;

	//draw title image
	/*
	*/
	al_draw_scaled_bitmap(
		gameWin,
		0, 0,
		gameWinW, gameWinH,
		offset_w, offset_h,
		gameWinW * scale, gameWinH * scale,
		0
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		300,
		ALLEGRO_ALIGN_CENTER,
		"PRESS \"ENTER\""
	);


	// [HACKATHON 3-3]
	// TODO: Draw button
	// Uncomment and fill the code below
	// drawButton(...);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	//	 btnSettings.hovered = ???(btnSettings, mouse_x, mouse_y);
}



//	[HACKATHON 3-8]
//	TODO: When btnSettings clicked, switch to settings scene
//  `game_change_scene` is defined in `game.h`.
//  You can check line 121 `scene_menu.c` to see how to use this function.
//  And find the corresponding function for `scene_setting`
// 	Utilize the member defined in struct `Button`.
//  The logic here is 
//  `if clicked the mouse` && `mouse position is in the area of button`
// 	      `Enter the setting scene`
//	Uncomment and fill the code below
/*
static void on_mouse_down() {
	if (btnSettings.???)
		game_change_scene(...);
}
*/


static void destroy() {
	stop_bgm(winBGM);
	al_destroy_bitmap(gameWin);
	//	[HACKATHON 3-10]
	//	TODO: Destroy button images
	//	Uncomment and fill the code below
	
}

static void on_key_down(int keycode) {

	switch (keycode) {
	case ALLEGRO_KEY_ENTER:
		game_change_scene(scene_menu_create());
		break;
	default:
		break;
	}
}


// TODO: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.

Scene scene_win_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Win";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	// [HACKATHON 3-9]

	// TODO: Register on_mouse_down.
	// Uncomment the code below
	//scene.on_mouse_down = &on_mouse_down;
	// -------------------------------------



	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Win scene created");
	return scene;
}
