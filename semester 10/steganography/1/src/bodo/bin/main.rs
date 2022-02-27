use bitvec::prelude::*;
use clap::Parser;
use std::{collections::HashMap, fs, io::prelude::*};
use ux::u5;

fn bodo_extract_bits(input: &[u8]) -> Vec<u5> {
    let mut ret = Vec::<u5>::new();
    let mut bit_iter = input
        .view_bits::<Msb0>()
        .iter()
        .by_vals()
        .map(|x| u5::new(x as u8))
        .peekable();
    while bit_iter.peek() != None {
        let mut bits: Vec<u5> = bit_iter.by_ref().take(5).collect();
        bits.resize(5, u5::MIN);
        let mut code_point = u5::MIN;
        for (shift, val) in bits.iter().rev().enumerate() {
            code_point |= *val << shift;
        }
        ret.push(code_point);
    }
    ret
}

enum BodoState {
    Latin,
    Cyrillic,
    DigitsEtc,
}

fn bodo_decode(init_state: BodoState, input: &[u5]) -> String {
    let mut ret = String::new();
    let mut state = init_state;
    let bodo_table = HashMap::from([
        (0b00011, ("A", "А", "-")),
        (0b11001, ("B", "Б", "?")),
        (0b01110, ("C", "Ц", ":")),
        (0b01001, ("D", "Д", "Кто там?")),
        (0b00001, ("E", "Е", "З")),
        (0b01101, ("F", "Ф", "Э")),
        (0b11010, ("G", "Г", "Ш")),
        (0b10100, ("H", "Х", "Щ")),
        (0b00110, ("I", "И", "8")),
        (0b01011, ("J", "Й", "Ю")),
        (0b01111, ("K", "К", "(")),
        (0b10010, ("L", "Л", ")")),
        (0b11100, ("M", "М", ".")),
        (0b01100, ("N", "Н", ",")),
        (0b11000, ("O", "О", "9")),
        (0b10110, ("P", "П", "0")),
        (0b10111, ("Q", "Я", "1")),
        (0b01010, ("R", "Р", "4")),
        (0b00101, ("S", "С", "'")),
        (0b10000, ("T", "Т", "5")),
        (0b00111, ("U", "У", "7")),
        (0b11110, ("V", "Ж", "=")),
        (0b10011, ("W", "В", "2")),
        (0b11101, ("X", "Ь", "/")),
        (0b10101, ("Y", "Ы", "6")),
        (0b10001, ("Z", "З", "+")),
    ]);
    for i in input.iter().map(|x| u8::from(*x)) {
        ret += match i {
            0b01000 => "\r",
            0b00010 => "\n",
            0b11111 => {
                state = BodoState::Latin;
                ""
            }
            0b11011 => {
                state = BodoState::DigitsEtc;
                ""
            }
            0b00100 => " ",
            0b00000 => {
                state = BodoState::Cyrillic;
                ""
            }
            _ => {
                let bodo_entry = bodo_table.get(&i).or(Some(&("", "", ""))).unwrap();
                match state {
                    BodoState::Latin => bodo_entry.0,
                    BodoState::Cyrillic => bodo_entry.1,
                    BodoState::DigitsEtc => bodo_entry.2,
                }
            }
        }
    }
    ret
}

#[derive(Parser, Debug)]
struct Args {
    /// Path to input message to decode
    #[clap(short, long)]
    path: String,
}

fn main() {
    let args = Args::parse();
    let mut file = fs::File::open(args.path).unwrap();
    let mut input: Vec<u8> = vec![];
    file.read_to_end(&mut input).unwrap();
    let bodo_extracted = bodo_extract_bits(&input);
    let output = bodo_decode(BodoState::Latin, &bodo_extracted);
    println!("{}", output);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn bodo_extract() {
        let input: &[u8] = [0b10001000, 0b11101101].as_slice();
        let expected = vec![
            u5::new(0b10001),
            u5::new(0b00011),
            u5::new(0b10110),
            u5::new(0b10000),
        ];
        let output = bodo_extract_bits(input);
        assert_eq!(expected, output);
    }

    #[test]
    fn bodo_decode_cyrillic_and_digits_etc() {
        let input = vec![
            u5::new(0b10110),
            u5::new(0b01010),
            u5::new(0b00110),
            u5::new(0b10011),
            u5::new(0b00001),
            u5::new(0b10000),
            u5::new(0b11011),
            u5::new(0b11001),
        ];
        let expected = "ПРИВЕТ?";
        let output = bodo_decode(BodoState::Cyrillic, &input);
        assert_eq!(expected, output);
    }

    #[test]
    fn bodo_decode_latin() {
        let input = vec![u5::new(0b00101), u5::new(0b11000), u5::new(0b00101)];
        let expected = "SOS";
        let output = bodo_decode(BodoState::Latin, &input);
        assert_eq!(expected, output);
    }
}
