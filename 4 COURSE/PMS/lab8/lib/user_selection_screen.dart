import 'package:flutter/material.dart';

import 'models/user_model.dart';

class UserSelectionScreen extends StatefulWidget {
  @override
  _UserSelectionScreenState createState() => _UserSelectionScreenState();
}

class _UserSelectionScreenState extends State<UserSelectionScreen> {
  String selectedUser = 'user';

  @override
  Widget build(BuildContext context) {
    List<UserModel> users = [
      UserModel(name: 'User', role: 'user'),
      UserModel(name: 'Manager', role: 'manager'),
    ];

    return Scaffold(
      appBar: AppBar(
        title: const Text('Выберите пользователя'),
      ),
      body: Center(
        child: DropdownButton<String>(
          value: selectedUser,
          items: users.map((UserModel user) {
            return DropdownMenuItem<String>(
              value: user.role,
              child: Text(user.name),
            );
          }).toList(),
          onChanged: (String? value) {
            setState(() {
              selectedUser = value!;
            });
          },
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          UserModel selected =
              users.firstWhere((user) => user.role == selectedUser);
          Navigator.pop(context, selected);
        },
        child: const Icon(Icons.check),
      ),
    );
  }
}
