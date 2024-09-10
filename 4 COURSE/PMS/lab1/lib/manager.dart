import 'worker.dart';
import 'organizational_interface.dart';

class Manager extends Worker implements Organizable {
  String department;

  Manager(String name, int age, double salary, this.department)
      : super(name, age, salary);

  @override
  void organizeMeeting(String topic) {
    print('$name is organizing a meeting on $topic');
  }

  @override
  void logMeeting(String topic) {
    print('$name logged the meeting on $topic in the $department department');
  }
}
