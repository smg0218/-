#include<stdio.h>
#include<stdlib.h>

int count, Round = 0;
int checking = 1;
int i, j = 0;

typedef struct _prize {
	int round, group1, group2, w_number1, w_number2, w_number3, w_number4, w_number5, w_number6,
		w_number7, w_number8, w_number9;
	struct _prize *Next;
}prize;

void Title(void);
void addPrize(prize *first, int addRound, int addGroup1, int addGroup2, int addW_Number1, int addW_Number2,
	int addW_Number3, int addW_Number4, int addW_Number5, int addW_Number6, int addW_Number7,
	int addW_Number8, int addW_Number9);
void N_data(void);
void S_First(prize *first, int Count);
void S_Third(prize *first, int Count);
int Checking(int p_check);
int PrizeCheck(prize *first, int Round);
int S_Check(prize *first, int round);
void W_Check(prize *CountPrize, int C_Group, int C_Number);
void deletePrize(prize *first, int Round);
void printAll(prize *first);
void freeAll(prize *first);

int main(void)
{
	FILE *fin;
	FILE *fout;
	int select = 0;
	int Group[2] = { 0 };
	int W_Number[9] = { 0 };
	int W_Group[2] = { 0 };
	int w_count, n_count = 0;
	int check = 0;

	Title(); 

	prize *head = malloc(sizeof(prize));
	prize *countPrize = head;

	head->Next = NULL;

	fin = fopen("연금복권 당첨번호.dll", "r+b");

	if (fin == NULL)
	{
		printf("파일이 없으므로 파일을 생성합니다.\n");

		fout = fopen("연금복권 당첨번호.dll", "w+b");
		fprintf(fout, "%d \n", j);

		fclose(fout);

		printf("파일이 생성되었습니다. 파일을 엽니다.\n");
		fin = fopen("연금복권 당첨번호.dll", "r+b");
	}	else {
		printf("저장된 당첨번호 목록을 가져옵니다.\n");
	}

	fscanf(fin, "%d", &count);

	for (i = 0; i < count; i++)	{
		fscanf(fin, "%d %d %d", &Round, &Group[0], &Group[1]);
		for (j = 0; j < 9; j++)	{
			fscanf(fin, "%d", &W_Number[j]);
		}
		addPrize(head, Round, Group[0], Group[1], W_Number[0], W_Number[1], W_Number[2], W_Number[3],
			W_Number[4], W_Number[5], W_Number[6], W_Number[7], W_Number[8]);
	}

	fclose(fin);

	while (1) {
		countPrize = head;

		printf("선택해주세요(1.당첨확인 2.당첨번호 추가 3.당첨번호 삭제 4.당첨번호 목록 5.종료) ");
		scanf("%d", &select);

		switch (select)	{
		case 1:
			if (count == 0)	{
				N_data();
				break;
			}

			S_First(head, count);
				
			break;
		
		case 2:
			checking = 1;

			while (checking) {
				printf("회차를 입력해주세요. ");
				scanf("%d", &Round);

				checking = Checking(Round);

				if (checking == 1)
					printf("양수만을 입력해주세요.\n");
			}

			check = S_Check(head, Round);

			if (check == 1) {
				printf("이미 같은 회차가 입력되어 있습니다.\n");
				break;
			}
			
			for (i = 0; i < 2; i++) {
				printf("%d번째 1등 조를 입력해주세요. ", i + 1);
				scanf("%d", &W_Group[i]);
				if (W_Group[i] < 1 || W_Group[i]>9)
				{
					printf("1~9사이의 숫자만을 입력해주세요.\n");
					i--;
				}
			}
			for (i = 0; i < 6; i++) {
				if (i < 1) {
					for (j = 0; j < 2; j++) {
						printf("%d번째 1등 번호를 입력해주세요. ", n_count + 1);
						scanf("%d", &W_Number[n_count]);

						if (W_Number[n_count] < 100000 || W_Number[n_count]>999999)
						{
							printf("100000~999999사이의 숫자만을 입력해주세요.\n");
							n_count--;
							j--;
						}
						n_count++;
					}
				}
				else if (i > 3) {
					w_count = i + 2;
					for (j = i; j < i + 2; j++)	{
						printf("%d등 번호를 입력해주세요. ", w_count);
						scanf("%d", &W_Number[n_count]);
						if (w_count == 6) {
							if (W_Number[n_count] < 10 || W_Number[n_count]>99) {
								printf("10~99사이의 숫자만을 입력해주세요.\n");
								n_count--;
								j--;
							}
						}	else if (w_count == 7) {
							if (W_Number[n_count] < 0 || W_Number[n_count]>9) {
								printf("1~9사이의 숫자만을 입력해주세요.\n");
								n_count--;
								j--;
							}
						}
						n_count++;
					}
				}
				else {

					printf("%d등 번호를 입력해주세요. ", i + 2);
					scanf("%d", &W_Number[n_count]);
					if (i == 1) {
						if (W_Number[n_count] < 100000 || W_Number[n_count]>999999)	{
							printf("100000~999999사이의 숫자만을 입력해주세요.\n");
							n_count--;
							i--;
						}
					}
					else if (i == 2) {
						if (W_Number[n_count] < 10000 || W_Number[n_count]>99999) {
							printf("10000~99999사이의 숫자만을 입력해주세요.\n");
							n_count--;
							i--;
						}
					}	else if (i == 3) {
						if (W_Number[n_count] < 100 || W_Number[n_count]>999) {
							printf("100~999사이의 숫자만을 입력해주세요.\n");
							n_count--;
							i--;
						}
					}
					n_count++;
				}
			}
			printf("추가중입니다.\n");

			addPrize(head, Round, W_Group[0], W_Group[1], W_Number[0], W_Number[1], W_Number[2], W_Number[3],
				W_Number[4], W_Number[5], W_Number[6], W_Number[7], W_Number[8]);
			count++;

			printf("추가되었습니다.\n");
			
			break;

		case 3:
			if (count == 0) {
				N_data();
				break;
			}

			S_Third(head, count);

			break;

		case 4:
			if (count == 0) {
				N_data();
				break;
			}	else {

				printAll(head);
			}

			break;

		case 5:
			printf("프로그램을 종료중입니다.\n");
			countPrize = head->Next;
			fout = fopen("연금복권 당첨번호.dll", "w+b");
			fprintf(fout, "%d \n", count);
			while (countPrize != NULL) {

				fprintf(fout, "%d %d %d %d %d %d %d %d %d %d %d %d \n", countPrize->round, countPrize->group1, countPrize->group2,
					countPrize->w_number1, countPrize->w_number2, countPrize->w_number3, countPrize->w_number4, countPrize->w_number5,
					countPrize->w_number6, countPrize->w_number7, countPrize->w_number8, countPrize->w_number9);

				countPrize = countPrize->Next;
			}
			fclose(fout);
			freeAll(head);
			printf("프로그램을 종료합니다.\n");
			system("pause");
			return 0;

		default:
			printf("1~5사이의 정수만을 입력해 주세요.\n");
		}
		select = 0;
		check = 0;
		printf("\n");
	}
}

