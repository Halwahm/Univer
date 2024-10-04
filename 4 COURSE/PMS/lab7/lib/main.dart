import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';

import 'task2.dart';
import 'task3.dart';
import 'task4.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  var directory = await getApplicationDocumentsDirectory();

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(
          scaffoldBackgroundColor: const Color.fromARGB(255, 222, 220, 228),
          fontFamily: "Bahnschrift"),
      debugShowCheckedModeBanner: false,
      title: 'Lab_07',
      home: const MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key}) : super(key: key);

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _selectedIndex = 0; // Индекс для отслеживания выбранного элемента

  final List<Widget> _widgetOptions = [
    const Task2(),
    const Task3(),
    const Task4(),
  ];

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index; // Обновляем индекс при нажатии на элемент
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: IndexedStack(
        index: _selectedIndex,
        children: _widgetOptions,
      ),
      bottomNavigationBar: BottomNavigationBar(
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.looks_two),
            label: '',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.looks_3),
            label: '',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.looks_4),
            label: '',
          ),
        ],
        currentIndex: _selectedIndex,
        unselectedItemColor: Colors.grey,
        selectedItemColor: Colors.blue,
        onTap: _onItemTapped,
      ),
    );
  }
}
