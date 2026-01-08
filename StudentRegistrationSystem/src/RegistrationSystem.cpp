#include "RegistrationSystem.h"

namespace reg {

bool RegistrationSystem::vecContains(const std::vector<std::string>& v, const std::string& x) {
  for (const auto& s : v) if (s == x) return true;
  return false;
}

bool RegistrationSystem::vecRemove(std::vector<std::string>& v, const std::string& x) {
  for (std::size_t i = 0; i < v.size(); ++i) {
    if (v[i] == x) {
      v.erase(v.begin() + static_cast<long>(i));
      return true;
    }
  }
  return false;
}

bool RegistrationSystem::addStudent(const std::string& id, const std::string& name, waitlist::Level level, std::string& err) {
  if (id.empty()) { err = "Student ID is empty."; return false; }
  if (name.empty()) { err = "Student name is empty."; return false; }
  if (students_.find(id) != students_.end()) { err = "Student already exists."; return false; }
  students_.insert({id, Student{id, name, level}});
  err.clear();
  return true;
}

const Student* RegistrationSystem::getStudent(const std::string& id) const {
  auto it = students_.find(id);
  if (it == students_.end()) return nullptr;
  return &it->second;
}

std::vector<Student> RegistrationSystem::listStudents() const {
  std::vector<Student> out;
  out.reserve(students_.size());
  for (const auto& kv : students_) out.push_back(kv.second);
  return out;
}

bool RegistrationSystem::addCourse(const std::string& code, const std::string& title, int capacity, std::string& err) {
  if (code.empty()) { err = "Course code is empty."; return false; }
  if (title.empty()) { err = "Course title is empty."; return false; }
  if (capacity <= 0) { err = "Capacity must be > 0."; return false; }
  if (courses_.find(code) != courses_.end()) { err = "Course already exists."; return false; }
  Course c;
  c.code = code;
  c.title = title;
  c.capacity = capacity;
  courses_.insert({code, c});
  err.clear();
  return true;
}

const Course* RegistrationSystem::getCourse(const std::string& code) const {
  auto it = courses_.find(code);
  if (it == courses_.end()) return nullptr;
  return &it->second;
}

std::vector<Course> RegistrationSystem::listCourses() const {
  std::vector<Course> out;
  out.reserve(courses_.size());
  for (const auto& kv : courses_) out.push_back(kv.second);
  return out;
}

bool RegistrationSystem::enroll(const std::string& studentId, const std::string& courseCode, std::string& msg) {
  auto sit = students_.find(studentId);
  if (sit == students_.end()) { msg = "Student not found."; return false; }
  auto cit = courses_.find(courseCode);
  if (cit == courses_.end()) { msg = "Course not found."; return false; }

  Course& c = cit->second;
  if (vecContains(c.enrolledStudentIds, studentId)) {
    msg = "Already enrolled in this course.";
    return true;
  }

  if (static_cast<int>(c.enrolledStudentIds.size()) < c.capacity) {
    c.enrolledStudentIds.push_back(studentId);
    msg = "Enrolled successfully.";
    return true;
  }

  // Full -> waitlist
  c.waitlist.addToWaitlist(studentId, sit->second.level);
  msg = "Course full: added to waitlist.";
  return false;
}

bool RegistrationSystem::drop(const std::string& studentId, const std::string& courseCode, std::string& msg) {
  auto sit = students_.find(studentId);
  if (sit == students_.end()) { msg = "Student not found."; return false; }
  auto cit = courses_.find(courseCode);
  if (cit == courses_.end()) { msg = "Course not found."; return false; }

  Course& c = cit->second;
  if (!vecRemove(c.enrolledStudentIds, studentId)) {
    msg = "Student is not enrolled in this course.";
    return false;
  }

  // Seat freed -> auto-enroll next from waitlist if available
  if (!c.waitlist.isEmpty()) {
    waitlist::Entry next = c.waitlist.autoEnroll();
    c.enrolledStudentIds.push_back(next.studentId);
    msg = "Dropped. Auto-enrolled from waitlist: " + next.studentId + ".";
    return true;
  }

  msg = "Dropped successfully.";
  return true;
}

std::vector<std::string> RegistrationSystem::coursesOfStudent(const std::string& studentId) const {
  std::vector<std::string> out;
  if (students_.find(studentId) == students_.end()) return out;
  for (const auto& kv : courses_) {
    if (vecContains(kv.second.enrolledStudentIds, studentId)) out.push_back(kv.first);
  }
  return out;
}

int RegistrationSystem::enrolledCount(const std::string& courseCode) const {
  auto it = courses_.find(courseCode);
  if (it == courses_.end()) return 0;
  return static_cast<int>(it->second.enrolledStudentIds.size());
}

int RegistrationSystem::waitlistSize(const std::string& courseCode) const {
  auto it = courses_.find(courseCode);
  if (it == courses_.end()) return 0;
  return it->second.waitlist.size();
}

} // namespace reg


