
import 'package:cloud_firestore/cloud_firestore.dart';
import 'models/worker.dart';

const String WORKER_COLLECTION_REF = "worker";

class DatabaseService{
    final _firestore = FirebaseFirestore.instance;

    late final CollectionReference _workerRef;

    DatabaseService(){
    _workerRef = _firestore.collection(WORKER_COLLECTION_REF).withConverter<Worker>(
      fromFirestore: (snapshots, _)=> Worker.fromJson(snapshots.data()!,),
      toFirestore: (worker, _) => worker.toJson()
  );
}

    Stream<QuerySnapshot> getWorkers(){
      return _workerRef.snapshots();
    }


    void addWorker(Worker worker) async{
      _workerRef.add(worker);
    }

    void updateWorker(String workerId, Worker worker) async{
      _workerRef.doc(workerId).update(worker.toJson());
    }

    void deleteWorker(String workerId) async{
      _workerRef.doc(workerId).delete();
    }
}