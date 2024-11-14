import 'package:flutter/material.dart';

class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final TextEditingController _todoController = TextEditingController();
  ListController listController = ListController(database: Database());

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: Key('taskScreen'),
      appBar: AppBar(
        title: const Text("List App"),
        centerTitle: true,
      ),
      body: Column(
        children: <Widget>[
          const SizedBox(height: 20),
          const Text(
            "Add Todo Here:",
            style: TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
            ),
          ),
          Card(
            margin: const EdgeInsets.all(20),
            child: Padding(
              padding: const EdgeInsets.all(10.0),
              child: Row(
                children: [
                  Expanded(
                    child: TextFormField(
                      key: const Key("addField"),
                      controller: _todoController,
                      decoration: const InputDecoration(
                        hintText: "Enter your task",
                      ),
                    ),
                  ),
                  IconButton(
                    key: const Key("addButton"),
                    icon: const Icon(Icons.add),
                    onPressed: () {
                      if (_todoController.text.isNotEmpty) {
                        listController
                            .addTodo(TodoModel(_todoController.text, false));
                        _todoController.clear();
                        setState(() {});
                      }
                    },
                  ),
                ],
              ),
            ),
          ),
          const SizedBox(height: 20),
          const Text(
            "Your Todos",
            style: TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
            ),
          ),
          Expanded(
            child: ListView.builder(
              itemCount: listController.todoList.length,
              itemBuilder: (_, index) {
                return TodoCard(index: index, listController: listController);
              },
            ),
          ),
        ],
      ),
    );
  }
}

class TodoModel {
  String content;
  bool done;

  TodoModel(this.content, this.done);
}

class ListController {
  final Database database;
  List<TodoModel> todoList = [];

  ListController({required this.database});

  void addTodo(TodoModel todo) {
    // Добавляем только уникальные задачи
    if (!todoList.any((existingTodo) => existingTodo.content == todo.content)) {
      todoList.add(todo);
    }
  }

  void checkboxSelected(bool newValue, int index) {
    todoList[index].done = newValue;
  }

  void clear() {
    todoList.clear();
  }

  Future<void> loadFromDatabase() async {
    todoList.add(await database.loadDatabase());
  }
}

class Database {
  Future<TodoModel> loadDatabase() async {
    try {
      await Future.delayed(const Duration(seconds: 1));
      return TodoModel("From Database", true);
    } catch (e) {
      print(e);
      rethrow;
    }
  }
}

class TodoCard extends StatefulWidget {
  final int index;
  final ListController listController;

  const TodoCard({required this.index, required this.listController});

  @override
  _TodoCardState createState() => _TodoCardState();
}

class _TodoCardState extends State<TodoCard> {
  @override
  Widget build(BuildContext context) {
    return Draggable(
      data: widget.listController.todoList[widget.index]
          .content, // Добавлено для перетаскивания
      feedback: Card(
        margin: const EdgeInsets.all(20),
        child: Padding(
          padding: const EdgeInsets.all(10.0),
          child: Text(
            widget.listController.todoList[widget.index].content,
            style: const TextStyle(
              fontSize: 15,
              fontWeight: FontWeight.bold,
            ),
          ),
        ),
      ),
      childWhenDragging: Container(), // Виджет при перетаскивании
      child: Card(
        margin: const EdgeInsets.symmetric(horizontal: 20, vertical: 5),
        child: Padding(
          padding: const EdgeInsets.all(10.0),
          child: Row(
            children: [
              Expanded(
                child: Text(
                  widget.listController.todoList[widget.index].content,
                  style: const TextStyle(
                    fontSize: 15,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
              Checkbox(
                key: Key(
                    "checkbox_${widget.index}"), // Ключи для каждого checkbox
                value: widget.listController.todoList[widget.index].done,
                onChanged: (newValue) {
                  widget.listController
                      .checkboxSelected(newValue!, widget.index);
                  setState(() {});
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}
