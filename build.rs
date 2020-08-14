fn main()
{
	println!("cargo:rerun-if-changed=lib/libepicinium.a");
	println!("cargo:rustc-flags=-l dylib=stdc++");
	println!("cargo:rustc-link-search=native=lib/");
	println!("cargo:rustc-link-lib=static=epicinium");
}
