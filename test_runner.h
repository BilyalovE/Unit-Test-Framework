#pragma once
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;


template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs){
    for(int i = 0; i < lhs.size(); ++i){
        if(lhs[i] != rhs[i]){
            return false;
        }
    }
    return true;
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u)
    {
        std::ostringstream os;
        os << " Assertion failed: " << std::endl;
        os << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

#define g(a) a
#define CONCAT(a) testRunner##a
#define TOKKEN(a) CONCAT(a)
#define UNIC_VAR TOKKEN(g(__LINE__))

#define RUN_TEST(tr, func) \
tr.RunTest(func, #func)

#define ASSERT_EQUAL(x, y) {                  \
    ostringstream UNIC_VAR;                   \
    UNIC_VAR << #x << " != " << #y << ",  "   \
    << __FILE__ << ": " << __LINE__;          \
    AssertEqual(x, y, UNIC_VAR.str());        \
}

#define ASSERT(x) {                           \
    ostringstream UNIC_VAR;                   \
    UNIC_VAR << #x << " is false, "           \
       << __FILE__ << ": " << __LINE__;       \
    AssertEqual(x, true, UNIC_VAR.str());     \
}


