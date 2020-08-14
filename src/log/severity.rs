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

#[allow(dead_code)]
#[repr(u8)]
pub enum Severity
{
	None,
	Fatal,
	Error,
	Warning,
	Info,
	Debug,
	Verbose,
}
