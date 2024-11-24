import 'package:flutter/material.dart';

import '../auth/auth_service.dart';
import '../auth/signin_page.dart';
import '../models/worker.dart';
import './../db_services.dart';

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key});

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final DatabaseService _databaseService = DatabaseService();
  final nameController = TextEditingController();
  final specializationController = TextEditingController();

  final nameController2 = TextEditingController();
  final specializationController2 = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      resizeToAvoidBottomInset: false,
      appBar: _appBar(),
      body: _buildUI(),
      floatingActionButton: FloatingActionButton(
        key: const ValueKey('addButton'),
        backgroundColor: Colors.blue,
        child: const Icon(
          Icons.add,
          color: Colors.white,
        ),
        onPressed: () {
          _addDialog();
        },
      ),
    );
  }

  PreferredSizeWidget _appBar() {
    return AppBar(
      backgroundColor: Colors.blue,
      centerTitle: true,
      title: const Text(
        'Workers',
        style: TextStyle(
          color: Colors.white,
        ),
      ),
      actions: [
        IconButton(
          icon: const Icon(Icons.logout),
          onPressed: () async {
            // Выполняем logout
            await AuthService().logout();
            // Возвращаемся на экран авторизации
            Navigator.of(context).pushReplacement(
              MaterialPageRoute(builder: (context) => const LoginScreen()),
            );
          },
        ),
      ],
    );
  }

  Widget _buildUI() {
    return SafeArea(
        child: Column(
      children: [
        _messagesListView(),
      ],
    ));
  }

  Widget _messagesListView() {
    return SizedBox(
      height: MediaQuery.of(context).size.height * 0.8,
      width: MediaQuery.of(context).size.width,
      child: StreamBuilder(
        stream: _databaseService.getWorkers(),
        builder: (context, snapshot) {
          List workers = snapshot.data?.docs ?? [];
          if (workers.isEmpty) {
            return const Center(
              child: Text('Add a Worker!'),
            );
          }
          return ListView.builder(
            itemCount: workers.length,
            itemBuilder: (context, index) {
              Worker worker = workers[index].data();
              String workerId = workers[index].id;

              return Draggable(
                feedback: Container(
                  decoration: BoxDecoration(
                    borderRadius:
                        BorderRadius.circular(10.0), // Закругление углов
                  ),
                  width: MediaQuery.of(context).size.width,
                  child: Card(
                    child: ListTile(
                      tileColor: Colors.blue[300],
                      title: Text("Имя: ${worker.name}",
                          style: const TextStyle(color: Colors.white)),
                      subtitle: Text("Специальность: ${worker.specialization}",
                          style: const TextStyle(color: Colors.white)),
                      trailing: Row(
                        mainAxisSize: MainAxisSize.min,
                        children: [
                          IconButton(
                            icon: Icon(Icons.edit, color: Colors.blue[800]),
                            onPressed: () {
                              _editDialog(worker, worker.name,
                                  worker.specialization, workerId);
                            },
                          ),
                          IconButton(
                            onPressed: () {
                              _databaseService.deleteWorker(workerId);
                            },
                            icon: Icon(Icons.delete, color: Colors.blue[800]),
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
                childWhenDragging: Container(),
                feedbackOffset: const Offset(0, -20),
                child: Card(
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10.0),
                  ),
                  child: ListTile(
                    tileColor: Colors.blue[300],
                    title: Text(
                      "Имя: ${worker.name}",
                      style: const TextStyle(color: Colors.white),
                    ),
                    subtitle: Text(
                      "Специальность: ${worker.specialization}",
                      style: const TextStyle(color: Colors.white),
                    ),
                    trailing: Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        IconButton(
                          icon: Icon(Icons.edit, color: Colors.blue[800]),
                          onPressed: () {
                            _editDialog(worker, worker.name,
                                worker.specialization, workerId);
                          },
                        ),
                        IconButton(
                          onPressed: () {
                            _databaseService.deleteWorker(workerId);
                          },
                          icon: Icon(Icons.delete, color: Colors.blue[800]),
                        ),
                      ],
                    ),
                  ),
                ),
              );
            },
          );
        },
      ),
    );
  }

  Future<void> _editDialog(Worker worker, String name, String specialization,
      String workerId) async {
    nameController.text = name;
    specializationController.text = specialization;

    return showDialog(
        context: context,
        builder: (context) {
          return AlertDialog(
            shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(0),
            ),
            title: const Text('Изменить'),
            content: SingleChildScrollView(
              child: Column(
                children: [
                  TextFormField(
                    key: const ValueKey('addField'),
                    controller: nameController,
                    decoration: const InputDecoration(labelText: 'Имя'),
                  ),
                  const SizedBox(
                    height: 20,
                  ),
                  TextFormField(
                    controller: specializationController,
                    decoration:
                        const InputDecoration(labelText: 'Специальность'),
                  )
                ],
              ),
            ),
            actions: [
              TextButton(
                  onPressed: () {
                    Navigator.pop(context);
                  },
                  child: const Text('Закрыть')),
              TextButton(
                  onPressed: () async {
                    Worker updatedWorker = worker.copyWith(
                        name: nameController.text.toString(),
                        specialization:
                            specializationController.text.toString());
                    _databaseService.updateWorker(workerId, updatedWorker);

                    nameController.clear();
                    specializationController.clear();
                    Navigator.pop(context);
                  },
                  child: const Text('Изменить')),
            ],
          );
        });
  }

  void _addDialog() async {
    return showDialog(
        context: context,
        builder: (context) {
          return AlertDialog(
            shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(0),
            ),
            title: const Text('Add worker'),
            content: SingleChildScrollView(
              child: Column(
                children: [
                  TextFormField(
                    controller: nameController2,
                    decoration: const InputDecoration(labelText: 'Имя'),
                  ),
                  const SizedBox(
                    height: 20,
                  ),
                  TextFormField(
                    controller: specializationController2,
                    decoration:
                        const InputDecoration(labelText: 'Специальность'),
                  )
                ],
              ),
            ),
            actions: [
              TextButton(
                  onPressed: () {
                    Navigator.pop(context);
                  },
                  child: const Text('Закрыть')),
              TextButton(
                  onPressed: () async {
                    Worker worker = Worker(
                        name: nameController2.text.toString(),
                        specialization:
                            specializationController2.text.toString());
                    _databaseService.addWorker(worker);
                    specializationController2.clear();
                    nameController2.clear();

                    Navigator.pop(context);
                  },
                  child: const Text('Добавить')),
            ],
          );
        });
  }
}
