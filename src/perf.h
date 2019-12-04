#ifndef _PERF_H_
#define _PERF_H_

enum trx_pos
{
  NEWORDER = 0,
  PAYMENT = 1,
  ORDERSTAT = 2,
  DELIVERY = 3,
  SLEV = 4,
  MAX_POS = 5
};

#define MAX_PROCEED_COUNT (200)

int perf_init();
int perf_deinit();

void update_neword(double prcd[]);
double calc_neword(double cost[]);


#endif //_PERF_H_
