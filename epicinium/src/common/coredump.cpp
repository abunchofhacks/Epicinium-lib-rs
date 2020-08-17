#include "coredump.hpp"
#include "source.hpp"

#if COREDUMP_ENABLED
#include <sys/resource.h>
#endif


void CoreDump::enable()
{
#if COREDUMP_ENABLED
	{
		struct rlimit core_limit;
		core_limit.rlim_cur = RLIM_INFINITY;
		core_limit.rlim_max = RLIM_INFINITY;

		if (setrlimit(RLIMIT_CORE, &core_limit) < 0)
		{
			// Plog has not yet been installed at this point.
			fprintf(stderr, "setrlimit: %s\n"
				"Warning: core dumps may be truncated or non-existant\n",
				strerror(errno));
		}
	}
#endif
}
