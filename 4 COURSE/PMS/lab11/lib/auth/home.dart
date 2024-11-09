import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';

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
      appBar: AppBar(
        title: Text("List App"),
        centerTitle: true,
      ),
      body: Column(
        children: <Widget>[
          SizedBox(
            height: 20,
          ),
          Text(
            "Add Todo Here:",
            style: TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
            ),
          ),
          Card(
            margin: EdgeInsets.all(20),
            child: Padding(
              padding: const EdgeInsets.all(10.0),
              child: Row(
                children: [
                  Expanded(
                    child: TextFormField(
                      key: Key("addField"),
                      controller: _todoController,
                    ),
                  ),
                  IconButton(
                    key: Key("addButton"),
                    icon: Icon(Icons.add),
                    onPressed: () {
                      if (_todoController.text != "") {
                        listController
                            .addTodo(TodoModel(_todoController.text, false));
                        //Database()
                        //.addTodo(_todoController.text, controller.user.uid);
                        _todoController.clear();
                        setState(() {});
                      }
                    },
                  )
                ],
              ),
            ),
          ),
          SizedBox(
            height: 20,
          ),
          SizedBox(
            height: 20,
          ),
          Text(
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
          )
        ],
      ),
    );
  }
}


class TodoModel {
  String content;
  bool done;

  TodoModel(
      this.content,
      this.done,
      );
}

class ListController {
  final Database database;
  List<TodoModel> todoList = [];

  ListController({required this.database});

  void addTodo(TodoModel todo) {
    todoList.add(todo);
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
      await Future.delayed(Duration(seconds: 1));
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

  const TodoCard({ required this.index, required this.listController});

  @override
  _TodoCardState createState() => _TodoCardState();
}

class _TodoCardState extends State<TodoCard> {
  @override
  Widget build(BuildContext context) {
    return Draggable(
      feedback: Card(
        margin: EdgeInsets.all(20),
        child: Padding(
          padding: const EdgeInsets.all(10.0),
          child: Text(
            widget.listController.todoList[widget.index].content,
            style: TextStyle(
              fontSize: 15,
              fontWeight: FontWeight.bold,
            ),
          ),
        ),
      ),
      child: Card(
        margin: EdgeInsets.symmetric(horizontal: 20, vertical: 5),
        child: Padding(
          padding: const EdgeInsets.all(10.0),
          child: Row(
            children: [
              Expanded(
                child: Text(
                  widget.listController.todoList[widget.index].content,
                  style: TextStyle(
                    fontSize: 15,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
              Checkbox(
                key: Key("checkbox" + widget.index.toString()),
                value: widget.listController.todoList[widget.index].done,
                onChanged: (newValue) {
                  widget.listController.checkboxSelected(newValue!, widget.index);
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