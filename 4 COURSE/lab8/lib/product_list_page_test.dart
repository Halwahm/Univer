// lib/product_list_page.dart

import 'package:flutter/material.dart';
import 'package:hive/hive.dart';
import 'models.dart';

class ProductListPageTest extends StatefulWidget {
  @override
  _ProductListPageState createState() => _ProductListPageState();
}

final List<String> smallSlides = ["Foods", "Bear", "Wine"];

class Slide {
  final String title;
  final String description;
  final Color color;
  final String image;

  Slide(this.title, this.description, this.color, this.image);
}

class _ProductListPageState extends State<ProductListPageTest> {
  late List<Slide> mainSlides;

  @override
  void initState() {
    super.initState();
    _updateSlides();
  }

  void _updateSlides() {
    mainSlides = products.map((product) {
      return Slide(
        product.name,
        'Price: \$${product.price}',
        const Color.fromRGBO(222, 232, 255, 1),
        'assets/images/ego1.png', // Укажите путь к вашему изображению
      );
    }).toList();
  }

  bool isFavorite(String productName) {
    return favorites.any((fav) => fav.item == productName);
  }

  void toggleFavorite(String productName) {
    setState(() {
      if (isFavorite(productName)) {
        favorites.removeWhere((fav) => fav.item == productName); // Удаляем из избранного
      } else {
        favorites.add(Favorite(productName)); // Добавляем в избранное
      }
      Hive.box("favorites").put("favorites", favorites);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Products')),
      body: Column(
        children: <Widget>[
          Padding(
            padding: const EdgeInsets.fromLTRB(15, 30, 0, 20),
            child: Align(
              alignment: Alignment.topLeft,
              child: RichText(
                text: const TextSpan(
                  children: [
                    TextSpan(
                      text: "Product",
                      style: TextStyle(
                        fontSize: 36,
                        fontWeight: FontWeight.normal,
                        color: Colors.black,
                      ),
                    ),
                    TextSpan(
                      text: " List",
                      style: TextStyle(
                        fontSize: 36,
                        fontWeight: FontWeight.bold,
                        color: Colors.black,
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ),
          const SizedBox(height: 20),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.fromLTRB(15, 20, 0, 20),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    _buildVerticalText("Bread"),
                    const SizedBox(height: 40),
                    _buildVerticalText("Noodles"),
                    const SizedBox(height: 40),
                    _buildVerticalText("Seafood"),
                  ],
                ),
              ),
              Container(
                width: 340,
                height: 420,
                child: PageView.builder(
                  padEnds: false,
                  itemCount: mainSlides.length,
                  itemBuilder: (context, index) {
                    return GestureDetector(
                      onTap: () {
                        // Переход на страницу деталей товара
                      },
                      child: Stack(
                        alignment: Alignment.center,
                        children: [
                          Container(
                            width: 240,
                            height: 370,
                            margin: const EdgeInsets.symmetric(horizontal: 15),
                            child: ClipRRect(
                              borderRadius: BorderRadius.circular(30),
                              child: Container(
                                color: mainSlides[index].color,
                                child: Center(
                                  child: Padding(
                                    padding: const EdgeInsets.all(20),
                                    child: Column(
                                      mainAxisAlignment: MainAxisAlignment.center,
                                      children: [
                                        const SizedBox(height: 100),
                                        Row(
                                          mainAxisAlignment: MainAxisAlignment.start,
                                          children: [
                                            Container(
                                              width: 10,
                                              height: 10,
                                              decoration: BoxDecoration(
                                                color: const Color.fromRGBO(255, 120, 91, 1),
                                                shape: BoxShape.circle,
                                              ),
                                            ),
                                            const SizedBox(width: 10),
                                            Text(
                                              mainSlides[index].title,
                                              style: const TextStyle(
                                                fontSize: 24,
                                                fontWeight: FontWeight.bold,
                                              ),
                                            ),
                                          ],
                                        ),
                                        const SizedBox(height: 10),
                                        Text(
                                          mainSlides[index].description,
                                          style: const TextStyle(
                                            fontSize: 16,
                                          ),
                                        ),
                                      ],
                                    ),
                                  ),
                                ),
                              ),
                            ),
                          ),
                          Positioned(
                            top: 60,
                            right: 10,
                            child: ClipRRect(
                              borderRadius: BorderRadius.circular(70),
                              child: Image.asset(
                                mainSlides[index].image,
                                width: 150,
                                height: 150,
                                fit: BoxFit.cover,
                              ),
                            ),
                          ),
                          Positioned(
                            top: 0,
                            left: 30,
                            child: GestureDetector(
                              onTap: () {
                                toggleFavorite(mainSlides[index].title);
                              },
                              child: Container(
                                width: 50,
                                height: 50,
                                decoration: BoxDecoration(
                                  color: const Color.fromRGBO(252, 120, 95, 1),
                                  shape: BoxShape.circle,
                                ),
                                child: Center(
                                  child: Icon(
                                    isFavorite(mainSlides[index].title)
                                        ? Icons.favorite
                                        : Icons.favorite_border,
                                    color: Colors.white,
                                    size: 20,
                                  ),
                                ),
                              ),
                            ),
                          ),
                        ],
                      ),
                    );
                  },
                ),
              ),
            ],
          ),
          const SizedBox(height: 20),
          // Блоки под слайдером
          Row(
            children: [
              IconButton(
                icon: const Icon(Icons.settings),
                onPressed: () {
                  print("Settings");
                },
              ),
              Expanded(
                child: Container(
                  height: 90,
                  child: PageView.builder(
                    padEnds: false,
                    itemCount: (smallSlides.length / 3).ceil(),
                    itemBuilder: (context, pageIndex) {
                      return Row(
                        children: List.generate(3, (index) {
                          final itemIndex = pageIndex * 3 + index;
                          if (itemIndex < smallSlides.length) {
                            return Container(
                              margin: const EdgeInsets.symmetric(horizontal: 10),
                              decoration: BoxDecoration(
                                color: smallSlides[itemIndex] == "Foods"
                                    ? const Color.fromRGBO(249,124,85, 1)
                                    : Colors.grey[200],
                                borderRadius: BorderRadius.circular(25),
                              ),
                              width: 90,
                              child: Center(
                                child: Text(
                                  smallSlides[itemIndex],
                                  style: TextStyle(
                                    fontSize: 18,
                                    color: smallSlides[itemIndex] == "Foods"
                                        ? Colors.white
                                        : Colors.black,
                                  ),
                                ),
                              ),
                            );
                          } else {
                            return const SizedBox.shrink();
                          }
                        }),
                      );
                    },
                  ),
                ),
              ),



            ],
          ),
          const SizedBox(height: 20),
        ],
      ),
      bottomNavigationBar: BottomAppBar(
        color: Colors.white,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: <Widget>[
            IconButton(
              icon: const Icon(Icons.home),
              onPressed: () {
                // Логика перехода на главную страницу
              },
            ),
            IconButton(
              icon: const Icon(Icons.person),
              onPressed: () {
                print("User");
              },
            ),
            IconButton(
              icon: const Icon(Icons.settings),
              onPressed: () {},
            ),
            IconButton(
              icon: const Icon(Icons.menu),
              onPressed: () {
                print("Menu");
              },
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildVerticalText(String text) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.start,
      children: [
        RotatedBox(
          quarterTurns: 3,
          child: Text(
            text,
            style: const TextStyle(
              fontSize: 16,
              color: Color.fromRGBO(3, 28, 56, 1),
            ),
          ),
        ),
        const SizedBox(width: 10),
        Container(
          width: 10,
          height: 10,
          decoration: BoxDecoration(
            color: text == "Bread"
                ? const Color.fromRGBO(255, 120, 91, 1)
                : Colors.white,
            shape: BoxShape.circle,
          ),
        ),
      ],
    );
  }
}