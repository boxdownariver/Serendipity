#include <signal.h>

extern volatile sig_atomic_t stateProvider;

void handleSignal(const int sig);
