/**/

pub mod log;
pub mod logic;

mod binding;
pub mod error;

pub use crate::binding::*;

#[cfg(test)]
mod tests
{
	#[test]
	fn it_works()
	{
		assert_eq!(2 + 2, 4);
	}
}
