/**/

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
