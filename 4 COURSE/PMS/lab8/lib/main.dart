import 'package:flutter/material.dart';
import 'package:hive_flutter/hive_flutter.dart';

import 'home_screen.dart';
import 'models/favorite_model.dart';
import 'models/product_model.dart';
import 'models/user_model.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await Hive.initFlutter();

  Hive.registerAdapter(UserModelAdapter());
  Hive.registerAdapter(ProductModelAdapter());
  Hive.registerAdapter(FavoriteModelAdapter());

  await Hive.openBox<ProductModel>('products');
  await Hive.openBox<FavoriteModel>('favorites');

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Nike Store',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
        fontFamily: 'Arial',
      ),
      home: HomeScreen(),
    );
  }
}
