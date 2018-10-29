#define _CRT_SECURE_NO_WARNINGS
//fopen 오류 임시방편 해결

#include "component.h" 
//gotoxy, move_cursor 등 기본적인 함수를 사용하기 위해 헤더 선언.
#include<fmod.hpp>
#include<fmod.h>
#include<fmod_errors.h>
//FMOD 함수를 사용하기 위해 헤더 3개 선언.

#pragma comment(lib,"fmodex_vc.lib")
//FMOD 라이브러리를 링크시킴.

FMOD::System *fmodsystem = 0;
FMOD::Sound *sounds[3] = { 0, };
FMOD::Channel *channel[3] = { 0, };
/*
기본적으로 사운드를 틀기 위해 선언한 타입별 변수.
FMOD::System은 음악을 틀기 위한 기기로, 포인터 fmodsystem을 가리키며 변수 초기화를 위해 0으로 정함.
FMOD::Sound는 효과음의 갯수만큼 선언하기 위해 쓰이며, 포인터 sounds를 가리키고 총 3개의 1차원 배열을 생성시키고 0으로 초기화.
FMOD::Channel은 사운드 채널을 컨트롤하여 사운드 볼륨을 설정해줄 수 있으며, 포인터 channel을 가리키고 총 3개의 1차원 배열을 생성시키고 0으로 초기화.
*/

FMOD_RESULT result;
//사운드를 생성하는 변수 타입인 FMOD_RESULT와 result라는 변수를 선언한다.

void FMOD_ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}
/*
FMOD 클래스 전반에 에러가 있는지 확인하기 위하여 void라는 사용자 정의 함수를 만들었으며 함수 이름은 ERRCHECK이다.
괄호에 있는 (FMOD_RESULT result)는 함수로 넘겨주는 데이터인 result로, 인자를 의미한다.

{
	만약 결과가 FMOD_OK의 결과값이 불일치한다면, (이때 FMOD_OK는 에러가 없다는 것을 의미)
	{
		FMOD error! (<result라는 인수 출력을 역할하는 정수 서식문자 %d>) <result 데이터를 인자로 하는 FMOD_ErrorString 문자열 서식문자>"를 출력하고 행을 바꾼다.
		에러가 나서 프로그램 종료함.
	}
}

쉽게 말해서 FMOD 클래스 전반에 에러가 있는지 체크함.
예를 들어 사운드 파일이 없다거나 잘못된 사운드 파일인 경우에 에러 체크를 해줘야 한다.
*/

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}
/*
FMOD 클래스 전반에 에러가 있는지 확인하기 위하여 void라는 사용자 정의 함수를 만들었으며 함수 이름은 ERRCHECK이다.
괄호에 있는 (FMOD_RESULT result)는 함수로 넘겨주는 데이터인 result로, 인자를 의미한다.

{
	만약 결과가 FMOD_OK의 결과값이 불일치한다면, (이때 FMOD_OK는 에러가 없다는 것을 의미)
	{
		FMOD error! (<result라는 인수 출력을 역할하는 정수 서식문자 %d>) <result 데이터를 인자로 하는 FMOD_ErrorString 문자열 서식문자>"를 출력하고 행을 바꾼다.
		에러가 나서 프로그램 종료함.
	}
}

쉽게 말해서 FMOD 클래스 전반에 에러가 있는지 체크함.
예를 들어 사운드 파일이 없다거나 잘못된 사운드 파일인 경우에 에러 체크를 해줘야 한다.
*/

//song 구조체 선언
struct song
{
	char songname[20];
	char artist[20];
	int level;
};
//song 구조체 선언 끝.

//*****************************
int score;
int combo;
int max_combo;
int offset = 75;
double acc;
int notecount;
char g_key[4] = { 'z', 'x', 'c', 'v' };
int note_set = 1;
//전역 변수 사용 부분
/*
int는 정수형 변수, double은 실수형 변수, char은 문자형 변수를 선언하는데 사용되는 변수 타입, 그 뒤에는 함수 이름을 정함.
정수형 변수인 offset은 75, note_set은 1로 값 지정됨.
char g_key[4] = { 'z', 'x', 'c', 'v' };에서
g_key[0]은 z, g_key[1]은 x, g_key[2]는 c, g_key[3]은 v라는 문자열을 차지하는 것을 뜻함. 배열 참고.
*/
//****************************

//주요 기능 함수 선언//
int draw_start_stage(int x, int y); 
int draw_credit();
int draw_choose_song(int x_m, int y_m);
void wirte_somnail(struct song *);
void draw_equalizer(int *equalizer_count, char pic[][8]);
void draw_song(int *sel, char key, struct song *);
void draw_offset();
void draw_setting();
int draw_game_screen(int note_set, int spd, int song, int diff);
void move_draw_song(char key, struct song *);
void move_set_cursor(char key, int *y, int y_m);
void auto_sync();
int stopmenu();
void draw_key_effect(char *key);
int judge_acc(char *key, int note[4][24]);
void draw_score_and_combo();
void draw_judge(int *jud);
void note_to_note(int *num, int notelen, char f_note[][5], int note[4][24]);
void draw_note(int set, int vac[4][24]);
void delete_key_FX(char *key);
void erease_judge();
int draw_result();
void draw_sync_check_note(int vac[][11]);
//주요 기능 함수 선언 끝


