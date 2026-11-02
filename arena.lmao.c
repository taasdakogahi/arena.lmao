#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//general
#define HP_MULTIPLIER 5
#define ATK_MULTIPLIER 3
//mobs
#define BASE_MOB_HP 30
#define BASE_MOB_ATK 7
//player
#define BASE_PLAYER_HP 60
#define BASE_PLAYER_ATK 15
#define BASE_PLAYER_HEAL 10
#define LVL_PROGRESSION 5

int menu_active = 1;

int mob_level = 1;

int main_menu();
int engine();

int main()
{
    srand(time(NULL));
    while(menu_active){
        if(main_menu() == 1){
            while(1){
                if(engine() ==0){
                    break;
                }
            }
        }
    }
    return 0;
}


int main_menu(){
    char choice;
        printf("\033[2J\033[H");
        printf("<--ARENA-->\n");
        printf("By carlpogi\n\n");
        printf("Main Menu\n");
        printf("Press W to start the game...\n");
        printf("Press Q to quit.\n");
        scanf(" %c", &choice);
        switch(choice){
            case 'w':
            case 'W':
                printf("\033[2J\033[H");
                while(getchar() != '\n');
                return 1;
                break;
            case 'q':
            case 'Q':
                printf("Exited the game.\n");
                menu_active = 0;
                return 0;
                break;
            default:
                printf("Invalid Input\n");
                printf("\033[2J\033[H");
                while(getchar() != '\n');
                return 2;
                break;
        }
}

int engine(){
    //state
    int stage = 1;
    int mob_alive = 1;
    int player_alive = 1;
    int progress_counter = 0;
    int choice;
    //player
    int player_lvl = 1;
    int player_atk = BASE_PLAYER_ATK;
    int player_hp = BASE_PLAYER_HP;
    int max_player_hp = player_hp;
    int player_heal = BASE_PLAYER_HEAL;
    //mob
    mob_level = stage;
    int mob_hp = BASE_MOB_HP;
    int max_mob_hp = mob_hp;
    int mob_atk;
    while(player_alive){
        if(mob_alive){
            printf("Monster lvl %d\n", mob_level);
            printf("HP: %d/%d\n", mob_hp, max_mob_hp);
            printf("\n\n");
            printf("You lvl %d\n", player_lvl);
            printf("HP: %d/%d\n", player_hp, max_player_hp);
            printf("1. Attack) 2. Heal) 3. Main Menu)\n");
            printf("Select: ");
            while(scanf("%d", &choice) != 1){
                printf("Can't you read? Stupid.");
                usleep(800000);
                while(getchar() != '\n');
                printf("\033[2K");
            }
            switch(choice){
                case 1: //Attack
                    mob_hp -= player_atk;
                    printf("\033[2J\033[H");
                    if(mob_hp <= 0){
                        mob_alive = 0;
                    }
                    break;
                case 2: //heal
                    player_hp += BASE_PLAYER_HEAL;
                    if(player_hp >= max_player_hp){
                        player_hp == max_player_hp;
                        printf("HP already full");
                    }
                    break;
                case 3: //quit
                    return 0;
            }
                
        } else {
            stage++;
            mob_level++;
            progress_counter++;
            max_mob_hp = BASE_MOB_HP + mob_level + HP_MULTIPLIER;
            mob_hp = max_mob_hp;
            mob_alive = 1;
            printf("Monster Killed\n");
            printf("\033[2J\033[H");
        }
        //mob turn
        if(mob_alive){
            mob_atk = rand() % BASE_MOB_ATK + mob_level;
            player_hp -= mob_atk;
            printf("Monster's turn\n\n\n\n");
            printf("Attack!\n");
            printf("You took -%d damage\n", mob_atk);
            usleep(1500000);
            if(player_hp <= 0){
                player_alive = 0;
                printf("LOL U SUCK\n");
                usleep(2000000);
                printf("I FUCKED YOUR MOM IN THE ASS LAST NIGHT.\n");
                printf("YOU WILL NEVER SUCCEED IN LIFE LOSER\n");
                usleep(3000000);
                return 0;
            }
            printf("\033[2J\033[H");
        }
        if(progress_counter == LVL_PROGRESSION){
            max_player_hp += HP_MULTIPLIER;
            player_atk += ATK_MULTIPLIER;
            player_heal + 3;
            player_lvl++;
            progress_counter = 0;
            printf("You Leveled Up!\n");
            usleep(1000000);
        }
    }
}