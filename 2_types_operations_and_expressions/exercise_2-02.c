#include <stdbool.h>
#include <stdio.h>

void test(void)
{
	int lim;
	char s[] = {};
	char c;
	int i;

	/* The following lines are the actual anwer. */
	bool cont = true;
	for (i = 0; cont; ++i) {
		if (i < lim - 1) {
			c = getchar();
			if (c == '\n')
				cont = false;
			else if (c == EOF)
				cont = false;
			else
				s[i] = c;
		}
		else
			cont = false;
	}
}

/*
for (⟨init code⟩; cont; ⟨increase code⟩) {
	if (bool11) {
		if (bool12) {
			⋱
				if(bool1n) {
					if (bool21)
						cont = false;
					else if (bool21)
						cont = false;
					⋮
					else if (bool2m)
						cont = false;
					else {
						⟨inner code⟩
					}
				}
				else cont = false;
			⋰
		}
		else cont = false;
	}
	else cont = false
}
*/
