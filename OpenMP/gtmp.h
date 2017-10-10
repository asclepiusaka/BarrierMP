//
// Created by saka on 10/4/17.
//

#ifndef OPENMPBARRIER_GTMP_H
#define OPENMPBARRIER_GTMP_H

void gtmp_init(int num_threads);
void gtmp_barrier();
void gtmp_finalize();
#endif //OPENMPBARRIER_GTMP_H
