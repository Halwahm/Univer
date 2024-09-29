import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

class Worker {
  int? id;
  String? name;
  String? specialty;

  Worker({this.id, this.name, this.specialty});

  // Define a factory method to create a Bakery object from a map
  factory Worker.fromMap(Map<String, dynamic> map) {
    return Worker(
      id: map['id'],
      name: map['name'],
      specialty: map['specialty'],
    );
  }

  // Define a method to convert the Bakery object to a map
  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'name': name,
      'specialty': specialty,
    };
  }
}

class DatabaseHelper {
  static final DatabaseHelper instance = DatabaseHelper._init();

  static Database? _database;

  DatabaseHelper._init();

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDB('trash.db');
    return _database!;
  }

  Future<Database> _initDB(String filePath) async {
    final dbPath = await getDatabasesPath();
    final path = join(dbPath, filePath);

    return await openDatabase(path, version: 1, onCreate: _createDB);
  }

  Future<void> _createDB(Database db, int version) async {
    await db.execute('''CREATE TABLE worker(
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          name TEXT,
          specialty TEXT
        )
''');
  }

  Future<int> createWorker(Worker worker) async {
    final db = await instance.database;
    return db.insert('worker', worker.toMap());
  }

  Future<List<Worker>> readAllWorkers() async {
    final db = await instance.database;
    final result = await db.query('worker');
    return result.map((e) => Worker.fromMap(e)).toList();
  }

  Future<int> updateWorker(Worker bak) async {
    final db = await instance.database;
    return db
        .update('worker', bak.toMap(), where: 'id = ?', whereArgs: [bak.id]);
  }

  Future<int> deleteWorker(int id) async {
    final db = await instance.database;
    return db.delete('worker', where: 'id = ?', whereArgs: [id]);
  }
}

class Task2 extends StatefulWidget {
  const Task2({Key? key}) : super(key: key);

  @override
  _Task2State createState() => _Task2State();
}

