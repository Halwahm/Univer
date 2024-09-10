import 'worker.dart';

abstract class Department {
  String departmentName;

  Department(this.departmentName);

  void conductMeeting();

  void hireWorker(Worker worker) {
    print('${worker.getName} hired to $departmentName');
  }
}

class EngineeringDepartment extends Department {
  EngineeringDepartment() : super('Engineering');

  @override
  void conductMeeting() {
    print('Engineering department is conducting a technical meeting.');
  }
}

class HRDepartment extends Department {
  HRDepartment() : super('HR');

  @override
  void conductMeeting() {
    print('HR department is conducting a recruitment meeting.');
  }
}
