// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.

#include "scene_settings.h"
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

#define MAX_VOLUME 5.0
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

static ALLEGRO_BITMAP* volumeup1 = NULL;
static ALLEGRO_BITMAP* volumeup2 = NULL;
static ALLEGRO_BITMAP* volumedown1 = NULL;
static ALLEGRO_BITMAP* volumedown2 = NULL;
static ALLEGRO_BITMAP* volumeTitle = NULL;

static ALLEGRO_BITMAP* seffectup1 = NULL;
static ALLEGRO_BITMAP* seffectup2 = NULL;
static ALLEGRO_BITMAP* seffectdown1 = NULL;
static ALLEGRO_BITMAP* seffectdown2 = NULL;
static ALLEGRO_BITMAP* seffectTitle = NULL;

static ALLEGRO_BITMAP* return1 = NULL;
static ALLEGRO_BITMAP* return2 = NULL;

static ALLEGRO_SAMPLE* settinmusic;
static ALLEGRO_SAMPLE_ID settingBGM;

static ALLEGRO_FONT* controltext = NULL;
static int btnvolumeW;
static int btnvolumeH;
static Button btnvolumeup;
static Button btnvolumedown;
static Button btnseffectup;
static Button btnseffectdown;
static Button btnreturn;
static void init() {

	// [HACKATHON 3-2]
	// TODO: Create button to settings
	//	Uncomment and fill the code below
	btnvolumeup = button_create(100, 150, 100, 100, "Assets/volumeup1.png", "Assets/volumeup2.png");
	btnvolumedown = button_create(600, 150, 100, 100, "Assets/volumedown1.png", "Assets/volumedown2.png");
	btnseffectup = button_create(100, 400, 100, 100, "Assets/volumeup1.png", "Assets/volumeup2.png");
	btnseffectdown = button_create(600, 400, 100, 100, "Assets/volumedown1.png", "Assets/volumedown2.png");
	btnreturn = button_create(20, 20, 50, 50, "Assets/return1.png", "Assets/return2.png");
	controltext = load_font("Assets/Minecraft.ttf", 40);
	stop_bgm(settingBGM);
	settingBGM = play_bgm(settingMusic, music_volume);
}

static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(btnvolumeup);
	drawButton(btnvolumedown);
	drawButton(btnseffectup);
	drawButton(btnseffectdown);
	drawButton(btnreturn);

	al_draw_textf(
		controltext,
		al_map_rgb(112, 204, 225),
		400,
		180,
		ALLEGRO_ALIGN_CENTER,
		"Volume : %.2f%%", music_volume / MAX_VOLUME * 100
	);

	al_draw_textf(
		controltext,
		al_map_rgb(112, 204, 225),
		400,
		430,
		ALLEGRO_ALIGN_CENTER,
		"Effect : %.2f%%", effect_volume / MAX_VOLUME * 100
	);
}
// The only function that is shared across files.

static void on_key_down(int keycode) {

	switch (keycode) {
	case ALLEGRO_KEY_ENTER:
		game_change_scene(scene_main_create());
		break;
	default:
		break;
	}
}

static void on_mouse_down() {
	if (btnreturn.hovered) {
		stop_bgm(settingBGM);
		game_change_scene(scene_menu_create());
	}
	if (btnvolumeup.hovered) {
		stop_bgm(settingBGM);
		if (music_volume + 0.5 <= MAX_VOLUME) {
			music_volume += 0.5;
		}
		settingBGM = play_bgm(themeMusic, music_volume);
	}
	if (btnvolumedown.hovered) {
		stop_bgm(settingBGM);
		if (music_volume - 0.5 >= 0) {
			music_volume -= 0.5;
		}
		settingBGM = play_bgm(themeMusic, music_volume);
	}
	if (btnseffectup.hovered) {
		stop_bgm(settingBGM);
		if (effect_volume + 0.5 <= MAX_VOLUME) {
			effect_volume += 0.5;
		}
		settingBGM = play_bgm(themeMusic, music_volume);
	}
	if (btnseffectdown.hovered) {
		stop_bgm(settingBGM);
		if (effect_volume - 0.5 >= 0) {
			effect_volume -= 0.5;
		}
		settingBGM = play_bgm(themeMusic, music_volume);
	}
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btnvolumeup.hovered = buttonHover(btnvolumeup, mouse_x, mouse_y);
	btnvolumedown.hovered = buttonHover(btnvolumedown, mouse_x, mouse_y);
	btnseffectup.hovered = buttonHover(btnseffectup, mouse_x, mouse_y);
	btnseffectdown.hovered = buttonHover(btnseffectdown, mouse_x, mouse_y);	
	btnreturn.hovered = buttonHover(btnreturn, mouse_x, mouse_y);
}

Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

static void destroy() {
	//	[HACKATHON 3-10]
	//	TODO: Destroy button images
	//	Uncomment and fill the code below
	stop_bgm(settingBGM);
	al_destroy_bitmap(btnvolumeup.default_img);
	al_destroy_bitmap(btnvolumeup.hovered_img);
	al_destroy_bitmap(btnvolumedown.default_img);
	al_destroy_bitmap(btnvolumedown.hovered_img);
	al_destroy_bitmap(btnseffectup.default_img);
	al_destroy_bitmap(btnseffectup.hovered_img);
	al_destroy_bitmap(btnseffectdown.default_img);
	al_destroy_bitmap(btnseffectdown.hovered_img);
	al_destroy_bitmap(btnreturn.default_img);
	al_destroy_bitmap(btnreturn.hovered_img);

}


/*
Scene scene_win_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Win";
	scene.draw = &draw;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Win scene created");
	return scene;
}
*/

