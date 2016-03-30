#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

typedef int DIRECT;

typedef struct xy{
	int x;
	int y;
}xy_t;

typedef struct food_xy{
	xy_t xy_food;
}food_xy_t;
typedef struct snake_body{
	xy_t xy_snake;
	struct snake_body *next;	
}snake_body_t;

enum direction{
	up=1,
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


snake_body_t *snake_head=NULL;

void gamewindow_init(int x,int y);
snake_body_t *snake_init();
snake_body_t *snake_tail(snake_body_t *snake_head);
int getkeyvalue();
void snake_show(snake_body_t *snake_head);
int snake_add(snake_body_t *snake_head,food_xy_t *food_xy,DIRECT *snake_dir,DIRECT *keyboard_dir);
void snake_free(snake_body_t *snake_head);
int snake_rule(snake_body_t *snake_head,xy_t windows);


int main()
{
    const int WIDTH = COLS-2;
    const int HIGHT = LINES-2;
    int keyvalue;
    
    gamewindow_init(20,20);
    snake_head=snake_init();
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_GREEN);
    attron(COLOR_PAIR(1));
    //mvaddch(HIGHT+10,WIDTH+10,'z');
    //addstr("zhanglei");
    //mvaddstr(HIGHT+11,WIDTH+11,"zhanglei");
    attroff(COLOR_PAIR(1));
    refresh();
    while(1){
        snake_show(snake_head);
        refresh();
        keyvalue=getkeyvalue();
        printf("keyvalue=%d\n",keyvalue);
        sleep(2);
    }
    return 0;
	
}

void gamewindow_init(int x,int y)
{
    initscr();
    refresh();
    box(stdscr,'|','-'); 
    refresh();
}

snake_body_t *snake_init()
{
	snake_body_t *snake_head,*snake1,*snake2;
	xy_t snake_xy;

	srand((int)time(0));
	snake_head=(snake_body_t *)malloc(sizeof(snake_body_t));
	snake1=(snake_body_t*)malloc(sizeof(snake_body_t));
	snake2=(snake_body_t*)malloc(sizeof(snake_body_t));
	if((snake_head!=NULL)&&(snake1!=NULL)&&(snake2!=NULL)){
		snake_head->next=snake1;
		snake1->next=snake2;
		snake2->next=NULL;
		do{
            snake_xy.x=(int)(rand()*1.0/RAND_MAX*COLS);
		    snake_xy.y=(int)(rand()*1.0/RAND_MAX*LINES);
            //printf("xy.x=%d,xy.y=%d!\n",LINES,COLS);
        }while(!(snake_xy.x>3&&snake_xy.y>3));
		snake_head->xy_snake.x=snake_xy.x;
		snake_head->xy_snake.y=snake_xy.y;
		snake1->xy_snake.x=snake_xy.x-1;
		snake1->xy_snake.y=snake_xy.y;
		snake2->xy_snake.x=snake_xy.x-2;
		snake2->xy_snake.y=snake_xy.y;
	}else{
		printf("snake_init error!\n");
		return NULL;
	}	
	return snake_head;

}
snake_body_t *snake_tail(snake_body_t *snake_head)
{
	snake_body_t *snake_tail=NULL;
	if(snake_head!=NULL){
		snake_tail=snake_head->next;
		while(snake_tail->next!=NULL){
			snake_tail=snake_tail->next;
		}
	}else{
		return NULL;
	}
	return snake_tail;

}

int getkeyvalue()
{
    char ch;
    ch=getch();
    switch(ch){
    case KEY_UP:
        return up;
    case KEY_DOWN:
        return down;
    case KEY_RIGHT:
        return right;
    case KEY_LEFT:
        return left;
    case 27:
        snake_free(snake_head);
        endwin();
        exit(1);
    default:
        printf("ch=%d\n",ch);
        return ch;
    }
	return 0;	
}

void snake_show(snake_body_t *snake_head)
{
    snake_body_t * tmp=NULL;
    tmp=snake_head;
    for(;tmp!=NULL;tmp=tmp->next){
        mvaddch(tmp->xy_snake.y,tmp->xy_snake.x,'*');
        //refresh();
    }
    return ;

}
int snake_add(snake_body_t * snake_head,food_xy_t * food_xy,DIRECT *snake_dir,DIRECT *keyboard_dir)
{
	int x,y;
	snake_body_t* snakeTail=snake_tail(snake_head);
	x=snake_head->xy_snake.x;
	y=snake_head->xy_snake.y;
	if(*snake_dir!=-*keyboard_dir){
	    x=x+dir[*keyboard_dir][0];
        y=y+dir[*keyboard_dir][1];	
	}else{
        printf("operation error!\n");
        return -1;
    }
	return 0;
}

void snake_free(snake_body_t * snake_head)
{
    snake_body_t *tmp=NULL;
    snake_body_t  *free_tmp=NULL;
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
int snake_rule(snake_body_t * snake_head,xy_t windows)
{
    int x,y;
    snake_body_t* tmp=NULL;
    x=snake_head->xy_snake.x;
    y=snake_head->xy_snake.y;
    if(x<0||y<0||x>windows.x||y>windows.y){
        printf("game over!\n");
        return -1;
    }
    tmp=snake_head->next;
    for(;tmp!=NULL;tmp=tmp->next){
        if(x==tmp->xy_snake.x&&y==tmp->xy_snake.y){
            printf("break rule!\n");
            return -1;
        }
    }
    return 0;
}

