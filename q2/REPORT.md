# COMP 3430 - Assignment 2 Adedotun Adeyemo 7784807 Report

## What happens if a signal handler gets invoked when it’s already handling a signal for that same signal/handler? For example, what happens when a process receives a signal for SIGUSR1 when it’s already handling SIGUSR1?

---

From observation when the same signal handler gets invoked again while one is already running, the new signal is blocked. The print statement in signal handler 1 is only shown once. So the second SIGUSR1 signal will not run because the the signal handler is already in use.

## What happens if a signal handler gets invoked if the process is already handling a different signal? For example, what happens when a process receives a signal for SIGUSR2 when it’s busy handling SIGUSR1?

---

From observation if two different signal handlers are invoked since they are not the same signal the second signal is not blocked and both signal handlers can run. So the SIGUSR1 signal will run as well as the SIGUSR2 signal.
