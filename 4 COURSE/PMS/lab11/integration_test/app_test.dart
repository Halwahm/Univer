import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:lab11/firebase_options.dart';
import 'package:lab11/main.dart';

// flutter drive --driver=test_driver/integration_test.dart --target=integration_test/app_test.dart
void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  setUpAll(() async {
    await Firebase.initializeApp(
      options: DefaultFirebaseOptions.currentPlatform,
    );
  });

  group('App Integration Tests', () {
    // testWidgets('User Registration and Navigation to Task Screen',
    //     (WidgetTester tester) async {
    //   await tester.pumpWidget(const MyApp());
    //   await tester.pumpAndSettle();
    //
    //   final createAccountButton = find.byKey(const Key('createAccountButton'));
    //   await tester.tap(createAccountButton);
    //   await tester.pumpAndSettle();
    //
    //   final emailFieldFinder = find.byKey(const Key('registrationEmailField'));
    //   final passwordFieldFinder =
    //       find.byKey(const Key('registrationPasswordField'));
    //   final registerButtonFinder = find.byKey(const Key('registerButton'));
    //
    //   await tester.enterText(emailFieldFinder, 'newuser343h@example.com');
    //   await tester.enterText(passwordFieldFinder, 'password123');
    //   await tester.tap(registerButtonFinder);
    //   await tester.pumpAndSettle();
    //
    //   print('Registration successful - Test Passed!');
    //   expect(true, true);
    // });

    testWidgets('User Login and Navigation to Task Screen',
        (WidgetTester tester) async {
      await tester.pumpWidget(const MyApp());
      await tester.pumpAndSettle();

      final emailFieldFinder = find.byKey(const Key('loginEmailField'));
      final passwordFieldFinder = find.byKey(const Key('loginPasswordField'));
      final loginButtonFinder = find.byKey(const Key('loginButton'));

      await tester.enterText(emailFieldFinder, 'newuser343h@example.com');
      await tester.enterText(passwordFieldFinder, 'password123');
      await tester.tap(loginButtonFinder);
      await Future.delayed(const Duration(seconds: 2));
      await tester.pumpAndSettle();
      await Future.delayed(const Duration(seconds: 2));
      final workersTextFinder = find.text('Workers');
      print('Looking for Workers text: $workersTextFinder');

      if (workersTextFinder.evaluate().isEmpty) {
        print(
            'Workers text not found. Current widget tree: ${tester.widgetList(find.byType(Scaffold))}');
      }

      expect(workersTextFinder, findsOneWidget,
          reason: 'User should be on the main task screen after login.');
    });

    //
    //   testWidgets('Add Task and Verify Task in List',
    //       (WidgetTester tester) async {
    //     // Запускаем приложение и сразу переходим на экран задач (предполагается, что пользователь уже вошел)
    //     await tester.pumpWidget(const MyApp());
    //     await tester.pumpAndSettle();
    //
    //     // Проверяем наличие элементов интерфейса для добавления задачи
    //     final taskInputField = find.byKey(const Key("addField"));
    //     final addButton = find.byKey(const Key("addButton"));
    //
    //     // Вводим текст новой задачи и добавляем
    //     await tester.enterText(taskInputField, 'New Task');
    //     await tester.tap(addButton);
    //     await tester.pumpAndSettle();
    //
    //     // Проверка: новая задача должна быть добавлена в список
    //     expect(find.text('New Task'), findsOneWidget,
    //         reason: 'New task should be visible in the task list.');
    //   });
    //
    //   testWidgets('Ensure No Duplicate Tasks', (WidgetTester tester) async {
    //     // Запускаем приложение и сразу переходим на экран задач (предполагается, что пользователь уже вошел)
    //     await tester.pumpWidget(const MyApp());
    //     await tester.pumpAndSettle();
    //
    //     // Проверяем наличие элементов интерфейса для добавления задачи
    //     final taskInputField = find.byKey(const Key("addField"));
    //     final addButton = find.byKey(const Key("addButton"));
    //
    //     // Вводим и добавляем задачу "Unique Task"
    //     await tester.enterText(taskInputField, 'Unique Task');
    //     await tester.tap(addButton);
    //     await tester.pumpAndSettle();
    //
    //     // Пытаемся добавить ту же задачу еще раз
    //     await tester.enterText(taskInputField, 'Unique Task');
    //     await tester.tap(addButton);
    //     await tester.pumpAndSettle();
    //
    //     // Проверка: задача "Unique Task" должна быть только одна в списке
    //     expect(find.text('Unique Task'), findsOneWidget,
    //         reason: 'Task should not be duplicated in the task list.');
    //   });
    // });
  });
}