int main(void)
{
ALL_START:
	FMOD_SYSTEM      *system;
	FMOD_SOUND       *start_stage, *set_enter;
	FMOD_CHANNEL     *channel = 0;
	FMOD_RESULT       result;

	unsigned int      version;

	result = FMOD_System_Create(&system);
	FMOD_ERRCHECK(result);

	result = FMOD_System_GetVersion(system, &version);
	FMOD_ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return 0;
	}
	result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(system, "Sounds/start_stage.mp3", FMOD_LOOP_NORMAL, 0, &start_stage);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(system, "Sounds/set_enter.mp3", FMOD_SOFTWARE, 0, &set_enter);
	FMOD_ERRCHECK(result);

	//***********************************************FMOD
START:
	int i, x, y, select, main_error = 0;
	x = 13; y = 18;

	result = FMOD_System_CreateSound(system, "Sounds/start_stage.mp3", FMOD_LOOP_NORMAL, 0, &start_stage);
	FMOD_ERRCHECK(result);
	result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, start_stage, 0, &channel);
	FMOD_ERRCHECK(result);
	select = draw_start_stage(x, y);

	for (;;)
	{
		if (select == 0)
		{
			result = FMOD_Sound_Release(start_stage);
			FMOD_ERRCHECK(result);
			result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, set_enter, 0, &channel);
			FMOD_ERRCHECK(result);
			/* for (i = 0; i < 2; i++)
			{
				draw_loading_screen(); 
				Sleep(200);
			} */ //지연시간 추가나 로딩 화면은 나중에 넣는 걸로.
			
			main_error = draw_choose_song(X_MAX, Y_MAX); //여기선 "1. 시작하기" 누를 때 기능 실현
		}
		else if (select == 1)
		{
			result = FMOD_Sound_Release(start_stage);
			FMOD_ERRCHECK(result);
			draw_credit();

			goto START;

		}
		else if (select == 2)
		{
			result = FMOD_Sound_Release(start_stage);
			FMOD_ERRCHECK(result);
			draw_setting();

			goto START;
		}
		if (main_error == 1)
			break;
		else if (main_error == 2)
			goto ALL_START;

	}


}

int draw_start_stage(int x, int y)
{
	FMOD_SYSTEM      *sys;
	FMOD_SOUND       *sound1;
	FMOD_CHANNEL     *channel = 0;
	FMOD_RESULT       result;

	unsigned int      version;

	result = FMOD_System_Create(&sys);
	FMOD_ERRCHECK(result);

	result = FMOD_System_GetVersion(sys, &version);
	FMOD_ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return 0;
	}
	result = FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "Sounds/set_enter.mp3", FMOD_HARDWARE, 0, &sound1);
	FMOD_ERRCHECK(result);

	//***********************************************FMOD

	char key;
	for (;;)
	{

		/*63칸  |*/  /*73 |*/
		printf("\n");
		printf("                        #######      #########\n");
		printf("        ,#######       ##     ##     ##     ##\n");
		printf("   ################   ###########    #########\n");
		printf("   ###        ####    ##       ##    ##\n");
		printf("    ###     ####      ##       ##    ##\n");
		printf("    ####  ####        ##       ##    ##\n");
		printf("     #####\n");
		printf("     #######\n");
		printf("      ###  #####                     ########  ########  ###    ##  ########  ######## \n");
		printf("      ###    ######                  ##        ##    ##  ####   ##     ##     ###      \n");
		printf("       ###       #####               ########  ##    ##  ## ##  ##     ##     ###      \n");
		printf("       ###            ###                  ##  ##    ##  ##  ## ##     ##     ###      \n");
		printf("        ###                          ########  ########  ##    ###  ########  ######## \n");
		printf("                                                       Modified Work of DJ MAX, Ver 0.1\n");
		printf("\n\n");
		printf("		메뉴를 선택하세요.\n");
		printf("		1. 게임 시작\n		2. 제작자 정보\n		3. 게임 설정\n		4. 종료\n\n\n");
		printf("		조작키 설명\n");
		printf("		↑,↓ : 커서이동		Enter : 선택                                   \n\n\n");

		for (;;)
		{
			gotoxy(x, y); printf("▶");
			key = _getch();
			if (y >= 18 && y <= 21)//메뉴 선택
			{
				if (key == 72 || key == 80) //키를 위 또는 아래 방향 키를 눌렀을 시
				{
					result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, &channel);
					FMOD_ERRCHECK(result);
					printf("\b\b"); printf("  ");
					move_cursor(key, &x, &y, X_MAX, Y_MAX);
					if (y > 21) y = y-4;
					if (y < 18) y = y+4;
				}
				else if (key == 13)//엔터키 누를시
				{
					if (y == 18) // 1.시작
					{
						system("cls");
						return 0;
					}
					else if (y == 19) // 2. 제작자 정보
					{
						system("cls");
						return 1;
					}
					else if (y == 20) //3. 게임 설정
					{
						system("cls");
						return 2;
					}
					else if (y == 21) //4. 종료
					{
						system("cls");
						return 3;
					}
				}
				else
				{
					continue;
				}
			}
		}

	}

}

