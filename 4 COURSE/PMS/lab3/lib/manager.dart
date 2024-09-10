import 'worker.dart';
import 'organizational_interface.dart';

class Manager extends Worker implements Organizable, Comparable<Manager> {
  String department;

  Manager(String name, int age, double salary, this.department)
      : super(name, age, salary);

  Manager.forHR(String name, int age)
      : department = 'HR',
        super(name, age, 40000.0);

  @override
  void organizeMeeting(String topic) {
    print('$name is organizing a meeting on $topic');
  }

  @override
  void assignTask(String task) {
    print('$name is assigning task: $task');
  }

  @override
  int compareTo(Manager other) {
    return this.salary.compareTo(other.salary);
  }
}