void Title(void) {
	printf("===============================\n");
	printf("= 연금복권 당첨 확인 프로그램 =\n");
	printf("===============================\n");
	printf("제작자 : 3학년 8반 18번 송민건\n\n");
}

void addPrize(prize *first, int addRound, int addGroup1, int addGroup2, int addW_Number1, int addW_Number2,
	int addW_Number3, int addW_Number4, int addW_Number5, int addW_Number6, int addW_Number7,
	int addW_Number8, int addW_Number9)	{
	prize *addPrize = malloc(sizeof(prize));
	prize *Count = first;

	addPrize->round = addRound;
	addPrize->group1 = addGroup1;
	addPrize->group2 = addGroup2;
	addPrize->w_number1 = addW_Number1;
	addPrize->w_number2 = addW_Number2;
	addPrize->w_number3 = addW_Number3;
	addPrize->w_number4 = addW_Number4;
	addPrize->w_number5 = addW_Number5;
	addPrize->w_number6 = addW_Number6;
	addPrize->w_number7 = addW_Number7;
	addPrize->w_number8 = addW_Number8;
	addPrize->w_number9 = addW_Number9;

	addPrize->Next = NULL;

	while (Count->Next != NULL)	{
		Count = Count->Next;
	}

	Count->Next = addPrize;
}

void N_data(void) {
	printf("데이터가 없습니다.\n");
}

void S_First(prize *first, int Count) {
	int check, c_Group, Number = 0;
	int i = 0;

	while (checking) {
		printf("회차를 입력해주세요. ");
		scanf("%d", &Round);

		checking = Checking(Round);

		if (checking == 1)
			printf("양수만을 입력해주세요.\n");
	}

	check = PrizeCheck(first, Round);

	if (check == Count) {
		printf("해당 회차가 없습니다.\n");
		return 0;
	}

	checking = 1;

	while (checking) {
		printf("조를 입력해주세요. ");
		scanf("%d", &c_Group);

		if (c_Group < 1 || c_Group > 9) {
			printf("1~9사이의 숫자만을 입력해주세요.\n");
		}
		else
			checking = 0;
	}

	checking = 1;

	while (checking) {
		printf("번호를 입력해주세요. ");
		scanf("%d", &Number);

		if (Number < 100000 || Number>999999) {
			printf("100000~999999사이의 숫자만을 입력해주세요.\n");
		}
		else
			checking = 0;
	}


	printf("확인중...\n");

	for (i = 0; i <= check; i++) {
		first = first->Next;
	}

	W_Check(first, c_Group, Number);

	return 0;
}

