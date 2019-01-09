#include <stdio.h>
#include <stdlib.h>

void swap(char * a, char * b){ // using in Flip function
	char c;
	c=*a;
	*a=*b;
	*b=c;
} 
int Input_image(int height,int width, char ** img);
char** Resize(int arg1, int * height, int * width, char ** img);
char** Rotate(int *height,int *width,int angle,char ** img);
void Flip(int height, int width, int flag, char ** img);
char* Copy(int x1,int y1,int c_h,int c_w,int height,int width,char ** img);
void Paste(int x2,int y2,int height,int width,char ** img,char * temp);
void Fill(int x,int y, int heigt, int width, char ** img, char change, char color,int * num);
int main (void){
	char ** img;
	int height,width;
	int test_num;
	int order_num;
	int query;
	int Error=1; // if error occurs, Error value is 1;
	int need; // using for arg1 in query1, angle in query2, flag in query3
	int x1,x2,y1,y2,c_h,c_w;
	char * copy_img;
	int pixel_num=0; // variable that stores the number of changed pixel by Fill function
	char color;
	int i,j; // used to make " for(i=0;;) "

	printf("Input testcase : ");
	scanf("%d",&test_num);
	while(test_num-->0){ // loop as much as the value of test_num
		printf("Input height , width : ");
		scanf("%d %d%*c",&height,&width);
		if(height<=0 || height>4096){
			printf("Error!\n");
			continue;
		}
		if(width<=0 || width>4096){
			printf("Error!\n");
			continue;
		}
		//if the entered value of heigth or width is out of range, print error message and skip to next test

		img=(char **)calloc(height,sizeof(char *));
		for(i=0;i<height;i++)
			img[i]=(char *)calloc(width,sizeof(char));
		// dynamically allocate img (size of height*width)
		
		Error=Input_image(height,width,img); // if error occurs while input img, th value of Error becomes 1
		if(Error){
			printf("Error!\n");
			continue; // if error occurs, skip to next case
		}

		printf("Input number of query : ");
		scanf("%d",&order_num);
		if(order_num<=0){
			printf("Error!\n");
			continue;
		}// if entered value of the number of query is minus or zero, send error message and skip to next case	

		while(order_num-- >0){// loop as much as entered value of order_num
			printf("Input query : ");
			scanf("%d",&query);
			printf("\n");
			switch(query){
				case 1: {
							printf("Resize\nInput 0 or 1 : ");
							scanf("%d",&need); // receive value for arg1 in Resize function and it is stored in variable name 'need'
							if(need != 0 && need != 1){
								printf("Error!\n");
								break;
							} // if need is out of range, send error message and end the switch() statement
							img=Resize(need,&height,&width,img);
							printf("Result, resize height : %d, width : %d :\n",height,width);
							break;
						}
				case 2: {
							printf("Rotate\nInput 0 or 1 or 2 : ");
							scanf("%d",&need); // receive value for angle in Rotate function and it is stored in variable name 'need'
							if(need<0 || need>2){
								printf("Error!\n");
								break;
							} // if need is out of range, send error message and end the switch() statement
							img=Rotate(&height,&width,need,img);
							printf("Result_rotate height : %d, width : %d\n",height,width);
							break;
						}
				case 3: {
							printf("Flip\nInput 0 or 1 : ");
							scanf("%d",&need); //  receive value for flag in Flip function and it is stored in variable name 'need'
							if(need != 0 && need != 1){
								printf("Error!\n");
								break;
							} // if need is out of range, send error message and end the switch() statemet
							Flip(height,width,need,img);
							break;
						}
				case 4: {
							Error=0;
							printf("Copy and Paste\nx1, y1, c_h, c_w, x2, y2 :");
							scanf("%d %d %d %d %d %d",&x1,&y1,&c_h,&c_w,&x2,&y2);
							if(x1<0 || x1>=width)
								Error=1;
							if(y1<0 || y1>=height)
								Error=1;
							if(x2<0 || x2>=width)
								Error=1;
							if(y2<0 || y2>=height)
								Error=1;
							if(c_h<=0 || c_w<=0)
								Error=1;
							// if the entered value satisfy one of those top four if-statement, the value of Error becomes 1 
							if(Error){ // if Error is 1, send error message and end the switch statement
								printf("Error!\n");
								break;
							}

							copy_img=(char *)malloc(sizeof(char));
							copy_img=Copy(x1,y1,c_h,c_w,height,width,img); // copy_img receives return value of Copy function
							Paste(x2,y2,height,width,img,copy_img);
							free(copy_img);// make copy_img by Copy function and used in Paste function and then the value of copy_img is no longer used, so free copy_img
							break;
							}
				case 5:{
						   printf("Fill\nInput y,x, color : ");
						   scanf("%d %d%*c%c",&y1,&x1,&color);
						   if(x1<0 || x1 >=width){
							   printf("Error!\n");
							   break;
						   }
						   if(y1<0 || y1 >=height){
							   printf("Error!\n");
							   break;
						   }
						   // if entered value of y or x is out of range, send error message and end switch statement
						   pixel_num=0; // reset pixel_num(variable for the number of changed pixel by Fill function)
						   if(img[y1][x1] != color)
							   Fill(x1,y1,height,width,img,img[y1][x1],color,&pixel_num);
						   // if pixel that I want to change is same as the value of color, it don't need to change anything
						   printf("Number of colored pixels = %d\n",pixel_num);
						   break;
					   }
				default: printf("Error!\n");// if entered value of query is out of range, send error message
			}

			//after doing query 1 or 2,3,4,5 or finding error, print entire image(variable name : img)
			printf("Result Image\n\n");
			for(i=0;i<height;i++){
				for(j=0;j<width;j++)
					printf("%c",img[i][j]);
				printf("\n");
			}
		}

		for(i=0;i<height;i++)
			free(img[i]);
		free(img);
		// after one test-case, free img because the stored values in img will no longer used. 
	}
	//after all test-case, end the project
	return 0;
}

