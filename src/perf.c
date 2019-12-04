#include "perf.h"
#include <pthread.h>
#include <stdint.h>

pthread_spinlock_t spinlock_neword;

double tpcc_perf[MAX_POS][MAX_PROCEED_COUNT];
uint64_t tpcc_count[MAX_POS];

void static init_neword()
{
  tpcc_count[NEWORDER] = 0;
  tpcc_perf[NEWORDER][0] = 0;
  tpcc_perf[NEWORDER][1] = 0;
  tpcc_perf[NEWORDER][2] = 0;
  tpcc_perf[NEWORDER][3] = 0;
  tpcc_perf[NEWORDER][4] = 0;
  tpcc_perf[NEWORDER][5] = 0;
  tpcc_perf[NEWORDER][6] = 0;
  tpcc_perf[NEWORDER][7] = 0;
  tpcc_perf[NEWORDER][8] = 0;
}

int perf_init()
{
  init_neword();

  int r = 0;
  r = pthread_spin_init(&spinlock_neword, PTHREAD_PROCESS_PRIVATE);
  if (r < 0)
    return r;

  return 0;
}

int perf_deinit()
{
  pthread_spin_destroy(&spinlock_neword);
  return 0;
}

void update_neword(double prcd[])
{
  pthread_spin_lock(&spinlock_neword);
  tpcc_count[NEWORDER]++;
  tpcc_perf[NEWORDER][0] += prcd[0];
  tpcc_perf[NEWORDER][1] += prcd[1];
  tpcc_perf[NEWORDER][2] += prcd[2];
  tpcc_perf[NEWORDER][3] += prcd[3];
  tpcc_perf[NEWORDER][4] += prcd[4];
  tpcc_perf[NEWORDER][5] += prcd[5];
  tpcc_perf[NEWORDER][6] += prcd[6];
  tpcc_perf[NEWORDER][7] += prcd[7];
  tpcc_perf[NEWORDER][8] += prcd[8];
  pthread_spin_unlock(&spinlock_neword);
}

double calc_neword(double cost[])
{
  pthread_spin_lock(&spinlock_neword);
  cost[0] = tpcc_perf[NEWORDER][0] / tpcc_count[NEWORDER];
  cost[1] = tpcc_perf[NEWORDER][1] / tpcc_count[NEWORDER];
  cost[2] = tpcc_perf[NEWORDER][2] / tpcc_count[NEWORDER];
  cost[3] = tpcc_perf[NEWORDER][3] / tpcc_count[NEWORDER];
  cost[4] = tpcc_perf[NEWORDER][4] / tpcc_count[NEWORDER];
  cost[5] = tpcc_perf[NEWORDER][5] / tpcc_count[NEWORDER];
  cost[6] = tpcc_perf[NEWORDER][6] / tpcc_count[NEWORDER];
  cost[7] = tpcc_perf[NEWORDER][7] / tpcc_count[NEWORDER];
  cost[8] = tpcc_perf[NEWORDER][8] / tpcc_count[NEWORDER];
  pthread_spin_unlock(&spinlock_neword);
}

void reset_neword()
{
  pthread_spin_lock(&spinlock_neword);
  tpcc_count[NEWORDER] = 0;
  tpcc_perf[NEWORDER][0] = 0;
  tpcc_perf[NEWORDER][1] = 0;
  tpcc_perf[NEWORDER][2] = 0;
  tpcc_perf[NEWORDER][3] = 0;
  tpcc_perf[NEWORDER][4] = 0;
  tpcc_perf[NEWORDER][5] = 0;
  tpcc_perf[NEWORDER][6] = 0;
  tpcc_perf[NEWORDER][7] = 0;
  tpcc_perf[NEWORDER][8] = 0;
  pthread_spin_unlock(&spinlock_neword);
}
