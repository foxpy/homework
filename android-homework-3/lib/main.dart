import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:scientific_calculator/polish_calculator.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Polish calculator',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Calculator'),
        ),
        body: const Calculator(),
      ),
    );
  }
}

class Calculator extends StatefulWidget {
  const Calculator({Key? key}) : super(key: key);

  @override
  _CalculatorState createState() => _CalculatorState();
}

class _CalculatorState extends State<Calculator> {
  var calculatorScreen = CalculatorScreen();

  @override
  Widget build(BuildContext context) {
    return NotificationListener<ButtonPressed>(
      onNotification: (notification) {
        setState(() {
          calculatorScreen.execute(notification.operation);
        });
        return true;
      },
      child: Column(
        children: <Widget>[
          calculatorScreen,
          const Divider(),
          const CalculatorRow(buttonLabels: ['C', 'div', 'mod', '^']),
          const CalculatorRow(buttonLabels: ['sin', 'cos', 'tg', 'ctg']),
          const CalculatorRow(buttonLabels: ['π', 'e', '√', 'log']),
          const CalculatorRow(buttonLabels: ['7', '8', '9', '+']),
          const CalculatorRow(buttonLabels: ['4', '5', '6', '-']),
          const CalculatorRow(buttonLabels: ['1', '2', '3', '*']),
          const CalculatorRow(buttonLabels: ['.', '0', '⎵', '/']),
        ],
      ),
    );
  }
}

class CalculatorRow extends StatelessWidget {
  const CalculatorRow({Key? key, required this.buttonLabels}) : super(key: key);

  final List<String> buttonLabels;

  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Row(
        children: buttonLabels.map((name) {
          return CalculatorButton(operation: name);
        }).toList(),
      ),
    );
  }
}

class CalculatorScreen extends StatefulWidget {
  final _calculatorScreenState = _CalculatorScreenState();
  CalculatorScreen({Key? key}) : super(key: key);

  void execute(String operation) {
    _calculatorScreenState._execute(operation);
  }

  @override
  // ignore: no_logic_in_create_state
  _CalculatorScreenState createState() => _calculatorScreenState;
}

class _CalculatorScreenState extends State<CalculatorScreen> {
  final calc = PolishCalculator();
  final scrollController = ScrollController();

  void _execute(String operation) {
    setState(() {
      calc.execute(operation);
    });
    SchedulerBinding.instance?.addPostFrameCallback((_) {
      scrollController.jumpTo(scrollController.position.maxScrollExtent);
    });
  }

  @override
  Widget build(BuildContext context) {
    var textStyle = Theme.of(context).textTheme.headline3;
    var fontSize = textStyle?.fontSize ?? 20;
    fontSize *= 1.25;
    return Container(
      padding: const EdgeInsets.fromLTRB(0.0, /* top */ 10.0, 0.0, 0.0),
      child: SingleChildScrollView(
        controller: scrollController,
        scrollDirection: Axis.horizontal,
        child: Text(
          calc.display(),
          style: GoogleFonts.robotoMono(
            textStyle: textStyle,
            fontWeight: FontWeight.bold,
            height: 1.0,
            fontSize: fontSize,
          ),
        ),
      ),
    );
  }
}

class ButtonPressed extends Notification {
  final String operation;
  ButtonPressed(this.operation);
}

class CalculatorButton extends StatelessWidget {
  const CalculatorButton({Key? key, required this.operation}) : super(key: key);

  final String operation;

  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: SizedBox(
        height: double.infinity,
        child: TextButton(
          onPressed: () {
            ButtonPressed(operation).dispatch(context);
          },
          child: Text(
            operation,
            style: GoogleFonts.robotoMono(
              textStyle: Theme.of(context).textTheme.headline5,
              height: 1.0,
            ),
          ),
        ),
      ),
    );
  }
}
