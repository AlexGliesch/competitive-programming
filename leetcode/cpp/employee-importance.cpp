/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
public:
  int totalImportanceRec(unordered_map<int, Employee*>& m, int id) {
    int ans = m[id]->importance;
    if (m.count(id) > 0) {
      for (int sid : m[id]->subordinates)
        ans += totalImportanceRec(m, sid);
    }
    return ans;
  }
  
  int getImportance(vector<Employee*> employees, int id) {
    unordered_map<int, Employee*> m;
    for (int e = 0; e < employees.size(); ++e) {
      m[employees[e]->id] = employees[e];
    } 
    if (m.count(id) == 0) return 0;
    return totalImportanceRec(m, id);  
  }
};