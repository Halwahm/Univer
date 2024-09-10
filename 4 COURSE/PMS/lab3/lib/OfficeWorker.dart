import 'OfficeWorkerIterator.dart';
import 'worker.dart';

class OfficeWorker implements Iterable<Worker> {
  List<Worker> _workers;

  OfficeWorker(this._workers);

  @override
  Iterator<Worker> get iterator => OfficeWorkerIterator(_workers);

  @override
  Iterable<Worker> take(int count) {
    return _workers.take(count);
  }

  @override
  bool any(bool Function(Worker element) test) {
    return _workers.any(test);
  }

  @override
  Iterable<R> cast<R>() {
    return _workers.cast<R>();
  }

  @override
  bool contains(Object? element) {
    return _workers.contains(element);
  }

  @override
  Worker elementAt(int index) {
    return _workers.elementAt(index);
  }

  @override
  bool every(bool Function(Worker element) test) {
    return _workers.every(test);
  }

  @override
  Iterable<T> expand<T>(Iterable<T> Function(Worker element) toElements) {
    return _workers.expand(toElements);
  }

  @override
  Worker firstWhere(bool Function(Worker element) test, {Worker Function()? orElse}) {
    return _workers.firstWhere(test, orElse: orElse);
  }

  @override
  T fold<T>(T initialValue, T Function(T previousValue, Worker element) combine) {
    return _workers.fold(initialValue, combine);
  }

  @override
  Iterable<Worker> followedBy(Iterable<Worker> other) {
    return _workers.followedBy(other);
  }

  @override
  void forEach(void Function(Worker element) action) {
    _workers.forEach(action);
  }

  @override
  bool get isEmpty => _workers.isEmpty;

  @override
  bool get isNotEmpty => _workers.isNotEmpty;

  @override
  String join([String separator = ""]) {
    return _workers.join(separator);
  }

  @override
  Worker get last => _workers.last;

  @override
  Worker lastWhere(bool Function(Worker element) test, {Worker Function()? orElse}) {
    return _workers.lastWhere(test, orElse: orElse);
  }

  @override
  int get length => _workers.length;

  @override
  Iterable<T> map<T>(T Function(Worker e) toElement) {
    return _workers.map(toElement);
  }

  @override
  Worker reduce(Worker Function(Worker value, Worker element) combine) {
    return _workers.reduce(combine);
  }

  @override
  Worker get single => _workers.single;

  @override
  Worker singleWhere(bool Function(Worker element) test, {Worker Function()? orElse}) {
    return _workers.singleWhere(test, orElse: orElse);
  }

  @override
  Iterable<Worker> skip(int count) {
    return _workers.skip(count);
  }

  @override
  Iterable<Worker> skipWhile(bool Function(Worker value) test) {
    return _workers.skipWhile(test);
  }

  @override
  Iterable<Worker> takeWhile(bool Function(Worker value) test) {
    return _workers.takeWhile(test);
  }

  @override
  List<Worker> toList({bool growable = true}) {
    return _workers.toList(growable: growable);
  }

  @override
  Set<Worker> toSet() {
    return _workers.toSet();
  }

  @override
  Iterable<Worker> where(bool Function(Worker element) test) {
    return _workers.where(test);
  }

  @override
  Iterable<T> whereType<T>() {
    return _workers.whereType<T>();
  }

  @override
  // TODO: implement first
  Worker get first => throw UnimplementedError();
}
