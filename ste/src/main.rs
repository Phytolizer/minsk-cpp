use std::fs::File;
use std::path::PathBuf;
use std::str::FromStr;

use lalrpop_util::lalrpop_mod;

mod ast;
lalrpop_mod!(pub ste);

fn main() {
    let matches = clap::App::new("ste")
        .version("0.1.0")
        .author("Kyle Coffey")
        .about("Strongly Typed Enum generator")
        .arg(
            clap::Arg::with_name("file")
                .short("f")
                .long("file")
                .value_name("FILE")
                .help("Sets the file to convert")
                .takes_value(true)
                .required(true),
        )
        .arg(
            clap::Arg::with_name("output")
                .short("o")
                .long("output")
                .value_name("FILE")
                .help("Sets the output file")
                .takes_value(true),
        )
        .get_matches();

    let file = PathBuf::from_str(matches.value_of("file").unwrap()).unwrap();
    let output = match matches.value_of("output") {
        Some(o) => PathBuf::from_str(o).unwrap(),
        None => {
            let mut path = file.clone();
            path.set_extension("hpp");
            path
        }
    };

    let result = ste::StronglyTypedEnumParser::new()
        .parse(&std::fs::read_to_string(file).unwrap())
        .unwrap();
    dbg!(&output);
    emit_code(result, output);
}

fn emit_code(result: ast::StronglyTypedEnum, output: PathBuf) {
    use std::io::Write;

    let mut f = File::create(output).unwrap();
    writeln!(f, "#pragma once").unwrap();
    writeln!(f, "#include <cstdint>").unwrap();
    writeln!(f, "#include <compare>").unwrap();
    writeln!(f, "// NOLINTNEXTLINE(readability-identifier-naming)").unwrap();
    writeln!(
        f,
        "namespace {} {{",
        result
            .namespace
            .iter()
            .chain(std::iter::once(&result.name))
            .cloned()
            .collect::<Vec<_>>()
            .join("::"),
    )
    .unwrap();
    writeln!(f, "class Type {{").unwrap();
    writeln!(f, "std::uint64_t value_;").unwrap();
    writeln!(f, "public:").unwrap();
    writeln!(
        f,
        "explicit constexpr Type(std::uint64_t value) : value_(value) {{}}",
    )
    .unwrap();
    writeln!(
        f,
        "constexpr std::uint64_t Value() const {{ return value_; }}"
    )
    .unwrap();
    writeln!(
        f,
        "constexpr std::strong_ordering operator<=>(const Type& other) const {{ return value_ <=> other.value_; }}"
    )
    .unwrap();
    writeln!(
        f,
        "constexpr bool operator==(const Type& other) const {{ return value_ == other.value_; }}"
    )
    .unwrap();
    writeln!(f, "}};").unwrap();
    for (i, variant) in result.variants.iter().enumerate() {
        writeln!(f, "constexpr Type {}{{{}}};", variant, i).unwrap();
    }
    writeln!(f, "}}").unwrap();
}
