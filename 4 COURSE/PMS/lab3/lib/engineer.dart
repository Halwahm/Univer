import 'worker.dart';
import 'dart:collection';

class Engineer extends Worker with IterableMixin<Engineer> implements Iterator<Engineer> {
  String specialty;
  int _index = -1;

  Engineer(String name, int age, double salary, this.specialty)
      : super(name, age, salary);

  Engineer.withSpecialty(String name, int age, String specialty)
      : this.specialty = specialty,
        super(name, age, 50000.0);

  void develop() {
    print('$name is developing something in $specialty');
  }

  @override
  Iterator<Engineer> get iterator => this;

  @override
  Engineer get current => this;

  @override
  bool moveNext() {
    if (_index < 0) {
      _index++;
      return true;
    }
    return false;
  }

  @override
  void reset() {
    _index = -1;
  }
}
