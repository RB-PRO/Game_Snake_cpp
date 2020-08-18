#define x_max 10 // Размеры поля
#define y_max 10 // Размеры поля
#include <iostream>
#include <thread> // sleep
#include <conio.h>
using namespace std::chrono_literals;

struct cases { // структура поля
	bool isApple = 0;
	bool isSnakeBody = 0;
};

typedef struct snake{ // Список змеи
	struct snake* next;
	int x, y;
} snake;

void lose(int point) { // Это на случай поражения.
	printf("Lose!\nTou store: %d\n",point);
}

int getRandomTo10(int a, int b) {
	return rand() % 9; // диапазон равен от 0 до 9 включительно
}

void push(snake** head, int x,int y) { // добавить в начало
	snake* tmp = (snake*)malloc(sizeof(snake));
	tmp->x = x;
	tmp->y = y;
	tmp->next = (*head);
	(*head) = tmp;
}

snake* getLast(snake* head) { // получить послений
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

snake* getLastButOne(snake* head) { 
	if (head == NULL) {
		exit(-2);
	}
	if (head->next == NULL) {
		return NULL;
	}
	while (head->next->next) {
		head = head->next;
	}
	return head;
}

int GetTwo(snake** head) { // Получить 2-й элемент
	//Получили NULL
	if (!head) {
		return(-1);
	}
	//Список пуст
	if (!(*head)) {
		return(-1);
	}
	if ((*head)->next==NULL) {
		return(-1);
	} else {
		return((*head)->next->x);
	}
}

void popBack(snake** head) {
	snake* lastbn = NULL;
	//Получили NULL
	if (!head) {
		exit(-1);
	}
	//Список пуст
	if (!(*head)) {
		exit(-1);
	}
	lastbn = getLastButOne(*head);
	//Если в списке один элемент
	if (lastbn == NULL) {
		free(*head);
		*head = NULL;
	} else {
		free(lastbn->next);
		lastbn->next = NULL;
	}
}

int main() {
	system("color F0");  // Установка белого фона и черного текста
	struct cases c[10][10];
	int x = 4, y = 4, rot = 0,tecalrow=0,point=1;
	int vspom, vspom1;
	/* Заданный изначально конграмират данных начальной координаты головы и её длина
		** rot:
			0
		3		1
			2

		** x and y:
		Координаты головы
	*/
	snake* head = NULL;
	push(&head, 4, 4); // Задаём башню этой зейке
	c[y][x].isSnakeBody = true; // Голова
	c[y-3][x].isApple = true; // тестовое яблоко
	while (true) { // В этом бесконечном цикле будем вести работы
		// Логика игры
		switch (rot) {
		case(0):
			y--; // перемещение именно такое
			break;
		case(1):
			x++;
			break;
		case(2):
			y++;
			break;
		case(3):
			x--;
			break;
		default:
			break;
		}

		// Обработка поедания себя и полей
		if ((x>9||x<0)|| (y > 9 || y < 0)|| c[y][x].isSnakeBody) {
			lose(point);
			break;
		}

		push(&head,x,y); // добавляем ему новое место
		c[y][x].isSnakeBody = true; // и вносим в базу
		// получить данные последние и обнулить на поле
		c[getLast(head)->y][getLast(head)->x].isSnakeBody = false; // Обнуляем на поле тело змея
		if (!(c[y][x].isApple)) { // обработка пожирания плодов
			popBack(&head); // Удаляем последний элемент
		} else { // Тут если съел яблоко
			c[y][x].isApple = false;
			while(1){
				vspom = rand() % (y_max - 1);
				vspom1 = rand() % (y_max - 1);
				if (!(c[vspom][vspom1].isSnakeBody)) {
					c[vspom][vspom1].isApple = true;
					break;
				}
			}
			point++;
		}

		// рендеринг
		for (int i = 0; i < y_max; i++) { 
			for (int j = 0; j < x_max; j++) {
				if (!(c[i][j].isApple) && !(c[i][j].isSnakeBody)) {
					printf("%c", 45);
				}
				if (c[i][j].isApple) {
					printf("%c", 65);
				}
				if (c[i][j].isSnakeBody) {
					printf("%c", 42);
				}
				printf("%c", 32);
			}
			printf("\n");
		}

		// обработка управления
		//Sleep(2000); // ждать 5 секунд, время эта функция считает в тысячных долях секунды
		for (int i=0;i<250;i++) {
			if (_kbhit()){ // слушатель нажатия на клаву
				// Тут нужно выхватывать именно второй элемента списка и рабоатть уже с ним
				vspom = GetTwo(&head);
				switch (_getch()){ // ждёт нажатия на клаву без Enter после этого
				case 72: //вверх
					if(tecalrow!=2)
						rot = 0;
					break;
				case 80: //вниз
					if (tecalrow != 0)
						rot = 2;
					break;
				case 75: //влево 
					if (tecalrow != 1)
						rot = 3;
					break;
				case 77: //вправо
					if (tecalrow != 3)
						rot = 1;
					break;
				}
				tecalrow = rot;
			}
			std::this_thread::sleep_for(1ms);
		}
		// cin >> rot; // отладочная обработка		
		system("cls"); // Отчистка консоли
	}
	return 0;
}