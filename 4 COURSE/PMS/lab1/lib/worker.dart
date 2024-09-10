class Worker {
  String name;
  int age;
  double salary;

  Worker(this.name, this.age, this.salary);

  Worker.withoutSalary(this.name, this.age) : salary = 0.0;

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
}
