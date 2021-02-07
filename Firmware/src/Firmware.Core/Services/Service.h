#pragma once

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			class Service
			{
			public:
				virtual ~Service() = default;

				virtual bool Initialize() = 0;
				virtual void Update() = 0;

				virtual void Stop() = 0;
			};
		}
	}
}
