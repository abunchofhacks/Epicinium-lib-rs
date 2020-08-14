/**/

use serde_derive::{Deserialize, Serialize};

#[derive(
	Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Serialize, Deserialize,
)]
#[serde(rename_all = "lowercase")]
#[repr(u8)]
pub enum PlayerColor
{
	/* No player. */
	None = 0,
	/* Player colors. */
	Red,
	Blue,
	Yellow,
	Teal,
	Black,
	Pink,
	Indigo,
	Purple,
	/* Non-player vision types used by the Automaton. */
	Blind,
	Observer,
	// Non-player vision type used by the Board internally to keep track of its
	// owner's vision.
	SelfInternalDoNotUse,
}

pub const PLAYER_MAX: usize = 8;

impl Default for PlayerColor
{
	fn default() -> PlayerColor
	{
		PlayerColor::None
	}
}

pub fn color_pool() -> Vec<PlayerColor>
{
	vec![
		PlayerColor::Red,
		PlayerColor::Blue,
		PlayerColor::Yellow,
		PlayerColor::Teal,
		PlayerColor::Black,
		PlayerColor::Pink,
		PlayerColor::Indigo,
		PlayerColor::Purple,
	]
}
