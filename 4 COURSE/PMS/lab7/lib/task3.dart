import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:shared_preferences/shared_preferences.dart';

class Task3 extends StatefulWidget {
  const Task3({Key? key}) : super(key: key);

  @override
  _Task3State createState() => _Task3State();
}

class _Task3State extends State<Task3> {
  final _keyController = TextEditingController();
  final _valueController = TextEditingController();

  String? _value;
  List<String> _keyValuePairs = [];

  Future<void> _saveData() async {
    final key = _keyController.text;
    final value = _valueController.text;

    if (key.isNotEmpty && value.isNotEmpty) {
      final prefs = await SharedPreferences.getInstance();
      await prefs.setString(key, value);
    }
  }

  Future<void> _readData() async {
    final prefs = await SharedPreferences.getInstance();
    final allPrefs = prefs.getKeys();
    setState(() {
      _keyValuePairs =
          allPrefs.map((key) => '$key: ${prefs.getString(key)}').toList();
    });
  }

  Future<void> _deleteData() async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.remove(_keyController.text);
    //await _readData();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Color.fromARGB(255, 222, 220, 228),
        title: Text('Задание 3'),
        centerTitle: true,
      ),
      body: Padding(
        padding: EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            TextField(
              controller: _keyController,
              decoration: const InputDecoration(
                labelText: 'Ключ',
                labelStyle: TextStyle(
                  color: Colors.black,
                ),
                enabledBorder: UnderlineInputBorder(
                  borderSide: BorderSide(color: Colors.white),
                ),
                focusedBorder: UnderlineInputBorder(
                  borderSide: BorderSide(color: Colors.white),
                ),
                fillColor: Colors.white,
                filled: true,
              ),
              style: TextStyle(
                color: Colors.black,
              ),
              keyboardType: TextInputType.numberWithOptions(decimal: true),
              inputFormatters: [
                FilteringTextInputFormatter.allow(RegExp(r'[0-9.]')),
              ],
            ),
            SizedBox(height: 10),
            TextField(
              controller: _valueController,
              decoration: const InputDecoration(
                labelText: 'Значение',
                labelStyle: TextStyle(
                  color: Colors.black,
                ),
                enabledBorder: UnderlineInputBorder(
                  borderSide: BorderSide(color: Colors.white),
                ),
                focusedBorder: UnderlineInputBorder(
                  borderSide: BorderSide(color: Colors.white),
                ),
                fillColor: Colors.white,
                filled: true,
              ),
            ),
            SizedBox(height: 16),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                ElevatedButton(
                  onPressed: _saveData,
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.blue,
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(10),
                    ),
                  ),
                  child: Text(
                    'Create',
                    style: TextStyle(color: Colors.white),
                  ),
                ),
                ElevatedButton(
                  onPressed: _readData,
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.blue,
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(10),
                    ),
                  ),
                  child: Text(
                    'Read',
                    style: TextStyle(color: Colors.white),
                  ),
                ),
                ElevatedButton(
                  onPressed: _deleteData,
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.blue,
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(10),
                    ),
                  ),
                  child: Text(
                    'Delete',
                    style: TextStyle(color: Colors.white),
                  ),
                ),
              ],
            ),
            SizedBox(height: 16),
            Text('Пары:',
                style: TextStyle(
                  fontSize: 20, // Размер шрифта
                  fontWeight: FontWeight.bold,
                )),
            SizedBox(height: 10,),
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: _keyValuePairs.map((pair) => Text(pair, style: TextStyle(fontSize: 20),)).toList(),
            ),
          ],
        ),
      ),
    );
  }
}
