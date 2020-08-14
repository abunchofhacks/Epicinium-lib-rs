/**/

use serde_derive::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Metadata
{
	pub playercount: i32,

	#[serde(rename = "pool")]
	pub pool_type: PoolType,

	#[serde(rename = "ruleset", default)]
	pub ruleset_name: Option<String>,

	#[serde(flatten)]
	other: std::collections::HashMap<String, serde_json::Value>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
#[serde(rename_all = "snake_case")]
pub enum PoolType
{
	None,
	Multiplayer,
	Custom,
	Diorama,
}
