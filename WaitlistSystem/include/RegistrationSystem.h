#pragma once

#include "WaitlistPQ.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace reg {

struct Student {
  std::string id;
  std::string name;
  waitlist::Level level = waitlist::Level::FRESHMAN;
};

struct Course {
  std::string code;
  std::string title;
  int capacity = 0;

  std::vector<std::string> enrolledStudentIds;
  waitlist::WaitlistPQ waitlist;
};

class RegistrationSystem {
public:
  // Students
  bool addStudent(const std::string& id, const std::string& name, waitlist::Level level, std::string& err);
  const Student* getStudent(const std::string& id) const;
  std::vector<Student> listStudents() const;

  // Courses
  bool addCourse(const std::string& code, const std::string& title, int capacity, std::string& err);
  const Course* getCourse(const std::string& code) const;
  std::vector<Course> listCourses() const;

  // Registration
  // Returns true if enrolled immediately; false if waitlisted or failed (see msg).
  bool enroll(const std::string& studentId, const std::string& courseCode, std::string& msg);

  // Returns true if dropped; false if not enrolled or invalid (see msg).
  // If a seat frees, auto-enrolls next from waitlist (if any).
  bool drop(const std::string& studentId, const std::string& courseCode, std::string& msg);

  std::vector<std::string> coursesOfStudent(const std::string& studentId) const;

  // Simple stats
  int enrolledCount(const std::string& courseCode) const;
  int waitlistSize(const std::string& courseCode) const;

private:
  std::unordered_map<std::string, Student> students_;
  std::unordered_map<std::string, Course> courses_;

  static bool vecContains(const std::vector<std::string>& v, const std::string& x);
  static bool vecRemove(std::vector<std::string>& v, const std::string& x);
};

} // namespace reg


