/**/

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
