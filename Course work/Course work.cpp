#include <iostream>
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <SDL_mixer.h>
#include <string.h>
#include <fstream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define S_WIDTH 1024
#define S_HIGHT 768
#define SIZE_OF_BUTTON_Y 100
#define SIZE_OF_BUTTON_X 250
#define SIZE_DECREASE 10
#define POINT_OF_XY 96
#define LENGTH_OF_POINT 934
#define HIGHT_OF_POINT 668
#define SIZE_OF_MEDALS 100
int convert(string s)
{
	int num = 0;
	int n = s.length();

	for (int i = 0; i < n; i++)
	{
		num = num * 10 + (int(s[i]) - 48);
	}
	return num;
}
void Recording_in_temp(string stroka, int count_lines, int Counter_of_generations, bool one_time)
{
	fstream file_records;
	ofstream temp;
	file_records.open("records.txt");
	temp.open("temp.txt", ofstream::out | ofstream::trunc);
	while (!file_records.eof())
	{
		file_records >> stroka;
		count_lines++;
		if (Counter_of_generations > convert(stroka) && one_time)
		{
			temp << Counter_of_generations << endl;
			one_time = false;
		}
		if (count_lines < 10)
			temp << stroka << endl;
	}
	file_records.close();
	temp.close();
}
void Recording_in_records(string stroka, int count_lines)
{
	fstream temp_2;
	ofstream file_records_2;
	file_records_2.open("records.txt", ofstream::out | ofstream::trunc);
	temp_2.open("temp.txt");
	while (!temp_2.eof())
	{
		count_lines++;
		temp_2 >> stroka;
		if (stroka == "")
			continue;
		file_records_2 << stroka << endl;
	}
	file_records_2.close();
	temp_2.close();
}
SDL_Texture* get_text(SDL_Renderer*& renderer, char* points, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 160,160,160 };
	textSurface = TTF_RenderText_Blended(font, points, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

bool Verification(int horizontal, int vertical, int Array[], int Copy[])
{
	int count = 0;
	for (int i = 0; i < horizontal; i++)
		for (int j = 0; j < vertical; j++)
		{
			if (Array[i * vertical + j] == Copy[i * vertical + j])
				count++;
		}
	if (count == horizontal * vertical)
		return true;
	else
		return false;
}
void Rewrite(int horizontal, int vertical, int Array[], int Copy[])
{
	for (int i = 0; i < horizontal; i++)
		for (int j = 0; j < vertical; j++)
		{
			Copy[i * vertical + j] = Array[i * vertical + j];
		}
}
int Central_values(int i, int j, int vertical, int horizontal, int Array[], int Great_counter)
{
	// Проверка верхней части
		if (Array[(i - 1) * vertical + j - 1])
			Great_counter++;

		if (Array[(i - 1) * vertical + j])
			Great_counter++;

		if (Array[(i - 1) * vertical + j + 1])
			Great_counter++;
	// Проверка боковых частей
		if (Array[i * vertical + j - 1])
			Great_counter++;

		if (Array[i * vertical + j + 1])
			Great_counter++;
	// Проверка нижних частей
		if (Array[(i + 1) * vertical + j - 1])
			Great_counter++;

		if (Array[(i + 1) * vertical + j])
			Great_counter++;

		if (Array[(i + 1) * vertical + j + 1])
			Great_counter++;
	return Great_counter;
}
int Upper_values(int i, int j, int vertical, int horizontal, int Array[], int Great_counter)
{
	if (i == 0)
	{
		if (Array[(i + 1) * vertical + j])
			Great_counter++;
		if (Array[i * vertical + j + 1])
			Great_counter++;
		if (Array[(i + 1) * vertical + j + 1])
			Great_counter++;
		return Great_counter;
	}
	if (i == horizontal - 1)
	{
		if (Array[(i - 1) * vertical + j])
			Great_counter++;
		if (Array[i * vertical + j + 1])
			Great_counter++;
		if (Array[(i - 1) * vertical + j + 1])
			Great_counter++;
		return Great_counter;
	}
	if (Array[(i - 1) * vertical + j])
		Great_counter++;
	if (Array[(i + 1) * vertical + j])
		Great_counter++;
	if (Array[(i - 1) * vertical + j + 1])
		Great_counter++;
	if (Array[i * vertical + j + 1])
		Great_counter++;
	if (Array[(i + 1) * vertical + j + 1])
		Great_counter++;
	return Great_counter;
}
int Left_values(int i, int j, int vertical, int horizontal, int Array[], int Great_counter)
{
	if (j == vertical - 1)
	{
		if (Array[i * vertical + j - 1])
			Great_counter++;
		if (Array[(i + 1) * vertical + j - 1])
			Great_counter++;
		if (Array[(i + 1) * vertical + j])
			Great_counter++;
		return Great_counter;
	}
	if (Array[i * vertical + j - 1])
		Great_counter++;
	if (Array[(i + 1) * vertical + j - 1])
		Great_counter++;
	if (Array[(i + 1) * vertical + j])
		Great_counter++;
	if (Array[(i + 1) * vertical + j + 1])
		Great_counter++;
	if (Array[i * vertical + j + 1])
		Great_counter++;
	return Great_counter;
}
int Right_values(int i, int j, int vertical, int horizontal, int Array[], int Great_counter)
{
	if (j == vertical - 1)
	{
		if (Array[(i - 1) * vertical + j])
			Great_counter++;
		if (Array[(i - 1) * vertical + j - 1])
			Great_counter++;
		if (Array[i * vertical + j - 1])
			Great_counter++;
		return Great_counter;
	}
	if (Array[i * vertical + j - 1])
		Great_counter++;
	if (Array[(i - 1) * vertical + j - 1])
		Great_counter++;
	if (Array[(i - 1) * vertical + j])
		Great_counter++;
	if (Array[(i - 1) * vertical + j + 1])
		Great_counter++;
	if (Array[i * vertical + j + 1])
		Great_counter++;
	return Great_counter;
}
int Lower_values(int i, int j, int vertical, int horizontal, int Array[], int Great_counter)
{
	if (Array[(i - 1) * vertical + j])
		Great_counter++;
	if (Array[(i - 1) * vertical + j - 1])
		Great_counter++;
	if (Array[i * vertical + j - 1])
		Great_counter++;
	if (Array[(i + 1) * vertical + j - 1])
		Great_counter++;
	if (Array[(i + 1) * vertical + j])
		Great_counter++;
	return Great_counter;
}
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	bool quit = false, play = false, settings = false, info = false, p_1 = false, s_1 = false, i_1 = false, b_1 = false,
		sc_1 = false, sc_2 = false, selected_first = false, selected_second = true, selected_third = false, inter_ffcm_1 = false,
		inter_ffcm_2 = false, inter_ffcm_3 = false, bs_1 = false, start = false, meaning = false, br_1 = false;
	int Coord_X, Coord_Y, Speed_scrole = 2; double changing_of_volume = 128;
	SDL_Event event;
	SDL_Window* window = SDL_CreateWindow("The life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WIDTH, S_HIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* music = Mix_LoadMUS("background music.wav");
	Mix_Chunk* tap = Mix_LoadWAV("click_on_button.wav");
	SDL_Texture* background = IMG_LoadTexture(renderer, "resources/background.png");
	SDL_Texture* button_play = IMG_LoadTexture(renderer, "resources/button_play.png");
	SDL_Texture* button_settings = IMG_LoadTexture(renderer, "resources/button_settings.png");
	SDL_Texture* button_info = IMG_LoadTexture(renderer, "resources/button_info.png");
	SDL_Texture* button_back = IMG_LoadTexture(renderer, "resources/button_back.png");
	SDL_Texture* settings_background = IMG_LoadTexture(renderer, "resources/settings_background.png");
	SDL_Texture* background_play_menu = IMG_LoadTexture(renderer, "resources/background_play_menu.png");
	SDL_Texture* scrole = IMG_LoadTexture(renderer, "resources/circle.png");
	SDL_Texture* field_for_check_mark = IMG_LoadTexture(renderer, "resources/field_for_check_mark.png");
	SDL_Texture* check_mark = IMG_LoadTexture(renderer, "resources/check_mark.png");
	SDL_Texture* button_start = IMG_LoadTexture(renderer, "resources/button_start.png");
	SDL_Texture* background_records = IMG_LoadTexture(renderer, "resources/background_records.png");
	SDL_Texture* button_restart = IMG_LoadTexture(renderer, "resources/button_restart.png");

	SDL_Texture* medal_gold = IMG_LoadTexture(renderer, "resources/gold_medal.png");
	SDL_Texture* medal_silver = IMG_LoadTexture(renderer, "resources/silver_medal.png");
	SDL_Texture* medal_bronze = IMG_LoadTexture(renderer, "resources/bronze_medal.png");
	SDL_Texture* medal_wood = IMG_LoadTexture(renderer, "resources/wood_medal.png");
	SDL_Rect pos_gold = { S_WIDTH / 4, S_HIGHT / 18 + SIZE_OF_MEDALS + 1 * SIZE_DECREASE, SIZE_OF_MEDALS, SIZE_OF_MEDALS };
	SDL_Rect pos_silver = { S_WIDTH / 4, S_HIGHT / 18 + 2 * SIZE_OF_MEDALS + 2 * SIZE_DECREASE, SIZE_OF_MEDALS, SIZE_OF_MEDALS };
	SDL_Rect pos_bronze = { S_WIDTH / 4, S_HIGHT / 18 + 3 * SIZE_OF_MEDALS + 3 * SIZE_DECREASE, SIZE_OF_MEDALS, SIZE_OF_MEDALS };
	SDL_Rect pos_wood = { S_WIDTH / 4, S_HIGHT / 18 + 4 * SIZE_OF_MEDALS + 4 * SIZE_DECREASE, SIZE_OF_MEDALS, SIZE_OF_MEDALS };

	SDL_Rect pos_gold_changed = { S_WIDTH / 4 +  2 * SIZE_OF_MEDALS, S_HIGHT / 18 + SIZE_OF_MEDALS + 1 * SIZE_DECREASE, 300, 100 };
	SDL_Rect pos_silver_changed = { S_WIDTH / 4 + 2 * SIZE_OF_MEDALS, S_HIGHT / 18 + 2 * SIZE_OF_MEDALS + 2 * SIZE_DECREASE, 300, 100 };
	SDL_Rect pos_bronze_changed = { S_WIDTH / 4 + 2 * SIZE_OF_MEDALS, S_HIGHT / 18 + 3 * SIZE_OF_MEDALS + 3 * SIZE_DECREASE, 300, 100 };
	SDL_Rect pos_wood_changed = { S_WIDTH / 4 + 2 * SIZE_OF_MEDALS, S_HIGHT / 18 + 4 * SIZE_OF_MEDALS + 4 * SIZE_DECREASE, 300, 100 };

	SDL_Rect Fill = { 0, 0, S_WIDTH, S_HIGHT };
	SDL_Rect Fill_changed = { 0, 0, S_WIDTH, S_HIGHT };
	SDL_Rect BPlay = { S_WIDTH / 2 - SIZE_OF_BUTTON_X/2 - 50, S_HIGHT / 2 + SIZE_OF_BUTTON_Y, SIZE_OF_BUTTON_X, SIZE_OF_BUTTON_Y };
	SDL_Rect BSettings = { S_WIDTH / 2 + SIZE_OF_BUTTON_X/2, S_HIGHT / 2 + SIZE_OF_BUTTON_Y, SIZE_OF_BUTTON_X, SIZE_OF_BUTTON_Y };
	SDL_Rect BInfo = { S_WIDTH / 2 - SIZE_OF_BUTTON_X/2 - 100 - 4 * SIZE_OF_BUTTON_X / 10, S_HIGHT / 2 + SIZE_OF_BUTTON_Y, 4*SIZE_OF_BUTTON_X/10, SIZE_OF_BUTTON_Y };
	SDL_Rect BBack = { S_WIDTH / 40, S_HIGHT - S_HIGHT / 8, 2 * SIZE_OF_BUTTON_X / 3, 2 * SIZE_OF_BUTTON_Y / 3 };
	SDL_Rect BBack_changed = { S_WIDTH / 80, S_HIGHT / 60, SIZE_OF_BUTTON_X / 2, SIZE_OF_BUTTON_Y / 2 };
	SDL_Rect ffcm_1 = { S_WIDTH / 2 + 230, S_HIGHT / 3, 50, 50 };
	SDL_Rect ffcm_2 = { S_WIDTH / 2 + 230, S_HIGHT / 2, 50, 50 };
	SDL_Rect ffcm_3 = { S_WIDTH / 2 + 230, 2 * S_HIGHT / 3, 50, 50 };
	SDL_Rect BStart = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2, S_HIGHT - SIZE_OF_BUTTON_Y, SIZE_OF_BUTTON_X, SIZE_OF_BUTTON_Y };
	SDL_Rect BRestart = { S_WIDTH - 50 - SIZE_OF_BUTTON_X / 5, S_HIGHT / 60, SIZE_OF_BUTTON_X / 5, SIZE_OF_BUTTON_Y / 2 };


	TTF_Init();
	TTF_Font* font = TTF_OpenFont("couriernew.ttf", 300);	
	char text_title[] = "The game of life", text_volume[] = "Volume:", text_settings[] = "Settings:", text_area[] = "Field size:", 
		text_40x40[] = "40 x 40", text_20x30[] = "20 x 30", text_10x10[] = "10 x 10", text_generations[] = "Number of generations:",
		text_records[] = "Records for the number of generations:", text_max_generations[] = "Maximum number of generations:";
	SDL_Texture* title = get_text(renderer, text_title, font);
	SDL_Texture* volume = get_text(renderer, text_volume, font);
	SDL_Texture* T_settings = get_text(renderer, text_settings, font);
	SDL_Texture* field = get_text(renderer, text_area, font);
	SDL_Texture* generations = get_text(renderer, text_generations, font);
	SDL_Texture* records = get_text(renderer, text_records, font);
	SDL_Texture* max_generations = get_text(renderer, text_max_generations, font);

	SDL_Texture* size_40x40 = get_text(renderer, text_40x40, font);
	SDL_Texture* size_20x30 = get_text(renderer, text_20x30, font);
	SDL_Texture* size_10x10 = get_text(renderer, text_10x10, font);
	SDL_Rect pos_40x40 = { S_WIDTH / 2, S_HIGHT / 3, 200, 50 };
	SDL_Rect pos_20x30 = { S_WIDTH / 2, S_HIGHT / 2, 200, 50 };
	SDL_Rect pos_10x10 = { S_WIDTH / 2, 2 * S_HIGHT / 3, 200, 50 };

	SDL_Rect pos_title = { S_WIDTH / 2 - 400, S_HIGHT / 8, 800, 200 };
	SDL_Rect pos_settings = { S_WIDTH / 2 - 150, S_HIGHT / 12, 300, 50 };
	SDL_Rect pos_volume = { S_WIDTH / 2 - 300, S_HIGHT / 6 + 50, 200, 50 };
	SDL_Rect pos_scrole = { S_WIDTH / 2 + 152, S_HIGHT / 6 + 58, 30, 30 };
	SDL_Rect pos_field = { S_WIDTH / 2 - 300, S_HIGHT / 3, 300, 50 };
	SDL_Rect pos_generations = { 50, S_HIGHT - S_HIGHT / 12, 200, 30 };
	SDL_Rect for_number_of_generations = { 255, S_HIGHT - S_HIGHT / 12 + 5, 30, 25 };
	SDL_Rect pos_maximum_generations = {  6 * S_WIDTH / 10 + 30, S_HIGHT - S_HIGHT / 12, 300, 30 };
	SDL_Rect pos_max_gen = { 6 * S_WIDTH / 10 + 335, S_HIGHT - S_HIGHT / 12 + 3, 30, 25 };
	SDL_Rect pos_records = { S_WIDTH / 4 - 2 * SIZE_DECREASE, S_HIGHT / 18 + 3 * SIZE_DECREASE, 700, 60 };

	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(128);
	Mix_VolumeChunk(tap, 128);
	int horizontal = 20, vertical = 30, max_number = 0;
	bool click_pressed_left = false, click_pressed_right = false; int Great_counter = 0, Recording_Record = 0, Counter_of_generations = 0;
	fstream max_file;
	string yota;
	while (!quit)
	{
		SDL_RenderCopy(renderer, background, NULL, &Fill);
		SDL_RenderCopy(renderer, button_play, NULL, &BPlay);
		SDL_RenderCopy(renderer, button_settings, NULL, &BSettings);
		SDL_RenderCopy(renderer, button_info, NULL, &BInfo);
		SDL_RenderCopy(renderer, title, NULL, &pos_title);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&Coord_X, &Coord_Y);
				if ((Coord_X <= (BPlay.x + BPlay.w)) && (Coord_X >= (BPlay.x)) && (Coord_Y <= (BPlay.y + BPlay.h)) && (Coord_Y >= (BPlay.y)))
				{
					p_1 = true;
					Mix_PlayChannel(-1, tap, 0);
					BPlay = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2 - 50 + SIZE_DECREASE, S_HIGHT / 2 + SIZE_OF_BUTTON_Y + SIZE_DECREASE / 2, SIZE_OF_BUTTON_X - 2 * SIZE_DECREASE, SIZE_OF_BUTTON_Y - SIZE_DECREASE };
				}
				else
					p_1 = false;
				if ((Coord_X <= (BSettings.x + BSettings.w)) && (Coord_X >= (BSettings.x)) && (Coord_Y <= (BSettings.y + BSettings.h)) && (Coord_Y >= (BSettings.y)))
				{
					s_1 = true;
					Mix_PlayChannel(-1, tap, 0);
					BSettings = { S_WIDTH / 2 + SIZE_OF_BUTTON_X / 2 + SIZE_DECREASE, S_HIGHT / 2 + SIZE_OF_BUTTON_Y + SIZE_DECREASE / 2, SIZE_OF_BUTTON_X - 2 * SIZE_DECREASE, SIZE_OF_BUTTON_Y - SIZE_DECREASE };
				}
				else
					s_1 = false;
				if ((Coord_X <= (BInfo.x + BInfo.w)) && (Coord_X >= (BInfo.x)) && (Coord_Y <= (BInfo.y + BInfo.h)) && (Coord_Y >= (BInfo.y)))
				{
					i_1 = true;
					Mix_PlayChannel(-1, tap, 0);
					BInfo = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2 - 100 - 4 * SIZE_OF_BUTTON_X / 10 + SIZE_DECREASE / 2, S_HIGHT / 2 + SIZE_OF_BUTTON_Y + SIZE_DECREASE / 2, 4 * SIZE_OF_BUTTON_X / 10 - SIZE_DECREASE, SIZE_OF_BUTTON_Y - SIZE_DECREASE };
				}
				else
					i_1 = false;
			}
			if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
			{
				BPlay = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2 - 50, S_HIGHT / 2 + SIZE_OF_BUTTON_Y, SIZE_OF_BUTTON_X, SIZE_OF_BUTTON_Y };
				BSettings = { S_WIDTH / 2 + SIZE_OF_BUTTON_X / 2, S_HIGHT / 2 + SIZE_OF_BUTTON_Y, SIZE_OF_BUTTON_X, SIZE_OF_BUTTON_Y };
				BInfo = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2 - 100 - 4 * SIZE_OF_BUTTON_X / 10, S_HIGHT / 2 + SIZE_OF_BUTTON_Y, 4 * SIZE_OF_BUTTON_X / 10, SIZE_OF_BUTTON_Y };
				SDL_GetMouseState(&Coord_X, &Coord_Y);
				
				if ((Coord_X <= (BPlay.x + BPlay.w)) && (Coord_X >= (BPlay.x)) && (Coord_Y <= (BPlay.y + BPlay.h)) && (Coord_Y >= (BPlay.y)) && p_1)
				{
					play = true;
				}
				if ((Coord_X <= (BSettings.x + BSettings.w)) && (Coord_X >= (BSettings.x)) && (Coord_Y <= (BSettings.y + BSettings.h)) && (Coord_Y >= (BSettings.y)) && s_1)
				{
					settings = true;
				}
				if ((Coord_X <= (BInfo.x + BInfo.w)) && (Coord_X >= (BInfo.x)) && (Coord_Y <= (BInfo.y + BInfo.h)) && (Coord_Y >= (BInfo.y)) && i_1)
				{
					info = true;
				}
			}
		}
		if (settings)
		{
			BBack = { S_WIDTH / 40, S_HIGHT - S_HIGHT / 8, 2 * SIZE_OF_BUTTON_X / 3, 2 * SIZE_OF_BUTTON_Y / 3 };
			bool key_pressed = false;
			int memory_x = 0, memory_y = 0;
			while (settings && !quit)
			{
				SDL_RenderCopy(renderer, settings_background, NULL, &Fill);
				SDL_RenderCopy(renderer, button_back, NULL, &BBack);
				SDL_RenderCopy(renderer, T_settings, NULL, &pos_settings);
				SDL_RenderCopy(renderer, volume, NULL, &pos_volume);
				SDL_RenderCopy(renderer, field, NULL, &pos_field);

				SDL_RenderCopy(renderer, size_40x40, NULL, &pos_40x40);
				SDL_RenderCopy(renderer, size_20x30, NULL, &pos_20x30);
				SDL_RenderCopy(renderer, size_10x10, NULL, &pos_10x10);

				SDL_RenderCopy(renderer, field_for_check_mark, NULL, &ffcm_1);
				SDL_RenderCopy(renderer, field_for_check_mark, NULL, &ffcm_2);
				SDL_RenderCopy(renderer, field_for_check_mark, NULL, &ffcm_3);

				if (selected_first)
					SDL_RenderCopy(renderer, check_mark, NULL, &ffcm_1);
				if (selected_second)
					SDL_RenderCopy(renderer, check_mark, NULL, &ffcm_2);
				if (selected_third)
					SDL_RenderCopy(renderer, check_mark, NULL, &ffcm_3);
				SDL_SetRenderDrawColor(renderer, 160, 160, 160, 0);
				for (int i = 70; i < 75; i++)
					SDL_RenderDrawLine(renderer, S_WIDTH / 2 - 95, S_HIGHT / 6 + i, S_WIDTH / 2 + 166, S_HIGHT / 6 + i);
				SDL_RenderCopy(renderer, scrole, NULL, &pos_scrole);
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						quit = true;
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						settings = false;

					if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&Coord_X, &Coord_Y);
						if ((Coord_X <= (pos_scrole.x + pos_scrole.w)) && (Coord_X >= (pos_scrole.x)) && (Coord_Y <= (pos_scrole.y + pos_scrole.h)) && (Coord_Y >= (pos_scrole.y)))
						{
							memory_x = Coord_X;
							Mix_PlayChannel(-1, tap, 0);
							pos_scrole.x += SIZE_DECREASE / 4;
							pos_scrole.y += SIZE_DECREASE / 4;
							pos_scrole.w -= SIZE_DECREASE / 2;
							pos_scrole.h -= SIZE_DECREASE / 2;
							sc_1 = true;
						}
						else
						{
							sc_1 = false;
						}
						if ((Coord_X <= (BBack.x + BBack.w)) && (Coord_X >= (BBack.x)) && (Coord_Y <= (BBack.y + BBack.h)) && (Coord_Y >= (BBack.y)))
						{
							b_1 = true;
							Mix_PlayChannel(-1, tap, 0);
							BBack = { S_WIDTH / 40 + SIZE_DECREASE / 2, S_HIGHT - S_HIGHT / 8 + SIZE_DECREASE / 2, 2 * SIZE_OF_BUTTON_X / 3 - 2 * SIZE_DECREASE, 2 * SIZE_OF_BUTTON_Y / 3 - SIZE_DECREASE };
						}
						else
							b_1 = false;
						if ((Coord_X <= (ffcm_1.x + ffcm_1.w)) && (Coord_X >= (ffcm_1.x)) && (Coord_Y <= (ffcm_1.y + ffcm_1.h)) && (Coord_Y >= (ffcm_1.y)))
						{
							inter_ffcm_1 = true;
							Mix_PlayChannel(-1, tap, 0);
							ffcm_1 = { S_WIDTH / 2 + 230 + SIZE_DECREASE / 2, S_HIGHT / 3 + SIZE_DECREASE / 2, 50 - SIZE_DECREASE, 50 - SIZE_DECREASE };
						}
						else
							inter_ffcm_1 = false;
						if ((Coord_X <= (ffcm_2.x + ffcm_2.w)) && (Coord_X >= (ffcm_2.x)) && (Coord_Y <= (ffcm_2.y + ffcm_2.h)) && (Coord_Y >= (ffcm_2.y)))
						{
							inter_ffcm_2 = true;
							Mix_PlayChannel(-1, tap, 0);
							ffcm_2 = { S_WIDTH / 2 + 230 + SIZE_DECREASE / 2, S_HIGHT / 2 + SIZE_DECREASE / 2, 50 - SIZE_DECREASE, 50 - SIZE_DECREASE };
						}
						else
							inter_ffcm_2 = false;
						if ((Coord_X <= (ffcm_3.x + ffcm_3.w)) && (Coord_X >= (ffcm_3.x)) && (Coord_Y <= (ffcm_3.y + ffcm_3.h)) && (Coord_Y >= (ffcm_3.y)))
						{
							inter_ffcm_3 = true;
							Mix_PlayChannel(-1, tap, 0);
							ffcm_3 = { S_WIDTH / 2 + 230 + SIZE_DECREASE / 2, 2 * S_HIGHT / 3 + SIZE_DECREASE / 2, 50 - SIZE_DECREASE, 50 - SIZE_DECREASE };
						}
						else
							inter_ffcm_3 = false;
						key_pressed = true;
					}
					if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
					{
						key_pressed = false;
						BBack = { S_WIDTH / 40, S_HIGHT - S_HIGHT / 8, 2 * SIZE_OF_BUTTON_X / 3, 2 * SIZE_OF_BUTTON_Y / 3 };
						if (sc_1)
						{
							pos_scrole.x -= SIZE_DECREASE / 4;
							pos_scrole.y -= SIZE_DECREASE / 4;
							pos_scrole.w += SIZE_DECREASE / 2;
							pos_scrole.h += SIZE_DECREASE / 2;
						}
						ffcm_1 = { S_WIDTH / 2 + 230, S_HIGHT / 3, 50, 50 };
						ffcm_2 = { S_WIDTH / 2 + 230, S_HIGHT / 2, 50, 50 };
						ffcm_3 = { S_WIDTH / 2 + 230, 2 * S_HIGHT / 3, 50, 50 };
						SDL_GetMouseState(&Coord_X, &Coord_Y);
						if ((Coord_X <= (BBack.x + BBack.w)) && (Coord_X >= (BBack.x)) && (Coord_Y <= (BBack.y + BBack.h)) && (Coord_Y >= (BBack.y)) && b_1)
						{
							settings = false;
							break;
						}
						if ((Coord_X <= (ffcm_1.x + ffcm_1.w)) && (Coord_X >= (ffcm_1.x)) && (Coord_Y <= (ffcm_1.y + ffcm_1.h)) && (Coord_Y >= (ffcm_1.y)) && inter_ffcm_1)
						{
							selected_first = true;
							selected_second = false;
							selected_third = false;
							horizontal = vertical = 40;
						}
						if ((Coord_X <= (ffcm_2.x + ffcm_2.w)) && (Coord_X >= (ffcm_2.x)) && (Coord_Y <= (ffcm_2.y + ffcm_2.h)) && (Coord_Y >= (ffcm_2.y)) && inter_ffcm_2)
						{
							selected_first = false;
							selected_second = true;
							selected_third = false;
							horizontal = 20; vertical = 30;
						}
						if ((Coord_X <= (ffcm_3.x + ffcm_3.w)) && (Coord_X >= (ffcm_3.x)) && (Coord_Y <= (ffcm_3.y + ffcm_3.h)) && (Coord_Y >= (ffcm_3.y)) && inter_ffcm_3)
						{
							selected_first = false;
							selected_second = false;
							selected_third = true;
							horizontal = 10; vertical = 10;
						}
					}
					////////////////////////////////
					if (event.type == SDL_MOUSEMOTION && !info)
					{
						if (key_pressed && sc_1)
						{
							SDL_GetMouseState(&Coord_X, &Coord_Y);
							if ((pos_scrole.x - pos_scrole.w) <= (S_WIDTH / 2 + 146))
							{
								if ((Coord_X - memory_x) > 0)
								{
									memory_x = Coord_X;
									pos_scrole.x = Coord_X;
									/*if ((S_WIDTH / 2 + 146 - memory_x) % 41 == 0)
										changing_of_volume += 21.3;*/
									if ((S_WIDTH / 2 + 146 - memory_x) - 41 == 0)
										changing_of_volume = 107;
									if ((S_WIDTH / 2 + 146 - memory_x) - 82 == 0)
										changing_of_volume = 85;
									if ((S_WIDTH / 2 + 146 - memory_x) - 123 == 0)
										changing_of_volume = 64;
									if ((S_WIDTH / 2 + 146 - memory_x) - 164 == 0)
										changing_of_volume = 43;
									if ((S_WIDTH / 2 + 146 - memory_x) - 205 == 0)
										changing_of_volume = 22;
									if ((S_WIDTH / 2 + 146 - memory_x) - 235 == 0)
										changing_of_volume = 0;
									Mix_VolumeMusic(changing_of_volume);
									Mix_VolumeChunk(tap, changing_of_volume);
								}
							}
							else
							{
								pos_scrole.x = S_WIDTH / 2 + 146 + pos_scrole.w / 2;
								changing_of_volume = 128;
								key_pressed = false;
							}
							if ((pos_scrole.x) >= (S_WIDTH / 2 - 100))
							{
								if ((memory_x - Coord_X) > 0)
								{
									memory_x = Coord_X;
									pos_scrole.x = Coord_X - pos_scrole.w / 2;
									if ((S_WIDTH / 2 + 146 - memory_x) - 41 == 0)
										changing_of_volume = 107;
									if ((S_WIDTH / 2 + 146 - memory_x) - 82 == 0)
										changing_of_volume = 85;
									if ((S_WIDTH / 2 + 146 - memory_x) - 123 == 0)
										changing_of_volume = 64;
									if ((S_WIDTH / 2 + 146 - memory_x) - 164 == 0)
										changing_of_volume = 43;
									if ((S_WIDTH / 2 + 146 - memory_x) - 205 == 0)
										changing_of_volume = 22;
									if ((S_WIDTH / 2 + 146 - memory_x) - 235 == 0)
										changing_of_volume = 0;
									Mix_VolumeMusic(changing_of_volume);
									Mix_VolumeChunk(tap, changing_of_volume);
								}
							}
							else
							{
								pos_scrole.x = S_WIDTH / 2 - 100;
								changing_of_volume = 0;
								key_pressed = false;
							}
						}
					}
				}
				SDL_RenderPresent(renderer);
			}
		}

		if (play)
		{
			Counter_of_generations = 0;
			max_file.open("records.txt");
			max_file >> yota;
			max_number = convert(yota);
			max_file.close();
			int* Array = (int*)malloc(horizontal * vertical * sizeof(int));
			int* Copy = (int*)malloc(horizontal * vertical * sizeof(int));
			for (int i = 0; i < horizontal; i++)
			{
				for (int j = 0; j < vertical; j++)
				{
					Array[i * vertical + j] = 0;
					Copy[i * vertical + j] = 0;
				}
			}
			double ratio_y, ratio_x;
			int number;
			if (vertical == 40 || vertical == 10)
				ratio_y = 0.6;
			else
				ratio_y = 0;
			if (horizontal == 40)
				ratio_x = 2.5;
			else
				if (horizontal == 10)
					ratio_x = -1;
				else
					ratio_x = 0;
			SDL_Rect* square = (SDL_Rect*)malloc(horizontal * vertical * sizeof(SDL_Rect));
			for (int i = 0; i < horizontal * vertical; i++)
				square[i] = {POINT_OF_XY, POINT_OF_XY, HIGHT_OF_POINT / horizontal, LENGTH_OF_POINT / vertical};
			char NOG[10], max_gen[10];
			_itoa_s(Counter_of_generations, NOG, 10);
			_itoa_s(max_number, max_gen, 10);
			SDL_Texture* texture_of_number_of_generations = get_text(renderer, NOG, font);
			SDL_Texture* texture_of_maximum = get_text(renderer, max_gen, font);
			while (play && !quit)
			{
				SDL_RenderCopy(renderer, background_play_menu, NULL, &Fill_changed);
				SDL_RenderCopy(renderer, button_back, NULL, &BBack_changed);
				SDL_RenderCopy(renderer, button_start, NULL, &BStart);
				SDL_RenderCopy(renderer, generations, NULL, &pos_generations);
				SDL_RenderCopy(renderer, texture_of_number_of_generations, NULL, &for_number_of_generations);
				SDL_RenderCopy(renderer, button_restart, NULL, &BRestart);
				SDL_RenderCopy(renderer, max_generations, NULL, &pos_maximum_generations);
				SDL_RenderCopy(renderer, texture_of_maximum, NULL, &pos_max_gen);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				for (int i = 0; i < horizontal; i++)
				{
					for (int j = 0; j < vertical; j++)
					{
						if ((i == horizontal - 1) && !Array[i * vertical + j])
						{
							if (horizontal == 40)
							{
								square[i * vertical + j] = {POINT_OF_XY + int((horizontal - 1) * LENGTH_OF_POINT / (horizontal + 2 + ratio_x)), POINT_OF_XY + int(j * HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y)), int(LENGTH_OF_POINT / (horizontal + 2 + ratio_x)), int(HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y))};
								SDL_RenderFillRect(renderer, &square[i * vertical + j]);
							}
							else
							{
								square[i * vertical + j] = {POINT_OF_XY + int((horizontal - 1) * LENGTH_OF_POINT / (horizontal + 2 + ratio_x)), POINT_OF_XY + int(j * HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y)), int(LENGTH_OF_POINT / (horizontal + 2 + ratio_x) - 8), int(HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y))};
								SDL_RenderFillRect(renderer, &square[i * vertical + j]);
							}
						}
						else
						{
							if (!Array[i * vertical + j])
							{
								square[i * vertical + j] = { POINT_OF_XY + int(i * LENGTH_OF_POINT / (horizontal + 2 + ratio_x)), POINT_OF_XY + int(j * HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y)), int(LENGTH_OF_POINT / (horizontal + 2 + ratio_x)), int(HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y)) };
								SDL_RenderFillRect(renderer, &square[i * vertical + j]);
							}
						}
					}
				}

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
				SDL_RenderDrawLine(renderer, POINT_OF_XY, POINT_OF_XY, POINT_OF_XY, HIGHT_OF_POINT);
				SDL_RenderDrawLine(renderer, POINT_OF_XY, POINT_OF_XY, LENGTH_OF_POINT, POINT_OF_XY);
				SDL_RenderDrawLine(renderer, LENGTH_OF_POINT, POINT_OF_XY, LENGTH_OF_POINT, HIGHT_OF_POINT);
				SDL_RenderDrawLine(renderer, POINT_OF_XY, HIGHT_OF_POINT, LENGTH_OF_POINT, HIGHT_OF_POINT);
				
				for (int i = 0; i < horizontal; i++)
					SDL_RenderDrawLine(renderer, POINT_OF_XY + i * LENGTH_OF_POINT / (horizontal + 2 + ratio_x), POINT_OF_XY, POINT_OF_XY + i * LENGTH_OF_POINT / (horizontal + 2 + ratio_x), HIGHT_OF_POINT);
				for (int j = 0; j < vertical; j++)
					SDL_RenderDrawLine(renderer, POINT_OF_XY, POINT_OF_XY + (j * HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y)), LENGTH_OF_POINT, POINT_OF_XY + (j * HIGHT_OF_POINT / (vertical + vertical / 6 + ratio_y)));

				for (int i = 0; i < horizontal * vertical; i++)
				{
					if (Array[i])
					{
						SDL_RenderFillRect(renderer, &square[i]);
					}
				}
				if (start)
				{
					Rewrite(horizontal, vertical, Array, Copy);
					for (int i = 0; i < horizontal; i++)
					{
						for (int j = 0; j < vertical; j++)
						{
							if (j == 0)
								Great_counter = Upper_values(i, j, vertical, horizontal, Array, Great_counter);
							else
								if (i == 0)
									Great_counter = Left_values(i, j, vertical, horizontal, Array, Great_counter);
								else
									if (i == horizontal - 1)
										Great_counter = Right_values(i, j, vertical, horizontal, Array, Great_counter);
									else
										if (j == vertical - 1)
											Great_counter = Lower_values(i, j, vertical, horizontal, Array, Great_counter);
										else
											Great_counter = Central_values(i, j, vertical, horizontal, Array, Great_counter);
							// Если рядом с мертвой клеткой находится 3 живые клетки
							if (!Array[i * vertical + j] && (Great_counter == 3))
								Array[i * vertical + j] = 1;
							// Если у живой клетки есть две или три живые соседки, то эта клетка продолжает жить; 
							// в противном случае (если живых соседей меньше двух или больше трёх) клетка умирает
							if (Array[i * vertical + j] && ((Great_counter < 2) || (Great_counter > 3)))
								Array[i * vertical + j] = 0;
							Great_counter = 0;
						}
					}
					meaning = Verification(horizontal, vertical, Array, Copy);
					if (meaning)
					{
						string stroka;
						bool one_time = true;
						int count_lines = 0;
						Recording_in_temp(stroka, count_lines, Counter_of_generations, one_time);
						Recording_in_records(stroka, count_lines);
						SDL_DestroyTexture(texture_of_maximum);
						max_file.open("records.txt");
						max_file >> yota;
						max_number = convert(yota);
						max_file.close();
						_itoa_s(max_number, max_gen, 10);
						texture_of_maximum = get_text(renderer, max_gen, font);
						start = false;
					}
					else
					{
						Counter_of_generations++;
						SDL_DestroyTexture(texture_of_number_of_generations);
						_itoa_s(Counter_of_generations, NOG, 10);
						texture_of_number_of_generations = get_text(renderer, NOG, font);
					}
					SDL_RenderCopy(renderer, texture_of_number_of_generations, NULL, &for_number_of_generations);
					SDL_RenderCopy(renderer, texture_of_maximum, NULL, &pos_max_gen);
					SDL_Delay(10);
				}
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						quit = true;
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
					{
						play = false;
						start = false;
					}
					if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
						click_pressed_right = true;
					if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
					{
						click_pressed_left = true;
						SDL_GetMouseState(&Coord_X, &Coord_Y);
						if ((Coord_X <= (BBack_changed.x + BBack_changed.w)) && (Coord_X >= (BBack_changed.x)) && (Coord_Y <= (BBack_changed.y + BBack_changed.h)) && (Coord_Y >= (BBack_changed.y)))
						{
							b_1 = true;
							Mix_PlayChannel(-1, tap, 0);
							BBack = { S_WIDTH / 40 + SIZE_DECREASE / 2, S_HIGHT - S_HIGHT / 8 + SIZE_DECREASE / 2, 2 * SIZE_OF_BUTTON_X / 3 - 2 * SIZE_DECREASE, 2 * SIZE_OF_BUTTON_Y / 3 - SIZE_DECREASE };
							BBack_changed = { S_WIDTH / 80 + SIZE_DECREASE / 2, S_HIGHT / 60 + SIZE_DECREASE / 2, SIZE_OF_BUTTON_X / 2 - 2 * SIZE_DECREASE, SIZE_OF_BUTTON_Y / 2 - SIZE_DECREASE };
						}
						else
							b_1 = false;
						if ((Coord_X <= (BStart.x + BStart.w)) && (Coord_X >= (BStart.x)) && (Coord_Y <= (BStart.y + BStart.h)) && (Coord_Y >= (BStart.y)))
						{
							bs_1 = true;
							Mix_PlayChannel(-1, tap, 0);
							BStart = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2 + SIZE_DECREASE / 2, S_HIGHT - SIZE_OF_BUTTON_Y + SIZE_DECREASE / 2, SIZE_OF_BUTTON_X - 2 * SIZE_DECREASE, SIZE_OF_BUTTON_Y - SIZE_DECREASE };
						}
						else
							bs_1 = false;
						if ((Coord_X <= (BRestart.x + BRestart.w)) && (Coord_X >= (BRestart.x)) && (Coord_Y <= (BRestart.y + BRestart.h)) && (Coord_Y >= (BRestart.y)))
						{
							br_1 = true;
							Mix_PlayChannel(-1, tap, 0);
							BRestart = { S_WIDTH - 50 - SIZE_OF_BUTTON_X / 5 + SIZE_DECREASE / 2, S_HIGHT / 60 + SIZE_DECREASE / 2, SIZE_OF_BUTTON_X / 5 - SIZE_DECREASE, SIZE_OF_BUTTON_Y / 2 - SIZE_DECREASE };
						}
						else
							br_1 = false;
						if (!start)
							for (int i = 0; i < horizontal; i++)
							{
								for (int j = 0; j < vertical; j++)
								{
									if ((Coord_X < (square[i * vertical + j].x + square[i * vertical + j].w)) && (Coord_X > (square[i * vertical + j].x)) && (Coord_Y < (square[i * vertical + j].y + square[i * vertical + j].h)) && (Coord_Y > (square[i * vertical + j].y)))
									{
										if (Array[i * vertical + j])
											Array[i * vertical + j] = 0;
										else
											Array[i * vertical + j] = 1;

									}
								}
							}
					}
					if (event.type == SDL_MOUSEMOTION && !start)
					{
						if (click_pressed_left)
						{
							SDL_GetMouseState(&Coord_X, &Coord_Y);
							for (int i = 0; i < horizontal; i++)
							{
								for (int j = 0; j < vertical; j++)
								{
									if ((Coord_X < (square[i * vertical + j].x + square[i * vertical + j].w)) && (Coord_X > (square[i * vertical + j].x)) && (Coord_Y < (square[i * vertical + j].y + square[i * vertical + j].h)) && (Coord_Y > (square[i * vertical + j].y)))
									{
										Array[i * vertical + j] = 1;
									}
								}
							}
						}
						if (click_pressed_right)
						{
							SDL_GetMouseState(&Coord_X, &Coord_Y);
							for (int i = 0; i < horizontal; i++)
							{
								for (int j = 0; j < vertical; j++)
								{
									if ((Coord_X < (square[i * vertical + j].x + square[i * vertical + j].w)) && (Coord_X > (square[i * vertical + j].x)) && (Coord_Y < (square[i * vertical + j].y + square[i * vertical + j].h)) && (Coord_Y > (square[i * vertical + j].y)))
									{
										Array[i * vertical + j] = 0;
									}
								}
							}
						}
					}
					if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT)
						click_pressed_right = false;
					if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
					{
						click_pressed_left = false;
						BBack_changed = { S_WIDTH / 80, S_HIGHT / 60, SIZE_OF_BUTTON_X / 2, SIZE_OF_BUTTON_Y / 2 };
						BStart = { S_WIDTH / 2 - SIZE_OF_BUTTON_X / 2, S_HIGHT - SIZE_OF_BUTTON_Y, SIZE_OF_BUTTON_X, SIZE_OF_BUTTON_Y };
						BRestart = { S_WIDTH - 50 - SIZE_OF_BUTTON_X / 5, S_HIGHT / 60, SIZE_OF_BUTTON_X / 5, SIZE_OF_BUTTON_Y / 2 };						
						SDL_GetMouseState(&Coord_X, &Coord_Y);
						if ((Coord_X <= (BBack_changed.x + BBack_changed.w)) && (Coord_X >= (BBack_changed.x)) && (Coord_Y <= (BBack_changed.y + BBack_changed.h)) && (Coord_Y >= (BBack_changed.y)) && b_1)
						{
							play = false;
							break;
						}
						if ((Coord_X <= (BStart.x + BStart.w)) && (Coord_X >= (BStart.x)) && (Coord_Y <= (BStart.y + BStart.h)) && (Coord_Y >= (BStart.y)) && bs_1 && !start)
						{
							Counter_of_generations = 0;
							start = true;
							break;
						}
						if ((Coord_X <= (BRestart.x + BRestart.w)) && (Coord_X >= (BRestart.x)) && (Coord_Y <= (BRestart.y + BRestart.h)) && (Coord_Y >= (BRestart.y)) && br_1 && !start)
						{
							for (int i = 0; i < horizontal; i++)
								for (int j = 0; j < vertical; j++)
									Array[i * vertical + j] = 0;
							Counter_of_generations = 0;
							SDL_DestroyTexture(texture_of_number_of_generations);
							_itoa_s(Counter_of_generations, NOG, 10);
							texture_of_number_of_generations = get_text(renderer, NOG, font);
							break;
						}
					}
				}
				SDL_RenderPresent(renderer);
			}
			free(Array);
			free(square);
		}

		if (info)
		{
			char text_gold[10], text_silver[10], text_bronze[10], text_wood[10];
			int count_of_main = 0;
			fstream main_file;
			main_file.open("records.txt");
			while (!main_file.eof())
			{
				count_of_main++;
				if (count_of_main == 1)
				{
					main_file >> text_gold;
					continue;
				}
				if (count_of_main == 2)
				{
					main_file >> text_silver;
					continue;
				}
				if (count_of_main == 3)
				{
					main_file >> text_bronze;
					continue;
				}
				if (count_of_main == 4)
				{
					main_file >> text_wood;
					break;
				}
			}
			main_file.close();
			SDL_Texture* texture_gold = get_text(renderer, text_gold, font);
			SDL_Texture* texture_silver = get_text(renderer, text_silver, font);
			SDL_Texture* texture_bronze = get_text(renderer, text_bronze, font);
			SDL_Texture* texture_wood = get_text(renderer, text_wood, font);
			
			while (info && !quit)
			{
				SDL_RenderCopy(renderer, background_records, NULL, &Fill);
				SDL_RenderCopy(renderer, button_back, NULL, &BBack_changed);
				SDL_RenderCopy(renderer, medal_gold, NULL, &pos_gold);
				SDL_RenderCopy(renderer, medal_silver, NULL, &pos_silver);
				SDL_RenderCopy(renderer, medal_bronze, NULL, &pos_bronze);
				SDL_RenderCopy(renderer, medal_wood, NULL, &pos_wood);
				SDL_RenderCopy(renderer, records, NULL, &pos_records);

				SDL_RenderCopy(renderer, texture_gold, NULL, &pos_gold_changed);
				SDL_RenderCopy(renderer, texture_silver, NULL, &pos_silver_changed);
				SDL_RenderCopy(renderer, texture_bronze, NULL, &pos_bronze_changed);
				SDL_RenderCopy(renderer, texture_wood, NULL, &pos_wood_changed);

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
						quit = true;
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						info = false;
					if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&Coord_X, &Coord_Y);
						if ((Coord_X <= (BBack_changed.x + BBack_changed.w)) && (Coord_X >= (BBack_changed.x)) && (Coord_Y <= (BBack_changed.y + BBack_changed.h)) && (Coord_Y >= (BBack_changed.y)))
						{
							b_1 = true;
							Mix_PlayChannel(-1, tap, 0);
							BBack = { S_WIDTH / 40 + SIZE_DECREASE / 2, S_HIGHT - S_HIGHT / 8 + SIZE_DECREASE / 2, 2 * SIZE_OF_BUTTON_X / 3 - 2 * SIZE_DECREASE, 2 * SIZE_OF_BUTTON_Y / 3 - SIZE_DECREASE };
							BBack_changed = { S_WIDTH / 80 + SIZE_DECREASE / 2, S_HIGHT / 60 + SIZE_DECREASE / 2, SIZE_OF_BUTTON_X / 2 - 2 * SIZE_DECREASE, SIZE_OF_BUTTON_Y / 2 - SIZE_DECREASE };
						}
						else
							b_1 = false;
					}
					if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
					{
						BBack_changed = { S_WIDTH / 80, S_HIGHT / 60, SIZE_OF_BUTTON_X / 2, SIZE_OF_BUTTON_Y / 2 };
						SDL_GetMouseState(&Coord_X, &Coord_Y);
						if ((Coord_X <= (BBack_changed.x + BBack_changed.w)) && (Coord_X >= (BBack_changed.x)) && (Coord_Y <= (BBack_changed.y + BBack_changed.h)) && (Coord_Y >= (BBack_changed.y)) && b_1)
						{
							info = false;
							break;
						}
					}
				}
				SDL_RenderPresent(renderer);
			}
		}
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(button_back);
	SDL_DestroyTexture(button_info);
	SDL_DestroyTexture(button_play);
	SDL_DestroyTexture(button_settings);
	SDL_DestroyTexture(settings_background);
	SDL_DestroyTexture(scrole);
	SDL_DestroyTexture(field_for_check_mark);
	SDL_DestroyTexture(check_mark);
	SDL_DestroyTexture(button_start);
	SDL_DestroyTexture(background_records);
	SDL_DestroyTexture(button_restart);
	SDL_DestroyTexture(records);
	SDL_DestroyTexture(medal_bronze);
	SDL_DestroyTexture(medal_gold);
	SDL_DestroyTexture(medal_silver);
	SDL_DestroyTexture(medal_wood);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}