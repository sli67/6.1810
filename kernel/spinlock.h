// Mutual exclusion lock.
struct spinlock {
  uint locked;       // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
#ifdef LAB_LOCK
  int nts;
  int n;
#endif
};

#ifdef LAB_LOCK
// Reader-writer lock.
struct rwspinlock {
  struct spinlock l;
  uint rw, stat[8], rcnt;
  uint wwait, wholder;
};
//rw 0 vacant
//rw 1 read
//rw 2 write
#endif
