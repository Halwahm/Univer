import 'package:flutter/material.dart';

import 'description_page.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        appBarTheme: const AppBarTheme(
          backgroundColor: Color.fromRGBO(255, 255, 255, 1),
          iconTheme: IconThemeData(color: Colors.black),
          elevation: 0,
        ),
      ),
      home: const MyHomePage(),
    );
  }
}

class Slide {
  final String title;
  final String description;
  final Color color;
  final String image;

  Slide(this.title, this.description, this.color,this.image);
}

class MyHomePage extends StatelessWidget {
  const MyHomePage({super.key});

  @override
  Widget build(BuildContext context) {
    final List<Slide> mainSlides = [
      Slide("Salad 1", "A Salad is a dish consiting of a mixture of small pieces of foods,usually vegetables", const Color.fromRGBO(222, 232, 255, 1),"assets/images/ego1.png"),
      Slide("Salad 2", "A Salad is a dish consiting of a mixture of small pieces of foods,usually vegetables", const Color.fromRGBO(114, 209, 199, 1),"assets/images/ego1.png"),
      Slide("Salad 5", "A Salad is a dish consiting of a mixture of small pieces of foods,usually vegetables", const Color.fromRGBO(180, 200, 255, 1),"assets/images/ego1.png"),
      Slide("Salad 4", "A Salad is a dish consiting of a mixture of small pieces of foods,usually vegetables", const Color.fromRGBO(250, 250, 250, 1),"assets/images/ego1.png"),
      Slide("Salad 5", "A Salad is a dish consiting of a mixture of small pieces of foods,usually vegetables", const Color.fromRGBO(200, 200, 255, 1),"assets/images/ego1.png"),
    ];

    final List<String> smallSlides = ["Foods", "Bear", "Wine"];

    return Scaffold(
      backgroundColor: const Color.fromRGBO(255, 255, 255, 1),
      appBar: AppBar(
        backgroundColor: const Color.fromRGBO(255, 255, 255, 1),
        iconTheme: const IconThemeData(color: Colors.black),
        elevation: 0,
        actions: <Widget>[
          IconButton(
            icon: const Icon(Icons.search),
            onPressed: () {
              print("search");
            },
          ),
          const SizedBox(width: 10),
          Padding(
            padding: const EdgeInsets.only(right: 10),
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.end,
                  children: List.generate(2, (index) {
                    return Container(
                      width: 10,
                      height: 10,
                      margin: const EdgeInsets.symmetric(horizontal: 2),
                      decoration: BoxDecoration(
                        color: Colors.black,
                        shape: BoxShape.circle,
                      ),
                    );
                  }),
                ),
                Row(
                  mainAxisAlignment: MainAxisAlignment.end,
                  children: List.generate(2, (index) {
                    return Container(
                      width: 10,
                      height: 10,
                      margin: const EdgeInsets.symmetric(horizontal: 2),
                      decoration: BoxDecoration(
                        color: Colors.black,
                        shape: BoxShape.circle,
                      ),
                    );
                  }),
                ),
              ],
            ),
          ),
        ],
      ),

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
                      text: "Break",
                      style: TextStyle(
                        fontSize: 36,
                        fontWeight: FontWeight.normal,
                        color: Colors.black,
                      ),
                    ),
                    TextSpan(
                      text: "fest",
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

                        Navigator.push(
                          context,
                          MaterialPageRoute(
                            builder: (context) => DetailPage(
                              title: mainSlides[index].title,
                              description: mainSlides[index].description,
                              color: mainSlides[index].color,
                              image: mainSlides[index].image,
                            ),

                          ),
                        );
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
                            child: Container(
                              width: 50,
                              height: 50,
                              decoration: BoxDecoration(
                                color: const Color.fromRGBO(252, 120, 95, 1),
                                shape: BoxShape.circle,
                              ),
                              child: const Center(
                                child: Icon(
                                  Icons.favorite,
                                  color: Colors.white,
                                  size: 20,
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
        ],
      ),
      bottomNavigationBar: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
          Container(
            color: const Color.fromRGBO(232, 233, 237, 1),
            height: 1,
          ),
          BottomAppBar(
            color: Colors.white,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: <Widget>[
                Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    IconButton(
                      icon: const Icon(Icons.home),
                      onPressed: () {
                        print("Home");
                      },
                      color: const Color.fromRGBO(255, 120, 91, 1),
                    ),
                    const SizedBox(width: 5),
                    const Text(
                      "Home",
                      style: TextStyle(
                        fontSize: 16,
                        fontWeight: FontWeight.bold,
                        color: Color.fromRGBO(255, 120, 91, 1),
                      ),
                    ),
                  ],
                ),
                IconButton(
                  icon: const Icon(Icons.person),
                  onPressed: () {
                    print("User");
                  },
                ),
                IconButton(
                  icon: const Icon(Icons.settings),
                  onPressed: () {
                    print("Settings");
                  },
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
        ],
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
