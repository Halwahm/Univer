import 'package:lab11/models/worker.dart';
import 'package:mockito/mockito.dart';
import 'package:test/test.dart';

class MockJsonMap extends Mock implements Map<String, Object?> {}

void main() {
  group('Bakery', () {
    late Worker worker;
    late Map<String, Object?> mockJson;

    setUp(() {
      mockJson = MockJsonMap();
      when(mockJson['name']).thenReturn('Misha');
      when(mockJson['specialization']).thenReturn('Stroitel');

      worker = Worker.fromJson(mockJson);
    });

    test('fromJson() should create a Worker object from JSON data', () {
      expect(worker.name, 'Misha');
      expect(worker.specialization, 'Stroitel');
    });

    test('copyWith() should create a new Worker object with updated values',
        () {
      final updatedBakery =
          worker.copyWith(name: 'Oleg', specialization: 'Programmer');

      expect(updatedBakery.name, 'Oleg');
      expect(updatedBakery.specialization, 'Programmer');
    });

    test('toJson() should convert Worker object to JSON data', () {
      final json = worker.toJson();

      expect(json['name'], 'Misha');
      expect(json['specialization'], 'Stroitel');
    });
  });
}
