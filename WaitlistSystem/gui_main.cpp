#include "RegistrationSystem.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

static const char* levelName(waitlist::Level lvl) {
  switch (lvl) {
    case waitlist::Level::SENIOR: return "Senior";
    case waitlist::Level::JUNIOR: return "Junior";
    case waitlist::Level::SOPHOMORE: return "Sophomore";
    case waitlist::Level::FRESHMAN: return "Freshman";
    default: return "Unknown";
  }
}

static waitlist::Level levelFromIndex(int idx) {
  switch (idx) {
    case 0: return waitlist::Level::SENIOR;
    case 1: return waitlist::Level::JUNIOR;
    case 2: return waitlist::Level::SOPHOMORE;
    case 3: return waitlist::Level::FRESHMAN;
    default: return waitlist::Level::FRESHMAN;
  }
}

int main(int, char**) {
  if (!glfwInit()) return 1;

  // GL 3.0+ backend uses GLSL version string
  const char* glsl_version = "#version 130";

  GLFWwindow* window = glfwCreateWindow(900, 600, "WaitlistPQ (Dear ImGui)", nullptr, nullptr);
  if (window == nullptr) return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  reg::RegistrationSystem sys;
  std::string status = "Ready.";

  // Student form
  char newStudentId[64] = "";
  char newStudentName[96] = "";
  int newStudentLevelIdx = 0;

  // Course form
  char newCourseCode[32] = "";
  char newCourseTitle[96] = "";
  int newCourseCap = 30;

  // Selection
  std::string selectedStudentId;
  std::string selectedCourseCode;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Student Course Registration System");
    ImGui::Text("Waitlist priority: Senior(1) > Junior(2) > Sophomore(3) > Freshman(4)");
    ImGui::Separator();

    const auto students = sys.listStudents();
    const auto courses = sys.listCourses();

    if (ImGui::BeginTabBar("MainTabs")) {
      if (ImGui::BeginTabItem("Students")) {
        ImGui::InputText("Student ID", newStudentId, sizeof(newStudentId));
        ImGui::InputText("Name", newStudentName, sizeof(newStudentName));
        const char* levels[] = {"Senior", "Junior", "Sophomore", "Freshman"};
        ImGui::Combo("Level", &newStudentLevelIdx, levels, 4);

        if (ImGui::Button("Register Student")) {
          std::string err;
          if (sys.addStudent(newStudentId, newStudentName, levelFromIndex(newStudentLevelIdx), err)) {
            status = "Student registered: " + std::string(newStudentId);
            selectedStudentId = newStudentId;
            newStudentId[0] = '\0';
            newStudentName[0] = '\0';
          } else {
            status = "Student register failed: " + err;
          }
        }

        ImGui::Separator();
        ImGui::Text("Students:");
        for (const auto& s : students) {
          bool selected = (selectedStudentId == s.id);
          std::string label = s.id + " - " + s.name + " (" + levelName(s.level) + ")";
          if (ImGui::Selectable(label.c_str(), selected)) selectedStudentId = s.id;
        }
        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Courses")) {
        ImGui::InputText("Course Code", newCourseCode, sizeof(newCourseCode));
        ImGui::InputText("Title", newCourseTitle, sizeof(newCourseTitle));
        ImGui::InputInt("Capacity", &newCourseCap);
        if (newCourseCap < 1) newCourseCap = 1;

        if (ImGui::Button("Add Course")) {
          std::string err;
          if (sys.addCourse(newCourseCode, newCourseTitle, newCourseCap, err)) {
            status = "Course added: " + std::string(newCourseCode);
            selectedCourseCode = newCourseCode;
            newCourseCode[0] = '\0';
            newCourseTitle[0] = '\0';
          } else {
            status = "Add course failed: " + err;
          }
        }

        ImGui::Separator();
        ImGui::Text("Courses:");
        for (const auto& c : courses) {
          bool selected = (selectedCourseCode == c.code);
          const int enrolled = static_cast<int>(c.enrolledStudentIds.size());
          const int wlSize = c.waitlist.size();
          std::string label = c.code + " - " + c.title + "  (" + std::to_string(enrolled) + "/" +
                              std::to_string(c.capacity) + "), waitlist=" + std::to_string(wlSize);
          if (ImGui::Selectable(label.c_str(), selected)) selectedCourseCode = c.code;
        }
        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Registration")) {
        ImGui::Text("Selected Student: %s", selectedStudentId.empty() ? "-" : selectedStudentId.c_str());
        ImGui::Text("Selected Course: %s", selectedCourseCode.empty() ? "-" : selectedCourseCode.c_str());
        if (ImGui::Button("Enroll (or Waitlist)")) {
          if (selectedStudentId.empty() || selectedCourseCode.empty()) {
            status = "Select a student and a course first.";
          } else {
            std::string msg;
            sys.enroll(selectedStudentId, selectedCourseCode, msg);
            status = msg;
          }
        }
        ImGui::SameLine();
        if (ImGui::Button("Drop")) {
          if (selectedStudentId.empty() || selectedCourseCode.empty()) {
            status = "Select a student and a course first.";
          } else {
            std::string msg;
            sys.drop(selectedStudentId, selectedCourseCode, msg);
            status = msg;
          }
        }
        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("My Courses")) {
        if (selectedStudentId.empty()) {
          ImGui::Text("Select a student in the Students tab.");
        } else {
          ImGui::Text("Student: %s", selectedStudentId.c_str());
          const auto my = sys.coursesOfStudent(selectedStudentId);
          if (my.empty()) ImGui::Text("(No enrolled courses)");
          for (const auto& code : my) ImGui::BulletText("%s", code.c_str());
        }
        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Waitlists")) {
        if (selectedCourseCode.empty()) {
          ImGui::Text("Select a course in the Courses tab.");
        } else {
          ImGui::Text("Course: %s", selectedCourseCode.c_str());
          ImGui::Text("Waitlist size: %d", sys.waitlistSize(selectedCourseCode));
          ImGui::Text("Enrolled: %d", sys.enrolledCount(selectedCourseCode));
          ImGui::Text("Note: Auto-enroll happens when someone drops the course.");
        }
        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }

    ImGui::Separator();
    ImGui::Text("Status: %s", status.c_str());
    ImGui::End();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}


