import 'package:cloud_firestore/cloud_firestore.dart';

import 'models/worker.dart';

const String WORKER_COLLECTION_REF = "worker";

class DatabaseService {
  final _firestore = FirebaseFirestore.instance;

  late final CollectionReference _workerRef;

  DatabaseService() {
    _workerRef =
        _firestore.collection(WORKER_COLLECTION_REF).withConverter<Worker>(
            fromFirestore: (snapshots, _) => Worker.fromJson(
                  snapshots.data()!,
                ),
            toFirestore: (worker, _) => worker.toJson());
  }

  Stream<QuerySnapshot> getWorkers() {
    return _workerRef.snapshots();
  }

  Future<void> addWorker(Worker worker) async {
    await _workerRef.add(worker.toJson());
  }

  Future<void> updateWorker(String workerId, Worker worker) async {
    await _workerRef.doc(workerId).update(worker.toJson());
  }

  void deleteWorker(String workerId) async {
    _workerRef.doc(workerId).delete();
  }
}