int draw_credit()
{
	FMOD_SYSTEM      *sys;
	FMOD_SOUND       *stage_credit, *set_back;
	FMOD_CHANNEL     *channel = 0;
	FMOD_RESULT       result;

	unsigned int      version;

	result = FMOD_System_Create(&sys);
	FMOD_ERRCHECK(result);

	result = FMOD_System_GetVersion(sys, &version);
	FMOD_ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return 0;
	}
	result = FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "Sounds/stage_credit.mp3", FMOD_LOOP_NORMAL, 0, &stage_credit);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "Sounds/set_back.mp3", FMOD_SOFTWARE, 0, &set_back);
	FMOD_ERRCHECK(result);

	//***********************************************FMOD

	char key;
	result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, stage_credit, 0, &channel);
	FMOD_ERRCHECK(result);
	for (;;)
	{


		system("cls");
		printf("Rap S0n1c by SHG & ASH\n");
		printf("버전: 0.1~alpha1\n\n");
		printf("변경 사항\n");
		printf("20181029 첫 시작 메인화면 및 제작자 정보 구성\n");
		printf("\n\n\n\n돌아가려면 Enter키를 누르세요.");

		key = _getch();

		if (key == 13) //엔터 키
		{
			result = FMOD_Sound_Release(stage_credit);
			FMOD_ERRCHECK(result);
			result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, set_back, 0, &channel);
			FMOD_ERRCHECK(result);
			Sleep(500);
			FMOD_ERRCHECK(result);
			system("cls");
			break;
		}
		else
			system("cls"); continue;
	}

}

int draw_choose_song(int x_m, int y_m)
{
SELECT_RESTART:
	FMOD_SYSTEM      *sys;
	FMOD_SOUND       *sound1, *sound2, *sound3, *move_sel;
	FMOD_CHANNEL     *g_channel[1] = { NULL };
	FMOD_RESULT       result;
	bool playing = 0;
	bool paused = 0;
	unsigned int ms = 0;
	unsigned int lenms = 0;

	FMOD_BOOL IsPlaying;

	int channelisplaying = 0;

	unsigned int      version;

	result = FMOD_System_Create(&sys);
	FMOD_ERRCHECK(result);

	result = FMOD_System_GetVersion(sys, &version);
	FMOD_ERRCHECK(result);

	result = fmodsystem->init(32, FMOD_INIT_NORMAL, 0);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return 1;
	}
	result = FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/somnail/first_kiss_somnail.mp3", FMOD_LOOP_NORMAL, 0, &sound1);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/somnail/black_swan_somnail.mp3", FMOD_LOOP_NORMAL, 0, &sound2);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/somnail/magnolia_somnail.mp3", FMOD_LOOP_NORMAL, 0, &sound3);
	FMOD_ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/SFX/djing_FX.mp3", FMOD_HARDWARE, 0, &move_sel);
	FMOD_ERRCHECK(result);

	//***********************************************FMOD
	char key = 0, offkey;
	char pic[8][8] = { 0, };
	int speed = 50, song = 1, difficulty = 1;//속도, 음악,난이도(1=NM 2=HD)
	int selected_music = 2, playing_music = 2, sw = 0, first = 1, l_r = 0;
	int cur_choice = 2; /*20181023 오류 수정: cur_choice 값 2로 설정*/
	struct song music[3];
	struct song temp;
	int i;
	int equalizer_count = 0;
	wirte_somnail(music);
	srand(time(NULL));
	system("cls");
	//10칸 기준
	//0123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|MAX=80         
	printf("  싱크 (노트속도) 조정 : + (느리게) - (빠르게)         s:게임 설정"); printf("\n");
	printf("   "); printf("\n");
	printf("  싱크   :          (ms)                               q:메인 화면으로"); printf("\n");
	printf("                              "); printf("\n");
	printf("  "); printf("\n");//***
	printf("    "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");//***
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");//***
	printf("                              ▼▼▼▼▼▼▼▼ "); printf("\n");
	printf("    곡명 :                   곡명 :                   곡명 :                   "); printf("\n");//곡명 : 15칸
	printf("    아티스트 :               아티스트 :               아티스트 :               "); printf("\n");//아티스트 : 11칸
	printf("    난이도 :                 난이도 :                 난이도 :                 "); printf("\n");//난이도 : 13칸
	printf("                              ▲▲▲▲▲▲▲▲ "); printf("\n");//***
	printf("     "); printf("\n");
	printf("   곡 이동 : ←,→    선택 : space");
	//END OF DOS Y_AXIS

	Sleep(800);

	for (;;)
	{

		if (first == 1)//첫 실행 시 사운드 재생
		{
			result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound2, 0, &g_channel[0]);
			first = 0;
		}

		if (sw == 1)//사운드를 풀어주는 함수
		{

			if (l_r == 1)
			{

				switch (playing_music)
				{
				case 1:
					FMOD_Sound_Release(sound1);
					break;
				case 2:
					FMOD_Sound_Release(sound2);
					break;
				case 3:
					FMOD_Sound_Release(sound3);
					break;
				}
				playing_music--;
				if (playing_music < 1)
					playing_music = 3;
			}
			else if (l_r == 2)
			{

				switch (playing_music)
				{
				case 1:

					FMOD_ERRCHECK(result);

					FMOD_Sound_Release(sound1);
					break;
				case 2:

					FMOD_ERRCHECK(result);

					FMOD_Sound_Release(sound2);
					break;
				case 3:

					FMOD_ERRCHECK(result);
					FMOD_Sound_Release(sound3);
					break;

				}
				playing_music++;
				if (playing_music > 3)
					playing_music = 1;
			}

		}
		if (sw == 1)//곡을 변환하기위한 스위치
		{
			if (selected_music == 1)
			{
				result = FMOD_System_CreateSound(sys, "sound/somnail/first_kiss_somnail.mp3", FMOD_LOOP_NORMAL, 0, &sound1);
				result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, &g_channel[0]);
				FMOD_ERRCHECK(result);
				sw = 0;
			}
			else if (selected_music == 2)
			{
				result = FMOD_System_CreateSound(sys, "sound/somnail/black_swan_somnail.mp3", FMOD_LOOP_NORMAL, 0, &sound2);
				FMOD_Channel_Stop(g_channel[0]);
				result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound2, 0, &g_channel[0]);
				FMOD_ERRCHECK(result);
				sw = 0;
			}
			else if (selected_music == 3)
			{
				result = FMOD_System_CreateSound(sys, "sound/somnail/magnolia_somnail.mp3", FMOD_LOOP_NORMAL, 0, &sound3);
				FMOD_Channel_Stop(g_channel[0]);
				result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound3, 0, &g_channel[0]);
				FMOD_ERRCHECK(result);
				sw = 0;
			}
		}
		for (;;)
		{

			//잡 효과
			Sleep(100);
			if (_kbhit() == 1)
			{
				key = _getch();
				offkey = key;
			}
			draw_equalizer(&equalizer_count, pic);

			draw_song(&selected_music, key, music);
			draw_offset();

			if (offkey == '+')
			{
				offset++;
				offkey = 0;
			}
			else if (offkey == '-')
			{
				offset--;
				offkey = 0;
			}
			if (key == 's')
			{
				switch (playing_music)
				{
				case 1:
					FMOD_Sound_Release(sound1);
					break;
				case 2:
					FMOD_Sound_Release(sound2);
					break;
				case 3:
					FMOD_Sound_Release(sound3);
					break;
				}
				draw_setting();
				goto SELECT_RESTART;
			}
			if (key == 'q')
			{
				switch (playing_music)
				{
				case 1:
					FMOD_Sound_Release(sound1);
					break;
				case 2:
					FMOD_Sound_Release(sound2);
					break;
				case 3:
					FMOD_Sound_Release(sound3);
					break;
				}
				system("cls");
				return 2;
			}
			if (key == 32)
			{
				if (playing_music == 1)
				{
					result = FMOD_Sound_Release(sound1);
					FMOD_ERRCHECK(result);
				}
				else if (playing_music == 2)
				{
					result = FMOD_Sound_Release(sound2);
					FMOD_ERRCHECK(result);
				}
				else if (playing_music == 3)
				{
					result = FMOD_Sound_Release(sound3);
					FMOD_ERRCHECK(result);
				}
				system("cls");
				cur_choice = draw_game_screen(note_set, speed, playing_music, difficulty);
				if (cur_choice == 8)
					goto SELECT_RESTART;
				else if (cur_choice == 5)
					return 2;
			}
			else if (key == 75 || key == 77)
			{
				move_draw_song(key, music);
				result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, move_sel, 0, &g_channel[0]);
				Sleep(100);
				FMOD_ERRCHECK(result);
				if (key == 77)
				{

					selected_music--;
					if (selected_music < 1)
						selected_music = 3;
					l_r = 1;
					sw = 1;
					key = 0;
					break;
				}
				else if (key == 75)
				{

					selected_music++;
					if (selected_music > 3)
						selected_music = 1;
					l_r = 2;
					sw = 1;
					key = 0;
					break;
				}

			}
			if (cur_choice == 0)
				return 0;
			else if (cur_choice == 1)
				return 1;
			else if (cur_choice == 2)
				break;
		}
	}
}

