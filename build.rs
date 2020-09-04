/*
 * Part of epicinium_lib
 * developed by A Bunch of Hacks.
 *
 * Copyright (c) 2018-2020 A Bunch of Hacks
 *
 * epicinium_lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * epicinium_lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * [authors:]
 * Sander in 't Veld (sander@abunchofhacks.coop)
 */

use std::io::Write;

fn main()
{
	let out_dir = std::env::var("OUT_DIR").unwrap();

	std::process::Command::new("cp")
		.arg("--recursive")
		.arg("--update")
		.arg("--preserve")
		.arg("./epicinium")
		.arg(format!("{}/", out_dir))
		.status()
		.expect("failed to copy files");

	let variant = if cfg!(feature = "version-is-dev")
	{
		"dev"
	}
	else if cfg!(feature = "candidate")
	{
		"candidate"
	}
	else if cfg!(debug_assertions)
	{
		"dev"
	}
	else
	{
		"release"
	};
	let variant_filename = format!("{}/epicinium/bin/variant", out_dir);
	let mut file = std::fs::File::create(variant_filename)
		.expect("failed to create variant");
	write!(file, "{}\n", variant).expect("failed to write variant");

	let working_dir = format!("{}/epicinium", out_dir);
	let working_path = std::path::Path::new(&working_dir);
	std::process::Command::new("make")
		.arg("libepicinium")
		.arg("--jobs")
		.current_dir(working_path)
		.status()
		.expect("failed to call make");

	let ep_path = std::path::Path::new("./epicinium");
	print_rerun_if_changed_recursively(ep_path).expect("failed to recurse");

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
