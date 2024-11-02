import 'package:flutter/material.dart';

import 'home_screen.dart';
import 'product_bloc.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final ProductBloc productBloc = ProductBloc();

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Nike Store',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
        fontFamily: 'Arial',
      ),
      home: HomeScreen(productBloc: productBloc),
    );
  }
}
