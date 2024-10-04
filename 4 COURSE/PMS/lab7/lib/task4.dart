import 'dart:convert';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:lab1/task2.dart';
import 'package:path_provider/path_provider.dart';

class Task4 extends StatefulWidget {
  const Task4({Key? key}) : super(key: key);

  @override
  _Task4State createState() => _Task4State();
}

class _Task4State extends State<Task4> {
  String _content = '';
  String _selectedDirectory = '';
  TextEditingController _nameController = TextEditingController();
  TextEditingController _specialtyController = TextEditingController();

  Future<File> _getFile(String directory) async {
    Directory appDirectory;

    if (Platform.isIOS) {
      switch (directory) {
        case 'TemporaryDirectory':
          appDirectory = await getTemporaryDirectory();
          break;
        case 'ApplicationDocumentsDirectory':
          appDirectory = await getApplicationDocumentsDirectory();
          break;
        case 'ApplicationSupportDirectory':
          appDirectory = await getApplicationSupportDirectory();
          break;
        case 'LibraryDirectory':
          appDirectory = await getLibraryDirectory();
          break;
        case 'CacheDirectory':
          appDirectory = await getTemporaryDirectory();
          break;
        default:
          throw Exception('Directory not supported on iOS platform!');
      }
    } else if (Platform.isAndroid) {
      switch (directory) {
        case 'TemporaryDirectory':
          appDirectory = await getTemporaryDirectory();
          break;
        case 'ApplicationDocumentsDirectory':
          appDirectory = await getApplicationDocumentsDirectory();
          break;
        case 'ApplicationSupportDirectory':
          appDirectory = await getApplicationSupportDirectory();
          break;
        case 'ExternalStorageDirectory':
          appDirectory = (await getExternalStorageDirectory())!;
          break;
        case 'ExternalCacheDirectories':
          appDirectory = (await getExternalCacheDirectories())!.first;
          break;
        case 'ExternalStorageDirectories':
          appDirectory = (await getExternalStorageDirectories())!.first;
          break;
        case 'Downloads':
          appDirectory = (await getDownloadsDirectory())!;
          break;
        case 'CacheDirectory':
          appDirectory = await getTemporaryDirectory();
          break;
        default:
          throw Exception('Directory not supported on Android platform!');
      }
    } else {
      throw Exception('Unsupported platform');
    }

    return File('${appDirectory.path}/worker.json');
  }

  Future<String> _readFile(String directory) async {
    try {
      final file = await _getFile(directory);
      final contents = await file.readAsString();

      // Преобразуем JSON-строку обратно в объект Worker
      final workerMap = jsonDecode(contents);
      Worker worker = Worker.fromMap(workerMap);

      return 'Имя: ${worker.name}, Специальность: ${worker.specialty}';
    } catch (e) {
      return 'Error reading file: $e';
    }
  }

  Future<void> _writeFile(String directory, Worker worker) async {
    try {
      final file = await _getFile(directory);
      // Конвертируем объект Worker в строку JSON
      final workerJson = jsonEncode(worker.toMap());
      await file.writeAsString(workerJson);
    } catch (e) {
      setState(() {
        _content = 'Error writing to file: $e';
      });
    }
  }

  @override
  void dispose() {
    _nameController.dispose();
    _specialtyController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          backgroundColor: const Color.fromARGB(255, 222, 220, 228),
          title: const Text('Задание 4'),
          centerTitle: true,
        ),
        body: SingleChildScrollView(
          child: Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                _buildDirectoryButton('TemporaryDirectory', 'Temporary'),
                _buildDirectoryButton(
                    'ApplicationDocumentsDirectory', 'Documents'),
                _buildDirectoryButton(
                    'ApplicationSupportDirectory', 'Application Support'),
                _buildDirectoryButton('LibraryDirectory', 'Library'),
                _buildDirectoryButton('CacheDirectory', 'Cache'),
                _buildDirectoryButton(
                    'ExternalStorageDirectory', 'External Storage'),
                _buildDirectoryButton(
                    'ExternalCacheDirectories', 'External Cache'),
                _buildDirectoryButton('ExternalStorageDirectories',
                    'External Storage Directories'),
                _buildDirectoryButton('Downloads', 'Downloads'),
                const SizedBox(height: 16),
                Text('Директория: $_selectedDirectory',
                    style: const TextStyle(
                      fontSize: 15,
                      fontWeight: FontWeight.bold,
                    )),
                const SizedBox(height: 16),
                Container(
                  padding: const EdgeInsets.symmetric(horizontal: 25.0),
                  child: TextField(
                    controller: _nameController,
                    decoration: const InputDecoration(
                      labelText: 'Имя',
                    ),
                  ),
                ),
                const SizedBox(height: 16),
                Container(
                  padding: const EdgeInsets.symmetric(horizontal: 25.0),
                  child: TextField(
                    controller: _specialtyController,
                    decoration: const InputDecoration(
                      labelText: 'Специальность',
                    ),
                  ),
                ),
                const SizedBox(height: 16),
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                  children: [
                    ElevatedButton(
                      onPressed: () async {
                        final content = await _readFile(_selectedDirectory);
                        setState(() {
                          _content = content;
                        });
                      },
                      style: ElevatedButton.styleFrom(
                        backgroundColor: Colors.blue,
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(10),
                        ),
                      ),
                      child: const Text(
                        'Читать файл',
                        style: TextStyle(color: Colors.white),
                      ),
                    ),
                    ElevatedButton(
                      onPressed: () async {
                        final worker = Worker(
                          name: _nameController.text,
                          specialty: _specialtyController.text,
                        );

                        await _writeFile(_selectedDirectory, worker);
                        setState(() {});
                      },
                      style: ElevatedButton.styleFrom(
                        backgroundColor: Colors.blue,
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(10),
                        ),
                      ),
                      child: const Text(
                        'Записать файл',
                        style: TextStyle(color: Colors.white),
                      ),
                    ),
                  ],
                ),
                const SizedBox(height: 16),
                const Text('Содержимое файла:'),
                const SizedBox(height: 8),
                Text(_content),
                const SizedBox(height: 16),
              ],
            ),
          ),
        ));
  }

  Widget _buildDirectoryButton(String directoryKey, String label) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 8.0),
      child: ElevatedButton(
        onPressed: () {
          setState(() {
            _selectedDirectory = directoryKey;
          });
        },
        style: ElevatedButton.styleFrom(
          backgroundColor: Colors.blue,
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(10),
          ),
          minimumSize: const Size(300, 40),
        ),
        child: Text(
          label,
          style: const TextStyle(color: Colors.white, fontSize: 18),
        ),
      ),
    );
  }
}
