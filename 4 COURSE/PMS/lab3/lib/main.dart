import 'worker.dart';
import 'manager.dart';
import 'engineer.dart';
import 'OfficeWorker.dart';
import 'OfficeWorkerIterator.dart';

void main() async {
  Worker worker1 = Worker('John Doe', 30, 30000);
  Manager manager1 = Manager('Alice', 40, 50000, 'Engineering');
  Engineer engineer1 = Engineer('Bob', 25, 40000, 'Software');

  List<Worker> workersList = [worker1, manager1, engineer1];
  OfficeWorker officeWorker = OfficeWorker(workersList);

  OfficeWorkerIterator iterator = OfficeWorkerIterator(workersList);
  while (iterator.moveNext()) {
    print('Iterating worker: ${iterator.current.name}');
  }

  Set<String> skills = {'Coding', 'Leadership', 'Problem-solving'};
  worker1.showSkills(skills);

  int experienceYears = 4;
  worker1.promoteEligibility(experienceYears);

  manager1.organizeMeeting('Project Planning');
  engineer1.develop();

  await performAsyncTask();
  Future<double> futureResult = calculateSalaryAsync();
  futureResult.then((result) => print('Future result: $result'));

  await listenToSingleSubscriptionStream();
  listenToBroadcastStream();

  print(worker1.toString());
  Worker workerFromJson = Worker.fromJson({
    'name': 'Jane Doe',
    'age': 28,
    'salary': 32000,
  });
  print(workerFromJson.toString());
}

Future<void> performAsyncTask() async {
  print('Starting async task...');
  await Future.delayed(Duration(seconds: 2));
  print('Async task completed.');
}

Future<double> calculateSalaryAsync() async {
  await Future.delayed(Duration(seconds: 1));
  return 1000;
}

Stream<int> numberStream() async* {
  for (int i = 1; i <= 5; i++) {
    yield i;
    await Future.delayed(Duration(seconds: 1));
  }
}

Future<void> listenToSingleSubscriptionStream() async {
  await for (int number in numberStream()) {
    print('Received from stream: $number');
  }
}

Stream<int> broadcastStream = Stream<int>.periodic(
    Duration(seconds: 1), (x) => x).asBroadcastStream();

void listenToBroadcastStream() {
  broadcastStream.listen((data) {
    print('Broadcast stream listener 1: $data');
  });

  broadcastStream.listen((data) {
    print('Broadcast stream listener 2: $data');
  });
}
