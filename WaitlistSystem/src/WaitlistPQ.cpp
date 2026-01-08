#include "WaitlistPQ.h"

#include <stdexcept>
#include <utility>

namespace waitlist {

// ---------- Entry ----------
Entry::Entry(std::string id, Level lvl, long long time)
    : studentId(std::move(id)), level(lvl), priority(static_cast<int>(lvl)), timestamp(time) {}

// ---------- WaitlistPQ ----------
WaitlistPQ::WaitlistPQ() : currentTime(0) {}

int WaitlistPQ::parent(int i) { return (i - 1) / 2; }
int WaitlistPQ::left(int i) { return 2 * i + 1; }
int WaitlistPQ::right(int i) { return 2 * i + 2; }

bool WaitlistPQ::higherPriority(const Entry& a, const Entry& b) {
  if (a.priority != b.priority) return a.priority < b.priority; // senior first
  return a.timestamp < b.timestamp;                              // FIFO if same level
}

void WaitlistPQ::heapifyUp(int index) {
  while (index > 0 && higherPriority(heap[index], heap[parent(index)])) {
    std::swap(heap[index], heap[parent(index)]);
    index = parent(index);
  }
}

void WaitlistPQ::heapifyDown(int index) {
  int smallest = index;
  int l = left(index);
  int r = right(index);

  if (l < static_cast<int>(heap.size()) && higherPriority(heap[l], heap[smallest])) smallest = l;
  if (r < static_cast<int>(heap.size()) && higherPriority(heap[r], heap[smallest])) smallest = r;

  if (smallest != index) {
    std::swap(heap[index], heap[smallest]);
    heapifyDown(smallest);
  }
}

bool WaitlistPQ::isEmpty() const { return heap.empty(); }
int WaitlistPQ::size() const { return static_cast<int>(heap.size()); }

// ---------- Operations ----------
void WaitlistPQ::addToWaitlist(const std::string& studentId, Level level) {
  Entry e(studentId, level, currentTime++);
  heap.push_back(e);
  heapifyUp(static_cast<int>(heap.size()) - 1);
}

Entry WaitlistPQ::removeFromWaitlist() {
  if (isEmpty()) throw std::runtime_error("Waitlist is empty");

  Entry top = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  if (!isEmpty()) heapifyDown(0);
  return top;
}

Entry WaitlistPQ::autoEnroll() { return removeFromWaitlist(); }

} // namespace waitlist
