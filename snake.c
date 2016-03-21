#include <stdio.h>
#include <curses.h>


typedef struct xy{
	int x;
	int y;
}xy;

typedef struct food_xy{
	xy xy_food;
}food_xy;
typedef struct snake_body{
	xy xy_snake;
	snake_body *next;	
}snake_body;

enum direction{
	up=0,
	down,
	left,
	right,
};
static dir[4][2]={
    {1,0},
    {-1,0},
    {0,1},
    {0,-1},
};

void gamewindow_init(int x,int y);
snake_body *snake_init();
snake_body *snake_tail(snake_body *snake_head);
int getkeyvalue();
void snake_show(snake_body *snake_head);
int snake_add(snake_body* snake_head,food_xy* food_xy,direct*snake_dir,direct*keyboard_dir);
void snake_free(snake_body* snake_head);
int snake_rule(snake_body* snake_head,xy windows);


int main()
{
    snake_body *snake_head=snake_init();
    gamewindow_init(20,20);
    mvaddch(10,10,'z');
    mvaddstr(10,11,"zhanglei");
    sleep(20000);
    endwin();
    snake_free(snake_head);
    return 0;
	
}

void gamewindow_init(int x,int y)
{
    initscr();
    box(stdscr,x,y); 
}

snake_body *snake_init()
{
	snake_body* snake_head;
	xy snake_xy;

	srand((unsigned)time(NULL));
	
	snake_head=(snake_body*)malloc(sizeof(snake_body));
	snake1=(snake_body*)malloc(sizeof(snake_body));
	snake2=(snake_body*)malloc(sizeof(snake_body));
	if(snake0!==NULL&&snake1!=NULL&&snake2!=NULL){
		snake_head->next=snake1;
		snake1->next=snake2;
		snake2->next=NULL;
		do{
			snake_xy.x=rand();
			snake_xy.y=rand();
		}while(snake_xy.x>=3&&snake_xy.y>=3);
		snake_head->xy_snake.x=snake_xy.x;
		snake_head->xy_snake.y=sanke_xy.y;
		snake1->xy_snake.x=snake_xy.x-1;
		snake1->xy_snake.y=snake_xy.y-1;
		snake2->xy_snake.x=snake_xy.x-2;
		snake2->xy_snake.y=snake_xy.y-2;
	}else{
		printf("snake_init error!\n");
		return NULL;
	}	
	return snake_head;

}
snake_body *snake_tail(snake_body *snake_head)
{
	snake_body *snake_tail=NULL;
	if(snake_head!=NULL){
	{
		snake_tail=snake_head->next;
		while(snake_tail->next!=NULL){
			snake_tail=snake->next;
		}
	}else{
		return NULL;
	}
	return snake_tail;

}

int getkeyvalue()
{
	return 0;	
}

void snake_show(snake_body *snake_head)
{
    snake_body * tmp=NULL;
    tmp=snake_head;
    for(;tmp!=NULL;tmp=tmp->next){
        move(tmp->snake_xy.x,tmp->snake_xy.y);
    }
    return ;

}
int snake_add(snake_body* snake_head,food_xy* food_xy,direct*snake_dir,direct*keyboard_dir)
{
	int x,y;
	snake_body* snake_tail=snake_tail(snake_head);
	x=snake_head->xy_snake.x;
	y=sanke_head->xy_snake.y;
	if(*snakeidr!=-*keyborad_dir){
	    x=x+dir[*keyborad_dir][0];
        y=y+dir[*keyborad_dir][1];	
	}else{
        printf("operation error!\n");
        return -1;
    }
	return 0;
}

void snake_free(snake_body* snake_head)
{
    snake_body *tmp=NULL;
    snake_body *free_tmp=NULL;
    free_tmp=snake_head->next;
    tmp=free_tmp->next;
    while(tmp==NULL){
        free(free_tmp);
        free_tmp=tmp;    
        tmp=free_tmp->next;
    }
    free(free_tmp);
    return ;
}
int snake_rule(snake_body* snake_head,xy windows)
{
    int x,y;
    snake_body* tmp=NULL;
    x=snake_head->xy_snake.x;
    y=snake_head->xy_snake.y;
    if(x<0||y<0||x>windows.x||y>windows.y){
        printf("game over!\n");
        return -1;
    }
    tmp=snake_head->next;
    for(;tmp!=NULL;tmp=tmp->next){
        if(x==tmp->xy_snake.x&&y==tmp->snake.y){
            printf("break rule!\n");
            return -1;
        }
    }
    return 0;
}

