import 'worker.dart';

class OfficeWorkerIterator implements Iterator<Worker> {
  final List<Worker> _workers;
  int _currentIndex = -1;

  OfficeWorkerIterator(this._workers);

  @override
  Worker get current {
    if (_currentIndex < 0 || _currentIndex >= _workers.length) {
      throw StateError('No current element');
    }
    return _workers[_currentIndex];
  }

  @override
  bool moveNext() {
    _currentIndex++;
    return _currentIndex < _workers.length;
  }
}
