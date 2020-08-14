/*
 * Part of epicinium_lib
 * developed by A Bunch of Hacks.
 *
 * Copyright (c) 2018-2020 A Bunch of Hacks
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
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