class _Task2State extends State<Task2> {
  final TextEditingController _nameController = TextEditingController();
  final TextEditingController _specialtyController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Color.fromARGB(255, 222, 220, 228),
        title: Text('Задание 2'),
        centerTitle: true,
      ),
      body: FutureBuilder<List<Worker>>(
        future: DatabaseHelper.instance.readAllWorkers(),
        builder: (BuildContext context, AsyncSnapshot<List<Worker>> snapshot) {
          if (snapshot.hasData) {
            return ListView.builder(
              itemCount: snapshot.data!.length,
              itemBuilder: (BuildContext context, int index) {
                final worker = snapshot.data![index];
                return Container(
                  margin: EdgeInsets.symmetric(vertical: 8, horizontal: 16),
                  child: ListTile(
                    tileColor: Colors.white,
                    title: Text('Имя: ${worker.name!}'),
                    subtitle: Text('Специальность: ${worker.specialty}'),
                    trailing: Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        IconButton(
                          icon: Icon(Icons.edit, color: Colors.blue[300]),
                          onPressed: () async {
                            _nameController.text = worker.name!;
                            _specialtyController.text = worker.specialty!;
                            showDialog(
                              context: context,
                              builder: (BuildContext context) {
                                return AlertDialog(
                                  shape: RoundedRectangleBorder(
                                    borderRadius: BorderRadius.circular(10.0),
                                  ),
                                  backgroundColor: Colors.blue,
                                  title: Text(
                                    'Изменить рабочего',
                                    style: TextStyle(color: Colors.white),
                                  ),
                                  content: Column(
                                    mainAxisSize: MainAxisSize.min,
                                    children: [
                                      TextField(
                                        controller: _nameController,
                                        decoration: const InputDecoration(
                                          labelText: 'Имя',
                                          labelStyle: TextStyle(
                                            color: Colors.white,
                                          ),
                                          enabledBorder: UnderlineInputBorder(
                                            borderSide:
                                                BorderSide(color: Colors.white),
                                          ),
                                          focusedBorder: UnderlineInputBorder(
                                            borderSide:
                                                BorderSide(color: Colors.blue),
                                          ),
                                          fillColor: Colors.blue,
                                          filled: true,
                                        ),
                                        style: TextStyle(
                                          color: Colors.white,
                                        ),
                                      ),
                                      SizedBox(height: 20),
                                      TextField(
                                        controller: _specialtyController,
                                        decoration: const InputDecoration(
                                          labelText: 'Специальность',
                                          labelStyle: TextStyle(
                                            color: Colors.white,
                                          ),
                                          enabledBorder: UnderlineInputBorder(
                                            borderSide:
                                                BorderSide(color: Colors.white),
                                          ),
                                          focusedBorder: UnderlineInputBorder(
                                            borderSide:
                                                BorderSide(color: Colors.blue),
                                          ),
                                          fillColor: Colors.blue,
                                          filled: true,
                                        ),
                                        style: TextStyle(
                                          color: Colors.white,
                                        ),
                                      ),
                                    ],
                                  ),
                                  actions: [
                                    TextButton(
                                      child: Text(
                                        'Закрыть',
                                        style: TextStyle(color: Colors.white60),
                                      ),
                                      onPressed: () {
                                        Navigator.of(context).pop();
                                      },
                                    ),
                                    TextButton(
                                      child: Text(
                                        'Изменить',
                                        style: TextStyle(color: Colors.white60),
                                      ),
                                      onPressed: () async {
                                        final name = _nameController.text;
                                        final specialty =
                                            _specialtyController.text;

                                        worker.name = name;
                                        worker.specialty = specialty;

                                        await DatabaseHelper.instance
                                            .updateWorker(worker);

                                        setState(() {});

                                        Navigator.of(context).pop();
                                      },
                                    ),
                                  ],
                                );
                              },
                            );
                          },
                        ),
                        IconButton(
                          icon: Icon(Icons.delete, color: Colors.blue[300]),
                          onPressed: () async {
                            await DatabaseHelper.instance
                                .deleteWorker(worker.id!);
                            setState(() {});
                          },
                        ),
                      ],
                    ),
                  ),
                );
              },
            );
          } else {
            return Center(
              child: CircularProgressIndicator(),
            );
          }
        },
      ),
      bottomNavigationBar: Padding(
        padding: EdgeInsets.all(8.0),
        child: ElevatedButton(
          style: ElevatedButton.styleFrom(
            backgroundColor: Colors.blue,
            foregroundColor: Colors.white,
          ),
          onPressed: () {
            _nameController.text = '';
            _specialtyController.text = '';
            showDialog(
              context: context,
              builder: (BuildContext context) {
                return AlertDialog(
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10.0),
                  ),
                  backgroundColor: Colors.blue,
                  title: Text(
                    'Добавить рабочего',
                    style: TextStyle(color: Colors.white),
                  ),
                  content: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      TextField(
                        controller: _nameController,
                        decoration: const InputDecoration(
                          labelText: 'Имя',
                          labelStyle: TextStyle(
                            color: Colors.white,
                          ),
                          enabledBorder: UnderlineInputBorder(
                            borderSide: BorderSide(color: Colors.white),
                          ),
                          focusedBorder: UnderlineInputBorder(
                            borderSide: BorderSide(color: Colors.blue),
                          ),
                          fillColor: Colors.blue,
                          filled: true,
                        ),
                        style: TextStyle(
                          color: Colors.white,
                        ),
                      ),
                      SizedBox(height: 20),
                      TextField(
                        controller: _specialtyController,
                        decoration: const InputDecoration(
                          labelText: 'Специальность',
                          labelStyle: TextStyle(
                            color: Colors.white,
                          ),
                          enabledBorder: UnderlineInputBorder(
                            borderSide: BorderSide(color: Colors.white),
                          ),
                          focusedBorder: UnderlineInputBorder(
                            borderSide: BorderSide(color: Colors.blue),
                          ),
                          fillColor: Colors.blue,
                          filled: true,
                        ),
                        style: TextStyle(
                          color: Colors.white,
                        ),
                      ),
                    ],
                  ),
                  actions: [
                    TextButton(
                      child: Text(
                        'Закрыть',
                        style: TextStyle(color: Colors.white60),
                      ),
                      onPressed: () {
                        Navigator.of(context).pop();
                      },
                    ),
                    TextButton(
                      child: Text(
                        'Добавить',
                        style: TextStyle(color: Colors.white60),
                      ),
                      onPressed: () async {
                        final name = _nameController.text;
                        final specialty = _specialtyController.text;

                        await DatabaseHelper.instance
                            .createWorker(Worker(name: name, specialty: specialty));

                        setState(() {});

                        Navigator.of(context).pop();
                      },
                    ),
                  ],
                );
              },
            );
          },
          child: Text('Добавить рабочего'),
        ),
      ),
    );
  }
}
