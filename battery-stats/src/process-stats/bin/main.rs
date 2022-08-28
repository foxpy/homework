use getopts::Options;
use itertools::Itertools;
use plotters::prelude::*;
use std::collections::HashMap;
use std::fs::File;
use std::hash::{Hash, Hasher};
use std::io::prelude::*;
use std::{env, fmt, fs, process};

#[derive(Debug)]
struct HashedDouble(f64);

impl HashedDouble {
    fn key(&self) -> u64 {
        self.0.to_bits()
    }
}

impl Hash for HashedDouble {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.key().hash(state)
    }
}

impl PartialEq for HashedDouble {
    fn eq(&self, other: &HashedDouble) -> bool {
        self.key() == other.key()
    }
}

impl Eq for HashedDouble {}

#[derive(Default)]
struct StatisticalPopulation {
    statistical_population: Vec<f64>,
    variation_series: Vec<f64>,
    average: f64,
    dispersion: f64,
    stddev: f64,
    corrected_dispersion: f64,
    corrected_stddev: f64,
}

impl StatisticalPopulation {
    fn new(input: &[f64]) -> StatisticalPopulation {
        let mut sp = StatisticalPopulation::default();
        sp.statistical_population = input.to_owned();
        sp.variation_series = input.to_owned();
        sp.variation_series
            .sort_by(|a, b| a.partial_cmp(b).unwrap());
        sp.average = sp.variation_series.iter().sum::<f64>() / sp.variation_series.len() as f64;
        sp.dispersion = sp
            .variation_series
            .iter()
            .map(|x| (x - sp.average).powf(2.0))
            .sum::<f64>()
            / sp.variation_series.len() as f64;
        sp.stddev = sp.dispersion.sqrt();
        sp.corrected_dispersion = sp.dispersion * sp.variation_series.len() as f64
            / (sp.variation_series.len() - 1) as f64;
        sp.corrected_stddev = sp.corrected_dispersion.sqrt();
        sp
    }

    fn plot_frequency_range(&self, path: &str) -> Result<(), Box<dyn std::error::Error>> {
        print!("Plotting frequency range to {}... ", path);
        std::io::stdout().flush().unwrap();
        let root = BitMapBackend::new(path, (1280, 720)).into_drawing_area();
        root.fill(&WHITE)?;
        let min = *self
            .variation_series
            .iter()
            .min_by(|a, b| a.partial_cmp(b).unwrap())
            .unwrap();
        let max = *self
            .variation_series
            .iter()
            .max_by(|a, b| a.partial_cmp(b).unwrap())
            .unwrap();
        let mut repetitions = HashMap::<HashedDouble, u64>::new();
        for val in self.variation_series.iter() {
            let entry = repetitions.entry(HashedDouble(*val)).or_insert(0);
            *entry += 1;
        }
        let upper = *repetitions
            .iter()
            .max_by(|a, b| a.1.partial_cmp(b.1).unwrap())
            .unwrap()
            .1
            + 1;
        let mut chart = ChartBuilder::on(&root)
            .caption("Полигон частот", ("sans-serif", 50).into_font())
            .margin(10)
            .x_label_area_size(30)
            .y_label_area_size(30)
            .build_ranged(min..max, 0f64..(upper as f64))?;
        chart.configure_mesh().draw()?;
        chart.draw_series(LineSeries::new(
            repetitions
                .iter()
                .map(|(a, b)| (a.0, *b as f64))
                .sorted_by(|(a, _), (b, _)| a.partial_cmp(b).unwrap()),
            &BLUE,
        ))?;
        chart.configure_series_labels().draw()?;
        println!("done!");
        Ok(())
    }

