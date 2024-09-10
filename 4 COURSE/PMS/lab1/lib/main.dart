import 'worker.dart';
import 'manager.dart';
import 'engineer.dart';
import 'department.dart';

void main() {
  Worker worker1 = Worker('John Doe', 30, 30000);
  Manager manager1 = Manager('Alice', 40, 50000, 'Engineering');
  Engineer engineer1 = Engineer('Bob', 35, 40000, 'Software');

  manager1.organizeMeeting('New Project');
  manager1.logMeeting('New Project');

  List<Worker> workers = [worker1, manager1, engineer1];
  for (var worker in workers) {
    worker.work(task: 'daily tasks');
  }

  Map<String, Worker> workerMap = {'Manager': manager1, 'Engineer': engineer1};
  workerMap.forEach((role, worker) {
    print('$role: ${worker.getName}');
  });

  Set<String> skills = {'Communication', 'Leadership', 'Problem-solving'};
  skills.add('Teamwork');
  print('Skills: $skills');

  for (int i = 0; i < workers.length; i++) {
    if (workers[i].age <= 30) continue;
    print('${workers[i].getName} is eligible for a promotion.');
    if (i == 1) break;
  }

  try {
    int result = 10 ~/ 0;
    print(result);
  } catch (e) {
    print('Exception caught: $e');
  } finally {
    print('Cleaning up.');
  }

  Department engDept = EngineeringDepartment();
  engDept.conductMeeting();
  engDept.hireWorker(engineer1);

  Department hrDept = HRDepartment();
  hrDept.conductMeeting();
  hrDept.hireWorker(manager1);
}
