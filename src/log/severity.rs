/**/

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
