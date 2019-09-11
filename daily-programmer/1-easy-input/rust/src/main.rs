use std::io;

fn main() {

    print!("Input name > ");
    let mut name = String::new();
    io::stdin().read_line(&mut name).unwrap();

    print!("Input years > ");
    let mut years = String::new();
    io::stdin().read_line(&mut years).unwrap();

    print!("Input username > ");
    let mut username = String::new();
    io::stdin().read_line(&mut username).unwrap();

    println!("Your name is {0}, you are {1} years old, your username is {2}", name, years, username);
	
}
