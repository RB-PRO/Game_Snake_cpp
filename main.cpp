#define x_max 10 // ������� ����
#define y_max 10 // ������� ����
#include <iostream>
#include <thread> // sleep
#include <conio.h>
using namespace std::chrono_literals;

struct cases { // ��������� ����
	bool isApple = 0;
	bool isSnakeBody = 0;
};

typedef struct snake{ // ������ ����
	struct snake* next;
	int x, y;
} snake;

void lose(int point) { // ��� �� ������ ���������.
	printf("Lose!\nTou store: %d\n",point);
}

int getRandomTo10(int a, int b) {
	return rand() % 9; // �������� ����� �� 0 �� 9 ������������
}

void push(snake** head, int x,int y) { // �������� � ������
	snake* tmp = (snake*)malloc(sizeof(snake));
	tmp->x = x;
	tmp->y = y;
	tmp->next = (*head);
	(*head) = tmp;
}

snake* getLast(snake* head) { // �������� ��������
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

int GetTwo(snake** head) { // �������� 2-� �������
	//�������� NULL
	if (!head) {
		return(-1);
	}
	//������ ����
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
	//�������� NULL
	if (!head) {
		exit(-1);
	}
	//������ ����
	if (!(*head)) {
		exit(-1);
	}
	lastbn = getLastButOne(*head);
	//���� � ������ ���� �������
	if (lastbn == NULL) {
		free(*head);
		*head = NULL;
	} else {
		free(lastbn->next);
		lastbn->next = NULL;
	}
}

int main() {
	system("color F0");  // ��������� ������ ���� � ������� ������
	struct cases c[10][10];
	int x = 4, y = 4, rot = 0,tecalrow=0,point=1;
	int vspom, vspom1;
	/* �������� ���������� ����������� ������ ��������� ���������� ������ � � �����
		** rot:
			0
		3		1
			2

		** x and y:
		���������� ������
	*/
	snake* head = NULL;
	push(&head, 4, 4); // ����� ����� ���� �����
	c[y][x].isSnakeBody = true; // ������
	c[y-3][x].isApple = true; // �������� ������
	while (true) { // � ���� ����������� ����� ����� ����� ������
		// ������ ����
		switch (rot) {
		case(0):
			y--; // ����������� ������ �����
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

		// ��������� �������� ���� � �����
		if ((x>9||x<0)|| (y > 9 || y < 0)|| c[y][x].isSnakeBody) {
			lose(point);
			break;
		}

		push(&head,x,y); // ��������� ��� ����� �����
		c[y][x].isSnakeBody = true; // � ������ � ����
		// �������� ������ ��������� � �������� �� ����
		c[getLast(head)->y][getLast(head)->x].isSnakeBody = false; // �������� �� ���� ���� ����
		if (!(c[y][x].isApple)) { // ��������� ��������� ������
			popBack(&head); // ������� ��������� �������
		} else { // ��� ���� ���� ������
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

		// ���������
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

		// ��������� ����������
		//Sleep(2000); // ����� 5 ������, ����� ��� ������� ������� � �������� ����� �������
		for (int i=0;i<250;i++) {
			if (_kbhit()){ // ��������� ������� �� �����
				// ��� ����� ����������� ������ ������ �������� ������ � �������� ��� � ���
				vspom = GetTwo(&head);
				switch (_getch()){ // ��� ������� �� ����� ��� Enter ����� �����
				case 72: //�����
					if(tecalrow!=2)
						rot = 0;
					break;
				case 80: //����
					if (tecalrow != 0)
						rot = 2;
					break;
				case 75: //����� 
					if (tecalrow != 1)
						rot = 3;
					break;
				case 77: //������
					if (tecalrow != 3)
						rot = 1;
					break;
				}
				tecalrow = rot;
			}
			std::this_thread::sleep_for(1ms);
		}
		// cin >> rot; // ���������� ���������		
		system("cls"); // �������� �������
	}
	return 0;
}