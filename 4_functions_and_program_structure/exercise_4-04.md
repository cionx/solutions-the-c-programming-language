# Exercise 4-4

> Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements.
> Add a command to clear the stack.

---

We add functions that manipulate the stack in the desired way:
```c
double top(void)
{
	double value = pop();
	push(value);
	return value;
}

void duplicate(void)
{
	double value = top();
	push(value);
}

void swap(void)
{
	double value1 = pop();
	double value2 = pop();
	push(value1);
	push(value2);
}

void clear(void)
{
	sp = 0;
}
```
For testing purposes we also add a function to view the entire stack.
```c
void view(void)
{
	for (int i = 0; i < sp; ++i)
		printf("%g ", val[i]);
	printf("\n");
}
```

We add access to these functions via single-character command names:
```c
			case 't':
				printf("\t%.8g\n", top());
				remove_linebreak();
				break;
			case 'd':
				printf("duplicate stack head ...\n");
				duplicate();
				remove_linebreak();
				break;
			case 's':
				printf("swap the two top stack entries...\n");
				swap();
				remove_linebreak();
				break;
			case 'c':
				printf("clear the stack...\n");
				clear();
				remove_linebreak();
				break;
			case 'v':
				view();
				remove_linebreak();
				break;
```
We need to be a bit careful here:
When we type `v <Enter>` we want to view the stack, but not manipulate it.
But the `<Enter>` introduces a line break, which then pops the top of the stack.
We therefore use an auxiliary function `remove_linebreak` to remove this line break:
```c
void remove_linebreak(void)
{
	int c = getch();
	if (c != '\n')
		ungetch(c);
}
```
