import 'dart:convert';
import 'mixins.dart';

class Worker with PersonInfoMixin {
  String name;
  int age;
  double salary;

  Worker(this.name, this.age, this.salary);

  String get getName => name;
  set setName(String newName) => name = newName;

  int get getAge => age;
  set setAge(int newAge) => age = newAge;

  double get getSalary => salary;
  set setSalary(double newSalary) => salary = newSalary;

  static int workerCount = 0;

  static void incrementWorkerCount() {
    workerCount++;
  }

  void work({String task = 'default task'}) {
    print('$name is working on $task');
  }

  void performTask(Function task) {
    task();
  }

  void takeBreak([int minutes = 10]) {
    print('$name is taking a break for $minutes minutes');
  }

  Map<String, dynamic> toJson() {
    return {
      'name': name,
      'age': age,
      'salary': salary,
    };
  }

  static Worker fromJson(Map<String, dynamic> json) {
    return Worker(
      json['name'],
      json['age'],
      (json['salary'] as num).toDouble(),
    );
  }

  @override
  String toString() {
    return jsonEncode(toJson());
  }
}
