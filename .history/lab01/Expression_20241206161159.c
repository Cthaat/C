#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 1000

/*定义一个运算符栈*/
typedef struct {
	char Operator[MAX_SIZE];
	int top;
} OptorStack;
/*定义一个操作数栈*/
typedef struct {
	double Operand[MAX_SIZE];
	int top;
} OpndStack;
/*初始化运算符栈*/
void InitOptor(OptorStack *S) {
	S->top = -1;
}
/*初始化操作数栈*/
void InitOpnd(OpndStack *S) {
	S->top = -1;
}
/*运算符出栈*/
int PopOptor(OptorStack *S) {
	if(S->top==-1) {
		printf("运算符栈为空\n");
		exit(10);
	}
	S->top--;
	return 1;
}
/*操作数出栈*/
int PopOpnd(OpndStack *S) {
	if(S->top==-1) {
		printf("操作数栈为空\n");
		exit(11);
	}
	S->top--;
	return 1;
}

/*运算符入栈*/
int PushOptor(OptorStack *S,char ch) {
	if(S->top==MAX_SIZE-1) {
		printf("运算符栈满\n");
		exit(12);
	}
	S->top++;
	S->Operator[S->top]=ch;
	return 1;
}
/*操作数入栈*/
int PushOpnd(OpndStack *S,double ch) {
	if(S->top==MAX_SIZE-1) {
		printf("操作数栈满\n");
		exit(13);
	}
	S->top++;
	S->Operand[S->top]=ch;
	return 1;
}
/*取运算符栈栈顶元素*/
char GetOptor(OptorStack *S) {
	if(S->top==-1) {
		printf("运算符栈为空\n");
		exit(17);
	}
	return S->Operator[S->top];
}
/*取操作数栈栈顶元素*/
double GetOpnd(OpndStack *S) {
	if(S->top==-1) {
		printf("操作数栈为空\n");
		exit(18);
	}
	return S->Operand[S->top];
}
/*表达式运算函数*/
double Calculate(double a,double b,char op) {
	double result;
	if(op=='+') result=a+b;
	if(op=='-') result=a-b;
	if(op=='*') result=a*b;
	if(op=='/') {   //要防止除数为0
		if(b==0) {
			printf("ERROR:除数不能为0\n");
			exit(15);
		}
		result=a/b;
	}
	return result;    //返回结果result
}

int change(char ch) {
	switch(ch) {
		case '+':
			return 0;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 3;
		case '(':
			return 4;
		case ')':
			return 5;
		case '#':
			return 6;
	}
}
/*定义一个算符优先关系矩阵*/
char cmp[7][8]= {">><<<>>",">><<<>>",">>>><>>",">>>><>>","<<<<<=?",">>>>?>>","<<<<<?="};
/*算符比较函数，返回优先级:>或<或=*/
int Compare(char ch1,char ch2) {
	if(cmp[change(ch1)][change(ch2)]=='?') {
		printf("输入表达式错误");
		exit(16);
	}
	return cmp[change(ch1)][change(ch2)];
}
/*检查函数,用来检查输入的表达式的操作数和运算符的合法性*/
int Check(char *S,int len) {
	int i;
	for(i=0; i<len; i++) {
		if(S[i]>='0'&&S[i]<='9')continue;
		if(S[i]=='('||S[i]==')'||S[i]=='*'||S[i]=='/'||S[i]=='+'||S[i]=='-'||S[i]=='.')continue;
		return 0;
	}
	return 1;
}

int main() {
	char expre[9999],opd[9999];   //expre用来存储表达式，opd用来存操作数
	int len;
	OptorStack Optor;
	OpndStack Opnd;
	InitOptor(&Optor);
	InitOpnd(&Opnd);
	PushOptor(&Optor,'#');
	printf("请输入表达式：\n");
	scanf("%s",expre);
	len = strlen(expre);
	if (Check(expre,len) == 0) {
		printf("输入的表达式不合法，可能存在多余字符\n");
		exit(19);
	}
	int i,j=0,k=0;
	double x,y;
	expre[len] = '#';   //在expre数组后加个#结尾标志
	for (i=0; i<=len; i++) {
		if ((expre[i]>='0' && expre[i]<='9') || expre[i] == '.') {
			opd[k++] = expre[i];   //将数字字符存入操作数数组opd中
			j = 1;
			continue;
		}
		if(j) {
			opd[k] = '\0';
			PushOpnd(&Opnd,atof(opd));
			j=0;
			k=0;
		}
		switch (Compare(GetOptor(&Optor),expre[i])) {  //比较运算符栈的栈顶运算符和运算符expre[i]的优先级
			case '<':
				PushOptor(&Optor,expre[i]);
				break;
			case '=':
				PopOptor(&Optor);
				break;
			case '>':
				y = GetOpnd(&Opnd),PopOpnd(&Opnd);
				x = GetOpnd(&Opnd),PopOpnd(&Opnd);
				PushOpnd(&Opnd,Calculate(x,y,GetOptor(&Optor)));
				PopOptor(&Optor);
				i--;
				break;
		}
	}
	double final_result = GetOpnd(&Opnd);
	printf("该表达式的结果为：%.2lf",final_result);
	return 0;
}