void wirte_somnail(struct song *sn)
{

	strcpy_s(sn->songname, 20, "first kiss  ");
	strcpy_s(sn->artist, 20, "BJJ     ");
	sn->level = 3;

	strcpy_s((sn + 1)->songname, 20, "black swan  ");
	strcpy_s((sn + 1)->artist, 20, "Tak        ");
	(sn + 1)->level = 6;

	strcpy_s((sn + 2)->songname, 20, "magnolia    ");
	strcpy_s((sn + 2)->artist, 20, "M2U        ");
	(sn + 2)->level = 5;

}

void draw_equalizer(int *equalizer_count, char pic[][8])
{
	int x = 30, y = 5, i, j, k;


	if (*equalizer_count == 3)
	{
		for (i = 0; i < 8; i++)
		{
			k = rand() % 5;
			pic[i][k] = 1;
		}
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 7; j++)
			{
				if (pic[i][j] == 1)
				{
					pic[i][j + 1] = 1;
				}
			}
		}
		*equalizer_count = 0;
	}
	for (i = 0; i < 8; i++)
	{
		for (j = 7; j > 0; j--)
		{
			pic[i][j] = pic[i][j - 1];
			pic[i][j - 1] = 0;
		}


	}
	for (i = 0; i < 8; i++)
	{
		gotoxy(x, y);
		for (j = 0; j < 8; j++)
		{
			if (pic[j][i] == 1)
				printf("■");
			else if (pic[j][i] == 0)
				printf("  ");
		}
		y += 1;
	}
	*equalizer_count = *equalizer_count + 1;

	return;


}

