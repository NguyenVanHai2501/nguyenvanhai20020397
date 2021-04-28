#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string.h>
#include <ctime>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <cmath>
using namespace std;


const int WIDTH_BK = 4800;
const int HEIGHT_BK = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int PLANE_WIDTH = 80;
const int PLANE_HEIGHT = 52;
const int THREAT_WIDTH = 80;
const int THREAT_HEIGHT = 33;
const int LASER_WIDTH = 1000;
const int LASER_HEIGHT = 45;
const int FIREBALL_WIDTH = 50;
const int FIREBALL_HEIGHT = 50;
const int BULLET_THREAT=30;
const int BOSS_WIDTH = 500;
const int BOSS_HEIGHT = 375;
const int ICE_STAR = 100;
const int NUM_ICE_STAR = 6;
const int SCR_SPEED = 1;
const int ROCKET_W = 50;
const int ROCKET_H = 100;
const int NUM_ROCKET = 6;

const string WINDOW_TITLE = "An Implementation of Code.org Painter";
bool stylelaser = false;
bool stylefireball = false;
int num_bullet_fireball = 0;
int BLOOD = 1000;
int NUM_THREAT = 4;

struct Coordinate
{
    double x,y;
};
struct Fly_equa
{
    double a,b;
};

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void plane_action(SDL_Event events, SDL_Rect &plane);
bool Destroy (SDL_Rect &A, SDL_Rect &B);
bool DestroyPlane (SDL_Rect &A, SDL_Rect &B);
bool DestroyBoss (SDL_Rect &Boss, SDL_Rect &B);
bool DestroyByRocket ( SDL_Rect &rocket, SDL_Rect &plane);
bool DestroyByIceStar ( SDL_Rect &ice_star, SDL_Rect &plane);
bool DestroyByBossFireBall ( SDL_Rect &fireball, SDL_Rect &plane );
bool action_main ( SDL_Event e, SDL_Rect &text, SDL_Rect &mouse);
void close();
SDL_Texture* loadTexture( std::string path );

SDL_Renderer* renderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Window* g_windows = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* g_background = NULL;
SDL_Surface* g_characters = NULL;
SDL_Event g_event;
TTF_Font* g_font;

SDL_Rect scr
{
    scr.x = 0,
    scr.y = 0,
    scr.w = SCREEN_WIDTH,
    scr.h = SCREEN_HEIGHT
};

SDL_Rect boss
{
    boss.x = 1200,
    boss.y = 50,
    boss.w = BOSS_WIDTH,
    boss.h = BOSS_HEIGHT
};
SDL_Rect bullet_exp
{
    bullet_exp.w = PLANE_HEIGHT,
    bullet_exp.h = PLANE_HEIGHT

};
SDL_Rect Exp
{
    Exp.w = PLANE_WIDTH,
    Exp.h = PLANE_WIDTH
};
SDL_Rect start
{
    start.x = 545,
    start.y = 125,
    start.w = 100,
    start.h = 30
};
SDL_Rect level
{
    level.x = 545,
    level.y = 180,
    level.w = 100,
    level.h = 30
};
SDL_Rect rule
{
    rule.x = 555,
    rule.y = 240,
    rule.w = 90,
    rule.h = 30
};
SDL_Rect Exit
{
    Exit.x = 555,
    Exit.y = 300,
    Exit.w = 90,
    Exit.h = 30
};
SDL_Rect Back
{
    Back.x = SCREEN_WIDTH - 120,
    Back.y = SCREEN_HEIGHT - 60,
    Back.w = 120,
    Back.h = 60
};
SDL_Rect fighting
{
    fighting.x = 300,
    fighting.y = 100,
    fighting.w = 0,
    fighting.h = 0
};
SDL_Rect rect
{
    rect.x = 800,
    rect.y = 450,
    rect.w = BLOOD/4,
    rect.h = 20
};
SDL_Rect blood
{   blood.x = 800,
    blood.y = 450,
    blood.w = 0,
    blood.h = 20
};
SDL_Rect rocket
{
    rocket.x = SCREEN_WIDTH - BOSS_WIDTH,
    rocket.y = boss.y + 170,
    rocket.w = ROCKET_W,
    rocket.h = ROCKET_H
};
SDL_Rect arrow
{
    arrow.x = 525,
    arrow.w = 20,
    arrow.h = 20
};
SDL_Rect greenTick
{
    greenTick.x = 500,
    greenTick.y = 205,
    greenTick.w = 20,
    greenTick.h = 20
};
SDL_Rect easy
{
    easy.x = 545,
    easy.y = 205,
    easy.w = 60,
    easy.h = 20
};
SDL_Rect medium
{
    medium.x = 545,
    medium.y = 235,
    medium.w = 100,
    medium.h = 20
};
SDL_Rect hard
{
    hard.x = 545,
    hard.y = 265,
    hard.w = 65,
    hard.h = 20
};
SDL_Rect restart
{
    restart.x = 540,
    restart.y = 265,
    restart.w = 120,
    restart.h = 40
};
SDL_Rect playAgain
{
    playAgain.x = 470,
    playAgain.y = 265,
    playAgain.w = 125,
    playAgain.h = 35
};
SDL_Rect winExit
{
    winExit.x = 605,
    winExit.y = 265,
    winExit.w = 125,
    winExit.h = 35
};

