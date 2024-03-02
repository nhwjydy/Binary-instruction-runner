#include<stdio.h>//output，readfile,
#include<stdlib.h>//Memory Allocation and use
#include<string.h>//Memory Copy Text Conversion
//all value
#define in_ *(int*)
char *msn,*t;
int end;

//function
#define in *(int*)
#define e(a) (msn+*(int*)t+a)
#define b (msn+*(int*)(t+4))
#define p (msn+*(int*)t)
void pint(void){
	printf("%s",p);
}
void pluss(void){
	(in p)++;
}
void equal(void){
	if(in p==in e(4))*b='#';
	else *b=0;
}
void less(void){
	if(in p<in e(4))*b='#';
	else *b=0;
}
void add(void){
	in b=in p+in e(4);
}
void plus(void){
	in b=(in p*in e(4));
}
void large(void){
	if(in p>in e(4))*b='#';
	else *b=0;
}
void nt(void){
	if(*p)*p=0;
	else *p=1;
}
void tochar(void){
	char str[10],n=sprintf(str,"%d",in p);
	memmove(b,str,n);
	
}

//Binary Runer

int main(int argc, char const *argv[])
{
	//openFile
	FILE *f;
	msn=malloc(4096);     //Memory allocation parameters are specified by default
	if(argc>1)f=fopen(argv[1],"rb");
	else{
		printf(">.");
		scanf("%s",msn);
		f=fopen(msn,"rb");
	}
	fseek(f,0,SEEK_END);
	end=ftell(f);
	fseek(f,0,SEEK_SET);
	fread(msn,end,1,f);
	
	//main
	void (*fn[25])()={pint,pint,pluss,equal,less,add,plus,large,nt,tochar};
	for (int F = 0; F < end; F+=16)
	{st:;
		if(in_((t=msn+F)+12)){
			fn[in_(t+12)]();     //Pecific input and output
		}else if (in_(t+8))
		{
			memmove(msn+in_(t+8),msn+in_(t),in_(t+4));     //Memory Copy
		}else{
			if (in_(t))
			{
				if (*(msn+in_(t)))
				{
					F=in_(t+4);     //Conditional execution jump
					goto st;
				}
			}else{
				F=in_(t+4);
				goto st;
			}
		}
	}
	return 0;
}
