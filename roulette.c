// userc68 software

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SINGLE_MULT 36
#define DOUBLE_MULT 18
#define TRIPLE_MULT 12
#define DOZEN_MULT 3
#define RB_LH_MULT 2

#define LOSS 0

// betting options, red/black 1:1, low/high 1:1 (1-18 or 19-36)
// dozen 2:1 (1-12, 13-24, 25-36), single # 35:1; double # 17:1; triple # 11:1

// how my newly invented ezwheel works: 0 + 1-36;
// if array element is even then black, if odd then red.
// if zero then you lose your money

uint8_t ezwheel[37] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
};

uint8_t spinwheel();
void eventwl(float bet, int multiplier, bool ifwin);

int main() {

  char typeofbet[10];
  float betmoney;

  printf("Gamble: ");
  scanf("%9s", typeofbet);

  printf("Bet: ");
  scanf("%f", &betmoney);

  int result = spinwheel();

  if (result == 0) { 
    printf("You LOSE your initial bet of $%.2f", betmoney);
    return 0;
  }
  
  if (strcmp(typeofbet, "r/b") == 0) {
    bool userpickblack;
    char redorblack[10];

    printf("Red or Black (r/b): ");
    scanf("%9s", redorblack);

    if (strcmp(redorblack, "r") == 0) {
      userpickblack = false;
    }
    else if (strcmp(redorblack, "b") == 0) {
      userpickblack = true;
    }
    else {
      fprintf(stderr, "error: invalid argument");
      return 1;
    }

    printf("The ball lands on #%d! \n", result);
    
    if ((result % 2 == 0 && userpickblack) || (result % 2 != 0 && !userpickblack)) {
      eventwl(betmoney, RB_LH_MULT, true);
      return 0;
    }
    else {
      eventwl(betmoney, LOSS, false);
      return 0;
    }
  }
  else if (strcmp(typeofbet, "l/h") == 0) {
    bool userpickhigh;
    char loworhigh[10];

    printf("Low or High (l/h): ");
    scanf("%9s", loworhigh);

    if (strcmp(loworhigh, "l") == 0) {
      userpickhigh = false;
    }
    else if (strcmp(loworhigh, "h") == 0) {
      userpickhigh = true;
    }
    else {
      fprintf(stderr, "error: invalid argument");
      return 1;
    }

    printf("The ball lands on #%d! \n", result);
    
    
    if ((result >= 18 && userpickhigh) || (result <= 18 && !userpickhigh)) {
      eventwl(betmoney, RB_LH_MULT, true);
      return 0;
    }
    else {
      eventwl(betmoney, LOSS, false);
      return 0;
    }
  }
  else if (strcmp(typeofbet, "doz") == 0) {
    int userpickdozn;

    printf("Dozen (1: 1-12, 2: 13-24, 3: 25-36): ");
    scanf("%d", &userpickdozn);

    if (userpickdozn > 3 || userpickdozn < 1) {
      fprintf(stderr, "error: invalid argument\n");
      return 1;
    }

    printf("The ball lands on #%d! \n", result);
    
    if ((userpickdozn == 1 && result >= 1 && result <= 12) || (userpickdozn == 2 && result >= 13 && result <= 24) || (userpickdozn == 3 && result >= 25 && result <= 36)) {
      eventwl(betmoney, DOZEN_MULT, true);
      return 0;
    }
    else {
      eventwl(betmoney, LOSS, false);
      return 0;
    }
  }
  else if (strcmp(typeofbet, "sin") == 0) {
    int userpickone;

    printf("Single (1-36): ");
    scanf("%d", &userpickone);

    if (userpickone < 1 || userpickone > 36) {
      fprintf(stderr, "error: invalid argument\n");
      return 1;
    }

    printf("The ball lands on #%d! \n", result);
    
    if (result == userpickone) {
      eventwl(betmoney, SINGLE_MULT, true);
      return 0;
    }
    else {
      eventwl(betmoney, LOSS, false);
      return 0;
    }
  }
  else if (strcmp(typeofbet, "dub") == 0) {
    int userpickone, userpicktwo;

    printf("Double (1-36): ");
    scanf("%d %d", &userpickone, &userpicktwo);

    if ((userpickone < 1 || userpickone > 36 || userpicktwo < 1 || userpicktwo > 36)) {
      fprintf(stderr, "error: invalid argument\n");
      return 1;
    }

    printf("The ball lands on #%d! \n", result);
    
    if (result == userpickone || result == userpicktwo) {
      eventwl(betmoney, DOUBLE_MULT, true);
      return 0;
    }
    else {
      eventwl(betmoney, LOSS, false);
      return 0;
    }
  }
  else if (strcmp(typeofbet, "tri") == 0) {
    int userpickone, userpicktwo, userpickthree;

    printf("Double (1-36): ");
    scanf("%d %d %d", &userpickone, &userpicktwo, &userpickthree);

    if ((userpickone < 1 || userpickone > 36 || userpicktwo < 1 || userpicktwo > 36 || userpickthree < 1 || userpickthree > 36)) {
      fprintf(stderr, "error: invalid argument\n");
      return 1;
    }

    printf("The ball lands on #%d! \n", result);
    
    if (result == userpickone || result == userpicktwo || result == userpickthree) {
      eventwl(betmoney, TRIPLE_MULT, true);
      return 0;
    }
    else {
      eventwl(betmoney, LOSS, false);
      return 0;
    }
  }
  else {
    fprintf(stderr, "error: invalid argument");
    return 1;
  }

  return 0;

}

uint8_t spinwheel() {
  unsigned int seed = 0;
  struct timespec ts;
  timespec_get(&ts, TIME_UTC); 
  seed ^= (unsigned int)(ts.tv_sec + ts.tv_nsec);
  seed ^= (unsigned int)getpid();
  srand(seed);
  return ezwheel[rand() % 37];
}

void eventwl(float bet, int multiplier, bool ifwin) {
  switch (ifwin) {
    case true:
      printf("You WIN +$%.2f", bet * multiplier - bet);
      break;
    case false:
      printf("You LOSE your initial bet of $%.2f", bet);
      break;
    default:
      fprintf(stderr, "error: eventwl switch error");
      exit(1);
  }
}