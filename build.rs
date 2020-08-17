fn main()
{
	let out_dir = std::env::var("OUT_DIR").unwrap();

	let guard_filename = format!("{}/.guard", out_dir);
	std::fs::File::create(guard_filename).expect("failed to create guard");

	std::process::Command::new("make")
		.arg("-f")
		.arg("build.make")
		.status()
		.expect("failed to call make");

	let ep_dir = std::path::Path::new("epicinium");
	print_rerun_if_changed_recursively(ep_dir).expect("failed to recurse");

	println!("cargo:rustc-flags=-l dylib=stdc++");
	println!("cargo:rustc-link-search=native={}/epicinium/bin/", out_dir);
	println!("cargo:rustc-link-lib=static=epicinium");
}

fn print_rerun_if_changed_recursively(
	dir: &std::path::Path,
) -> std::io::Result<()>
{
	for entry in std::fs::read_dir(dir)?
	{
		let entry = entry?;
		let path = entry.path();
		if path.is_dir()
		{
			print_rerun_if_changed_recursively(&path)?;
		}
		else
		{
			let filename = path.to_str().expect("invalid characters in path");
			println!("cargo:rerun-if-changed={}", filename);
		}
	}
	Ok(())
}
