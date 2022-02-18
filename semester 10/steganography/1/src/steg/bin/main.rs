use std::{env, fs, process};
use std::collections::VecDeque;
use xml::reader::{EventReader, XmlEvent};

fn help(prog_name: &str, exit_code: i32) {
    println!("Usage: {} input.docx", prog_name);
    process::exit(exit_code);
}

fn eat<R: std::io::Read>(xml: &mut EventReader<R>, data: &mut VecDeque<bool>) {
    let mut up: bool = false;
    loop {
        match xml.next().unwrap() {
            XmlEvent::StartElement {
                name,
                attributes: _,
                namespace: _,
            } => if name.local_name == "t" {
                match xml.next().unwrap() {
                    XmlEvent::Characters(s) | XmlEvent::Whitespace(s) => {
                        for _ in 0..s.chars().count() {
                            data.push_back(up);
                        }
                        return;
                    },
                    _ => (),
                }
            } else if name.local_name == "w" {
                up = true;
            },
            XmlEvent::EndElement {
                name,
            } => if name.local_name == "r" {
                break;
            },
            _ => (),
        }
    }
}

fn data_to_binary(data: &mut VecDeque<bool>) -> Vec<u8> {
    let mut ret = VecDeque::<u8>::new();
    while data.len() >= 8 {
        let mut c: u8 = 0;
        for _ in 0..8 {
            c <<= 1;
            c |= if data.pop_front().unwrap() { 1u8 } else { 0u8 };
        }
        ret.push_back(c);
    }
    while ret.back() == Some(&0) {
        ret.pop_back();
    }
    ret.into_iter().collect()
}

fn main() {
    let mut args = env::args();
    if args.len() != 2 {
        help(&args.next().unwrap(), 1);
    } else {
        let path = args.nth(1).unwrap();
        let mut archive = zip::ZipArchive::new(fs::File::open(path).unwrap()).unwrap();
        let file = archive.by_name("word/document.xml").unwrap();
        let mut xml = EventReader::new(file);
        let mut data = VecDeque::<bool>::new();
        loop {
            match xml.next().unwrap() {
                XmlEvent::StartElement {
                    name,
                    attributes: _,
                    namespace: _,
                } => {
                    if name.local_name == "r" {
                        eat(&mut xml, &mut data);
                    }
                },
                XmlEvent::EndDocument => break,
                _ => (),
            }
        }
        let binary = data_to_binary(&mut data);
        std::io::copy(&mut binary.as_slice(), &mut std::io::stdout()).unwrap();
    }
}