int main(int argc, char* argv[])
{
    srand(time(NULL));
    SDL_Window* window;
    initSDL(window,renderer);

    bool is_quit = false;
    bool is_play = false;
    bool is_level = false;
    bool is_rule = false;
    bool is_win = false;
    bool is_loss =  false;

    SDL_Texture* Texture_exp3 = loadTexture("exp3.png");
    SDL_Texture* Texture_bullet_exp = loadTexture("bullet_exp.png");
    SDL_Texture* Texture_boss_bullet = loadTexture("boss_bullet.png");
    SDL_Texture* Texture_bullet_exp_boss = loadTexture("bullet_exp_boss.png");
    SDL_Texture* Texture_plane = loadTexture("plane.png");
    SDL_Texture* Texture_plane_bullet = loadTexture("plane_bullet.png");
    SDL_Texture* Texture_scr = loadTexture("bg4800.png");
    SDL_Texture* Texture_bk = loadTexture("bk_font.png");
    SDL_Texture* Texture_start = loadTexture("start_font.jpg");
    SDL_Texture* Texture_level = loadTexture("level_font.jpg");
    SDL_Texture* Texture_showlevel = loadTexture("show_level.jpg");
    SDL_Texture* Texture_showlevel2 = loadTexture("show_level2.jpg");
    SDL_Texture* Texture_rule = loadTexture("rule_font.jpg");
    SDL_Texture* Texture_showrule = loadTexture("show_rule.jpg");
    SDL_Texture* Texture_showrule2 = loadTexture("show_rule2.jpg");
    SDL_Texture* Texture_gameover = loadTexture("game_over.jpg");
    SDL_Texture* Texture_gameover2 = loadTexture("game_over2.jpg");
    SDL_Texture* Texture_gameover3 = loadTexture("game_over3.jpg");
    SDL_Texture* Texture_win = loadTexture("game_win.jpg");
    SDL_Texture* Texture_win2 = loadTexture("game_win2.jpg");
    SDL_Texture* Texture_win3 = loadTexture("game_win3.jpg");
    SDL_Texture* Texture_exit = loadTexture("exit_font.jpg");
    SDL_Texture* Texture_fighting = loadTexture("fighting.png");
    SDL_Texture* Texture_arrow = loadTexture("arrow.png");
    SDL_Texture* Texture_greenTick = loadTexture("green_tick.png");
    SDL_Texture* Texture_threat = loadTexture("threat.png");
    SDL_Texture* Texture_bullet_threat = loadTexture("bullet_threat.png");
    SDL_Texture* Texture_threat_boss = loadTexture("threat_boss.png");
    SDL_Texture* Texture_laser = loadTexture("laser3.png");
    SDL_Texture* Texture_fireball = loadTexture("fire_ball.png");
    SDL_Texture* Texture_rocketup = loadTexture("rocketup.png");
    SDL_Texture* Texture_rocketdown = loadTexture("rocketdown.png");


   while (!is_quit)
  {
    while (true)
    {
       SDL_Rect mouse;
       mouse.x = g_event.button.x;
       mouse.y = g_event.button.y;
       scr.x = 0;
       if (g_event.type == SDL_QUIT)
        {
            quitSDL(window, renderer);
            close();
            return 0;
        }
       if (is_level ==  false && is_rule == false && is_win == false && is_loss == false)
       {
        SDL_RenderCopy(renderer,Texture_bk, &scr, NULL);
        SDL_PollEvent(&g_event);
        if (g_event.type == SDL_QUIT)
        {
            is_quit = true;
            break;
        }
        mouse.x = g_event.button.x;
        mouse.y = g_event.button.y;
        if (action_main(g_event,start,mouse))
        {
            SDL_RenderCopy( renderer, Texture_start, &scr, NULL );
            SDL_PollEvent(&g_event);
            if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                is_play = true;
                break;
            }
        }
        if (action_main(g_event,level,mouse))
        {
            SDL_RenderCopy(renderer,Texture_level,&scr,NULL);
            SDL_PollEvent(&g_event);
            if (g_event.type == SDL_MOUSEBUTTONDOWN) is_level = true;
        }

        if (action_main(g_event,rule,mouse))
        {
            SDL_RenderCopy(renderer,Texture_rule,NULL,&scr);
            SDL_PollEvent(&g_event);
            if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                is_rule = true;
            }
        }

        if (action_main(g_event,Exit,mouse))
        {
            SDL_RenderCopy(renderer,Texture_exit,NULL,&scr);
            SDL_PollEvent(&g_event);
            if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                quitSDL(window, renderer);
                close();
                return 0;
            }
        }
       }

        if ( is_level )
        {
            SDL_RenderCopy(renderer, Texture_showlevel, &scr, NULL);
            SDL_RenderCopy(renderer, Texture_greenTick, NULL, &greenTick );
            SDL_PollEvent(&g_event);
            if (action_main(g_event,Back, mouse))
            {
                SDL_RenderCopy(renderer, Texture_showlevel2, NULL, &scr);
                SDL_RenderCopy(renderer, Texture_greenTick, NULL, &greenTick );
                SDL_PollEvent(&g_event);
                if (g_event.type == SDL_MOUSEBUTTONDOWN) is_level = false;
            }
            if (action_main(g_event,easy, mouse))
            {
                arrow.y = easy.y;
                SDL_RenderCopy(renderer, Texture_arrow,NULL, &arrow);
                if (g_event.type == SDL_MOUSEBUTTONDOWN) { greenTick.y = easy.y; NUM_THREAT = 4; }
            }
            if (action_main(g_event,medium, mouse))
            {
                arrow.y = medium.y;
                SDL_RenderCopy(renderer, Texture_arrow,NULL, &arrow);
                if (g_event.type == SDL_MOUSEBUTTONDOWN) { greenTick.y = medium.y; NUM_THREAT = 6; }
            }
            if (action_main(g_event,hard, mouse))
            {
                arrow.y = hard.y;
                SDL_RenderCopy(renderer, Texture_arrow,NULL, &arrow);
                if (g_event.type == SDL_MOUSEBUTTONDOWN) { greenTick.y = hard.y; NUM_THREAT = 10; }
            }
        }

        if ( is_rule )
        {
            SDL_RenderCopy(renderer, Texture_showrule , &scr, NULL);
            SDL_PollEvent(&g_event);
            if (action_main(g_event,Back, mouse))
            {
                SDL_RenderCopy(renderer, Texture_showrule2, NULL, &scr);
                SDL_PollEvent(&g_event);
                if (g_event.type == SDL_MOUSEBUTTONDOWN) is_rule = false;
            }
        }


        if (is_loss)
        {
            SDL_RenderCopy(renderer, Texture_gameover, &scr, NULL);
            SDL_PollEvent(&g_event);
            if (action_main(g_event, restart, mouse))
            {
                SDL_RenderCopy(renderer, Texture_gameover3, &scr, NULL);
                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    is_loss = false;
                    is_play = true;
                    break;
                }
            }
            if (action_main(g_event, Back, mouse))
            {
                SDL_RenderCopy(renderer, Texture_gameover2, &scr, NULL);
                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    is_loss = false;
                }
            }
        }


        if (is_win)
        {
            SDL_RenderCopy(renderer, Texture_win, &scr, NULL);
            SDL_PollEvent(&g_event);
            if (action_main(g_event,playAgain, mouse))
            {
                SDL_RenderCopy(renderer, Texture_win2, &scr, NULL);
                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    is_win = false;
                    is_play = true;
                    break;
                }
            }
            if (action_main(g_event, winExit, mouse))
            {
                SDL_RenderCopy(renderer, Texture_win3,&scr, NULL);
                if (g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    quitSDL(window, renderer);
                    close();
                    return 0;
                }
            }
        }


        SDL_RenderPresent( renderer );

    }
    SDL_Rect fireball_num[10000];
    SDL_Rect threat[20];
    SDL_Rect bullet_threat[20][10];
    SDL_Rect ice_star[20];
    SDL_Rect Roc[NUM_ROCKET*2];
    SDL_Rect boss_fireball;
    SDL_Rect laser;
    SDL_Rect plane;
    plane.x = 0;
    plane.y = SCREEN_HEIGHT/2;
    plane.w = PLANE_WIDTH;
    plane.h = PLANE_HEIGHT;
    fighting.w = 0;
    fighting.h = 0;
    for (int i = 1; i <= 20; i++) { ice_star[i].w = ICE_STAR; ice_star[i].h = ICE_STAR;}
    ice_star[NUM_ICE_STAR].x=-SCREEN_WIDTH;
    boss_fireball.x = -1;
    boss_fireball.w = -1;
    boss.x = 1200;
    BLOOD = 1000;
    blood.w = 1;

    Coordinate coordinate[20][20]; // lay toa do may bay (muc tieu) luc ban cho threat thu i, va vien dan thu j dc ban ra
    Fly_equa fly_equa[20][20]; // tao phuong trinh chuyen dong cua dan ban cho vien dan thu j cua threat thu i
    int num_bullet_threat[10];
    Uint32 time_run = -1;
    int style_bullet_boss = 0;
    for (int i = 1; i <= NUM_THREAT; i++) threat[i].x = -SCREEN_WIDTH;

    bool is_set_bullet = true;
    bool is_set_boss = false;
    bool is_boss_fireball = false;
    bool is_ice_star = false;
    bool is_rocket = false;
    bool is_rocket_up = false;
    bool is_rocket_down = false;
    bool is_fighting = true;

    while (is_play)
    {
      SDL_PollEvent(&g_event);
      if (g_event.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
       plane_action ( g_event,plane );
       if (scr.x < 3600)  scr.x += SCR_SPEED;
       else { is_set_bullet = false; is_set_boss = true; }
       if (is_set_bullet == false)
        for (int i = 1; i <= NUM_THREAT; i++)
         if (threat[i].x != -SCREEN_WIDTH)
         {
            is_set_boss = false;
            break;
         }
       SDL_Delay(30);
       SDL_RenderCopy( renderer, Texture_scr, &scr, NULL );
       SDL_RenderCopy( renderer, Texture_plane, NULL, &plane );
       //tao threat
        for (int i = 1; i <= NUM_THREAT; i++)
        {
          if (is_set_bullet == true)
          {
            if (threat[i].x == -SCREEN_WIDTH)
            {
                int res = rand()% (350/PLANE_HEIGHT + 1);
                threat[i].x = 1200;
                threat[i].y = res*PLANE_HEIGHT;
                threat[i].w = THREAT_WIDTH;
                threat[i].h = THREAT_HEIGHT;
                //khoi tao so vien dan ban dau cua 1 threat
                num_bullet_threat[i] = 0;
            }
            if (threat[i].x % 200 == 0 && threat[i].x > plane.x + 3*PLANE_WIDTH )
            {
                num_bullet_threat[i]++;
                // set bullet
                bullet_threat[i][num_bullet_threat[i]].x = threat[i].x - BULLET_THREAT;
                bullet_threat[i][num_bullet_threat[i]].y = threat[i].y - 2;
                bullet_threat[i][num_bullet_threat[i]].w = BULLET_THREAT;
                bullet_threat[i][num_bullet_threat[i]].h = BULLET_THREAT;
                // tao toado cua may bay luc nay
                coordinate[i][num_bullet_threat[i]].x = plane.x + PLANE_WIDTH/2;
                coordinate[i][num_bullet_threat[i]].y = plane.y;
                // tao pt bay cua dan
                 fly_equa[i][num_bullet_threat[i]].a = (coordinate[i][num_bullet_threat[i]].y - bullet_threat[i][num_bullet_threat[i]].y) / (coordinate[i][num_bullet_threat[i]].x - bullet_threat[i][num_bullet_threat[i]].x);
                 fly_equa[i][num_bullet_threat[i]].b = coordinate[i][num_bullet_threat[i]].y - fly_equa[i][num_bullet_threat[i]].a * coordinate[i][num_bullet_threat[i]].x;
            }
          }
            if (threat[i].x + THREAT_WIDTH + 1 >= 0)
            {
                SDL_RenderCopy( renderer, Texture_threat, NULL, &threat[i] );
                threat[i].x -= 2;
            }
            else threat[i].x = -SCREEN_WIDTH;
            for (int j = 1; j <= num_bullet_threat[i]; j++)
             if (bullet_threat[i][j].x + BULLET_THREAT > 0)
             {
                SDL_RenderCopy( renderer, Texture_bullet_threat, NULL, &bullet_threat[i][j] );
                bullet_threat[i][j].x -= 10;
                bullet_threat[i][j].y = fly_equa[i][j].a * bullet_threat[i][j].x + fly_equa[i][j].b;
             }
        }
       // tao ban dan fireball
       SDL_Rect fireball;
       if (stylefireball == true)
       {
             fireball_num[num_bullet_fireball];
             fireball_num[num_bullet_fireball].x = plane.x + PLANE_WIDTH;
             fireball_num[num_bullet_fireball].y = plane.y;
             fireball_num[num_bullet_fireball].w = FIREBALL_WIDTH;
             fireball_num[num_bullet_fireball].h = FIREBALL_HEIGHT;
             bullet_exp.x = plane.x + PLANE_WIDTH;
             bullet_exp.y = plane.y;
             SDL_RenderCopy( renderer, Texture_plane_bullet, NULL, &plane );
             SDL_RenderCopy( renderer, Texture_bullet_exp, NULL, &bullet_exp);
       }
       for (int i = 0; i <= num_bullet_fireball; i++)
       {
           if (fireball_num[i].x <= 1200 && fireball_num[i].x != -SCREEN_WIDTH)
            {
                fireball_num[i].x += 15;
                SDL_RenderCopy( renderer, Texture_fireball, NULL, &fireball_num[i] );
                if (fireball_num[i].x > 1200) fireball_num[i].x = -SCREEN_WIDTH;
            }
            //xu li va cham va huy threat
           for (int j = 1; j <= NUM_THREAT; j++)
           {
            if (Destroy(fireball_num[i],threat[j]))
              {
                  Exp.x = threat[j].x;
                  Exp.y = threat[j].y - threat[j].h + Exp.h/2;
                  SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
                  threat[j].x = -SCREEN_WIDTH;
                  fireball_num[i].x = -SCREEN_WIDTH;
              }
           }
       }
       stylefireball = false;
       //set bullet laser
       if (stylelaser == true)
       {
                laser.x = (plane.x + PLANE_WIDTH);
                laser.y = plane.y + 5;
                laser.w = LASER_WIDTH;
                laser.h = LASER_HEIGHT;
                SDL_RenderCopy( renderer, Texture_laser, NULL, &laser  );
                SDL_RenderCopy( renderer, Texture_laser, NULL, &laser  );
                SDL_RenderCopy( renderer, Texture_laser, NULL, &laser  );
                SDL_RenderCopy( renderer, Texture_plane_bullet, NULL, &plane );
                stylelaser = false;
            // xu li huy threat va boss
            for (int j = 1; j <= NUM_THREAT; j++)
                if (Destroy(laser,threat[j]))
                {
                  Exp.x = threat[j].x;
                  Exp.y = threat[j].y - threat[j].h + Exp.h/2;
                  SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
                  threat[j].x = -SCREEN_WIDTH;
                }
            if (DestroyBoss(boss,laser))
            {
              BLOOD -= 1;
              blood.w = BLOOD/4;
              Exp.x = boss.x;
              Exp.y = laser.y;
              SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
            }
       }

       // tao man danh vs boss
       if (is_set_boss)
       {
        SDL_RenderCopy( renderer, Texture_threat_boss, NULL, &boss);
        if ( boss.x > SCREEN_WIDTH - boss.w)  boss.x -= 2;
        else
        {
         SDL_SetRenderDrawColor(renderer,0,0,0,0);
         SDL_RenderDrawRect(renderer,&rect);
         SDL_SetRenderDrawColor(renderer,255,0,0,255);
         SDL_RenderFillRect(renderer,&blood);
         //bullet fire_ball of boss;
         if (is_fighting)
         {
            if ( fighting.w < 400)
            {
                fighting.w += 40;
                fighting.h += 25;
                blood.w += 25;
            }
            else { is_fighting = false; SDL_Delay(2000); }
            SDL_RenderCopy(renderer,Texture_fighting, NULL, &fighting);
            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderDrawRect(renderer,&rect);
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
            SDL_RenderFillRect(renderer,&blood);
            SDL_RenderPresent( renderer );
         }
         else
         {
         if (time_run + 4 <= SDL_GetTicks()/1000)
         {
             time_run = SDL_GetTicks()/1000;
             style_bullet_boss = rand()% ( 3 - 1 + 1 ) + 1;
             if (style_bullet_boss == 2) is_boss_fireball = true;
             if (style_bullet_boss == 1) is_ice_star = true;
             if (style_bullet_boss == 3 && is_rocket == false)
             {
                is_rocket = true;
                is_rocket_up = true;
                is_rocket_down = true;
             }
         }

         if (is_boss_fireball)
         {
          if (boss_fireball.x + boss_fireball.w < 0)
          {
              int res = rand()% ( 3 - 1 + 1 ) + 1;
             boss_fireball.w = 40;
             boss_fireball.h = 40;
             boss_fireball.x = 2*(BOSS_WIDTH/5) - boss_fireball.w + boss.x;
             boss_fireball.y = res*BOSS_HEIGHT/5;
             Exp.x = boss_fireball.x - Exp.w + boss_fireball.w*3/2;
             Exp.y = boss_fireball.y - Exp.w + boss_fireball.w*5/3;
             SDL_RenderCopy(renderer, Texture_bullet_exp_boss, NULL, &Exp );
          }
         if (boss_fireball.x + boss_fireball.w >= 0)
         {
             SDL_RenderCopy(renderer, Texture_bullet_threat, NULL, &boss_fireball);
             boss_fireball.x -= 8;
             boss_fireball.y -= 1;
             boss_fireball.w += 2;
             boss_fireball.h += 2;
         }
         if (boss_fireball.x + boss_fireball.w < 0) is_boss_fireball = false;
         }
         //dan mua sao bang cua boss
         if (is_ice_star)
         {
         if (ice_star[NUM_ICE_STAR].x == -SCREEN_WIDTH)
          for (int i = 1; i <= NUM_ICE_STAR; i++)
          {
             if (i % 2 != 0) ice_star[i].x = boss.x + BOSS_WIDTH/2;
             else ice_star[i].x = boss.x-20;
             ice_star[i].y =- ice_star[i].h*i - 2.5*(i-1);
          }
         for (int i = 1; i <= NUM_ICE_STAR; i++)
           if (ice_star[i].x + ice_star[i].w >= 0)
           {
             ice_star[i].x -= 5;
             ice_star[i].y += 5;
             SDL_RenderCopy(renderer,Texture_boss_bullet, NULL,&ice_star[i]);
           }
           else ice_star[i].x =- SCREEN_WIDTH;
          if (ice_star[NUM_ICE_STAR].x == -SCREEN_WIDTH) is_ice_star = false;
        }
        // rocket of boss
        if (is_rocket)
        {
            if (is_rocket_up) { rocket.y = boss.y+170; is_rocket_up = false; }
            if (rocket.y+rocket.h >= 0 && is_rocket_down == false)
            {
                if (rocket.y == boss.y+170)
                {
                    Exp.x = rocket.x-5;
                    Exp.y = rocket.y-5;
                    SDL_RenderCopy(renderer, Texture_bullet_exp_boss, NULL, &Exp );
                }
                SDL_RenderCopy(renderer, Texture_rocketup, NULL, &rocket);
                rocket.y -= 6;
            }
            else
            {
            if (is_rocket_down)
            {
             Roc[NUM_ROCKET].x = plane.x;
             Roc[NUM_ROCKET].y = -ROCKET_H;
             Roc[NUM_ROCKET].w = ROCKET_W;
             Roc[NUM_ROCKET].h = ROCKET_H;
             for ( int i = 1 ; i <= NUM_ROCKET-1 ; i++)
             {
                int res = rand()% ( boss.x/ROCKET_W + 1);
                Roc[i].x = res*ROCKET_W;
                Roc[i].y = -ROCKET_H;
                Roc[i].w = ROCKET_W;
                Roc[i].h = ROCKET_H;
             }
             is_rocket_down = false;
            }
             for (int i = 1 ; i <= NUM_ROCKET; i++)
             {
                SDL_RenderCopy(renderer, Texture_rocketdown, NULL, &Roc[i]);
                if (Roc[i].y <= 450)   Roc[i].y += 4;
                else  { Exp.x = Roc[i].x;
                        Exp.y = Roc[i].y;
                        SDL_RenderCopy( renderer, Texture_exp3, NULL, &Exp);
                        SDL_RenderPresent(renderer);
                        is_rocket = false;
                      }
             }
            }
        }


        for (int i = 0; i <= num_bullet_fireball; i++)
         if (DestroyBoss(boss,fireball_num[i]) && fireball_num[i].x != -1 )
           {
              BLOOD -= 1;
              blood.w = BLOOD/4;
              Exp.x = boss.x;
              Exp.y = fireball_num[i].y;
              SDL_RenderCopy(renderer,Texture_exp3, NULL, &Exp);
              fireball_num[i].x = -SCREEN_WIDTH;
           }

         }
        }
       }


        // end game : loss
        if (is_set_boss)
        for (int i = 1 ; i <= NUM_ROCKET; i++ && is_rocket)
            if (DestroyByRocket(Roc[i],plane))
                {
                    Exp.x = plane.x;
                    Exp.y = plane.y - plane.h + Exp.h/2;
                    SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
                    for (int j = 1 ; j <= NUM_ROCKET; j++)
                        Roc[j].x = -SCREEN_WIDTH;
                    SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
                    SDL_RenderPresent(renderer);
                    for (int j = 1; j <= NUM_ICE_STAR; j++)
                    ice_star[j].x = -SCREEN_WIDTH;
                    SDL_Delay(1000);
                    is_loss = true;
                    is_play = false;
                    break;
                }
        if (is_set_boss)
        if (DestroyPlane(boss,plane) || ( DestroyByBossFireBall(boss_fireball,plane) && is_boss_fireball))
        {
              Exp.x = plane.x;
              Exp.y = plane.y - plane.h + Exp.h/2;
              SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
              boss_fireball.x = -SCREEN_WIDTH;
              SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
              SDL_RenderPresent(renderer);
              for (int j = 1; j <= NUM_ICE_STAR; j++)
                ice_star[j].x = -SCREEN_WIDTH;
              SDL_Delay(1000);
              is_loss = true;
              is_play = false;
              break;
        }
        if (is_set_boss && is_ice_star)
        for (int i = 1; i <= NUM_ICE_STAR; i++)
           if (DestroyByIceStar(ice_star[i], plane))
            {
              Exp.x = plane.x;
              Exp.y = plane.y-plane.h+Exp.h/2;
              Uint32 t = SDL_GetTicks()/1000;
              SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
              SDL_RenderPresent(renderer);
              for (int j = 1; j <= NUM_ICE_STAR; j++)
                ice_star[j].x = -SCREEN_WIDTH;
              SDL_Delay(1000);
              is_loss = true;
              is_play = false;
              break;
            }

        for (int i = 1; i <= NUM_THREAT; i++)
        for (int j = 1; j <= num_bullet_threat[i]; j++)
       {
         if (bullet_threat[i][j].x+BULLET_THREAT > 0)
           if (DestroyPlane(plane,bullet_threat[i][j]) || DestroyPlane(plane,threat[i]))
            {
                Exp.x = plane.x;
                Exp.y = plane.y-plane.h+Exp.h/2;
                SDL_RenderCopy(renderer, Texture_exp3, NULL, &Exp);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000);
                is_loss = true;
                is_play = false;
                i = 10;
                break;
            }
       }
        //end game : win
        if (blood.w <= 0)
        {
            for (int i = 1; i <= 5; i++)
            {
                int resx = rand()% ( 10 + 1 );
                int resy = rand()% ( 10 + 1 );
                Exp.x = boss.x + resx*50;
                Exp.y = boss.y + 150 + resy*25 - Exp.h;
                SDL_RenderCopy( renderer ,Texture_exp3, NULL, &Exp );
                SDL_RenderPresent(renderer);
            }
            SDL_Delay(2000);
            is_play = false;
            is_win = true;
       }

      SDL_RenderPresent( renderer );

    }
  }


    waitUntilKeyPressed();
    quitSDL(window, renderer);
    close();
    return 0;
}
void close()
{
    SDL_FreeSurface( g_background );
    g_background = NULL;
    SDL_DestroyWindow( g_windows );
    g_windows = NULL;
    SDL_Quit();
}
void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
        exit(1);
    }
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
              e.type == SDL_QUIT)
            return;
        SDL_Delay(100);
    }
}
void plane_action(SDL_Event events, SDL_Rect &plane)
{
  if (events.type == SDL_KEYDOWN)
  {
    switch (events.key.keysym.sym)
    {
    case SDLK_UP:
      plane.y -= PLANE_HEIGHT/6;
      if (plane.y<0) plane.y = 0;
      //Todo
      break;
    case SDLK_DOWN:
      plane.y += PLANE_HEIGHT/6;
      if (plane.y>350) plane.y = 350;
      //Todo
      break;
    case SDLK_RIGHT:
      plane.x += PLANE_WIDTH/6;
      if (plane.x>SCREEN_WIDTH-PLANE_WIDTH) plane.x=SCREEN_WIDTH-PLANE_WIDTH;
      //Todo
      break;
    case SDLK_LEFT:
      plane.x -= PLANE_WIDTH/6;
      if (plane.x<0) plane.x = 0;
      break;
    default:
      break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN)
  {
     if (events.button.button == SDL_BUTTON_LEFT)
     {
         stylelaser = true;
     }
     else if (events.button.button == SDL_BUTTON_RIGHT)
     {
         stylefireball = true;
     }
  }
  else if (events.type == SDL_MOUSEBUTTONUP)
    if (events.button.button == SDL_BUTTON_RIGHT)
      {
          num_bullet_fireball++;
      }

}
SDL_Texture* loadTexture( std::string path )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
bool Destroy (SDL_Rect &A, SDL_Rect &B)
{
    if (( B.y + B.h/2 >= A.y && B.y + B.h/2 <= A.y + A.h )
     && ( B.x >= A.x && B.x <= A.x + A.w))
     return true;
    return false;
}
bool DestroyPlane (SDL_Rect &A, SDL_Rect &B)
{
    if ((B.y + B.h/2 >= A.y && B.y + B.h/2 <= A.y + A.h)
      &&(B.x >= A.x && B.x <= A.x + 3*A.w/4)) return true;
    else if ((B.y + B.h/2 >= A.y && B.y + B.h/2 <= A.y + A.h)
      &&(B.x + B.w >= A.x && B.x + B.w <= A.x + 3*A.w/4)) return true;
    else return false;
}
bool DestroyBoss (SDL_Rect &Boss, SDL_Rect &B)
{
    if (B.x + B.w >= Boss.x && B.y + B.h/2 >= Boss.y + 150 && B.y + B.h/2 <= Boss.y + Boss.h)
        return true;
    else return false;
}
bool DestroyByBossFireBall ( SDL_Rect &fireball, SDL_Rect &plane )
{
    int Xp = plane.x + plane.w/2, Yp = plane.y + plane.h/2,
        Xb = fireball.x + fireball.w/2 , Yb = fireball.y + fireball.h/2;
    int d = (Xp - Xb)*(Xp - Xb) + (Yp - Yb)*(Yp - Yb);
    if (d*4 <= fireball.w*fireball.w) return true;
    return false;
}
bool DestroyByIceStar ( SDL_Rect &ice_star, SDL_Rect &plane)
{
    if (ice_star.x + 10 >= plane.x && ice_star.x + 10 <= plane.x + plane.w
    &&  ice_star.y - 10 + ice_star.h >= plane.y && ice_star.y - 10 + ice_star.h <= plane.y + plane.h)
    return true;
    return false;
}
bool DestroyByRocket ( SDL_Rect &rocket, SDL_Rect &plane)
{
    if (rocket.x + rocket.w/2 >= plane.x && rocket.x + rocket.w/2 <= plane.x + plane.w
    &&  rocket.y + 4*rocket.h/5 >= plane.y && rocket.y + 4*rocket.h/5 <= plane.y + plane.h) return true;
    else
    if (rocket.x + rocket.w/2 >= plane.x && rocket.x + rocket.w/2 <= plane.x + plane.w
    &&  rocket.y >= plane.y && rocket.y <= plane.y + plane.h ) return true;
    else return false;
}
bool action_main ( SDL_Event e, SDL_Rect &text, SDL_Rect &mouse)
{
    if (mouse.x >= text.x && mouse.x <= text.x + text.w
     && mouse.y >= text.y && mouse.y <= text.y + text.h )
     return true;
    return false;
}

