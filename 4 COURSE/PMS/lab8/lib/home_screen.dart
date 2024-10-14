import 'package:flutter/material.dart';
import 'package:hive_flutter/adapters.dart';

import 'details_screen.dart';
import 'favorites_screen.dart';
import 'models/product_model.dart';
import 'models/user_model.dart';
import 'product_card.dart';
import 'product_management_screen.dart';
import 'user_selection_screen.dart';

class HomeScreen extends StatefulWidget {
  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  UserModel? _currentUser;
  late Box<ProductModel> productsBox;

  @override
  void initState() {
    super.initState();
    productsBox = Hive.box<ProductModel>('products');
    _initializeProducts();
    WidgetsBinding.instance.addPostFrameCallback((_) {
      _selectUser();
    });
  }

  void _initializeProducts() {
    if (productsBox.isEmpty) {
      productsBox.addAll([
        ProductModel(
          id: '1',
          title: 'Nike GTX 2',
          price: '\$329',
          image: 'assets/images/gtx2.png',
          images: ['assets/images/gtx2.png', 'assets/images/gtx.png'],
          description: 'Описание Nike GTX 2',
        ),
        ProductModel(
          id: '2',
          title: 'Nike GTX',
          price: '\$100',
          image: 'assets/images/gtx.png',
          images: ['assets/images/gtx.png', 'assets/images/gtx2.png'],
          description: 'Описание Nike GTX',
          isOnSale: true,
        ),
        ProductModel(
          id: '3',
          title: 'Nike Air Zoom',
          price: '\$150',
          image: 'assets/images/shoe_3.png',
          images: ['assets/images/shoe_3.png', 'assets/images/gtx2.png'],
          description: 'Описание Nike Air Zoom',
        ),
      ]);
    }
  }

  Future<void> _selectUser() async {
    final user = await Navigator.push<UserModel>(
      context,
      MaterialPageRoute(builder: (context) => UserSelectionScreen()),
    );
    if (user != null) {
      setState(() {
        _currentUser = user;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    if (_currentUser == null) {
      return const Scaffold();
    }

    return Scaffold(
      backgroundColor: const Color(0xFFF3F6FD),
      appBar: AppBar(
        backgroundColor: Colors.transparent,
        elevation: 0,
        flexibleSpace: Stack(
          children: [
            Positioned.fill(
              child: Container(
                color: Colors.white,
              ),
            ),
            Positioned(
              right: 0,
              top: 0,
              bottom: 0,
              width: MediaQuery.of(context).size.width * 0.4,
              child: Container(
                color: const Color(0xFFF3F6FD),
              ),
            ),
          ],
        ),
        centerTitle: true,
        title: Image.asset('assets/images/nike_logo.png', height: 30),
        leading: IconButton(
          icon: const Icon(Icons.menu, color: Colors.black, size: 40),
          onPressed: () {
            _selectUser();
          },
        ),
        actions: [
          IconButton(
            icon: const Icon(Icons.favorite_border,
                color: Colors.black, size: 40),
            onPressed: () {
              Navigator.push(
                context,
                MaterialPageRoute(
                  builder: (context) =>
                      FavoritesScreen(userName: _currentUser!.name),
                ),
              );
            },
          ),
          const SizedBox(width: 16),
        ],
      ),
      floatingActionButton: _currentUser!.role == 'manager'
          ? FloatingActionButton(
              child: const Icon(Icons.edit),
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(
                      builder: (context) => ProductManagementScreen()),
                ).then((_) => setState(() {}));
              },
            )
          : null,
      body: Stack(
        children: [
          Positioned(
            left: 0,
            right: 0,
            top: 0,
            bottom: 0,
            child: Container(
              color: Colors.white,
            ),
          ),
          Positioned(
            right: 0,
            top: 0,
            bottom: 0,
            width: MediaQuery.of(context).size.width * 0.4,
            child: Container(
              color: const Color(0xFFF3F6FD),
            ),
          ),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 24),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                const SizedBox(height: 20),
                Center(
                  child: Image.asset(
                    'assets/images/asset1.png',
                    height: 250,
                  ),
                ),
                const SizedBox(height: 20),
                RichText(
                  text: const TextSpan(
                    children: [
                      TextSpan(
                        text: 'Nike\n',
                        style: TextStyle(
                          fontSize: 36,
                          fontWeight: FontWeight.bold,
                          color: Color(0xFF1D1E3C),
                        ),
                      ),
                      TextSpan(
                        text: 'Collection',
                        style: TextStyle(
                          fontSize: 32,
                          fontWeight: FontWeight.w300,
                          color: Color(0xFFB0B0C3),
                        ),
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 10),
                Expanded(
                  child: ValueListenableBuilder(
                    valueListenable: productsBox.listenable(),
                    builder: (context, Box<ProductModel> box, _) {
                      if (box.values.isEmpty) {
                        return const Center(child: Text('Нет товаров'));
                      } else {
                        return ListView.builder(
                          scrollDirection: Axis.horizontal,
                          itemCount: box.values.length,
                          itemBuilder: (context, index) {
                            ProductModel product = box.getAt(index)!;
                            return ProductCard(
                              product: product,
                              userName: _currentUser!.name,
                              onPressed: () {
                                Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                    builder: (context) => DetailsScreen(
                                        product: product,
                                        currentUser: _currentUser!.name),
                                  ),
                                );
                              },
                              margin: const EdgeInsets.only(right: 12),
                            );
                          },
                        );
                      }
                    },
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