void S_Third(prize *first, int Count) {
	int Check = 0;

	checking = 1;

	while (checking) {
		printf("삭제할 회차를 입력해주세요. ");
		scanf("%d", &Round);

		checking = Checking(Round);

		if (checking == 1)
			printf("양수만을 입력해주세요.\n");
	}

	Check = PrizeCheck(first, Round);

	if (Check == Count) {
		printf("해당 회차가 없습니다.\n");
		return 0;
	}

	printf("삭제중입니다.\n");

	deletePrize(first, Round);
	count--;

	printf("삭제되었습니다.\n");
}

int Checking(int check) {
	if (check < 1)
		return 1;
	else
		return 0;
}

int PrizeCheck(prize *first, int Round) {
	prize *countPrize = first;
	int P_Count = 0;

	while (countPrize->Next != NULL) {
		if (countPrize->Next->round == Round)
			return P_Count;
		countPrize = countPrize->Next;
		P_Count++;
	}
	if (countPrize->Next == NULL) {
		return P_Count;
	}
}

int S_Check(prize *first, int round) {
	while (first != NULL) {
		if (round == first->round) {
			return 1;
		}
		first = first->Next;
	}
}

void W_Check(prize *CountPrize, int C_Group, int C_Number) {
	int f_count = 0;
	int remainder = C_Number;

	if (C_Group == CountPrize->group1 && C_Number == CountPrize->w_number1)
		printf("1등 입니다.\n");
	else
		f_count++;
	if (C_Group == CountPrize->group2 && C_Number == CountPrize->w_number2)
		printf("1등 입니다.\n");
	else
		f_count++;
	if (C_Group == CountPrize->group1 && C_Number == CountPrize->w_number1 - 1)
		printf("2등 입니다.\n");
	else
		f_count++;
	if (C_Group == CountPrize->group1 && C_Number == CountPrize->w_number1 + 1)
		printf("2등 입니다.\n");
	else
		f_count++;
	if (C_Group == CountPrize->group2 && C_Number == CountPrize->w_number2 - 1)
		printf("2등 입니다.\n");
	else
		f_count++;
	if (C_Group == CountPrize->group2 && C_Number == CountPrize->w_number2 + 1)
		printf("2등 입니다.\n");
	else
		f_count++;
	if (C_Number == CountPrize->w_number3)
		printf("3등 입니다.\n");
	else
		f_count++;
	remainder = remainder % 100000;
	if (remainder == CountPrize->w_number4)
		printf("4등 입니다.\n");
	else
		f_count++;
	remainder = remainder % 1000;
	if (remainder == CountPrize->w_number5)
		printf("5등 입니다.\n");
	else
		f_count++;
	remainder = remainder % 100;
	if (remainder == CountPrize->w_number6)
		printf("6등 입니다.\n");
	else
		f_count++;
	if (remainder == CountPrize->w_number7)
		printf("6등 입니다.\n");
	else
		f_count++;
	remainder = remainder % 10;
	if (remainder == CountPrize->w_number8)
		printf("7등 입니다.\n");
	else
		f_count++;
	if (remainder == CountPrize->w_number9)
		printf("7등 입니다.\n");
	else
		f_count++;

	if (f_count == 13)
		printf("꽝입니다.\n");
}

void deletePrize(prize *first, int Round) {
	prize *Count = first;
	prize *deleteData = Count->Next;

	while (deleteData->round != Round)	{
		Count = deleteData;
		deleteData = deleteData->Next;
	}

	Count->Next = deleteData->Next;
	free(deleteData);
}

void printAll(prize * first) {
	prize *printing = first->Next;

	printf("당첨번호 목록을 출력합니다.\n");
	printf("\n");

	while (printing != NULL)
	{
		printf("%d회차 정보 : 1등 %d조 %d, %d조 %d 3등 %d 4등 %d 5등 %d 6등 %d, %d 7등 %d, %d\n", printing->round, printing->group1,
			printing->w_number1, printing->group2, printing->w_number2, printing->w_number3, printing->w_number4,
			printing->w_number5, printing->w_number6, printing->w_number7, printing->w_number8, printing->w_number9);
		printing = printing->Next;
	}
}

void freeAll(prize *first) {
	prize *Count;
	prize *deleteData = first;

	while (deleteData != NULL)	{
		Count = deleteData->Next;
		free(deleteData);
		deleteData = Count;
	}
}
