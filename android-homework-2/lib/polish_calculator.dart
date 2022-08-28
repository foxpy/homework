import 'dart:math';

enum _State {
  empty,
  digit,
  digitWithDot,
}

class PolishCalculator {
  var _state = _State.empty;
  var _input = '';
  final _stack = <double>[];

  bool _isSpace(String operation) {
    return operation == '⎵';
  }

  bool _isDigit(String operation) {
    return RegExp(r'^\d$').hasMatch(operation);
  }

  bool _isReset(String operation) {
    return operation == 'C';
  }

  bool _isOperator(String operation) {
    return <String>{'div', 'mod', '^', '+', '-', '*', '/'}.contains(operation);
  }

  bool _isDot(String operation) {
    return operation == '.';
  }

  void _pushDigit(String operation) {
    switch (_state) {
      case _State.empty:
        _input += operation;
        _state = _State.digit;
        break;
      case _State.digit:
      case _State.digitWithDot:
        _input += operation;
        break;
      default:
    }
  }

  void _pushSpace() {
    switch (_state) {
      case _State.empty:
        break;
      case _State.digit:
      case _State.digitWithDot:
        _stack.add(double.parse(_input));
        _input = '';
        _state = _State.empty;
        break;
      default:
    }
  }

  void _pushReset() {
    _state = _State.empty;
    _stack.clear();
    _input = '';
  }

  double _executeOperator(String operation, double a, double b) {
    switch (operation) {
      case '+':
        return a + b;
      case '-':
        return a - b;
      case '*':
        return a * b;
      case '/':
        return a / b;
      case 'mod':
        return a % b;
      case 'div':
        return (a ~/ b).toDouble();
      case '^':
        return pow(a, b).toDouble();
      default:
        return 0.0;
    }
  }

  void _pushOperator(String operation) {
    switch (_state) {
      case _State.empty:
        if (_stack.length < 2) {
          return;
        } else {
          var b = _stack.removeLast();
          var a = _stack.removeLast();
          _stack.add(_executeOperator(operation, a, b));
        }
        break;
      case _State.digit:
      case _State.digitWithDot:
        _pushSpace();
        _pushOperator(operation);
        break;
      default:
    }
  }

  void _pushDot() {
    switch (_state) {
      case _State.empty:
      case _State.digitWithDot:
        return;
      case _State.digit:
        _input += '.';
        _state = _State.digitWithDot;
        break;
      default:
    }
  }

  void execute(String operation) {
    if (_isDigit(operation)) {
      _pushDigit(operation);
    } else if (_isSpace(operation)) {
      _pushSpace();
    } else if (_isReset(operation)) {
      _pushReset();
    } else if (_isOperator(operation)) {
      _pushOperator(operation);
    } else if (_isDot(operation)) {
      _pushDot();
    }
  }

  String display() {
    return _stack.join(' ') +
        (_stack.isNotEmpty && _input.isNotEmpty ? ' ' : '') +
        _input +
        (_state != _State.empty ? '_' : '');
  }
}
