#include <stdio.h>
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
}



int main()
{
	
	
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

void snake_show(snake_body *snake_init)
{


}
void snake_add(snake_body* snake_head,food_xy* food_xy,direct*snake_dir,direct*keyboard_dir)
{
	int x,y;
	snake_body* snake_tail=snake_tail(snake_head);
	x=snake_head->xy_snake.x;
	y=sanke_head->xy_snake.y;
	if(food_xy.x==x&&food_xy.y==y){
		if(*snakeidr=*keyborad_dir){
			
		}
	}
	
}

