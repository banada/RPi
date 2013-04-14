/*     2A2B -- a game of dumb luck
*
*      Authors: Nathaniel Chen
*      Copyright Nathaniel Chen 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* one struct for comp, one for user */
struct keep {
	int num[4];
	int guess[4];
	char check[4];
};
struct keep *user;
struct keep *comp;
int turn;

int get_numbers (int (*p)) {
	int i;
	int k;
	int num[4];
	int j;

	for (k=0; k<4; k++) {

		i = getchar();
	
		if (i == '\n')
			return 0;
		if (i == EOF)
			return 0;

		i -= '0';
		if (i < 0 || i > 9) {
			printf("error! not an int\n");
			return -1;
		}
		num[k] = i;

		/* all numbers must be different */
		if (k > 0) {
			for (j=0; j<k; j++) {
				if (num[k] == num[j]) {
					printf("error! numbers must all be different\n");
					return -1;
				}
			}
		}

		p[k] = num[k];
	}

return 0;
}

int computer_guess (void) {
	int i;
	int k;

	/* first turn */
	if (turn == 0) {
		for (i=0; i<4; i++) {
			comp->guess[i] = (rand() % 10);

			/* all numbers must be different */
			if (i > 0) {
				for (k=0;k<i;k++) {
					while (comp->guess[i] == comp->guess[k]) {
						comp->guess[i] = (rand() % 10);
					}
				}
			}
		} 
	}

	/* next turns -- randomly guess what isn't A or B */
	/* randomly guess anything that isn't A right now */
	if (turn > 0) {
		for (i=0; i<4; i++) {
			if (comp->check[i] == 'A')
				continue;
			else {
				comp->guess[i] = (rand() % 10);
				/* all numbers must be different */
				if (i > 0) {
					for (k=0;k<i;k++) {
						while (comp->guess[i] == comp->guess[k]) {
							comp->guess[i] = (rand() % 10);
						}
					}
				}
			}
		}
	}

	turn++;
}

int user_guess (void) {
	int i;
	int k;

	/* first turn */
	if (turn == 0) {
		for (i=0; i<4; i++) {
			user->guess[i] = (rand() % 10);

			/* all numbers must be different */
			if (i > 0) {
				for (k=0;k<i;k++) {
					while (user->guess[i] == user->guess[k]) {
						user->guess[i] = (rand() % 10);
					}
				}
			}
		} 
	}

	/* next turns -- randomly guess what isn't A or B */
	/* randomly guess anything that isn't A right now */
	if (turn > 0) {
		for (i=0; i<4; i++) {
			if (user->check[i] == 'A')
				continue;
			else {
				user->guess[i] = (rand() % 10);
				/* all numbers must be different */
				if (i > 0) {
					for (k=0;k<i;k++) {
						while (user->guess[i] == user->guess[k]) {
							user->guess[i] = (rand() % 10);
						}
					}
				}
			}
		}
	}


	turn++;
}

int check (struct keep *checker, struct keep *checkee) {
	int i;
	int k;

	/* check for 2A2B */
	for (i=0; i<4; i++) {
		if (checker->guess[i] == checkee->num[i])
			checker->check[i] = 'A';
		else {
			for (k=0; k<4; k++) {
				if (checker->guess[i] == checkee->num[k]) {
					checker->check[i] = 'B';
				}
			}
		}
	}
return 0;
}

int main (void) {
	int i;
	int k;

	turn = 0;
	user = calloc(1, sizeof(struct keep));
	comp = calloc(1, sizeof(struct keep));

	/* FIXME initialize check vals */
	comp->check[0] = '0';
	comp->check[1] = '0';
	comp->check[2] = '0';
	comp->check[3] = '0';
	user->check[0] = '0';
	user->check[1] = '0';
	user->check[2] = '0';
	user->check[3] = '0';

	printf("Pick four numbers from 0-9 (e.g. 1234)\n");
	if (get_numbers(user->num) < 0)
		return 0;

	printf("Your numbers: ");
	for (i=0; i<4; i++) {
		printf("%d", user->num[i]);
		if (i==3)
			printf("\n");
	}

	/* set random computer numbers */
	printf("Computer's numbers: ");
	/* seed */
	srand(time(NULL));
	for (i=0; i<4; i++) {
		/* modulo 10 will always give us 0-9 */
		comp->num[i] = (rand() % 10);

		/* all numbers must be different */
		// FIXME
		if (i > 0) {
			for (k=0;k<i;k++) {
				while (comp->num[i] == comp->num[k]) {
					comp->num[i] = (rand() % 10);
				}
			}
		}

		printf("%d", comp->num[i]);
	}
	printf("\n");

	/* FIXME this needs to be a separate function called in a while */
	while (!((comp->check[0] == 'A') && (comp->check[1] == 'A') && (comp->check[2] == 'A') && (comp->check[3] == 'A'))) {
// ||		((user->check[0] == 'A') && (user->check[1] == 'A') && (user->check[2] == 'A') && (user->check[3] == 'A')) ;) {

		user_guess();
		check(user, comp);

		printf("User's Guess: ");
		for (i=0; i<4; i++)
			printf("%d", user->guess[i]);
		printf("\nResult: ");
		for (i=0; i<4; i++)
			printf("%c", user->check[i]);
		printf("\n");

		computer_guess();
		check(comp, user);

		printf("Computer's Guess: ");
		for (i=0; i<4; i++)
			printf("%d", comp->guess[i]);
		printf("\nResult: ");
		for (i=0; i<4; i++)
			printf("%c", comp->check[i]);
		printf("\n");

	}

return 0;
}

