# Rust library bindings for Epicinium

Rust bindings for libepicinium, a library containing the core functionality of the strategy game [Epicinium](https://epicinium.nl).
This library implements Epicinium's game logic to load maps and calculate subsequent game states.

The rest of Epicinium will be open-sourced in the near future.
It will also be coming soon to [Steam](https://epicinium.nl/steam).

Epicinium is being developed by [A Bunch of Hacks](https://abunchofhacks.coop),
a worker cooperative for video game and software development from the Netherlands.
Contact us at [info@epicinium.nl](mailto:info@epicinium.nl).

## Contents

*  `src/` defines idiomatic Rust bindings for the C foreign function interface of libepicinium
*  `epicinium/src/build/libepicinium.cpp` is the C++ implementation of libepicinium
*  `epicinium/src/logic` contains C++ source files for Epicinium's game logic
*  `epicinium/src/ai` contains C++ source files for Epicinium's artificial intelligence
*  `epicinium/src/common` contains C++ source files for various utilities used in Epicinium
*  `epicinium/libs/jsoncpp` contains C++ source files for [JsonCpp](https://github.com/open-source-parsers/jsoncpp), a dependency of Epicinium
*  `epicinium/libs/plog` contains C++ source files for [Plog](https://github.com/SergiusTheBest/plog), a dependency of Epicinium
*  `epicinium/Makefile` is a copy of the full Makefile used to compile Epicinium
*  `epicinium/.config.make` defines additional flags passed to the Makefile
*  the `build.rs` build script calls the Makefile to compile a static library of libepicinium from its C++ source, which is then linked by Cargo with the Rust bindings

## External dependencies

*  [GNU Make](https://www.gnu.org/software/make/)
*  [GnuWin32](http://gnuwin32.sourceforge.net/) (on Windows)

## License

This library was created by [A Bunch of Hacks](https://abunchofhacks.coop).
It is made available to you under the AGPL-3.0 License,
as specified in `LICENSE.txt`.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Affero General Public License (AGPL) as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.

## Related repositories

*  [Epicinium documentation](https://github.com/abunchofhacks/epicinium-documentation), which includes a wiki and a tutorial for Epicinium
*  [Epicinium-NeuralNewt](https://github.com/abunchofhacks/Epicinium-NeuralNewt), a libtorch framework for training (partially) convolutional neural networks to play Epicinium via NeuralNewt, a parameterized decision tree AI, with evolutionary training techniques
*  [Epicinium-NeuralNewt-automatonlib](https://github.com/abunchofhacks/Epicinium-NeuralNewt-automatonlib), a precompiled C++ library with Epicinium logic for Epicinium-NeuralNewt
