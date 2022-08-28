use getopts::Options;
use std::fs::File;
use std::io::{prelude::*, SeekFrom};
use std::{env, process, thread, time};

const DEFAULT_ITERATIONS: u64 = 500;
const DEFAULT_FREQUENCY: f64 = 5.0;
const DEFAULT_PATH: &str = "/sys/class/power_supply/BAT0/power_now";

fn print_help(program_name: &str, opts: Options) -> ! {
    let brief = format!("Usage: {} [options] output.csv", program_name);
    print!("{}", opts.usage(&brief));
    process::exit(0);
}

fn read_battery_data<T: std::io::Write>(
    battery: &mut File,
    frequency: f64,
    iterations: u64,
    output: &mut csv::Writer<T>,
) -> std::io::Result<()> {
    for i in 0..iterations {
        battery.seek(SeekFrom::Start(0))?;
        let mut power = String::new();
        battery.read_to_string(&mut power)?;
        let power = power.trim().parse::<f64>().unwrap() / 1e6;
        output.write_record(&[format!("{}", i), format!("{}", power)])?;
        thread::sleep(time::Duration::from_secs_f64(frequency));
    }
    Ok(())
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut opts = Options::new();
    opts.optflag("h", "help", "print this message");
    opts.optopt(
        "n",
        "iterations",
        format!("Read data N times, defaults to {}", DEFAULT_ITERATIONS).as_ref(),
        "N",
    );
    opts.optopt(
        "f",
        "frequency",
        format!(
            "time interval between polls: FREQ seconds, defaults to {}",
            DEFAULT_FREQUENCY
        )
        .as_ref(),
        "FREQ",
    );
    opts.optopt(
        "p",
        "path",
        format!("file used for data polling, defaults to {}", DEFAULT_PATH).as_ref(),
        "PATH",
    );
    let matches = opts.parse(&args[1..]).unwrap();
    if matches.opt_present("h") {
        print_help(&args[0], opts);
    }

    if matches.free.is_empty() {
        panic!("No output file specified");
    }

    let iterations: u64 = match matches.opt_str("n") {
        Some(i) => i.parse().expect("Iterations should be a number"),
        None => DEFAULT_ITERATIONS,
    };

    let frequency: f64 = match matches.opt_str("f") {
        Some(f) => f.parse().expect("Frequency should be a number"),
        None => DEFAULT_FREQUENCY,
    };
    if frequency < 0.0 {
        println!("Frequency should be positive");
        process::exit(1);
    }

    let path = match matches.opt_str("p") {
        Some(p) => p,
        None => String::from(DEFAULT_PATH),
    };
    let mut battery = File::open(path).unwrap();

    let path = &matches.free[0];
    let output = File::create(path).unwrap();
    let mut writer = csv::Writer::from_writer(output);
    writer.write_record(&["N", "Power"]).unwrap();

    read_battery_data(&mut battery, frequency, iterations, &mut writer).unwrap();
}
