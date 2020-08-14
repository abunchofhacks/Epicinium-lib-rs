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

use serde_json;

#[derive(Debug)]
pub enum InterfaceError
{
	AllocationFailed,
	ArgumentNulError(std::ffi::NulError),
	Json(serde_json::Error),
	Utf8(std::str::Utf8Error),
}

impl From<std::ffi::NulError> for InterfaceError
{
	fn from(error: std::ffi::NulError) -> Self
	{
		InterfaceError::ArgumentNulError(error)
	}
}

impl From<serde_json::Error> for InterfaceError
{
	fn from(error: serde_json::Error) -> Self
	{
		InterfaceError::Json(error)
	}
}

impl From<std::str::Utf8Error> for InterfaceError
{
	fn from(error: std::str::Utf8Error) -> Self
	{
		InterfaceError::Utf8(error)
	}
}

impl std::fmt::Display for InterfaceError
{
	fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result
	{
		match self
		{
			InterfaceError::AllocationFailed => write!(f, "allocation failed"),
			InterfaceError::ArgumentNulError(error) => error.fmt(f),
			InterfaceError::Json(error) => error.fmt(f),
			InterfaceError::Utf8(error) => error.fmt(f),
		}
	}
}

impl std::error::Error for InterfaceError {}

#[derive(Debug)]
pub enum InitializationError
{
	Failed,
}

impl std::fmt::Display for InitializationError
{
	fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result
	{
		match self
		{
			InitializationError::Failed => write!(f, "initialization failed"),
		}
	}
}

impl std::error::Error for InitializationError {}
