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

use crate::logic::ai;
use crate::logic::map;
use crate::logic::player::PlayerColor;

use serde_derive::{Deserialize, Serialize};

// These are only the fields that libepicinium is interested in.
#[derive(Debug, Clone, Serialize)]
pub struct Metadata
{
	#[serde(rename = "map")]
	pub map_name: String,

	#[serde(rename = "online")]
	pub is_online: bool,

	#[serde(rename = "planningtime")]
	pub planning_time_in_seconds_or_zero: u32,

	pub players: Vec<PlayerMetadata>,
	pub watchers: Vec<WatcherMetadata>,
	pub bots: Vec<BotMetadata>,

	#[serde(flatten)]
	pub map_metadata: map::Metadata,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct PlayerMetadata
{
	#[serde(rename = "player")]
	pub color: PlayerColor,

	pub username: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct WatcherMetadata
{
	pub username: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct BotMetadata
{
	#[serde(rename = "player")]
	pub color: PlayerColor,

	#[serde(flatten)]
	pub ai_metadata: ai::Metadata,
}
