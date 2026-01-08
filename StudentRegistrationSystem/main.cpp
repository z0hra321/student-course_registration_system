#include "WaitlistPQ.h"

#include <iostream>
#include <limits>
#include <stdexcept>

static const char* levelName(waitlist::Level lvl) {
  switch (lvl) {
    case waitlist::Level::SENIOR: return "Senior";
    case waitlist::Level::JUNIOR: return "Junior";
    case waitlist::Level::SOPHOMORE: return "Sophomore";
    case waitlist::Level::FRESHMAN: return "Freshman";
    default: return "Unknown";
  }
}

static waitlist::Level readLevelFromUser() {
  while (true) {
    std::cout << "Select level:\n"
              << "  1) Senior\n"
              << "  2) Junior\n"
              << "  3) Sophomore\n"
              << "  4) Freshman\n"
              << "Enter choice (1-4): ";
    int c = 0;
    if (!(std::cin >> c)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    switch (c) {
      case 1: return waitlist::Level::SENIOR;
      case 2: return waitlist::Level::JUNIOR;
      case 3: return waitlist::Level::SOPHOMORE;
      case 4: return waitlist::Level::FRESHMAN;
      default: break;
    }
  }
}

int main() {
  waitlist::WaitlistPQ wl;

  std::cout << "=== WaitlistPQ Interactive Demo ===\n";
  std::cout << "Priority: Senior(1) > Junior(2) > Sophomore(3) > Freshman(4)\n";
  std::cout << "Tie-break: FIFO within the same level.\n\n";

  while (true) {
    std::cout << "\nMenu:\n"
              << "  1) Add to waitlist\n"
              << "  2) Remove from waitlist (pop next)\n"
              << "  3) Auto-enroll (same as pop next)\n"
              << "  4) Size\n"
              << "  0) Exit\n"
              << "Enter choice: ";

    int choice = -1;
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (choice == 0) break;

    if (choice == 1) {
      std::string id;
      std::cout << "Enter studentId: ";
      std::cin >> id;
      waitlist::Level lvl = readLevelFromUser();
      wl.addToWaitlist(id, lvl);
      std::cout << "Added: " << id << " (" << levelName(lvl) << ")\n";
    } else if (choice == 2) {
      try {
        waitlist::Entry e = wl.removeFromWaitlist();
        std::cout << "Next: " << e.studentId << " (" << levelName(e.level) << ")\n";
      } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
      }
    } else if (choice == 3) {
      try {
        waitlist::Entry e = wl.autoEnroll();
        std::cout << "Auto-enrolled: " << e.studentId << " (" << levelName(e.level) << ")\n";
      } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
      }
    } else if (choice == 4) {
      std::cout << "Size: " << wl.size() << "\n";
    } else {
      std::cout << "Invalid choice.\n";
    }
  }

  return 0;
}

