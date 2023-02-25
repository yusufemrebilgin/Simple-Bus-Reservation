#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<string.h>
void login(void);
void admin(void);
void user(void);
void trip(int);
void selectSeat(int,int);
int password(char[]);
void header(int,int,char[]);
void printCh219(int,int);

int busNumber[15] = {} , seat[15][40] = {} , lastSeat[15] = {};
float price[15] = {};
char passenger[15][40][30], from[15][15], to[15][15], departure[15][6], arrival[15][6];

int main(){
	
	system("COLOR E");
	login();
	
	return 0;
}

void login(){

	char ch;
	
	while(1){
		
		system("cls");
		header(20,1,"LOGIN");
		printf("\t\t \xDB\xBA User    [1] \n\n");
		printf("\t\t \xDB\xBA Admin   [2] \n\n");
		printf("\t\t \xDB\xBA Exit    [0] \n\n");
		
		ch = getch();
		if(ch=='1')
			user();
		if(ch=='2')
			admin();
		if(ch=='0'){
			system("cls");
			break;
		}

	}
	
}


void admin(){
	
	int temp;
	char ch, pw[9] = "admin";
	
	while(1){
		
		system("cls");
		header(20,0,"ADMIN");
		printf("\xDB\xB3 Password: ");
		if( password(pw)==1 ){
			
			while(1){
				
				system("cls");
				header(20,0,"ADMIN");
				printf("\t\t\xDB\xBA Add Trip  [1] \n\n");
				printf("\t\t\xDB\xBA Exit      [0] \n\n");
			
				ch = getch();
				if( ch=='1' )
					trip(0);	
				if( ch=='0' )
					break;
			}
			break;
		}
	}
		
}

void user(){
	
	char ch, pw[9] = "user123";
	
	while(1){
	
		header(20,0,"LOGIN");
		printf("\xDB\xB3 Password: ");
	
		if( password(pw)==1 ){
			
			while(1){
				system("cls");
				header(20,0,"MENU");
				printf("\t \xB3 Search Tickets        [1]\n");
				printf("\t \xB3 Search Trip           [2]\n\n");
				printf("\t \xB3 Exit                  [0]\n");
				
				ch = getch();
				if( ch=='1' )
					trip(1);
				if( ch=='2' )
					trip(2);
				if( ch=='0' )
					break;
			}
			break;
		}
	}
	
}

void trip(int select){
	
	static int i;
	int j, k;
	char ch;

	if( select==0 ){
	
		system("cls");
		printf("\xDB\xBA Please Enter Bus Number:      ");
		for(j=0, k=0 ; j<5 ; ){
			ch = getch();
			if( ch>='0' && ch<='9' ){
				k = ch-48 + k * 10;
				printf("%c", ch);
				j++;
				busNumber[i] = k;
			}
			else if( ch==8 && j!=0 ){
				printf("\b \b");
				j--;
			}
			else if( ch==13 )
				break;
		}
		printf("\n");
		printf("\xDB\xBA Enter Price:                  ");
		scanf("%f", &price[i]);
		printf("\xDB\xBA From:                         ");
		scanf("%s", from[i]);
		printf("\xDB\xBA To:                           ");
		scanf("%s", to[i]);
		printf("\xDB\xBA Departure time:               ");
		scanf("%s", departure[i]);
		printf("\xDB\xBA Arrival time:                 ");
		scanf("%s", arrival[i]);
	
		i++;
	}
	
	if( select==1 ){
		
		if( busNumber[j]!=0 ){
			
			system("cls");
			printf("\xBA Please choose one of the buses for the trip.\n\n");
			
			for(j=0, k=0; j<15 && busNumber[j]!=0 ;j++){
				
				printf("%d\xB3 %5s \xBA %12s  >>  %-12s \xBA  %-9.2fTL  \xB3  Last %2d Seat(s)\n"
								   ,j+1, departure[j], from[j], to[j], price[j], 40-lastSeat[j]);
				k++;
			}
			ch = getch();
			for(  ; ch<=k+48 ;){
				selectSeat( 2 , ch-49 );
				break;
			}		
		}
		
		else{
			system("cls");
			printf("\xDB\xBA There is no active bus trip.");
			getch();	
		}
		
	}
	
	if( select==2 ){
		
		int temp, seatNumber;
		
		while(1){
			
			system("cls");
			printf("\xB3 Please Enter Your Bus Number:        ");
			scanf("%d", &temp);
			if( temp>99999 ){
				printf("\n\xB3 Wrong number entered.");
				Sleep(700);
			}
			else{
				printf("\xB3 Please Enter Your Seat Number:       ");
				scanf("%d", &seatNumber);
				break;
			}
		}
		
		j = 0;
		
		while(1){

		
			if( temp==busNumber[j] ){
				
				system("cls");
				printf("\xBA Name:                %s\n\n"     ,passenger[j][seatNumber-1]);
				printf("\xBA Bus Number:          %d\n"       ,busNumber[j]);
				printf("\xBA Seat:                %d\n"       ,seatNumber);
				printf("\xBA Price:               %.2fTL\n\n" ,price[j]);
				printf("\xBA From:                %s\n"       ,from[j]);
				printf("\xBA To:                  %s\n"       ,to[j]);
				printf("\xBA Departure:           %s\n"       ,departure[j]);
				printf("\xBA Arrival:             %s\n"       ,arrival[j]);
				
				break;
			}	
			j++;
		}
		getch();
	}
	
}