    fn plot_histogram(&self, path: &str) -> Result<(), Box<dyn std::error::Error>> {
        print!("Plotting histogram to {}... ", path);
        std::io::stdout().flush().unwrap();
        let root = BitMapBackend::new(path, (1280, 720)).into_drawing_area();
        root.fill(&WHITE)?;
        let rounded: Vec<u32> = self
            .variation_series
            .iter()
            .map(|x| x.floor() as u32)
            .collect();
        let min = *rounded.first().unwrap() - 2;
        let max = *rounded.last().unwrap() + 2;
        let mut repetitions = HashMap::<u32, u32>::new();
        for val in rounded.iter() {
            let entry = repetitions.entry(*val).or_insert(0);
            *entry += 1;
        }
        let upper = *repetitions
            .iter()
            .max_by(|(_, a), (_, b)| a.partial_cmp(b).unwrap())
            .unwrap()
            .1 as f32
            * 1.1;
        let mut chart = ChartBuilder::on(&root)
            .x_label_area_size(35)
            .y_label_area_size(40)
            .margin(5)
            .caption("Гистограмма", ("sans-serif", 50.0).into_font())
            .build_ranged(min..max, 0f32..upper)?;
        chart
            .configure_mesh()
            .disable_x_mesh()
            .disable_y_mesh()
            .line_style_1(&WHITE.mix(0.3))
            .x_label_offset(30)
            .axis_desc_style(("sans-serif", 15).into_font())
            .draw()?;
        chart.draw_series(
            Histogram::vertical(&chart)
                .style(BLUE.mix(0.6).filled())
                .margin(0)
                .data(rounded.iter().map(|x: &u32| (*x, 1f32))),
        )?;
        println!("done!");
        Ok(())
    }
}

impl fmt::Display for StatisticalPopulation {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        writeln!(f, "Всего элементов: {}", self.statistical_population.len())?;
        writeln!(
            f,
            "Генеральная совокупность: {:?}",
            self.statistical_population
        )?;
        writeln!(f, "Вариационный ряд: {:?}", self.variation_series)?;
        writeln!(f, "Математическое ожидание: {:.5}", self.average)?;
        writeln!(f, "Дисперсия: {:.5}", self.dispersion)?;
        writeln!(f, "Стандартное отклонение: {:.5}", self.stddev)?;
        writeln!(
            f,
            "Дисперсия исправленная: {:.5}",
            self.corrected_dispersion
        )?;
        write!(
            f,
            "Стандартное отклонение исправленное: {:.5}",
            self.corrected_stddev
        )
    }
}

fn print_help(program_name: &str, opts: Options) -> ! {
    let brief = format!("Usage: {} [options] input.csv", program_name);
    print!("{}", opts.usage(&brief));
    process::exit(0);
}

fn read_input_file(file: &str) -> std::io::Result<Vec<f64>> {
    let mut measures = vec![];
    let file = File::open(file)?;
    let mut reader = csv::ReaderBuilder::new()
        .has_headers(true)
        .from_reader(file);
    for i in reader.records() {
        let record = i?;
        let power: f64 = record[1].parse().unwrap();
        measures.push(power);
    }
    Ok(measures)
}

fn sample(input: &[f64], start: usize, n: usize) -> Vec<f64> {
    input
        .iter()
        .skip(start - 1)
        .enumerate()
        .filter(|(i, _)| i % n == n - 1)
        .map(|(_, v)| *v)
        .collect()
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = env::args().collect();
    let mut opts = Options::new();
    opts.optflag("h", "help", "print this message");
    opts.optopt("d", "output-directory", "Graph output folder", "DIR");
    let matches = opts.parse(&args[1..]).unwrap();
    if matches.opt_present("h") {
        print_help(&args[0], opts);
    }
    if matches.opt_present("d") {
        let output_directory = matches.opt_str("d").unwrap();
        if env::set_current_dir(&output_directory).is_err() {
            fs::create_dir_all(&output_directory).unwrap();
            env::set_current_dir(&output_directory).unwrap();
        }
    }
    if matches.free.is_empty() {
        panic!("No input file specified");
    }

    let measures = read_input_file(&matches.free[0]).unwrap();
    let general = StatisticalPopulation::new(&measures);
    let each_second = StatisticalPopulation::new(&sample(&measures, 1, 2));
    let each_fifth = StatisticalPopulation::new(&sample(&measures, 1, 5));
    let sample = StatisticalPopulation::new(&sample(&measures, 2, 5));
    println!("{}", general);
    println!("\nВыборка [каждый второй]:\n{}", each_second);
    println!("\nВыборка [каждый пятый]:\n{}", each_fifth);
    println!("\nВыборка [аудиторная часть]:\n{}", sample);
    general.plot_frequency_range("general_frequency_range.png")?;
    general.plot_histogram("general_histogram.png")?;
    each_second.plot_frequency_range("each_second_frequency_range.png")?;
    each_second.plot_histogram("each_second_histogram.png")?;
    each_fifth.plot_frequency_range("each_fifth_frequency_range.png")?;
    each_fifth.plot_histogram("each_fifth_histogram.png")?;
    sample.plot_frequency_range("sample_frequency_range.png")?;
    sample.plot_histogram("sample_histogram.png")?;
    Ok(())
}