void draw_song(int *sel, char key, struct song *sn)
{
	int  y = 16;
	gotoxy(11, y);
	printf("%s", sn->songname);
	gotoxy(16, y + 1);
	printf("%s", sn->artist);
	gotoxy(14, y + 2);
	printf("%d", sn->level);
	gotoxy(36, y);
	printf("%s", (sn + 1)->songname);
	gotoxy(41, y + 1);
	printf("%s", (sn + 1)->artist);
	gotoxy(39, y + 2);
	printf("%d", (sn + 1)->level);
	gotoxy(60, y);
	printf("%s", (sn + 2)->songname);
	gotoxy(65, y + 1);
	printf("%s", (sn + 2)->artist);
	gotoxy(63, y + 2);
	printf("%d", (sn + 2)->level);
}

void draw_offset()
{
	int x = 13, y = 2;
	gotoxy(x, y);
	printf("%d", offset);
}

void draw_setting()
{
	FMOD_SYSTEM      *sys;
	FMOD_SOUND       *set_enter, *stage_setting;
	FMOD_CHANNEL     *channel = 0;
	FMOD_RESULT       result;

	unsigned int      version;

	result = FMOD_System_Create(&sys);
	ERRCHECK(result);

	result = FMOD_System_GetVersion(sys, &version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
	}
	result = FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "Sounds/set_enter.mp3", FMOD_HARDWARE, 0, &set_enter);
	ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "Sounds/stage_setting.mp3", FMOD_LOOP_NORMAL, 0, &stage_setting);
	ERRCHECK(result);

	//***********************************************FMOD

	int select_x = 2, select_y = 2;
	char key;

	result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, stage_setting, 0, &channel);
	ERRCHECK(result);

	system("cls");
	//10칸 기준
	//		0123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789|MAX=80         
	printf("                      게임 설정 "); printf("\n");
	printf("  "); printf("\n");
	printf("       싱크(노트 속도) :         "); printf("\n");
	printf("  "); printf("\n");
	printf("       노트 모양 :       (1.● 2.■ 3.★)"); printf("\n");
	printf(" "); printf("\n");//***
	printf("       오토싱크(Beta)"); printf("\n");
	printf(" "); printf("\n");
	printf("       선택화면으로"); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");//***
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");
	printf("  "); printf("\n");//***
	printf("    "); printf("\n");
	printf("    "); printf("\n");//곡명 : 15칸
	printf("           "); printf("\n");//아티스트 : 11칸
	printf("조작키 설명\n");
	printf("    커서 이동 : ↑,↓  조절 : ←,→  선택 : Enter   "); printf("\n");//난이도 : 13칸
	printf("   "); printf("\n");//***
	//END OF DOS Y_AXIS

	for (;;)
	{
		gotoxy(select_x, select_y);
		printf("▶");
		gotoxy(25, 2);
		printf("%d", offset);
		gotoxy(20, 4);
		printf("%d", note_set);
		key = _getch();

		if (key == 72 || key == 80)
		{
			gotoxy(select_x, select_y);
			printf("  ");
			result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, set_enter, 0, &channel);
			ERRCHECK(result);
			move_set_cursor(key, &select_y, 8);
		}

		if (select_y == 2)
		{
			if (key == 75)
				offset--;
			else if (key == 77)
				offset++;
		}
		else if (select_y == 4)
		{
			if (key == 75)
			{
				note_set--;
				if (note_set < 1)
					note_set++;
			}
			else if (key == 77)
			{
				note_set++;
				if (note_set > 3)
					note_set--;
			}
		}
		else if (select_y == 6)
		{
			if (key == 13)
			{
				result = FMOD_Sound_Release(stage_setting);
				ERRCHECK(result);
				auto_sync();
				return;
			}
		}
		else if (select_y == 8)
		{
			if (key == 13)
			{
				result = FMOD_Sound_Release(stage_setting);
				ERRCHECK(result);
				system("cls");
				return;
			}
		}
	}
}

