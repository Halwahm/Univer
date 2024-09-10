import 'worker.dart';

abstract class Department {
  String name;
  List<Worker> workers = [];

  Department(this.name);

  void addWorker(Worker worker) {
    workers.add(worker);
    print('${worker.name} hired to $name');
  }

  void removeWorker(Worker worker) {
    workers.remove(worker);
    print('${worker.name} removed from $name');
  }

  void conductMeeting();
}

class HRDepartment extends Department {
  HRDepartment() : super('HR');

  @override
  void conductMeeting() {
    print('HR department is conducting a recruitment meeting.');
  }
}

class EngineeringDepartment extends Department {
  EngineeringDepartment() : super('Engineering');

  @override
  void conductMeeting() {
    print('Engineering department is conducting a technical meeting.');
  }
}
