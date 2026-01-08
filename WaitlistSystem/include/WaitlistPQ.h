#pragma once

#include <string>
#include <vector>

namespace waitlist {

enum class Level {
  SENIOR = 1,
  JUNIOR = 2,
  SOPHOMORE = 3,
  FRESHMAN = 4
};

struct Entry {
  std::string studentId;
  Level level;
  int priority;
  long long timestamp;

  Entry(std::string id, Level lvl, long long time);
};

class WaitlistPQ {
private:
  std::vector<Entry> heap;
  long long currentTime;

  int parent(int i);
  int left(int i);
  int right(int i);

  void heapifyUp(int index);
  void heapifyDown(int index);

  bool higherPriority(const Entry& a, const Entry& b);

public:
  WaitlistPQ();

  bool isEmpty() const;

  void addToWaitlist(const std::string& studentId, Level level);
  Entry removeFromWaitlist(); // highest priority entry
  Entry autoEnroll();         // wrapper for removal

  int size() const;
};

} // namespace waitlist