int draw_game_screen(int note_set, int spd, int song, int diff)
{
GAME_RESTART:
	FMOD_SYSTEM      *sys;
	FMOD_SOUND       *sound1, *sound2, *sound3, *move_sel;
	FMOD_CHANNEL     *g_channel[1] = { NULL };
	FMOD_RESULT       result;
	bool playing = 0;
	bool paused = 0;
	unsigned int ms = 0;
	unsigned int lenms = 0;

	FMOD_BOOL IsPlaying;

	int channelisplaying = 0;

	unsigned int      version;

	result = FMOD_System_Create(&sys);
	ERRCHECK(result);

	result = FMOD_System_GetVersion(sys, &version);
	ERRCHECK(result);

	result = fmodsystem->init(32, FMOD_INIT_NORMAL, 0);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return 0;
	}
	result = FMOD_System_Init(sys, 32, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/songs/first_kiss.mp3", FMOD_HARDWARE, 0, &sound1);
	ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/songs/black_swan.mp3", FMOD_HARDWARE, 0, &sound2);
	ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/songs/Magnolia.mp3", FMOD_HARDWARE, 0, &sound3);
	ERRCHECK(result);
	result = FMOD_System_CreateSound(sys, "sound/SFX/menu_button_sound.mp3", FMOD_HARDWARE, 0, &move_sel);
	ERRCHECK(result);
	//변수 선언
	//---------------------------------------------------------------
	int x = 10, y = 0;
	int i, j, k;
	int playlen = 0;
	char key = 0;
	char file_note[20000][5];
	int note[4][24] = { 0, 0, };
	int n_of_file = 0, num = 0;
	int judge = 0;
	int stop_select = 0;
	double acc2 = 0.0;
	int play_count = 0;
	//----------------------------------------------------------------

	//초기값 설정
	//----------------------------------------------------------------
	score = 0;
	combo = 0;
	acc = 1;
	notecount = 0;
	//-------------------------------------------------------------------

	//텍스트 파일 불러오기
	//------------------------------------------------------------------
	FILE *notefile = nullptr; /*20181023 오류 수정: notefile의 포인터 변수 초기화*/
	if (song == 1)
	{
		notefile = fopen("sound/songs/first_kiss.txt", "r");
	}
	else if (song == 2)
	{
		notefile = fopen("sound/songs/black_swan.txt", "r");
	}
	else if (song == 3)
	{
		notefile = fopen("sound/songs/Magnolia.txt", "r");
	}
	if (notefile == NULL)
		printf("파일 불러오기 실패\n");
	//파일 길이 측정
	//**********************************
	fseek(notefile, 0L, SEEK_END);
	n_of_file = ftell(notefile);
	n_of_file = (n_of_file / 6) + 1;
	//********************************
	//파일을 가져온 후, 분석하여 배열에 저장
	//**********************************************
	fseek(notefile, 0, SEEK_SET);
	for (i = 0; i < n_of_file; i++)
	{
		for (j = 0; j < 5; j++)
		{
			file_note[i][j] = fgetc(notefile);
			fseek(notefile, 0L, SEEK_CUR);
		}
	}
	fclose(notefile);
	//**********************************************
	//---------------------------------------------------------------------


	for (i = 0; i < 21; i++)
	{
		gotoxy(x, y);
		for (j = 0; j < 4; j++)
		{
			printf("│      ");
		}
		printf("│");
		y += 1;
	}
	gotoxy(x, y);
	printf("├───┼───┼───┼───┤");
	y += 1;
	gotoxy(x, y);
	for (j = 0; j < 5; j++)
	{
		printf("│      ");
	}
	y += 1;
	gotoxy(x, y);
	printf("└───┴───┴───┴───┘");
	gotoxy(60, 2);
	printf("q:정지메뉴");
	gotoxy(44, 20);
	printf("--perfect");
	gotoxy(44, 18);
	printf("--Good");

	for (playlen = 0; playlen < n_of_file + 22; playlen++)
	{
		if (note[3][20] == 1 || note[2][20] == 1 || note[1][20] == 1 || note[0][20] == 1 || score != 0)
		{
			if (play_count == 0)
			{
				if (song == 1)
				{
					result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound1, 0, &g_channel[0]);
					play_count++;
				}
				else if (song == 2)
				{
					result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound2, 0, &g_channel[0]);
					play_count++;
				}
				else if (song == 3)
				{
					result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound3, 0, &g_channel[0]);
					play_count++;
				}
			}
			ERRCHECK(result);
		}
		if (_kbhit())
			key = _getch();

		if (key == 'q')
		{
			if (song == 1)
			{
				FMOD_Sound_Release(sound1);
				ERRCHECK(result);
			}
			else if (song == 2)
			{
				FMOD_Sound_Release(sound2);
				ERRCHECK(result);
			}
			else if (song == 3)
			{
				FMOD_Sound_Release(sound3);
				ERRCHECK(result);
			}
			stop_select = stopmenu();
			if (stop_select == 8)
				return 8;
			else if (stop_select == 4)
				goto GAME_RESTART;
			else if (stop_select == 5)
				return 5;

		}
		if (key == 'z' || key == 'x' || key == 'c' || key == 'v')
		{
			draw_key_effect(&key);
			judge = judge_acc(&key, note);
		}
		if (note[0][23] == 1 || note[1][23] == 1 || note[2][23] == 1 || note[3][23] == 1)
			judge = 4;



		if (judge == 2)
		{
			combo++;
			score += 300;
			score += (6 * combo);
			notecount++;
			acc2 += 100.0;
			if (max_combo < combo)
				max_combo = combo;
		}
		else if (judge == 1)
		{
			combo++;
			score += 100;
			score += (2 * combo);
			notecount++;
			acc2 += 70.0;
			if (max_combo < combo)
				max_combo = combo;
		}
		else if (judge == 4)
		{
			combo = 0;
			notecount++;
			acc2 += 0.0;
		}





		acc = acc2 / notecount;
		draw_score_and_combo();
		draw_judge(&judge);

		note_to_note(&num, n_of_file, file_note, note);
		draw_note(1, note);
		Sleep(offset);
		for (i = 0; i < 4; i++)
		{
			for (j = 23; j > 0; j--)
			{
				note[i][j] = note[i][j - 1];
				note[i][j - 1] = 0;
			}


		}
		note[i][20] = 0;
		delete_key_FX(&key);
		erease_judge();

	}
	draw_result();
}

