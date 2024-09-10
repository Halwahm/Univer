import 'worker.dart';

class Engineer extends Worker {
  String specialty;

  Engineer(String name, int age, double salary, this.specialty)
      : super(name, age, salary);

  Engineer.withSpecialty(String name, int age, String specialty)
      : specialty = specialty,
        super(name, age, 50000.0);

  void develop() {
    print('$name is developing something in $specialty');
  }
}
