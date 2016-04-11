#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#if 0
#define LOG(format, args...);   \
    {                           \
        int x,y;                \
        getyx(stdscr,x,y);      \
        move(1,1);              \
        printf(format, ##args); \
        move(x,y);              \
    }
#else
#define LOG(format,args...); 
#endif

//#define FALSE 0
//#define TRUE  1

typedef int DIRECT;

typedef struct xy{
	int x;
	int y;
}xy_t;

xy_t xy_food;
typedef struct snake_body{
	xy_t xy_snake;
	struct snake_body *next;
    struct snake_body *pre;	
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

static char globalDir=up;


snake_body_t *snake_head=NULL;

void gamewindow_init(int x,int y);
snake_body_t *snake_init();
int foodcreat(void);
snake_body_t *snake_tail(snake_body_t *snake_head);
int getkeyvalue();
void log(const char *msg);
void snake_show(snake_body_t *snake_head,char globalDir);
int snake_add(snake_body_t *snake_head);
void snake_free(snake_body_t *snake_head);
int snake_rule(snake_body_t *snake_head,xy_t windows);


int main()
{
    const int WIDTH = COLS-2;
    const int HIGHT = LINES-2;
    int keyvalue;
    xy_t store_xy;
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
    foodcreat();
    mvaddch(xy_food.y,xy_food.x,'#');
    while(1){
        clear();		
        getyx(stdscr,store_xy.y,store_xy.x);
        mvaddch(xy_food.y,xy_food.x,'#');
        box(stdscr,'|','-'); 
        snake_show(snake_head,globalDir);
        keyvalue=getkeyvalue();
		refresh();
        //printf("keyvalue=%x\n",keyvalue);
        if(TRUE==snake_add(snake_head)){
            foodcreat();
        }
        usleep(100);
    }
    return 0;
	
}

void gamewindow_init(int x,int y)
{
    initscr();
    keypad(stdscr,TRUE);
    noecho();
    refresh();
    box(stdscr,'|','-'); 
    refresh();
}
int getkeyvalue()
{
    //char ch;
    globalDir=getch();
    switch(globalDir){
    case 2:
        globalDir=up;
		//printf("globalDir:%d\n",globalDir);
        break;
    case 4:
        globalDir=down;
		//printf("globalDir:%d\n",globalDir);
        break;
    case 3:
        globalDir=right;
		//printf("globalDir:%d\n",globalDir);
        break;
    case 1:
        globalDir=left;
		//printf("globalDir:%d\n",globalDir);
        break;
	case '2':
        globalDir=up;
        break;
    case '3':
        globalDir=down;
        break;
    case '4':
        globalDir=right;
        break;
    case '5':
        globalDir=left;
        break;
    case 27:
        snake_free(snake_head);
        endwin();
        exit(1);
        break;
    default:
        printf("error direction!\n");
		//printf("globalDir:%d\n",KEY_UP);
		
        break;
    }
	return 0;	
}
void log(const char *msg)
{
    int x,y;
    getyx(stdscr,x,y);
    move(1,1);
    printf("[info:%s]",msg);
    move(x,y);

    return;

}
int foodcreat(void)
{
	do{
        xy_food.x=(int)(rand()*1.0/RAND_MAX*COLS);
		xy_food.y=(int)(rand()*1.0/RAND_MAX*LINES);
        //printf("xy.x=%d,xy.y=%d!\n",LINES,COLS);
     }while(!(xy_food.x>3&&xy_food.y>1&&xy_food.y<LINES&&xy_food.x<COLS));
    

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
		snake_head->pre=NULL;
		snake1->pre=snake_head;
		snake2->pre=snake1;
		do{
            snake_xy.x=(int)(rand()*1.0/RAND_MAX*COLS);
		    snake_xy.y=(int)(rand()*1.0/RAND_MAX*LINES);
            //printf("xy.x=%d,xy.y=%d!\n",LINES,COLS);
        }while(!(snake_xy.x>3&&snake_xy.y>1&&snake_xy.y<LINES&&snake_xy.x<COLS));
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



void snake_show(snake_body_t *snake_head,char globalDir)
{
    snake_body_t * tmp=NULL;
    snake_body_t * tmptail=NULL;
    tmp=snake_head;
	char i=0;
    tmptail=snake_tail(snake_head);
	
	while(tmptail->pre!=NULL){
		tmptail->xy_snake.x=tmptail->pre->xy_snake.x;
		tmptail->xy_snake.y=tmptail->pre->xy_snake.y;
		tmptail=tmptail->pre;
	}
    switch(globalDir){
    case up:
        tmp->xy_snake.y=tmp->xy_snake.y-1;
        LOG("up y=%d",tmp->xy_snake.y);
		break;
	case down:	
    	tmp->xy_snake.y=tmp->xy_snake.y+1;
        LOG("down y=%d",tmp->xy_snake.y);
		break;
	case right:	
    	tmp->xy_snake.x=tmp->xy_snake.x+1;
        LOG("right x=%d",tmp->xy_snake.x);
		break;
	case left:	
    	tmp->xy_snake.x=tmp->xy_snake.x-1;
        LOG("left x=%d",tmp->xy_snake.x);
		break;
	default:
		printf("error dir!\r");
		break;
    }
    for(;tmp!=NULL;tmp=tmp->next){
        mvaddch(tmp->xy_snake.y,tmp->xy_snake.x,'*');   
    }
	
    return ;

}
int snake_add(snake_body_t * snake_head)
{
	int x,y;
    snake_body_t *tmp=NULL;
	snake_body_t* snakeTail=snake_tail(snake_head);
	x=snake_head->xy_snake.x;
	y=snake_head->xy_snake.y;
	switch(globalDir){
        case up:
            if((snake_head->xy_snake.y-1==xy_food.y)&&(snake_head->xy_snake.x==xy_food.x)){
                tmp=(snake_body_t *)malloc(sizeof(snake_body_t));
                tmp->next=snake_head;
                tmp->xy_snake.y=xy_food.y;
                tmp->xy_snake.x=xy_food.x;
                snake_head->pre=tmp;
                snake_head=tmp;
                snake_head->pre=NULL;
            }
            else{
                return FALSE;
            }
            break;
        case down:
            if((snake_head->xy_snake.y+1==xy_food.y)&&(snake_head->xy_snake.x==xy_food.x)){
                tmp=(snake_body_t *)malloc(sizeof(snake_body_t));
                tmp->next=snake_head;
                tmp->xy_snake.y=xy_food.y;
                tmp->xy_snake.x=xy_food.x;
                snake_head->pre=tmp;
                snake_head=tmp;
                snake_head->pre=NULL;
            }   
            else{
                return FALSE;              
            }
            break;
        case right:
            if((snake_head->xy_snake.x+1==xy_food.y)&&(snake_head->xy_snake.y==xy_food.y)){
                tmp=(snake_body_t *)malloc(sizeof(snake_body_t));
                tmp->next=snake_head;
                tmp->xy_snake.y=xy_food.y;
                tmp->xy_snake.x=xy_food.x;
                snake_head->pre=tmp;
                snake_head=tmp;
                snake_head->pre=NULL;
            }
            else{
                return FALSE;              
            }
            break;
        case left:
            if((snake_head->xy_snake.x+1==xy_food.x)&&(snake_head->xy_snake.y==xy_food.y)){
                tmp=(snake_body_t *)malloc(sizeof(snake_body_t));
                tmp->next=snake_head;
                tmp->xy_snake.y=xy_food.y;
                tmp->xy_snake.x=xy_food.x;
                snake_head->pre=tmp;
                snake_head=tmp;
                snake_head->pre=NULL;
            }
            else{
                return FALSE;              
            }
            break;
        default:
            printf("operation error!\n");
            return FALSE;
            break;
    }
	return TRUE;
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