void move_draw_song(char key, struct song *sn)
{
	struct song temp;
	int i;
	switch (key)
	{
	case 75:
		strcpy_s(temp.songname, _TRUNCATE, (sn)->songname);
		strcpy_s(temp.artist, _TRUNCATE, (sn)->artist);
		temp.level = (sn)->level;
		for (i = 0; i < 2; i++)
		{
			strcpy_s((sn + i)->songname, _TRUNCATE, (sn + i + 1)->songname);
			strcpy_s((sn + i)->artist, _TRUNCATE, (sn + i + 1)->artist);
			(sn + i)->level = (sn + i + 1)->level;
		}
		strcpy_s((sn + 2)->artist, _TRUNCATE, temp.artist);
		strcpy_s((sn + 2)->songname, _TRUNCATE, temp.songname);
		(sn + 2)->level = temp.level;
		break;
	case 77:
		strcpy_s(temp.songname, _TRUNCATE, (sn + 2)->songname);
		strcpy_s(temp.artist, _TRUNCATE, (sn + 2)->artist);
		temp.level = (sn + 2)->level;
		for (i = 2; i > 0; i--)
		{
			strcpy_s((sn + i)->songname, _TRUNCATE, (sn + i - 1)->songname);
			strcpy_s((sn + i)->artist, _TRUNCATE, (sn + i - 1)->artist);
			(sn + i)->level = (sn + i - 1)->level;
		}
		strcpy_s((sn)->artist, _TRUNCATE, temp.artist);
		strcpy_s((sn)->songname, _TRUNCATE, temp.songname);
		(sn)->level = temp.level;
		break;
	}
}

void move_set_cursor(char key, int *y, int y_m)

{
	switch (key)
	{
	case 72:

		*y = *y - 2;
		if (*y < 2) *y += 2;
		break;
	case 80:
		*y += 2;
		if (*y > y_m) *y -= 2;
		break;
	}
}

void auto_sync()
{
	int i, j, tic, tik;
	int x = 0, y = 0;
	double sy_time;
	clock_t start, finish;
	int note[4][11] = { 0, };
	int sy_avg_time = 0;
	char key;
	system("cls");
	printf("자동 싱크 맞추기(Test ver.)\n");
	printf("컴퓨터의 속도를 대략적으로 계산하여 싱크를 맞춥니다.\n");
	printf("계속 하려면 아무키나 누르세요\n");
	_getch();
	system("cls");


	for (i = 0; i < 10; i++)
	{
		gotoxy(x, y);
		for (j = 0; j < 4; j++)
		{
			printf("│      ");
		}
		printf("│");
		y += 1;
	}
	gotoxy(x, y);
	printf("├───┼───┼───┼───┤");
	y += 1;
	gotoxy(x, y);
	for (j = 0; j < 5; j++)
	{
		printf("│      ");
	}
	y += 1;
	gotoxy(x, y);
	printf("└───┴───┴───┴───┘");
	for (tic = 0; tic < 5; tic++)
	{
		for (j = 0; j < 6; j += 3)
		{

			for (i = 0; i < 4; i++)
			{

				note[i][j] = 1;
			}
		}

		start = clock();
		for (tik = 0; tik < 10; tik++)
		{
			draw_sync_check_note(note);
			Sleep(100);
			for (i = 0; i < 4; i++)
			{
				for (j = 10; j > 0; j--)
				{
					note[i][j] = note[i][j - 1];
					note[i][j - 1] = 0;
				}


			}
			note[i][10] = 0;
		}
		finish = clock();

		sy_time = (double)(finish - start) / CLOCKS_PER_SEC;
		sy_time = sy_time - 1;
		sy_time *= 100;
		sy_avg_time += (int)(sy_time);
	}
	sy_avg_time /= 10;



	gotoxy(2, 13);
	printf("감지된 싱크 : %d", 100 - sy_avg_time);
	gotoxy(2, 14);
	printf("적용하시겠습니까? (y=예 n=아니요)");
	gotoxy(2, 15);
	printf("선택 후 바로 곡 선택화면으로 돌아갑니다.");
	for (;;)
	{
		key = _getch();
		if (key == 'y')
		{
			offset = 100;
			offset -= sy_avg_time;
			return;
		}
		else if (key == 'n')
		{
			return;
		}
		else
			continue;
	}



}

int stopmenu()
{
	char key;
	system("cls");
	for (;;)
	{
		gotoxy(0, 0);
		printf("정지메뉴");
		gotoxy(0, 1);
		printf("1.곡 선택 화면");
		gotoxy(0, 2);
		printf("2.재시작");
		gotoxy(0, 3);
		printf("3.메인 메뉴로");
		gotoxy(0, 4);
		printf("이어하기 기능은 지원하지 않습니다.");
		gotoxy(20, 1);
		printf("싱크 : %d", offset);
		key = _getch();
		system("cls");
		if (key == '+')
			offset++;
		else if (key == '-')
			offset--;
		else if (key == '1')
			return 8;
		else if (key == '2')
			return 4;
		else if (key == '3')
			return 5;
	}
}

void draw_key_effect(char *key)
{
	if (*key == g_key[0])
	{
		gotoxy(12, 22);
		printf("■■■");
	}
	else if (*key == g_key[1])
	{
		gotoxy(20, 22);
		printf("■■■");
	}
	else if (*key == g_key[2])
	{
		gotoxy(28, 22);
		printf("■■■");
	}
	else if (*key == g_key[3])
	{
		gotoxy(36, 22);
		printf("■■■");
	}
}

