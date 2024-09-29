import 'dart:io';

import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';

class Task4 extends StatefulWidget {
  const Task4({Key? key}) : super(key: key);

  @override
  _Task4State createState() => _Task4State();
}

class _Task4State extends State<Task4> {
  String _content = '';
  String _selectedDirectory = '';
  TextEditingController _textEditingController = TextEditingController();

  Future<File> _getFile(String directory) async {
    Directory appDirectory;

    if (Platform.isIOS) {
      // iOS директории
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
          appDirectory =
              await getTemporaryDirectory(); // iOS Cache maps to Temporary
          break;
        default:
          throw Exception('Directory not supported on iOS platform!');
      }
    } else if (Platform.isAndroid) {
      // Android директории
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
          appDirectory =
              await getTemporaryDirectory(); // Cache mapping to Temporary
          break;
        default:
          throw Exception('Directory not supported on Android platform!');
      }
    } else {
      throw Exception('Unsupported platform');
    }

    return File('${appDirectory.path}/example.txt');
  }

  Future<String> _readFile(String directory) async {
    try {
      final file = await _getFile(directory);
      final contents = await file.readAsString();
      return contents;
    } catch (e) {
      return 'Error reading file: $e';
    }
  }

  Future<void> _writeFile(String directory, String content) async {
    try {
      final file = await _getFile(directory);
      await file.writeAsString(content);
    } catch (e) {
      setState(() {
        _content = 'Error writing to file: $e';
      });
    }
  }

  @override
  void dispose() {
    _textEditingController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          backgroundColor: Color.fromARGB(255, 222, 220, 228),
          title: Text('Задание 4'),
          centerTitle: true,
        ),
        body: SingleChildScrollView(
          // Добавлен SingleChildScrollView
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
                SizedBox(height: 16),
                Text('Директория: $_selectedDirectory',
                    style: TextStyle(
                      fontSize: 15, // Размер шрифта
                      fontWeight: FontWeight.bold,
                    )),
                SizedBox(height: 16),
                Container(
                  padding: EdgeInsets.symmetric(horizontal: 25.0),
                  child: TextField(
                    controller: _textEditingController,
                    decoration: InputDecoration(
                      labelText: 'Вводимая информация',
                    ),
                  ),
                ),
                SizedBox(height: 16),
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
                      child: Text(
                        'Read File',
                        style: TextStyle(color: Colors.white),
                      ),
                    ),
                    ElevatedButton(
                      onPressed: () async {
                        final text = _textEditingController.text;
                        if (text.isNotEmpty) {
                          await _writeFile(_selectedDirectory, text);
                        }
                      },
                      style: ElevatedButton.styleFrom(
                        backgroundColor: Colors.blue,
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(10),
                        ),
                      ),
                      child: Text(
                        'Write File',
                        style: TextStyle(color: Colors.white),
                      ),
                    ),
                  ],
                ),
                SizedBox(height: 16),
                Text('Содержимое файла:'),
                SizedBox(height: 8),
                Text('$_content'),
                SizedBox(height: 16),
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
          minimumSize: Size(300, 40),
        ),
        child: Text(
          label,
          style: TextStyle(color: Colors.white, fontSize: 18),
        ),
      ),
    );
  }
}
