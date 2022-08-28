import 'package:scientific_calculator/polish_calculator.dart';
import 'package:test/test.dart';

void main() {
  group('Polish calculator', () {
    test('start screen should be empty', () {
      final calc = PolishCalculator();
      expect(calc.display(), '');
    });

    test('numbers added are printed on screen', () {
      final calc = PolishCalculator();
      calc.execute('1');
      expect(calc.display(), '1_');
      calc.execute('2');
      expect(calc.display(), '12_');
    });
  });
}