int judge_acc(char *key, int note[4][24])
{

	if (*key == g_key[0])
	{
		if (note[0][20] == 1 || note[0][21] == 1)
		{
			if (note[0][20] == 1)
			{
				note[0][20] = 0;
			}
			else if (note[0][21] == 1)
			{
				note[0][21] = 0;
			}
			return 2;
		}
		else if (note[0][19] == 1 || note[0][18] == 1)
		{
			if (note[0][19] == 1)
			{
				note[0][19] = 0;
			}
			else if (note[0][18] == 1)
			{
				note[0][18] = 0;
			}
			return 1;
		}
	}
	else if (*key == g_key[1])
	{
		if (note[1][20] == 1 || note[1][21] == 1)
		{
			if (note[1][20] == 1)
			{
				note[1][20] = 0;
			}
			else if (note[1][21] == 1)
			{
				note[1][21] = 0;
			}
			return 2;
		}
		else if (note[1][19] == 1 || note[1][18] == 1)
		{
			if (note[1][19] == 1)
			{
				note[1][19] = 0;
			}
			else if (note[1][18] == 1)
			{
				note[1][18] = 0;
			}
			return 1;
		}
	}
	else if (*key == g_key[2])
	{
		if (note[2][20] == 1 || note[2][21] == 1)
		{
			if (note[2][20] == 1)
			{
				note[2][20] = 0;
			}
			else if (note[2][21] == 1)
			{
				note[2][21] = 0;
			}
			return 2;
		}
		else if (note[2][19] == 1 || note[2][18] == 1)
		{
			if (note[2][19] == 1)
			{
				note[2][19] = 0;
			}
			else if (note[2][18] == 1)
			{
				note[2][18] = 0;
			}
			return 1;
		}
	}
	else if (*key == g_key[3])
	{
		if (note[3][20] == 1 || note[3][21] == 1)
		{
			if (note[3][20] == 1)
			{
				note[3][20] = 0;
			}
			else if (note[3][21] == 1)
			{
				note[3][21] = 0;
			}
			return 2;
		}
		else if (note[3][19] == 1 || note[3][18] == 1)
		{
			if (note[3][19] == 1)
			{
				note[3][19] = 0;
			}
			else if (note[3][18] == 1)
			{
				note[3][18] = 0;
			}
			return 1;
		}
	}

	return 0;

}

void draw_score_and_combo()
{
	gotoxy(2, 10);
	printf("콤보");
	gotoxy(2, 11);
	printf("%3d", combo);
	gotoxy(2, 13);
	printf("점수");
	gotoxy(2, 14);
	printf("%d", score);
	gotoxy(2, 17);
	printf("정확도");
	gotoxy(2, 18);
	printf("%.2lf", acc);
}

void draw_judge(int *jud)
{
	int x = 45, y = 15;
	gotoxy(x, y);
	if (*jud == 1)
		printf("●GOOD!●    ");
	else if (*jud == 2)
		printf("★PERFECT!!★");
	else if (*jud == 4)
		printf("miss...      ");
	else
		return;
	*jud = 0;
}

void note_to_note(int *num, int notelen, char f_note[][5], int note[4][24])

{
	int j, c;
	for (j
 = 0; j < 4; j++)
	{
		if (f_note[(*num)][j] == '0')
			note[j][0] = 0;
		else if (f_note[(*num)][j] == '1')
			note[j][0] = 1;
	}
	*num += 1;
}

void draw_note(int set, int vac[4][24])
{
	int x = 12, y = 0;
	int i, j;
	int clean_count = 0;
	gotoxy(x, y);
	for (i = 0; i < 21; i++)
	{

		for (j = 0; j < 4; j++)
		{

			if (i == 20 || i == 19 || i == 18 || i == 17)
			{
				gotoxy(x, i);
				printf("	  ");
			}
			gotoxy(x, y);
			if (vac[j][i] == 1)
			{
				switch (note_set)
				{
				case 1:
					printf("●●●");
					break;
				case 2:
					printf("■■■");
					break;
				case 3:
					printf("★★★");
					break;
				}
				if (y > 0)
				{
					gotoxy(x, y - 1);
					printf("	  ");
				}
			}

			x += 8;
		}
		x = 12;
		y += 1;
	}
}

void delete_key_FX(char *key)
{
	if (*key == g_key[0])
	{
		gotoxy(12, 22);
		printf("      ");
	}
	else if (*key == g_key[1])
	{
		gotoxy(20, 22);
		printf("      ");
	}
	else if (*key == g_key[2])
	{
		gotoxy(28, 22);
		printf("      ");
	}
	else if (*key == g_key[3])
	{
		gotoxy(36, 22);
		printf("      ");
	}
	*key = 0;
}

void erease_judge()
{
	int x = 45, y = 15;
	gotoxy(x, y);
	printf("              ");
}

int draw_result()
{
	system("cls");

	printf("점수 : %d\n", score);
	printf("정확도 : %.2lf\n", acc);
	printf("콤보 : %d\n", max_combo);
	printf("아무 키나 누르면 선곡화면으로 이동");
	_getch();
	return 8;
}

void draw_sync_check_note(int vac[][11])
{
	int x = 2, y = 0;
	int al, i, j;
	int clean_count = 0;
	int note_set = 1;
	gotoxy(x, y);
	for (al = 0; al < 2; al++)
	{
		y = 0;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (i == 9)
				{
					gotoxy(x, y);
					printf("  ");
				}
				gotoxy(x, i);
				printf("      ");

				gotoxy(x, y);
				if (vac[j][i] == 1)
				{
					switch (note_set)
					{
					case 1:
						printf("●●●");
						break;
					}
					if (y > 0)
					{
						gotoxy(x, y - 1);
						printf("      ");
					}
				}

				x += 8;
			}
			x = 2;
			y += 1;
		}
	}
}