int Input_image(int height,int width,char ** img){
	int i,j;
	char ch;
	printf("Input the image\n");
	for(i=0;i<height;i++){
		for(j=0;j<=width;j++){
			do{
				scanf("%c",&ch);   //    공백이 들어오면 무시한다. while문의 조건으로 인해
			}while(ch==' ');          //     ' '가 입력되면 다음 문자를 입력받게 되어있다.

			if(ch == '\n'){				//  '\n'이 입력되었을 시
				while(j<width){    //  '\n' 가 한 row의 width만큼 문자를 받기 전에 입력되면 그 row의 나머지 칸들을 ' '로 채워넣는다
					img[i][j++]=' ';
				}
				break;                    // '\n'이 입력되면 한 row에 대한 입력을 중단하고 다음 row에 대해 입력받는다.
			}
			else if(j == width){   // 한 row에 width만큼 모든 문자가 입력된 뒤에 '\n' 입력되지 않은 경우
				while(1){
					scanf("%c",&ch);
					if(ch == '\n')
						break;
				}                             // 오류가 난 한 line은 '\n'이 입력될 때까지 받아들인다
				return 1;              // 오류가 났으므로 return값 1
			}
			else
				img[i][j]=ch;       // '\n' 입력되지 않고 한 row에 width만큼 칸이 채워져 있지 않을 때
			                                // 받아들인 문자를 img에 저장한다.
		}
	}
	return 0;                        // 오류가 발생하지 않았을 시에 return값 0
}

