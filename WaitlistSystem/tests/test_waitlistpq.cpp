#include "WaitlistPQ.h"

#include <cassert>
#include <iostream>

int main() {
  waitlist::WaitlistPQ wl;

  // Seniors should be served first; FIFO among same level.
  wl.addToWaitlist("A", waitlist::Level::SOPHOMORE);
  wl.addToWaitlist("B", waitlist::Level::SENIOR);
  wl.addToWaitlist("C", waitlist::Level::SENIOR);
  wl.addToWaitlist("D", waitlist::Level::JUNIOR);

  waitlist::Entry s1 = wl.removeFromWaitlist();
  waitlist::Entry s2 = wl.removeFromWaitlist();
  waitlist::Entry s3 = wl.removeFromWaitlist();
  waitlist::Entry s4 = wl.removeFromWaitlist();

  assert(s1.studentId == "B");
  assert(s2.studentId == "C");
  assert(s3.studentId == "D");
  assert(s4.studentId == "A");

  std::cout << "test_waitlistpq: PASS\n";
  return 0;
}