void selectSeat(int option, int n){
	
	int i, j, k=1, l, temp;
	char ch;

	if( option==1 ){
		
		printf("\xBA Bus Number:  %-5d\n", busNumber[n]);
		printf("\xBA Departure:   %-5s\n", departure[n]);
		printf("\xBA From:        %-15s\n", from[n]);
		printf("\xBA To:          %-15s\n\n\n", to[n]);
		
		for( i=0; i<14 ;i++ ){
		
			printf("\xBA");
			
			for( j=0; j<3 ; j++ ){
			
				if( j==0 ){
					
					if(seat[n][k-1]==0)	
						printf(" %d\t", k);
					else
						printf(" %c\t", 254);
					k++;
				}
				
				else if( i==7 && (j==1 || j==2) )
					continue;
					
				else{
					if( seat[n][k-1]==0 )
						printf("%3d", k);
					else
						printf("%3c", 254);
					k++;
				}
			}
			printf("\n");
		}
	}
	
	if( option==2 ){
	
		while(1){
			
			system("cls");
			selectSeat(1,n);
			printf("\n\xBA Please Select Seat Number:       \t\t");
			scanf("%2d", &l);
	
			if( l>40 ){
				printf("\n\n\xB3 Wrong seat number entered.");
				Sleep(800);
			}
			
			else{
			
				if( seat[n][l-1]!=0 ){
					printf("\n\n\xB3 The seat you have chosen has already been purchased."); 
					Sleep(800);
				}
				else{
					printf("\n\xBA Please Enter Name:               \t\t");
					scanf("%s", passenger[n][l-1]);
					seat[n][l-1]++;
					lastSeat[n]++;
					break;
				}	
			}
			
		}
	}
}

int password(char pw[]){
	
	int i;
	char ch, control[9];
	
	for(i=0; i<8 ; ){
		ch = getch();
		if( ch>32 && ch<127 ){
			control[i++] = ch;
			printf("*");
		}
		else if( ch==8 && i!=0 ){
			printf("\b \b");
			i--;
		}
		else if( ch==13 )
			break;
			
	}
	control[i]='\0';
		
	if( strcmp(pw,control)==0 )
		return 1;
	else{
		printf("\n\n\n>> Wrong password.\n>> Press any key to continue...");
		getch();
	}
	
}

void printCh219(int n, int ms){
	
	for( n ; n!=0 ; n-- ){
		printf("%c", 219);	
		Sleep(ms);
	}
}

void header(int n, int ms, char str[]){
	
	system("cls");
	printCh219(n,ms);
	printf(" %s ", str);
	printCh219(n,ms);
	printf("\n\n\n");
	
}