char** Resize(int arg1, int * height, int * width, char ** img){
	int i,j,k,h;                           // for문을 돌리고 이미지의 index 값으로 쓰이는 변수들
	char pixel_to_resize;      // 확대시킬 때 기존이미지 픽셀값을 저장해두는 변수
	char ** reduced_img;    // 축소시킨 결과 이미지를 저장하는 변수
	int reduced_pixel;          // 기존이미지의 2*2픽셀의 합을 저장했다가 4로 나누어서 2*2픽셀의 평균을 저장해두는 변수
	                                          // 기존 이미지를 축소시킬 때, 기존 이미지의 2*2픽셀이 축소되어진 한 픽셀의 값을 저장하는 변수
	int past_height=*height , past_width=*width;     // height와 width값을 resize한 값으로 바꾸기 전에 기존 이미지 크기를 저장해두는 변수

	if(arg1 == 0){
		if((*height)>2048 || *width>2048){     // 기존이미지의 높이나 너비를 2배시킬 시 4096을 넘어가는 경우 수행을 멈추고 오류메시지 띄운다
			printf("Size Error!\n");
			return img;
		} 

		(*height)*=2;
		(*width)*=2;  // main에서 img의 크기를 저장해두는 height, width를 2배시킨다.

		img=(char **)realloc(img,sizeof(char *)*(*height));
		for(i=0;i<(past_height);i++)
			img[i]=(char *)realloc(img[i],sizeof(char)*(*width));
		for(i=past_height;i<(*height);i++)
			img[i]=(char*)malloc(sizeof(char)*(*width)); // img를 2배가 된 height와 2배가 된 width 크기를 갖도록 동적할당(realloc, malloc)을 해준다 

		for(i=(*height)/2-1;i>=0;i--)                      //  img[i][j]는 확대시킬 기존이미지의 픽셀      
			for(j=(*width)/2-1;j>=0;j--){ 
				pixel_to_resize=img[i][j];
				for(k=0;k<2;k++)                                //   img[2*i][2*j] 기준으로 오른쪽으로 2칸 아래로 2칸이 만드는 2*2 크기의 사각형에 포함되는
					for(h=0;h<2;h++)                           //   4개의 픽셀(img[2*i][2*j],img[2*i][2*j+1],img[2*i+1][2*j],img[2*i+1][2*j+1])을 확대시키려는 
						img[2*i+k][2*j+h]=pixel_to_resize;         //                                                         기존 이미지 픽셀값(pixel_to_resize)으로 채워넣는다.
			}
		return img;
	}

	else if(arg1 == 1){
		if((*height)<2 || (*width)<2){  // 기존 이미지의 높이와 너비를 각각 2배 축소시킬 시
			printf("Size Error!\n");           //  0 이하 값을 갖게 되면 오류발생
			return img;
		}
		(*height)/=2;
		(*width)/=2;      //main함수에서 이미지의 크기를 저장해두는 height와 width값을 2배 축소시킨다.

		reduced_img=(char **)malloc(sizeof(char *)*(*height));
		for(i=0;i<*height;i++)
			reduced_img[i]=(char *)malloc(sizeof(char)*(*width));  //축소된 이미지를 저장할 새로운 배열을 축소된 height와 width 크기만큼 동적할당 해준다.
	
		for(i=0;i<(*height);i++)
			for(j=0;j<(*width);j++){         //  reduced_img[i][j]에 저장될 값을 구하는 작업을 한다
				reduced_pixel=0;  

				for(k=0;k<2;k++)               // img[2*i][2*j]기준으로 오른쪽2칸, 아래로2칸에 해당하는 
					for(h=0;h<2;h++){        //  2*2 픽셀(img[2*i][2*j],img[2*i+1][2*j],img[2*i][2*j+1],img[2*i+1][2*j+1])들의 총합부터 구한다.                   
 						if(img[2*i+k][2*j+h] == ' ')  // 기존 이미지에 저장된 픽셀이 ' '(공백)이면 무시한다
							continue;
						reduced_pixel+=(int)(img[2*i+k][2*j+h]);
					}

				reduced_pixel/=4; // 4개의 픽셀 총합을 4로 나눈다.
				reduced_img[i][j]=(char)reduced_pixel;   // reduced_img[i][j]에 계산한 값을 저장한다.
			}
		for(i=0;i<2*(*height);i++) 
			free(img[i]);
		free(img);       //img를 free시킨다.

		return reduced_img;
	}
}

