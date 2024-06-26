#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ch *(char*)               // t - context address | msn - current context
#define in *(int*)				

#define pn   * msn                // input   value
#define bn   *(msn + 1)           // output  value
#define at(n) (t +   n)           // context address offset
#define p     (t + * msn)         // Input   address
#define b     (t + *(msn + 1))    // Output  address
#define e(n)  (t + * msn + n)     // Input   address offset
#define bi(n) (t + *(msn + 1) + n)// Output  address offset

int *msn, end;
char *t;

void pint(void) {
	printf("%s", p);
}
void pluss(void) {
	(*p)++;
}
void equal(void) {
	*b = (*p == *e(4)) ? 'R' : 0;
}
void less(void) {
	*b = (*p < *e(4)) ? 'R' : 0;
}
void add(void) {
	*b = *p + *e(4);
}
void plus(void) {
	*b = (*p) * (*e(4));
}
void large(void) {
	*b = (*p > *e(4)) ? 'R' : 0;
}
void nt(void) {
	*p = *p ? 0 : 1;
}
void tochar(void) {
	char str[10];
	int n = sprintf(str, "%d", *p);
	memmove(b, str, n);
}

int main(int argc, char const *argv[]) {
	FILE *f;
	msn = malloc(256);
	if (argc > 1) f = fopen(argv[1], "rb");
	else {
		printf(">.");
		scanf("%s", (char *)msn);
		f = fopen((char *)msn, "rb");
	}

	fread(msn, 16, 1, f);
	t = (char *)(msn = realloc(msn, *(msn + 3) ? * (msn + 2) : 4096));
	fseek(f, 0, SEEK_END);
	end = ftell(f);
	fseek(f, 0, SEEK_SET);
	fread(msn, end, 1, f);

	void (*fn[])() = {NULL, pint, pluss, equal, less, add, plus, large, nt, tochar};
	while (((char *)msn - t) < end) {
		if (*(msn + 3)) {
			fn[*(msn + 3)]();
		} else if (*(msn + 2)) {
			memmove(t + * (msn + 2), t + * (msn), *(msn + 1));
		} else {
			if (*(msn)) {
				if (*(t + * (msn))) {
					msn = (int *)(t + * (msn + 1));
					continue;
				}
			} else {
				msn = (int *)(t + * (msn + 1));
				continue;
			}
		}
		msn += 4;
	}
	free(t);
	fclose(f);
	return 0;
}