char** Rotate(int *height,int *width,int angle,char ** img){
	char ** rotated_img;                         // rotate 시킨 결과이미지 저장
	int past_height,past_width;             // rotate 시키기 전 이미지의 높이와 너비 저장
	int size_temp;  
	char char_temp;                                 
	int i,j,k;
	switch(angle){
		case 0:{
				   past_height=*height;
				   past_width=*width;
				   // height와 width값 바꾸기 전에 회전시키기 전 이미지 크기를 저장해둔다

				   size_temp=*height;
				   *height=*width;
				   *width=size_temp;
				   // main에서 이미지의 크기를 저장하는 height와 width값을 size_temp 변수를 이용해 swap시킨다.

				   rotated_img=(char **)malloc(sizeof(char *)*(*height));
				   for(i=0;i<*height;i++)
					   rotated_img[i]=(char *)malloc(sizeof(char));
				   //회전시킨 결과값을 저장해둘 배열(rotated_img)을 height*1 크기로 동적할당한다.

				   for(i=past_height-1;i>=0;i--){   // 기존이미지의 i인덱스 row를 rotated_img의 (past_height-1-i)인덱스 colomn에 넣는 작업을 수행한다.
					   for(k=0;k<*height;k++)
						   rotated_img[k]=(char *)realloc(rotated_img[k],sizeof(char)*(past_height-i)); // i에 대한 loop를 돌 때마다 rotated_img의 colomn개수를 past_height-i만큼 늘린다.

					   for(j=0;j<past_width;j++)
						   rotated_img[j][past_height-1-i]=img[i][j];  //기존이미지 i인덱스 row의 j번째 pixel은 rotated_img의 (past_height-1-i)인덱스 colomn의 j번째 pixel에 대응된다.

					   free(img[i]); // i에 대한 loop를 돌 때마다 i인덱스 row에 대해 위의 작업을 한 후 여기서 free시킨다.
				   }
				   free(img);
				   return rotated_img;
				   break;
			   }
		case 1:{
				   for(i=0;i<(*height)/2;i++){  // i인덱스 row와 height-1-i인덱스 row 안의 값들을 서로 swap시킨다
					   for(j=0;j<(*width);j++){
						   char_temp=img[i][j];
						   img[i][j]=img[(*height-1)-i][(*width-1)-j];
						   img[(*height-1)-i][(*width-1)-j]=char_temp;
					   }
				   }
				   if((*height)%2 == 1){ // 홀수개의 row일 경우 가운데 row에서 j인덱스 값과 width-1-j인덱스값을 swap시킨다 
					   for(j=0;j<(*width)/2;j++){
						   char_temp=img[(*height)/2][j];
						   img[(*height)/2][j]=img[(*height)/2][(*width-1)-j];
						   img[(*height)/2][(*width-1)-j]=char_temp;
					   }
				   }
				   return img;
				   break;
			   }
		case 2:{
				   past_height=*height;
				   past_width=*width; // 회전시키기 전 height와 width값 저장

				   size_temp=*height;
				   *height=*width;
				   *width=size_temp;
				   //main 함수에서 이미지의 크기를 저장하고 있는 height와 width값을 바꾼다
				   rotated_img=(char **)malloc(sizeof(char *)*(*height));
				   for(i=0;i<*height;i++)
					   rotated_img[i]=(char *)malloc(sizeof(char));
				   //rotated_img(회전시킨 이미지를 저장하는 변수)를 기존이미지의 너비를 높이로 하고 너비가 1인 크기로 초기화한다
				   
				   for(i=0;i<past_height;i++){  // 기존 이미지의 i인덱스 row를 rotated_img의 i 인덱스 colomn의 값을 서로 대응시키려고 한다
					   for(k=0;k<(*height);k++)
						   rotated_img[k]=(char *)realloc(rotated_img[k],sizeof(char)*(i+1));  // i인덱스 colomn값을 받아들이기 위해 rotated_img의 colomn 개수를 늘린다.
					   for(j=0;j<past_width;j++)
						   rotated_img[(*height-1)-j][i]=img[0][j]; // 기존 이미지의 i인덱스 row의 맨 왼쪽에서부터 오른 쪽으로 나아가면서 해당 값을 rotated_img의 i 인덱스 colomn의 맨 아래부터 대응시킨다
					   free(img[0]);   // 기존이미지의 i인덱스 row를 free시킨다
					   for(k=1;k<(*width)-i;k++)
						   img[k-1]=img[k];     // 기존 이미지의 i인덱스 row를 rotated_img에 대응시키는 작업 후에 free시키고 아직 rotated_img에
				   }                                         // 대응시키지 않은 row들을 모두 한 칸씩 앞으로 옮긴다.(기존인덱스의 -1에 해당하는 인덱스에 위치시킨다) 
				   free(img);                        // 그러면 for문에서 i에 대한 수행시 img[0]은 기존이미지의 i 인덱스 row를 가리키게 된다

				   return rotated_img;
				   break;
			   }
	}
}
void Flip(int height, int width, int flag, char ** img){
	int i,j;
	if(flag == 0){
		for(i=0;i<(height)/2;i++) 
			for(j=0;j<width;j++){
				swap(&img[i][j],&img[(height-1)-i][j]);
			}
	}
	else{
		for(i=0;i<height;i++)
			for(j=0;j<(width)/2;j++){
				swap(&img[i][j],&img[i][(width-1)-j]);
			}
	}
}
char* Copy(int x1,int y1,int c_h,int c_w,int height,int width,char ** img){
	int i,j;
	char *copied_img; // copy한 이미지를 저장하는 일차원 배열

	if(x1+c_w>width)
		c_w=width-x1;
	if(y1+c_h>height)
		c_h=height-y1;
	// copy할 이미지 크기가 기존 이미지를 넘어가지 않도록 c_w와 c_h를 조정한다. 
	copied_img=(char *)malloc(sizeof(char)*c_h*(c_w+1));
	// 1차원배열이지만 2차원 배열처럼 사용하기 위해 한 row가 끝나면 '\0' 또는 '\n'을 넣기 위해 c_h*(c_w+1)의 크기로 동적할당한다
	for(i=y1;i<y1+c_h;i++){
		for(j=x1;j<x1+c_w;j++)
			copied_img[(i-y1)*(c_w+1)+(j-x1)]=img[i][j];
		copied_img[(i-y1)*(c_w+1)+(j-x1)]='\0'; // row가 끝나면 '\0'문자를 추가로 저장한다
	}
	copied_img[((i-1)-y1)*(c_w+1)+(j-x1)]='\n';	// 마지막 row가 끝나면 '\0' 대신 '\n'을 추가로 저장한다
	return copied_img;
}
void Paste(int x2,int y2,int height,int width,char ** img,char * temp){
	int i,j;
	int temp_w=0;
	int temp_h=0;

	// temp의 너비 구하기 = c_w+1
	while(1){
		if(temp[temp_w] == '\0' || temp[temp_w] == '\n'){
			temp_w+=1;
			break;
		}
		temp_w++;
	}	
	//temp의 높이 구하기 =c_h
	while(1){
		if(temp[temp_h*temp_w+(temp_w-1)] == '\n'){
			temp_h+=1;
			break;
		}
		temp_h++;
	}
	//기존 이미지의 x2와 y2위치에서 오른 쪽으로 temp_w-1칸, 아래로 temp_h칸이 가리키는 사각형 영역과 기존이미지 사이즈와
	//겹치는 부분만 기존이미지값을 temp에 저장된 값으로 바꾼다.
	for(i=y2; i < y2+(temp_h);i++){
		if(i == height)
			break;
		for(j=x2;j< x2+(temp_w-1);j++){
			if(j == width)
				break;
			img[i][j]=temp[((i-y2)*temp_w)+(j-x2)];
		}
	}
}
void Fill(int x,int y, int height, int width, char ** img, char to_change, char color,int * num){
	int i;
	/* x와 y는 값이 바뀌어야되는 지 아닌 지 판단해야할  픽셀의 위치를 나타낸다
	     to_change는 입력받은 y와 x에 해당하는 픽셀의 값을 저장하고 있다. 
		 즉 x와 y로 들어온 픽셀이 to_change에 저장된 값과 같으면 color값으로 변경한다.
		 main함수에서 선언한 query 5 수행시 색깔이 바뀌는 픽셀의 총 개수를 저장하는 
		 변수의 값을 함수 내에서 변경시키기 위한 int * num*/
	if(x<0 || x>=width)
		return;
	if(y<0 || y>=height)
		return
		// x와 y가 가르키는 위치가 이미지 범위를 벗어나면 아무 수행 없이 종료한다.
	if(img[y][x] == to_change){ // y,x에 해당하는 픽셀이 바뀌어야할 값과 같을 경우
		img[y][x]=color;   // 픽셀값을 바꾸고
		*num+=1;             // main함수 내 선언된 값을 +1시키고
		 // 해당 픽셀(y,x위치)의 왼쪽, 오른쪽, 위쪽, 아래쪽 픽셀위치를 y와 x에 넣어 Fill함수를 재귀 호출한다.
		Fill(x-1,y,height,width,img,to_change,color,num);       
		Fill(x+1,y,height,width,img,to_change,color,num);
		Fill(x,y+1,height,width,img,to_change,color,num);
		Fill(x,y-1,height,width,img,to_change,color,num);
	}
}
